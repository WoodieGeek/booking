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

struct TableOrders : public Table {
    Column<int> ID;
    Column<int> RestaurantsID;
    Column<int> UserID;
    Column<int> StartTime;
    Column<int> FinishTime;
    TableOrders() {
        Name_ = "Orders";
        ID.Name = Name_ + ".ID";
        RestaurantsID.Name = Name_ + ".RestaurantsID";
        UserID.Name = Name_ + ".UserID";
        StartTime.Name = Name_ + ".StartTime";
        FinishTime.Name = Name_ + ".FinishTime";
    }
};

struct TableTables : public Table {
    Column<int> ID;
    Column<int> RestaurantID;
    Column<int> H;
    Column<int> W;
    Column<int> X;
    Column<int> Y;
    Column<int> Type;
    TableTables() {
        Name_ = "Tables";
        ID.Name = Name_ + ".ID";
        RestaurantID.Name = Name_ + ".RestaurantID";
        H.Name = Name_ + ".H";
        W.Name = Name_ + ".W";
        X.Name = Name_ + ".X";
        Y.Name = Name_ + ".Y";
        Type.Name = Name_ + ".Type";
    }
};

struct TableTableType : public Table {
    Column<int> ID;
    Column<QString> Name;
    TableTableType() {
        Name_ = "TableType";
        ID.Name = Name_ + ".ID";
        Name.Name = Name_ + ".Name";
    }
};

struct TableBookedTables : public Table {
    Column<int> TableID;
    Column<int> OrderID;
    TableBookedTables() {
        Name_= "BookedTables";
        TableID.Name = Name_ + ".TableID";
        OrderID.Name = Name_ + ".OrderID";
    }
};

#endif // SQLTABLE_H
