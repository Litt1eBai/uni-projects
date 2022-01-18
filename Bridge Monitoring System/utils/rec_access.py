#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# =================================================
# Created By: Jens Liu
# Created At: 17.01.2022
# Email: jens.l29@outlook.com
# =================================================
"""
    this file is created for project: final
"""
# =================================================
import datetime
from utils.db_access_until import DbAccessUtil
from data.sensor import Sensor
from data.sensor_type import SnsrType
from data.record import Record

# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class RecordAccess(object):
    def __init__(self):
        self.__connection = DbAccessUtil().get_connection()

    def get_rec_with_id(self, id) -> Record or None:
        recs = self.get_recs_based_on("WHERE r.rec_id = " + id)
        if recs is not None:
            return recs[0]
        return None

    def get_recs_within_time(self, start_time: datetime.datetime,
                             end_time: datetime.datetime) -> []:
        return self.get_recs_based_on(
            "WHERE r.rec_time BETWEEN '" + start_time.strftime('%Y-%m-%d %H:%M:%S') +
            "' AND '" + end_time.strftime('%Y-%m-%d %H:%M:%S'))

    def get_recs_of_snsr(self, snsr_id: int) -> []:
        return self.get_recs_based_on("WHERE r.snsr_id = " + str(snsr_id))

    def get_recs_of_snsr_within_time(self, snsr_id: int,
                                     start_time: datetime.datetime,
                                     end_time: datetime.datetime) -> []:
        return self.get_recs_based_on(
            "WHERE r.snsr_id = " + str(snsr_id) + " AND (r.rec_time BETWEEN '" + start_time.strftime(
                '%Y-%m-%d %H:%M:%S') +
            "' AND '" + end_time.strftime('%Y-%m-%d %H:%M:%S') + "')")

    def get_recs_based_on(self, where: str) -> []:
        if self.__connection is None:
            return None
        sql = """
            SELECT r.rec_id, r.snsr_id, r.inst_val, r.assoc_val, r.rec_time,
                s.snsr_name, s.snsr_type_id, s.snsr_addr, s.snsr_req_cmd,
                st.snsr_type_name, st.snsr_req_tunl, st.snsr_req_cp,
                st.snsr_req_port, st.snsr_req_inst_val_regex,
                st.snsr_req_assoc_val_regex,
                st.snsr_inst_val_name, st.snsr_assoc_val_name
            FROM records AS r
            LEFT JOIN sensors AS s ON s.snsr_id = r.snsr_id
            LEFT JOIN sensor_types AS st ON st.snsr_type_id = s.snsr_type_id
        """

        if where.lower().startswith("where"):
            sql += where

        cur = self.__connection.cursor()
        cur.execute(sql)
        self.__connection.commit()

        recs = []

        row = cur.fetchone()
        while row:
            (rec_id, snsr_id, inst_val, assoc_val, rec_time,
             snsr_name, snsr_type_id, snsr_addr, snsr_req_cmd,
             snsr_type_name, snsr_req_tunl, snsr_req_cp,
             snsr_req_port, snsr_req_inst_val_regex,
             snsr_req_assoc_val_regex, snsr_inst_val_name,
             snsr_assoc_val_name) = row
            try:
                snsr_type = SnsrType(snsr_type_id, snsr_type_name, snsr_req_tunl,
                                     snsr_req_cp, snsr_req_port, snsr_req_inst_val_regex,
                                     snsr_req_assoc_val_regex, snsr_inst_val_name,
                                     snsr_assoc_val_name)
            except SnsrType.InstanceChangedException as e:
                snsr_type = e.old_ins
            try:
                snsr = Sensor(snsr_id, snsr_name, snsr_addr, snsr_req_cmd, snsr_type)
            except Sensor.InstanceChangedException as e:
                snsr = e.old_ins
            rec = Record(rec_id, snsr, inst_val, assoc_val, rec_time)
            recs.append(rec)

    def add_rec(self, rec: Record):
        snsr_id = rec.snsr.snsr_id
        inst_val = rec.inst_val
        assoc_val = rec.assoc_val
        rec_time = rec.rec_time
        sql = "INSERT INTO records VALUES(%s, %s, %s, %s)"
        cur = self.__connection.cursor()

        cur.execute(sql, (snsr_id, inst_val, assoc_val, rec_time))
        cur.execute("SELECT LAST_INSERT_ID()")
        self.__connection.commit()

        id = cur.fetchone()
        rec.rec_id = id


if __name__ == '__main__':
    RecordAccess().get_recs_of_snsr_within_time(
        1, datetime.datetime(2020, 1, 1), datetime.datetime(2021, 1, 1))
