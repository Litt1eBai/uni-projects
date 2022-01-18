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
import time
import socket
import threading
import struct
import datetime
from utils.server_req_util import ServerRequestUtil
from data.sensor_type import SnsrType
from data.record import Record

# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class Sensor(object):
    """
    this class is sensor
    if creating two instances with the same snsr_id, it returns the same instances
    if two instances are to be created with snsr_id being the same while other attributes being modified,
    it raises InstanceChangedException, you can access the old instance in its old_ins attribute
    """

    _instances = {}

    class InstanceChangedException(Exception):
        def __init__(self, old_ins):
            self.old_ins = old_ins

    def __init__(self, id: int, name: str, addr: str,
                 req_cmd: str, snsr_type: SnsrType):
        self.snsr_id = id
        self.snsr_name = name
        self.snsr_addr = addr
        self.snsr_req_cmd = req_cmd
        self.snsr_type = snsr_type

    def __new__(cls, id: int, name: str, addr: str,
                req_cmd: str, snsr_type: SnsrType, *args, **kwargs):
        if str(id) in cls._instances:
            ins: cls = cls._instances[str(id)]
            if id == ins.snsr_id and \
                    name == ins.snsr_name and \
                    addr == ins.snsr_addr and \
                    req_cmd == ins.snsr_req_cmd and \
                    snsr_type == ins.snsr_type:
                return cls._instances[str(id)]
            else:
                raise Sensor.InstanceChangedException(cls._instances[str(id)])

        else:
            new_ins = object.__new__(cls)
            cls._instances[str(id)] = new_ins
            return new_ins

    @classmethod
    def create_covering_old_instance(cls, id, name, addr, req_cmd, snsr_type):
        try:
            new_ins = cls(id, name, addr, req_cmd, snsr_type)
            return new_ins
        except cls.InstanceChangedException as e:
            old_ins: Sensor = e.old_ins
            old_ins.snsr_id = id
            old_ins.snsr_name = name
            old_ins.snsr_addr = addr
            old_ins.snsr_req_cmd = req_cmd
            old_ins.snsr_type = snsr_type
            return old_ins

    def pop_instance(self):
        """
        this function removes the object reference kept by the class
        use it before you remove the object
        :return:
        """
        self._instances.pop(str(self.snsr_id))

    def __str__(self) -> str:
        return "{id=" + str(self.snsr_id) + ", name=" + \
               self.snsr_name + ", type_id=" + str(
            self.snsr_type.snsr_type_id) + " type=" + str(self.snsr_type.snsr_type_id) + "}"


class SensorConnect(object):
    """
    this class is used for sensor to receive data from server
    """

    _instances = {}

    class InstanceChangedException(Exception):
        def __init__(self, old_ins):
            self.old_ins = old_ins

    def __init__(self, snsr: Sensor, time_interval=10):
        """

        :param snsr: sensor
        :param time_interval: pause time between requests
        """
        self.snsr = snsr
        self.__time_interval = time_interval
        self.__start = False
        self.__receivingThread = None
        self.__data_callback_function = None
        self.__start_threading_callback_function = None
        self.__stop_threading_callback_function = None
        self.__rec_cache = []
        self.__max_rec_cache = 32

    def __new__(cls, snsr: Sensor, *args, **kwargs):
        if str(snsr.snsr_id) in cls._instances:
            old_ins: SensorConnect = cls._instances[str(snsr.snsr_id)]
            if old_ins.snsr == snsr:
                return cls._instances[str(snsr.snsr_id)]
            else:
                raise cls.InstanceChangedException(old_ins)
        else:
            new_ins = object.__new__(cls)
            cls._instances[str(snsr.snsr_id)] = new_ins
            return new_ins

    @classmethod
    def create_covering_old_instance(cls, snsr: Sensor):
        """
        this function creates an instance for
        :param snsr:
        :return:
        """
        try:
            new_ins = cls(snsr)
            return new_ins
        except cls.InstanceChangedException as e:
            old_ins: SensorConnect = e.old_ins
            old_ins.snsr = snsr
            return old_ins

    def pop_instance(self):
        """
        this function removes reference to the object kept by class
        call it before removing the object
        :return:
        """
        self._instances.pop(str(self.snsr.snsr_id))

    def __process_data(self, data: tuple) -> bool:
        """
        this function takes data and process it, including committing to database and do callbacks
        :param data: a tuple of ((inst_name, inst_val), (assoc_name, assoc_val))
        :return: whether data correctly processed
        """
        inst_regex = self.snsr.snsr_type.snsr_req_inst_val_regex
        inst_name = self.snsr.snsr_type.snsr_inst_val_name
        assoc_regex = self.snsr.snsr_type.snsr_req_assoc_val_regex
        assoc_name = self.snsr.snsr_type.snsr_assoc_val_name

        check_sum = data[-2:]
        if check_sum != ServerRequestUtil.crc16(data[:-2]):
            print("[ERROR]: CRC16 check failed for sensor " + str(self.snsr.snsr_id))
            return False
        inst_val = None
        assoc_val = None
        try:
            if inst_regex is not None:
                inst_val = eval(inst_regex)
            if assoc_regex is not None:
                assoc_val = eval(assoc_regex)

            general_data = ((inst_name, inst_val), (assoc_name, assoc_val))
            rec = self.__pack_data_into_record(general_data)

            self.__do_data_callback(rec)

        except SyntaxError:
            print("[ERROR]: regular expression is wrong for sensor " + str(self.snsr.snsr_id))
            print("inst: " + inst_regex + ", assoc: " + assoc_regex)
            return False

        return True

    def __pack_data_into_record(self, data: tuple) -> Record:
        """
        this function packs data into Record object
        :param data: a tuple of ((inst_name, inst_val), (assoc_name, assoc_val))
        :return: a Record object with rec_id being -1
        """
        ((inst_name, inst_val), (assoc_name, assoc_val)) = data
        rec_time = datetime.datetime.now()
        rec = Record(None, self.snsr, inst_val, assoc_val, rec_time)
        print(rec)
        return rec

    def __do_udp_receive(self):
        """
        this function is called by receiving thread
        :return:
        """
        snsr_cmd = bytes.fromhex(self.snsr.snsr_req_cmd)
        snsr_server = 'demo-monitor.igong.com'
        snsr_port = self.snsr.snsr_type.snsr_req_port
        udp_sock = ServerRequestUtil.get_udp_connection()
        try:
            while self.__start:
                udp_sock.sendto(snsr_cmd, (snsr_server, snsr_port))
                try:
                    data, _ = udp_sock.recvfrom(8192)
                except socket.timeout:
                    print("[ERROR]: timeout for sensor " + str(self.snsr.snsr_id))
                    continue
                if data is not None:
                    if self.__process_data(data):
                        time.sleep(2)
                    else:
                        continue
        finally:
            print("[DEBUG]: UDP socket closed for sensor " + str(self.snsr.snsr_id))
            udp_sock.close()

    def __do_tcp_receive(self):
        """
        this function is called by receiving thread
        :return:
        """
        snsr_cmd = bytes.fromhex(self.snsr.snsr_req_cmd)
        snsr_server = 'demo-monitor.igong.com'
        snsr_port = self.snsr.snsr_type.snsr_req_port
        tcp_sock = ServerRequestUtil.get_tcp_connection()
        try:
            tcp_sock.connect((snsr_server, snsr_port))
        except:
            print("[ERROR]: failed to connect to server for sensor " + str(self.snsr.snsr_id))
            return
        try:
            while self.__start:
                tcp_sock.sendall(snsr_cmd)
                try:
                    data = tcp_sock.recv(8192)
                except socket.timeout:
                    print("[ERROR]: timeout for sensor " + str(self.snsr.snsr_id))
                    continue
                if data is not None:
                    if self.__process_data(data):
                        time.sleep(2)
                    else:
                        continue
        finally:
            print("[DEBUG]: TCP socket closed for sensor " + str(self.snsr.snsr_id))
            tcp_sock.close()

    def start_receiving(self):
        """
        this function starts receiving data of the sensor, it starts a receiving thread
        :return:
        """
        self.__start = True
        if self.snsr.snsr_type.snsr_req_cp == 'UDP':
            self.__receivingThread = threading.Thread(target=self.__do_udp_receive, args=())
            self.__receivingThread.setDaemon(True)
            self.__receivingThread.start()
            print("[DEBUG]: UDP receiving thread for sensor " + str(self.snsr.snsr_id) + " has started")
            self.__do_start_threading_callback()
        elif self.snsr.snsr_type.snsr_req_cp == 'TCP':
            self.__receivingThread = threading.Thread(target=self.__do_tcp_receive(), args=())
            self.__receivingThread.setDaemon(True)
            self.__receivingThread.start()
            print("[DEBUG]: TCP receiving thread for sensor " + str(self.snsr.snsr_id) + " has started")
            self.__do_start_threading_callback()

    def stop_threading(self):
        """
        this function stops the receiving thread
        :return:
        """
        self.__start = False
        if self.__receivingThread is not None:
            while self.__receivingThread.is_alive():
                time.sleep(0.1)
            print("[DEBUG]: UDP receiving thread for sensor " + str(self.snsr.snsr_id) + " has stopped")
            self.__do_stop_threading_callback()

    def __do_data_callback(self, data: Record):
        """
        this function calls callback function for data
        :param data:
        :return:
        """
        print("[DEBGU]: got data for sensor " + str(self.snsr.snsr_id) + ": ", data)
        if self.__data_callback_function is not None:
            self.__data_callback_function(data)

    def __do_start_threading_callback(self):
        """
        this function calls callback function after thread starts
        :return:
        """
        if self.__start_threading_callback_function is not None:
            self.__start_threading_callback_function()

    def __do_stop_threading_callback(self):
        """
        this function calls callback function after thread stops
        :return:
        """
        if self.__stop_threading_callback_function is not None:
            self.__stop_threading_callback_function()

    def __str__(self):
        return "{snsr=" + self.snsr.__str__() + \
        ", connected=" + str(self.__start) + "}"

    @property
    def start(self):
        return self.__start

    @property
    def data_callback_function(self):
        return self.__data_callback_function

    @data_callback_function.setter
    def data_callback_function(self, func):
        self.__data_callback_function = func

    @property
    def start_threading_callback_function(self):
        return self.__start_threading_callback_function

    @start_threading_callback_function.setter
    def start_threading_callback_function(self, func):
        self.start_threading_callback_function = func

    @property
    def stop_threading_callback_function(self):
        return self.__stop_threading_callback_function

    @stop_threading_callback_function.setter
    def stop_threading_callback_function(self, func):
        self.stop_threading_callback_function = func


if __name__ == '__main__':
    from utils.snsr_access import SnsrAccess

    snsrs = SnsrAccess().get_snsrs_based_on("")
    print(snsrs)
    for snsr in snsrs:
        sc = SensorConnect(snsr)
        sc.start_receiving()

    while True:
        continue
