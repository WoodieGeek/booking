#ifndef SQLTABLE_H
#define SQLTABLE_H
#include <bits/stdc++.h>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QJsonObject>
#include <QDebug>
#include "operations.h"

struct TableUsers : public Table {
    Column<int> ID;
    Column<QString> Name;
    Column<int> Type;
    TableUsers() {
        Name_ = "Users";
        ID.Name = Name_ + ".ID";
        Name.Name = Name_ + ".Name";
        Type.Name = Name_ + ".Type";

    }
};

struct TableRestaurants : public Table {
    Column<int> ID;
    Column<QString> Name;
    Column<QString> Description;
    Column<QString> Address;
    Column<QString> Thumbnail;
    TableRestaurants() {
        Name_ = "Restaurants";
        ID.Name = Name_ + ".ID";
        Name.Name = Name_ + ".Name";
        Description.Name = Name_ + ".Description";
        Address.Name = Name_ + ".Address";
        Thumbnail.Name = Name_ + ".Thumbnail";
    }
};


#endif // SQLTABLE_H
