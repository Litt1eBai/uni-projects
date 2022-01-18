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
from PyQt5 import QtWidgets
from qt.snsr_activ_widget_base import Ui_SnsrActvWidget
# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class SnsrActivWidget(QtWidgets.QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.ui = Ui_SnsrActvWidget()
        self.ui.setupUi(self)
        self.__snsrconns = None





if __name__ == '__main__':
    pass
