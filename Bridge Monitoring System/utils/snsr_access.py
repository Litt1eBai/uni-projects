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
from utils.db_access_until import DbAccessUtil
from data.sensor import Sensor
from data.sensor import SensorConnect
from data.sensor_type import SnsrType

# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class SnsrAccess(object):

    def __init__(self):
        self.__connection = DbAccessUtil().get_connection()

    def get_snsr_with_id(self, snsr_id: int) -> Sensor or None:
        snsrs = self.get_snsrs_based_on("WHERE s.snsr_id = " + str(snsr_id))
        if snsrs is not None and len(snsrs) > 0:
            return snsrs[0]
        return None

    def get_snsrconn_with_id(self, snsr_id: int) -> SensorConnect or None:
        snsrconns = self.get_snsrconns_based_on("WHERE s.snsr_id = " + str(snsr_id))
        if snsrconns is not None and len(snsrconns) > 0:
            return snsrconns[0]
        return None

    def get_snsrs_with_typeid(self, type_id: int) -> []:
        return self.get_snsrs_based_on("WHERE s.snsr_type_id = " + str(type_id))

    def get_snsrconns_with_typeid(self, type_id: int) -> []:
        return self.get_snsrconns_based_on("WHERE s.snsr_type_id = " + str(type_id))

    def get_snsrs_with_type(self, type: str) -> []:
        return self.get_snsrs_based_on("WHERE st.snsr_type_name = " + type)

    def get_snsrconns_with_type(self, type: str) -> []:
        return self.get_snsrconns_based_on("WHERE st.snsr_type_name = " + type)

    def get_snsrs_with_name_like(self, like: str) -> []:
        return self.get_snsrs_based_on("WHERE st.snsr_type_name LIKE %" + like + "%")

    def get_snsrconns_with_name_like(self, like: str) -> []:
        return self.get_snsrconns_based_on("WHERE st.snsr_type_name LIKE %" + like + "%")

    def get_snsrs_based_on(self, where: str) -> []:
        if self.__connection is None:
            return None
        sql = """
        SELECT s.snsr_id, s.snsr_name, st.snsr_type_id, s.snsr_addr, s.snsr_req_cmd,
            st.snsr_type_name, st.snsr_req_tunl,
            st.snsr_req_cp, st.snsr_req_port,
            st.snsr_req_inst_val_regex,
            st.snsr_req_assoc_val_regex,
            st.snsr_inst_val_name, st.snsr_assoc_val_name
        FROM sensors AS s
        LEFT JOIN sensor_types AS st 
        ON st.snsr_type_id = s.snsr_type_id
        """

        if where is not None and where.lower().startswith("where"):
            sql += where

        # print("to execute " + sql)
        cur = self.__connection.cursor()
        cur.execute(sql)
        self.__connection.rollback()

        row = cur.fetchone()
        snsrs = []

        while row:
            (id, name, type_id, addr, cmd, type_name,
             tunl, cp, port, inst_regex, assoc_regex, inst_name, assoc_name) = row
            # try:
            #     snsr_type = SnsrType(type_id, type_name, tunl, cp,
            #                          port, inst_regex, assoc_regex, inst_name, assoc_name)
            # except SnsrType.InstanceChangedException as e:
            #     snsr_type = e.old_ins
            snsr_type = SnsrType.create_covering_old_instance(
                type_id, type_name, tunl, cp, port, inst_regex,
                assoc_regex, inst_name, assoc_name
            )
            snsr = Sensor.create_covering_old_instance(
                id, name, addr, cmd, snsr_type
            )
            # try:
            #     snsr = Sensor(id, name, addr, cmd, snsr_type)
            # except Sensor.InstanceChangedException as e:
            #     snsr = e.old_ins
            snsrs.append(snsr)
            row = cur.fetchone()

        return snsrs

    def get_snsrconns_based_on(self, where: str) -> []:
        if self.__connection is None:
            return None
        sql = """
        SELECT s.snsr_id, s.snsr_name, st.snsr_type_id, s.snsr_addr, s.snsr_req_cmd,
            st.snsr_type_name, st.snsr_req_tunl,
            st.snsr_req_cp, st.snsr_req_port,
            st.snsr_req_inst_val_regex,
            st.snsr_req_assoc_val_regex,
            st.snsr_inst_val_name, st.snsr_assoc_val_name
        FROM sensors AS s
        LEFT JOIN sensor_types AS st 
        ON st.snsr_type_id = s.snsr_type_id
        """

        if where is not None and where.lower().startswith("where"):
            sql += where

        # print("to execute " + sql)
        cur = self.__connection.cursor()
        cur.execute(sql)
        self.__connection.rollback()

        row = cur.fetchone()
        snsrconns = []

        while row:
            (id, name, type_id, addr, cmd, type_name,
             tunl, cp, port, inst_regex, assoc_regex, inst_name, assoc_name) = row
            # try:
            #     snsr_type = SnsrType(type_id, type_name, tunl, cp,
            #                          port, inst_regex, assoc_regex, inst_name, assoc_name)
            # except SnsrType.InstanceChangedException as e:
            #     snsr_type = e.old_ins
            snsr_type = SnsrType.create_covering_old_instance(
                type_id, type_name, tunl, cp, port, inst_regex,
                assoc_regex, inst_name, assoc_name
            )
            snsr = Sensor.create_covering_old_instance(
                id, name, addr, cmd, snsr_type
            )
            snsrconn = SensorConnect.create_covering_old_instance(snsr)
            snsrconns.append(snsrconn)
            row = cur.fetchone()

        return snsrconns

    def add_snsr(self, snsr: Sensor):
        if self.__connection is None:
            return
        sql = "INSERT INTO sensors VALUES (%s, %s, %s, %s, %s)"
        cur = self.__connection.cursor()

        cur.execute(sql, (snsr.snsr_id, snsr.snsr_name, snsr.snsr_type.snsr_type_id,
                          snsr.snsr_addr, snsr.snsr_req_cmd))
        # cur.execute("SELECT LAST_INSERT_ID()")
        self.__connection.commit()
        # id = cur.fetchone()
        # snsr.snsr_id = id

    def update_snsr(self, snsr: Sensor):
        if self.__connection is None:
            return
        sql = """
        UPDATE sensors 
        SET snsr_name = %s, snsr_type_id = %s, snsr_addr = %s, snsr_req_cmd = %s
        WHERE snsr_id = %s
        """
        cur = self.__connection.cursor()
        cur.execute(sql,
                    (snsr.snsr_name, snsr.snsr_type.snsr_type_name, snsr.snsr_req_cmd))
        self.__connection.commit()

    def get_last_id(self) -> int:
        cur = self.__connection.cursor()
        cur.execute("SELECT LAST_INSERT_ID()")
        self.__connection.rollback()
        id = cur.fetchone()
        return id


if __name__ == '__main__':
    snsrconns = SnsrAccess().get_snsrconns_based_on("")
    for snsrconn in snsrconns:
        print(snsrconn)
    # snsrs = SnsrAccess().get_snsrs_based_on("")
    # for snsr in snsrs:
    #     print(snsr)
    # snsr_type = SnsrType(1, '', 1, '', 1, '', '', '', '')
    # snsr1 = Sensor.create_covering_old_instance(1, 'name1', '', '', snsr_type)
    # print(snsr1, snsr1.__hash__())
    # snsr2 = Sensor.create_covering_old_instance(1, 'name2', '', '', snsr_type)
    # print(snsr2, snsr2.__hash__())
