#!/usr/bin/env python
# -*- coding: utf-8 -*-

import socketserver
from datetime import datetime
import pickle


class MyTCPHandler(socketserver.BaseRequestHandler):
    '''
    The RequestHandler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    '''

    def handle(self):
        # self.request is the TCP socket connected to the client
        self.data = self.request.recv(1024).strip()
        print('{} wrote:'.format(self.client_address[0]))
        print(self.data)

        # save the packet
        with open('packet-{}-{}'.format(self.client_address[0], datetime.now()), 'wb') as f:
            pickle.dump(self.data, f)


if __name__ == '__main__':
    HOST, PORT = '127.0.0.1', 9999

    # Create the server, binding to HOST:PORT
    server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)

    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()
