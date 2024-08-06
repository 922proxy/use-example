import urllib
import socks
import http.client
from urllib.error import URLError
import ssl
from urllib.request import build_opener, HTTPHandler, HTTPSHandler


def merge_dict(a, b):
    d = a.copy()
    d.update(b)
    return d


class SocksiPyConnection(http.client.HTTPConnection):
    def __init__(self, proxytype, proxyaddr, proxyport=None, rdns=True, username=None, password=None, *args, **kwargs):
        self.proxyargs = (proxytype, proxyaddr, proxyport, rdns, username, password)
        http.client.HTTPConnection.__init__(self, *args, **kwargs)

    def connect(self):
        self.sock = socks.socksocket()
        self.sock.setproxy(*self.proxyargs)
        if type(self.timeout) in (int, float):
            self.sock.settimeout(self.timeout)
        self.sock.connect((self.host, self.port))


class SocksiPyConnectionS(http.client.HTTPSConnection):
    def __init__(self, proxytype, proxyaddr, proxyport=None, rdns=True, username=None, password=None, *args, **kwargs):
        self.proxyargs = (proxytype, proxyaddr, proxyport, rdns, username, password)
        http.client.HTTPSConnection.__init__(self, *args, **kwargs)

    def connect(self):
        sock = socks.socksocket()
        sock.setproxy(*self.proxyargs)
        if type(self.timeout) in (int, float):
            sock.settimeout(self.timeout)
        sock.connect((self.host, self.port))
        self.sock = ssl.wrap_socket(sock, self.key_file, self.cert_file)


class SocksiPyHandler(HTTPHandler, HTTPSHandler):
    def __init__(self, *args, **kwargs):
        self.args = args
        self.kw = kwargs
        HTTPHandler.__init__(self)

    def http_open(self, req):
        def build(host, port=None, timeout=0, **kwargs):
            kw = merge_dict(self.kw, kwargs)
            conn = SocksiPyConnection(*self.args, host=host, port=port, timeout=timeout, **kw)
            return conn

        return self.do_open(build, req)

    def https_open(self, req):
        def build(host, port=None, timeout=0, **kwargs):
            kw = merge_dict(self.kw, kwargs)
            conn = SocksiPyConnectionS(*self.args, host=host, port=port, timeout=timeout, **kw)
            return conn

        return self.do_open(build, req)


username = ""
password = ""
ip = "ip.proxys5.net"
port = 6500
proxy = "socks5://{username}:{password}@{ip}:{port}".format(username=username, password=password, ip=ip, port=port)
# socks.set_default_proxy(socks.SOCKS5, ip, port,username=username,password=password)
# socket.socket = socks.socksocket

url = 'https://www.google.com/'

try:
    req = urllib.request.Request(url=url, headers={'User-Agent':'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.88 Safari/537.36'})
    opener = build_opener(SocksiPyHandler(socks.SOCKS5, ip, port, username=username, password=password))
    response = opener.open(req)
    # response = urllib.request.urlopen(req)
    # response = request.urlopen(url)
    print(response.read().decode('utf-8'))
except URLError as e:
    print(e)
