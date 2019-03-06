#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <memory>
#include <QString>
#include <QLocale>
#include <QTextStream>
#include <QDebug>
#include "filter.h"

static void add(int x, QString& s) {
    s += QString::number(x) + ", ";
}

static void add(const QString& p, QString& s) {
    s += "'" + p + "', ";
}

template <typename T>
struct Column {
    QString Name;
    QString Table;
    T Value;
    Filter operator == (const T& rhs) {
        QString result = this->Name + " = ";
        add(rhs, result);
        result.resize(result.size() - 2);
        return {result};
    }
    template <typename V>
    Filter operator == (const Column<V>& rhs) {
        return {this->Name + " = " + rhs.Name};
    }

    Filter operator <= (const T& rhs) {
        return {this->Name + " <= " + QString::number(rhs)};
    }

    Filter operator >= (const T& rhs) {
        return {this->Name + " >= " + QString::number(rhs)};
    }

    Column<T> operator = (const T& rhs) {
        Value = rhs;
        return *this;
    }
};

struct Table {
    QString Name_;
};

struct Operation {
public:
    Operation() = default;

    template<typename ...Cs>
    Operation(bool addTable, Operation* parent = nullptr, Cs... columns)
        : Parent_(parent) {
        Parse(addTable, columns...);
    }

    Operation(Operation* parent)
        : Parent_(parent) {
    }

    QString Serialization() const {
        return Parent_ ? Parent_->Serialization() + PartQuery_ : PartQuery_;
    }

    template<typename T, typename ...Cs>
    void Parse(bool addTable, const Column<T>& column, Cs ...columns) {
        Names_ += (addTable? column.Table + "." : "") + column.Name + ", ";
        QLocale local;
        add(column.Value, Values_);
        Parse(addTable, columns...);
    }

    void Parse(bool) {
        Names_.resize(Names_.size() - 2);
        Values_.resize(Values_.size() - 2);
    }

    Operation* Parent_;
    QString Names_;
    QString Values_;
    QString PartQuery_;
};




#endif // OPERATIONS_H
