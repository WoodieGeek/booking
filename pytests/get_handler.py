import requests
import cluster


class GetHandler(cluster.Handler):

    def restaurants(self):
        response = requests.get(self.url + "/restaurants.json")
        return response.text


if __name__ == '__main__':
    handler = GetHandler()
    res = (handler.restaurants())
    print(res)
