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
import typing
from enum import Enum, IntEnum
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtCore import Qt, QModelIndex
from PyQt5.QtWidgets import QWidget

import data.sensor_type
from utils.snsr_access import SnsrAccess
from data.sensor import Sensor

# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class SensorModel(QtCore.QAbstractTableModel):
    class ModelCol(IntEnum):
        SNSR_ID = 0
        SNSR_NAME = 1
        SNSR_TYPE_NAME = 2
        SNSR_ADDR = 3
        SNSR_RECEIVING = 4
        # SNSR_REQ_TUNL = 5
        # SNSR_REQ_CP = 6
        # SNSR_REQ_PORT = 7
        # SNSR_REQ_CMD = 8
        # SNSR_INST_VAL_NAME = 9
        # SNSR_REQ_INST_VAL_REGEX = 10
        # SNSR_ASSOC_VAL_NAME = 11
        # SNSR_REQ_ASSOC_VAL_REGEX = 12
        # SNSR_TYPE_ID = 13

    def __init__(self, snsr_access: SnsrAccess=None, parent=None):
        super().__init__(parent)
        self._snsr_access = snsr_access or SnsrAccess()
        self._snsrconns = self._snsr_access.get_snsrconns_based_on("")

    def columnCount(self, parent: QModelIndex = ...) -> int:
        return 5

    def rowCount(self, parent: QModelIndex = ...) -> int:
        if self._snsrconns is not None:
            return len(self._snsrconns)
        return 0

    def data(self, index: QModelIndex, role: int = ...) -> typing.Any:
        if not index.isValid():
            return None

        if index.row() >= len(self._snsrconns):
            return None

        if role == Qt.DisplayRole:
            if index.column() == SensorModel.ModelCol.SNSR_ID:
                return self._snsrconns[index.row()].snsr.snsr_id
            elif index.column() == SensorModel.ModelCol.SNSR_NAME:
                return self._snsrconns[index.row()].snsr.snsr_name
            elif index.column() == SensorModel.ModelCol.SNSR_TYPE_NAME:
                return self._snsrconns[index.row()].snsr.snsr_type.snsr_type_name
            elif index.column() == SensorModel.ModelCol.SNSR_ADDR:
                return self._snsrconns[index.row()].snsr.snsr_addr
            elif index.column() == SensorModel.ModelCol.SNSR_RECEIVING:
                if self._snsrconns[index.row()].start:
                    return True
                else:
                    return False
        return None

    def headerData(self, section: int, orientation: Qt.Orientation, role: int = ...) -> typing.Any:
        if role != Qt.DisplayRole:
            return None
        if orientation == Qt.Horizontal:
            if section == SensorModel.ModelCol.SNSR_ID:
                return "Id"
            elif section == SensorModel.ModelCol.SNSR_NAME:
                return "Name"
            elif section == SensorModel.ModelCol.SNSR_TYPE_NAME:
                return "Type"
            elif section == SensorModel.ModelCol.SNSR_ADDR:
                return "Address"
            elif section == SensorModel.ModelCol.SNSR_RECEIVING:
                return "Status"
        else:
            return section + 1

    # def flags(self, index: QModelIndex) -> Qt.ItemFlags:
        # QtCore.QAbstractItemModel.flags(index)
        # QtCore.QAbstractTableModel.flags(index)
        # if not index.isValid():
        #     return Qt.NoItemFlags
        # return Qt.ItemIsEditable | Qt.ItemIsEnabled

        # return Qt.ItemIsEditable

    # def insertRow(self, row: int, parent: QModelIndex = ...) -> bool:
    #     row = self.rowCount()
    #     self.beginInsertRows()
    #     self._snsrs.append()

    def appendRow(self, snsr: Sensor, parent: QModelIndex):
        row = self.rowCount()
        self.beginInsertRows(parent, row, row)
        self._snsrs.append(snsr)
        self.endInsertRows()

    def removeRow(self, row: int, parent: QModelIndex = ...) -> bool:
        if row < 0 or row > self.len(self._snsrs):
            return False
        else:
            self.beginRemoveRows(parent, row, row)
            self._snsrs.pop(row)
            self.endRemoveRows()
            return True

    def removeRows(self, row: int, count: int, parent: QModelIndex = ...) -> bool:
        return super().removeRows(row, count, parent)

    def insertRows(self, row: int, count: int, parent: QModelIndex = ...) -> bool:
        return super().insertRows(row, count, parent)

    def setData(self, index: QModelIndex, value: typing.Any, role: int = ...) -> bool:
        if index.isValid() and role == Qt.EditRole:
            try:
                if index.column() == SensorModel.ModelCol.SNSR_ID:
                    self._snsrs[index.row()].snsr_id = int(value)
                elif index.column() == SensorModel.ModelCol.SNSR_NAME:
                    self._snsrs[index.row()].snsr_name = str(value)
                elif index.column() == SensorModel.ModelCol.SNSR_ADDR:
                    self._snsrs[index.row()].snsr_addr = str(value)
                return True
            except Exception as e:
                print(e)
                return False
        return False


# class SensorEditDelegate(QtWidgets.QItemDelegate):
#
#     def __init__(self, snsr_types, parent=None):
#         super(SensorEditDelegate, self).__init__(parent)
#         self._snsr_types = snsr_types
#
#     def setEditorData(self, editor: QWidget, index: QtCore.QModelIndex) -> None:
#         super().setEditorData(editor, index)
#
#     def createEditor(self, parent: QWidget, option: 'QStyleOptionViewItem', index: QtCore.QModelIndex) -> QWidget:
#         if index.column() == SensorModel.ModelCol.SNSR_TYPE_NAME:
#             editor = QtWidgets.QComboBox


if __name__ == '__main__':
    pass
