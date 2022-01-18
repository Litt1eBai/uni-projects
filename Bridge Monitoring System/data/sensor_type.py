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
# Imports
# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class SnsrType(object):
    """
    this class is for the type of the sensor
    if creating two instances with the same type_id, it returns the same instances
    if two instances are to be created with type_id being the same while other attributes being modified,
    it raises InstanceChangedException, you can access the old instance in its old_ins attribute
    """
    _instances = {}

    class InstanceChangedException(Exception):
        """
        the InstanceChangedException is raised when two instances to be created with same type_id
        but other attributes are not the same
        """

        def __init__(self, old_ins):
            self.old_ins = old_ins

    def __init__(self, type_id, type_name, req_tunl, req_cp,
                 req_port, req_inst_val_regex, req_assoc_val_regex,
                 inst_val_name, assoc_val_name):
        """

        :param type_id: type id
        :param type_name: type name
        :param req_tunl: tunel used for request
        :param req_cp: connection protocol used for request
        :param req_port: port used for request
        :param req_inst_val_regex: regular expression to resolve instance value returned from server
        :param req_assoc_val_regex: regular expression to resolve associated value
        :param inst_val_name: name  or interpretation for instance value
        :param assoc_val_name: name or interpretation for associated value
        """
        self.snsr_type_id = type_id
        self.snsr_type_name = type_name
        self.snsr_req_tunl = req_tunl
        self.snsr_req_cp = req_cp
        self.snsr_req_port = req_port
        self.snsr_req_inst_val_regex = req_inst_val_regex
        self.snsr_req_assoc_val_regex = req_assoc_val_regex
        self.snsr_inst_val_name = inst_val_name
        self.snsr_assoc_val_name = assoc_val_name

    def __new__(cls, type_id: int, type_name: str, req_tunl: int, req_cp: str,
                req_port: int, req_inst_val_regex: str, req_assoc_val_regex: str,
                inst_val_name: str, assoc_val_name: str, *args, **kwargs):

        if str(type_id) in cls._instances:

            ins: SnsrType = cls._instances[str(type_id)]

            if type_name == ins.snsr_type_name and \
                    req_tunl == ins.snsr_req_tunl and \
                    req_cp == ins.snsr_req_cp and \
                    req_port == ins.snsr_req_port and \
                    req_inst_val_regex == ins.snsr_req_inst_val_regex and \
                    req_assoc_val_regex == ins.snsr_req_assoc_val_regex and \
                    inst_val_name == ins.snsr_inst_val_name and \
                    assoc_val_name == ins.snsr_assoc_val_name:
                return cls._instances[str(type_id)]

            else:
                raise cls.InstanceChangedException(cls._instances[str(type_id)])

        else:
            new_ins = object.__new__(cls)
            cls._instances[str(type_id)] = new_ins
            return new_ins

    @classmethod
    def create_covering_old_instance(cls, type_id: int, type_name: str, req_tunl: int, req_cp: str,
                                     req_port: int, req_inst_val_regex: str, req_assoc_val_regex: str,
                                     inst_val_name: str, assoc_val_name: str):
        """
        by calling, it creates a new instance of SnsrType object.
        if there is an instance with same id, it rewrites values of the old instance and
        return the updated old instance
        if there is no instance with same id, it returns a new instance
        :param type_id:
        :param type_name:
        :param req_tunl:
        :param req_cp:
        :param req_port:
        :param req_inst_val_regex:
        :param req_assoc_val_regex:
        :param inst_val_name:
        :param assoc_val_name:
        :return:
        """
        try:
            new_ins = cls(type_id, type_name, req_tunl, req_cp,
                          req_port, req_inst_val_regex, req_assoc_val_regex,
                          inst_val_name, assoc_val_name)
        except cls.InstanceChangedException as e:
            old_ins: SnsrType = e.old_ins
            old_ins.snsr_type_name = type_name
            old_ins.snsr_req_tunl = req_tunl
            old_ins.snsr_req_cp = req_cp
            old_ins.snsr_req_port = req_port
            old_ins.snsr_req_inst_val_regex = req_inst_val_regex
            old_ins.snsr_assoc_val_name = req_assoc_val_regex
            old_ins.snsr_inst_val_name = inst_val_name
            old_ins.snsr_assoc_val_name = assoc_val_name
            return old_ins

        return new_ins

    def pop_instance(self):
        """
        this function removes the reference of the object kept my class
        use it before removing the object
        :return:
        """
        self._instances.pop(str(self.snsr_type_id))


if __name__ == '__main__':
    ins = SnsrType.__new__(SnsrType, 1, '', 1, '', 1, '', '', '', '')
    print(ins.snsr_type_id)
