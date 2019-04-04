import subprocess
import json


class Cluster:
    def read_config(self):
        file_config = open('config', 'r')
        str_config = ""
        for line in file_config:
            str_config += line
        config = json.loads(str_config)
        self.PORT = config["PORT"]
        self.IP = config["IP"]
        self.NameDb = config["DB"]
        file_config.close()

    def __init__(self):
        self.process = subprocess.Popen("./booking")
        self.read_config()

    def __del__(self):
        self.process.terminate()


class Handler:
    def __init__(self):
        self.cluser = Cluster()
        self.url = 'http://' + self.cluser.IP + ':' + str(self.cluser.PORT)


if __name__ == "__main__":
    c = Cluster()
