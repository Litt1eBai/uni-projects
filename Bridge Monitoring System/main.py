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
from PyQt5 import QtWidgets
import sys

from qt.dashboard_base import Ui_DashboardWindow
# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    DashboardWindow = QtWidgets.QMainWindow()
    ui = Ui_DashboardWindow()
    ui.setupUi(DashboardWindow)
    DashboardWindow.show()
    sys.exit(app.exec_())
