#!/usr/bin/env python
# -*- coding: utf-8 -*-

import pickle
import socket
import telnetlib


def interactive_socket(sock):
    shell = telnetlib.Telnet()
    shell.sock = sock
    shell.interact()


def replay(packet_filepath, target=('127.0.0.1', 8000)):

    with open(packet_filepath, 'rb') as f:
        data = pickle.load(f)

    sock = socket.socket()
    sock.connect(target)
    sock.sendall(data)

    interactive_socket(sock)


if __name__ == '__main__':
    # packet from "dump_socket_server.py"
    replay('packet-127.0.0.1-2015-12-04 23:34:46.914050', ('127.0.0.1', 9999))
