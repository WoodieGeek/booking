# -*- coding: utf-8 -*-
import requests
import cluster


class GetHandler(cluster.Handler):

    def restaurants(self):
        response = requests.get(self.url + "/restaurants.json")
        response.close()
        return response.text

    def orders(self, ID):
        response = requests.get(self.url + '/orders.json', params={'id': ID})
        return response.text

    def tables(self, ID, date):
        p = {'id': ID, 'date': date}
        response = requests.get(self.url + '/tables.json',  params=p)
        return response.text


if __name__ == '__main__':
    handler = GetHandler()
    res = handler.orders(1)
    print(res)
