# -*- coding: utf-8 -*-
import os
import json
import unittest
import sys
sys.path.insert(0, '../../pytests')
from get_handler import GetHandler

RecordRestaurants = [
    {
        "Address": "msc",
        "Description": "mmm",
        "ID": "1",
        "Name": "Meatless",
        "Thumbmail": "/image"
    },
    {
        "Address": "г. Уфа Проспект Октября, 115",
        "Description": "Уютный семейный ресторан",
        "ID": "2",
        "Name": "Своя компания",
        "Thumbmail": "/svoya-kompaniya"
    }
]

RecordOrder = [
    {
        "FinishTime": "1550847967",
        "ID": "1",
        "Restaurant": {
            "Address": "msc",
            "Description": "mmm",
            "ID": "1",
            "Name": "Meatless",
            "Thumbnail": "/image"
        },
        "StartTime": "1550840767",
        "Tables": [
            {
                "H": "10",
                "ID": "1",
                "Type": "rectangle",
                "W": "10",
                "X": "50",
                "Y": "50"
            },
            {
                "H": "20",
                "ID": "2",
                "Type": "rectangle",
                "W": "20",
                "X": "100",
                "Y": "100"
            }
        ]
    }
]

RecordTables = [
    {
        "H": "10",
        "ID": "1",
        "Orders": ["1550840767", "1550847967"],
        "Type": "1",
        "W": "10",
        "X": "50",
        "Y": "50"
    },
    {
        "H": "20",
        "ID": "2",
        "Orders": ["1550840767", "1550847967"],
        "Type": "1",
        "W": "20",
        "X": "100",
        "Y": "100"
    }
]


handler = None


class Test(unittest.TestCase):

    def test_get_restaurants(self):
        responce = json.loads(handler.restaurants())
        self.assertSequenceEqual(RecordRestaurants, responce)

    def test_orders_by_id(self):
        responce = json.loads(handler.orders(1))
        self.assertSequenceEqual(RecordOrder, responce)

    def test_tables_by_id_date(self):
        responce = json.loads(handler.tables(1, 1550847967))
        self.assertSequenceEqual(RecordTables, responce)


if __name__ == '__main__':
    os.chdir("../../pytests")
    handler = GetHandler()
    unittest.main()
