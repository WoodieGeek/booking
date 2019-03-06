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
        ID = {"ID", Name_};
        Name = {"Name", Name_};
        Type = {"Type", Name_};

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
        ID = {"ID", Name_};
        Name = {"Name", Name_};
        Description = {"Description", Name_};
        Address = {"Address", Name_};
        Thumbnail = {"Thumbnail", Name_};
    }
};

struct TableOrders : public Table {
    Column<int> ID;
    Column<int> RestaurantID;
    Column<int> UserID;
    Column<int> StartTime;
    Column<int> FinishTime;
    TableOrders() {
        Name_ = "Orders";
        ID = {"ID", Name_};
        RestaurantID = {"RestaurantID", Name_};
        UserID = {"UserID", Name_};
        StartTime = {"StartTime",  Name_};
        FinishTime = {"FinishTime",  Name_};
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
        ID = {"ID", Name_};
        RestaurantID = {"RestaurantID", Name_};
        H = {"H", Name_};
        W = {"W", Name_};
        X = {"X", Name_};
        Y = {"Y", Name_};
        Type = {"Type", Name_};
    }
};

struct TableTableType : public Table {
    Column<int> ID;
    Column<QString> Name;
    TableTableType() {
        Name_ = "TableType";
        ID = {"ID", Name_};
        Name = {"Name", Name_};
    }
};

struct TableBookedTables : public Table {
    Column<int> TableID;
    Column<int> OrderID;
    TableBookedTables() {
        Name_ = "BookedTables";
        TableID = {"TableID", Name_};
        OrderID = {"OrderID", Name_};
    }
};

#endif // SQLTABLE_H
