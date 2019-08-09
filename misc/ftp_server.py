import logging
from pyftpdlib.authorizers import DummyAuthorizer
from pyftpdlib.handlers import FTPHandler
from pyftpdlib.servers import FTPServer

authorizer = DummyAuthorizer()
authorizer.add_user("user", "12345", ".")

handler = FTPHandler
handler.authorizer = authorizer
logging.basicConfig(level=logging.DEBUG)

server = FTPServer(("127.0.0.1", 2121), handler)
server.serve_forever()
