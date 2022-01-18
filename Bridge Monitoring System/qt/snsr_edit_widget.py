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
from PyQt5 import QtWidgets, QtCore
from qt.snsr_edit_widget_base import Ui_SnsrEditWidget
from models.sensor_model import SensorModel
# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class SnsrEditWidget(QtWidgets.QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.ui = Ui_SnsrEditWidget()
        self.ui.setupUi(self)
        self.ui.snsrTableView.horizontalHeader().setSectionResizeMode(QtWidgets.QHeaderView.Stretch)
        self.__snsr_model = None

    def set_snsr_model(self, snsr_model: SensorModel):
        self.__snsr_model = snsr_model
        self.ui.snsrTableView.setModel(self.__snsr_model)


if __name__ == '__main__':
    pass
