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

# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class Record(object):

    class InstanceChangedException(Exception):
        def __init__(self, old_ins):
            self.old_ins = old_ins

    def __init__(self, rec_id, snsr, inst_val, assoc_val, rec_time):
        self.rec_id = rec_id
        self.snsr = snsr
        self.inst_val = inst_val
        self.assoc_val = assoc_val
        self.rec_time = rec_time

    def __str__(self):
        return "{id=" + str(self.rec_id) + ", inst_val=" + \
               str(self.inst_val) + ", assoc_val=" + str(self.assoc_val) + \
               ", snsr=" + self.snsr.__str__() + ", rec_time=" + str(self.rec_time) + "}"

if __name__ == '__main__':
    pass
