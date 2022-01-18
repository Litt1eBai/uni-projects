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
from PyQt5 import QtWidgets
from PyQt5 import QtCore

from dashboard_window_base import Ui_DashboardWindow
from utils.snsr_access import SnsrAccess
from utils.rec_access import RecordAccess
from models.sensor_model import SensorModel

# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class DashboardWindow(QtWidgets.QMainWindow):

    def __init__(self, *args, **kwargs):
        # ui setup
        super().__init__(*args, **kwargs)
        self.ui = Ui_DashboardWindow()
        self.ui.setupUi(self)

        # initialise models
        self.__snsr_type_model = None
        self.__snsr_model = SensorModel()
        self.__rec_model = None

        # passing models to sub widgets
        self.ui.snsr_edit_widget.set_snsr_model(self.__snsr_model)


if __name__ == '__main__':
    app = QtWidgets.QApplication([])

    widget = DashboardWindow()
    widget.show()

    app.exec_()
