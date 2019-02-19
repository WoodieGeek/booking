CREATE TABLE UserType ( 
ID integer primary key ,
Name varchar(30) NOT NULL
);

CREATE TABLE Users (
ID integer primary key,
Name varchar(100) NOT NULL,
Type integer NOT NULL,
foreign key (Type) references UserType(ID)
);
CREATE TABLE TableType ( 
ID integer primary key ,
Name varchar(30) NOT NULL
);
CREATE TABLE Restaurants ( 
ID integer primary key ,
Name varchar(30) NOT NULL,
Description varchar(200), 
Address varchar(100),
Thumbnail varchar(30)
);
CREATE TABLE Tables ( 
ID integer primary key,
RestaurantID integer NOT NULL,
Type integer  NOT NULL,
H integer NOT NULL,
W integer NOT NULL,
X integer NOT NULL,
Y integer NOT NULL,
foreign key (RestaurantID) references Restaurants(ID),
foreign key (Type) references TableType(ID)
);
CREATE TABLE Orders (
ID integer primary key,
RestaurantID integer NOT NULL,
UserID integer NOT NULL,
StartTime integer NOT NULL,
FinishTime integer NOT NULL,
foreign key (RestaurantID) references Restaurants(ID),
foreign key (UserID) references Users(ID)
);
CREATE TABLE BookedTables (
TableID integer NOT NULL,
OrderID integer NOT NULL,
foreign key (TableID) references Tables(ID),
foreign key (OrderID) references Orders(ID)
);

