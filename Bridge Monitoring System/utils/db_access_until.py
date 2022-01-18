#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# =================================================
# Created By: Jens Liu
# Created At: 16.01.2022
# Email: jens.l29@outlook.com
# =================================================
"""
    this file is created for project: final
"""
# =================================================
import pymysql

# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class DbAccessUtil(object):

    def __init__(self):
        # self.user = 'jens'
        # self.password = '1234'
        # self.host = '192.168.242.128'
        self.user = 'root'
        self.password = 'Jens2002'
        self.host = 'localhost'
        self.database = 'py_final_project_fall2021'
        self.port = 3306

    def get_connection(self) -> pymysql.Connection:
        try:
            conn = pymysql.connect(user=self.user,
                                   password=self.password,
                                   host=self.host,
                                   database=self.database,
                                   port=self.port)
            print("[DEBUG]: connected to database")
            return conn

        except Exception as e:
            print("[DEBUG]: get connection failed")
            return None


if __name__ == '__main__':
    pass
