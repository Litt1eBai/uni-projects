#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# =================================================
# Created By: Jens Liu
# Created At: 15.01.2022
# Email: jens.l29@outlook.com
# =================================================
"""
    this file is created for project: final
"""
# =================================================
import socket

# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class ServerRequestUtil(object):

    @classmethod
    def get_udp_connection(cls):
        udp_sock = socket.socket(socket.AF_INET,
                                 socket.SOCK_DGRAM,
                                 socket.IPPROTO_UDP)
        udp_sock.setsockopt(socket.SOL_SOCKET,
                            socket.SO_REUSEADDR,
                            1)
        udp_sock.settimeout(2)
        return udp_sock

    @classmethod
    def get_tcp_connection(cls):
        tcp_sock = socket.socket(socket.AF_INET,
                                 socket.SOCK_STREAM,
                                 socket.IPPROTO_TCP)
        tcp_sock.setsockopt(socket.SOL_SOCKET,
                            socket.SO_REUSEADDR,
                            1)
        tcp_sock.settimeout(2)
        return tcp_sock


    @classmethod
    def crc16(cls, x):
        """
        :param x: bytes:
        :return: return 2-byte values:
        """
        if not isinstance(x, bytes):
            raise ValueError('Parameter must be a bytes type')
        b = 0xA001
        a = 0xFFFF
        for byte in x:
            a = a ^ byte
            for _ in range(8):
                last = a % 2
                a = a >> 1
                if last == 1:
                    a = a ^ b
        aa = '0' * (6 - len(hex(a))) + hex(a)[2:]
        ll, hh = int(aa[:2], 16), int(aa[2:], 16)
        rtn = '%x' % (hh * 256 + ll & 0xffff)
        while len(rtn) < 4:
            rtn = '0' + rtn
        rtn = cls.hextobytes(rtn)
        return rtn

    @classmethod
    def hextobytes(cls, x):
        if not isinstance(x, str):
            x = str(x, 'ascii')
        return bytes.fromhex(x)


if __name__ == '__main__':
    pass
