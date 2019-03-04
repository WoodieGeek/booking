#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <bits/stdc++.h>
#include <QString>
#include <QLocale>
#include <QTextStream>
#include <QDebug>
#include "filter.h"

static void add(int x, QString& s) {
    s += QString::number(x) + ", ";
}

static void add(QString p, QString s) {
    s += "\"" + p + "\", ";
}

template <typename T>
struct Column {
    QString Name;
    T Value;
    Filter operator == (T rhs) {
        QString result = this->Name + " = ";
        add(rhs, result);
        result.resize(result.size() - 2);
        return {result};
    }
};

struct Table {
    QString Name_;
};

struct Operation {
public:
    Operation() = default;

    template<typename ...Cs>
    Operation(Operation* parent = nullptr, Cs... columns)
        : Parent_(parent) {
        Parse(columns...);
    }

    Operation(Operation* parent)
        : Parent_(parent) {
    }

    QString Serialization() const {
        return Parent_ ? Parent_->Serialization() + PartQuery_ : PartQuery_;
    }

    template<typename T, typename ...Cs>
    void Parse(const Column<T>& column, Cs ...columns) {
        Names_ += column.Name + ", ";
        QLocale local;
        add(column.Value, Values_);
        Parse(columns...);
    }

    void Parse() {
        Names_.resize(Names_.size() - 2);
        Values_.resize(Values_.size() - 2);
    }

    Operation* Parent_;
    QString Names_;
    QString Values_;
    QString PartQuery_;
};




#endif // OPERATIONS_H
