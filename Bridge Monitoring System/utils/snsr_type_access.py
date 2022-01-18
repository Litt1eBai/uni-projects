#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# =================================================
# Created By: Jens Liu
# Created At: 18.01.2022
# Email: jens.l29@outlook.com
# =================================================
"""
    this file is created for project: final
"""
# =================================================
from utils.db_access_until import DbAccessUtil
from data.sensor_type import SnsrType

# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class SnsrTypeAccess(object):
    def __init__(self):
        self.__connection = DbAccessUtil().get_connection()

    def get_snsrtypes_with_id(self, id: int) -> SnsrType or None:
        snsrtypes = self.get_snsrtypes_based_on("WHERE snsr_type_id = " + str(id))
        if snsrtypes is not None and len(snsrtypes) > 0:
            return snsrtypes[0]
        return None

    def get_snsrtypes_with_name_like(self, like: str) -> []:
        snsrtypes = self.get_snsrtypes_based_on("WHERE snsr_type_name LIKE" + "%" + like + "%")
        return snsrtypes

    def get_snsrtypes_with_tunl(self, tunl: int) -> []:
        snsrtypes = self.get_snsrtypes_based_on("WHERE snsr_req_tunl = " + str(tunl))
        return snsrtypes

    def get_snsrtypes_with_cp(self, cp: str) -> []:
        snsrtypes = self.get_snsrtypes_based_on("WHERE snsr_req_cp = " + cp)
        return snsrtypes

    def get_snsrtypes_with_port(self, port: int) -> []:
        snsrtypes = self.get_snsrtypes_based_on("WHERE snsr_req_port = " + port)
        return snsrtypes

    def get_snsrtypes_based_on(self, where: str) -> []:
        if self.__connection is None:
            return None
        sql = """
        SELECT snsr_type_id, snsr_type_name, snsr_req_tunl, 
        snsr_req_cp, snsr_req_port, snsr_req_inst_val_regex, snsr_req_assoc_val_regex,
        snsr_inst_val_name, snsr_assoc_val_name 
        FROM sensor_types
        """

        if where.lower().startswith("where"):
            sql += where

        cur = self.__connection.cursor()
        cur.execute(sql)
        self.__connection.rollback()
        row = cur.fetchone()
        snsr_types = []
        while row:
            (type_id, type_name, req_tunl,
             req_cp, req_port, req_inst_val_regex, req_assoc_val_regex,
             inst_val_name, assoc_val_name) = row
            snsr_type = SnsrType.create_covering_old_instance(
                type_id, type_name, req_tunl, req_cp,
                req_port, req_inst_val_regex, req_assoc_val_regex,
                inst_val_name, assoc_val_name
            )
            # try:
            #     snsr_type = SnsrType(type_id, type_name, req_tunl, req_cp,
            #                          req_port, req_inst_val_regex, req_assoc_val_regex,
            #                          inst_val_name, assoc_val_name)
            # except SnsrType.InstanceChangedException as e:
            #     snsr_type = e.old_ins
            snsr_types.append(snsr_type)
        return snsr_types


if __name__ == '__main__':
    pass
