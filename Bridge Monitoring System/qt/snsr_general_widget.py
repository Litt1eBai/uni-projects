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
from qt.snsr_general_widget_base import Ui_SnsrGeneralWidget
from data.sensor import Sensor, SensorConnect
from data.record import Record

# =================================================

__author__ = 'JensLiu'
__version__ = '1.0.0'


class SnsrGeneralWidget(QtWidgets.QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.ui = Ui_SnsrGeneralWidget()
        self.ui.setupUi(self)
        self.__snsrconn: SensorConnect or None = None

    def __init_content(self):
        if self.__snsrconn is None:
            return
        self.ui.lbl_snsr_id.setText(str(self.__snsrconn.snsr.snsr_id))
        self.ui.lbl_snsr_name.setText(self.__snsrconn.snsr.snsr_name)
        self.ui.lbl_snsr_type.setText(self.__snsrconn.snsr.snsr_type.snsr_type_name)

        if self.__snsrconn.snsr.snsr_type.snsr_req_inst_val_regex is not None:
            self.ui.lbl_inst_name.setVisible(True)
            self.ui.lbl_snsr_inst_val.setVisible(True)
            self.ui.lbl_inst_name.setText(self.__snsrconn.snsr.snsr_type.snsr_inst_val_name)
        else:
            self.ui.lbl_inst_name.setVisible(False)
            self.ui.lbl_snsr_inst_val.setVisible(False)

        if self.__snsrconn.snsr.snsr_type.snsr_req_assoc_val_regex is not None:
            self.ui.lbl_assoc_name.setVisible(True)
            self.ui.lbl_snsr_assoc_val.setVisible(True)
            self.ui.lbl_assoc_name.setText(self.__snsrconn.snsr.snsr_type.snsr_assoc_val_name)
        else:
            self.ui.lbl_assoc_name.setVisible(False)
            self.ui.lbl_snsr_assoc_val.setVisible(False)

    def __data_callback(self, rec: Record):
        self.ui.lbl_snsr_inst_val.setText(str(rec.inst_val))
        self.ui.lbl_snsr_assoc_val.setText(str(rec.assoc_val))
        self.ui.lbl_update_date.setText(str(rec.rec_time))

    def __start_threading_callback(self):
        self.ui.btn_start.setEnabled(False)
        self.ui.btn_stop.setEnabled(True)

    def __stop_threading_callback(self):
        self.ui.btn_start.setEnabled(True)
        self.ui.btn_stop.setEnabled(False)

    def _evt_btn_start_clicked(self):
        self.ui.btn_start.setEnabled(False)
        self.__snsrconn.start_threading()
        self.ui.btn_stop.setEnabled(True)

    def _evt_btn_stop_clicked(self):
        self.ui.btn_stop.setEnabled(False)
        self.__snsrconn.stop_threading()
        self.ui.btn_start.setEnabled(True)

    def set_snsrconn(self, snsrconn: SensorConnect):
        self.__snsrconn = snsrconn
        self.__init_content()

    def init(self, snsrconn: SensorConnect):
        self.set_snsrconn(snsrconn)
        snsrconn.add_data_callback_function(self.__data_callback)
        snsrconn.add_start_threading_callback_function(self.__start_threading_callback)
        snsrconn.add_stop_threading_callback_function(self.__stop_threading_callback)
        self.__init_content()
        self.__snsrconn.start_threading()
        self.ui.btn_start.clicked.connect(self._evt_btn_start_clicked)
        self.ui.btn_stop.clicked.connect(self._evt_btn_stop_clicked)


if __name__ == '__main__':
    from utils.snsr_access import SnsrAccess

    conn = SnsrAccess().get_snsrconn_with_id(6)

    app = QtWidgets.QApplication([])
    widget = SnsrGeneralWidget()
    widget.init(conn)
    widget.show()
    app.exec_()


    # snsrs = SnsrAccess().get_snsrs_based_on("")
    # for snsr in snsrs:
    #     sc = SensorConnect(snsr)
    #
    # while True:
    #     continue
