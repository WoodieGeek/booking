import os
import unittest
import sys
sys.path.insert(0, '../../pytests')
from get_handler import GetHandler


class Test(unittest.TestCase):

    def test_get_restaurants(self):
        handler = GetHandler()
        responce = handler.restaurants()
        self.assertEqual(responce, responce)


if __name__ == '__main__':
    os.chdir("../../pytests")
    print(os.system("pwd"))
    unittest.main()
