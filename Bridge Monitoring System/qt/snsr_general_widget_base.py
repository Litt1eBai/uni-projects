# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '.\snsr_general_widget.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_SnsrGeneralWidget(object):
    def setupUi(self, SnsrGeneralWidget):
        SnsrGeneralWidget.setObjectName("SnsrGeneralWidget")
        SnsrGeneralWidget.resize(553, 418)
        self.verticalLayout_5 = QtWidgets.QVBoxLayout(SnsrGeneralWidget)
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.gbox_outer = QtWidgets.QGroupBox(SnsrGeneralWidget)
        self.gbox_outer.setObjectName("gbox_outer")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.gbox_outer)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.tabWidget = QtWidgets.QTabWidget(self.gbox_outer)
        self.tabWidget.setObjectName("tabWidget")
        self.tab = QtWidgets.QWidget()
        self.tab.setObjectName("tab")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.tab)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.groupBox = QtWidgets.QGroupBox(self.tab)
        self.groupBox.setObjectName("groupBox")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.groupBox)
        self.verticalLayout.setObjectName("verticalLayout")
        self.gridLayout_2 = QtWidgets.QGridLayout()
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(self.groupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.lbl_snsr_name = QtWidgets.QLabel(self.groupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lbl_snsr_name.sizePolicy().hasHeightForWidth())
        self.lbl_snsr_name.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.lbl_snsr_name.setFont(font)
        self.lbl_snsr_name.setObjectName("lbl_snsr_name")
        self.horizontalLayout.addWidget(self.lbl_snsr_name)
        self.gridLayout_2.addLayout(self.horizontalLayout, 0, 0, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_2.addItem(spacerItem, 0, 1, 1, 1)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.label_4 = QtWidgets.QLabel(self.groupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_4.sizePolicy().hasHeightForWidth())
        self.label_4.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_2.addWidget(self.label_4)
        self.lbl_snsr_id = QtWidgets.QLabel(self.groupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lbl_snsr_id.sizePolicy().hasHeightForWidth())
        self.lbl_snsr_id.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.lbl_snsr_id.setFont(font)
        self.lbl_snsr_id.setObjectName("lbl_snsr_id")
        self.horizontalLayout_2.addWidget(self.lbl_snsr_id)
        self.gridLayout_2.addLayout(self.horizontalLayout_2, 0, 2, 1, 1)
        spacerItem1 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_2.addItem(spacerItem1, 0, 3, 1, 1)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.label_2 = QtWidgets.QLabel(self.groupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_2.sizePolicy().hasHeightForWidth())
        self.label_2.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_3.addWidget(self.label_2)
        self.lbl_snsr_type = QtWidgets.QLabel(self.groupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lbl_snsr_type.sizePolicy().hasHeightForWidth())
        self.lbl_snsr_type.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.lbl_snsr_type.setFont(font)
        self.lbl_snsr_type.setObjectName("lbl_snsr_type")
        self.horizontalLayout_3.addWidget(self.lbl_snsr_type)
        self.gridLayout_2.addLayout(self.horizontalLayout_3, 0, 4, 1, 1)
        self.verticalLayout.addLayout(self.gridLayout_2)
        self.verticalLayout_4.addWidget(self.groupBox)
        self.gbox_statistics = QtWidgets.QGroupBox(self.tab)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.gbox_statistics.sizePolicy().hasHeightForWidth())
        self.gbox_statistics.setSizePolicy(sizePolicy)
        self.gbox_statistics.setObjectName("gbox_statistics")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.gbox_statistics)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.gridLayout = QtWidgets.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.lbl_inst_name = QtWidgets.QLabel(self.gbox_statistics)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lbl_inst_name.sizePolicy().hasHeightForWidth())
        self.lbl_inst_name.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.lbl_inst_name.setFont(font)
        self.lbl_inst_name.setObjectName("lbl_inst_name")
        self.gridLayout.addWidget(self.lbl_inst_name, 0, 0, 1, 1)
        self.lbl_snsr_inst_val = QtWidgets.QLabel(self.gbox_statistics)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lbl_snsr_inst_val.sizePolicy().hasHeightForWidth())
        self.lbl_snsr_inst_val.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.lbl_snsr_inst_val.setFont(font)
        self.lbl_snsr_inst_val.setObjectName("lbl_snsr_inst_val")
        self.gridLayout.addWidget(self.lbl_snsr_inst_val, 0, 1, 1, 1)
        self.lbl_assoc_name = QtWidgets.QLabel(self.gbox_statistics)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lbl_assoc_name.sizePolicy().hasHeightForWidth())
        self.lbl_assoc_name.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.lbl_assoc_name.setFont(font)
        self.lbl_assoc_name.setObjectName("lbl_assoc_name")
        self.gridLayout.addWidget(self.lbl_assoc_name, 1, 0, 1, 1)
        self.lbl_snsr_assoc_val = QtWidgets.QLabel(self.gbox_statistics)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lbl_snsr_assoc_val.sizePolicy().hasHeightForWidth())
        self.lbl_snsr_assoc_val.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.lbl_snsr_assoc_val.setFont(font)
        self.lbl_snsr_assoc_val.setObjectName("lbl_snsr_assoc_val")
        self.gridLayout.addWidget(self.lbl_snsr_assoc_val, 1, 1, 1, 1)
        self.label_3 = QtWidgets.QLabel(self.gbox_statistics)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_3.sizePolicy().hasHeightForWidth())
        self.label_3.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.gridLayout.addWidget(self.label_3, 2, 0, 1, 1)
        self.lbl_update_date = QtWidgets.QLabel(self.gbox_statistics)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lbl_update_date.sizePolicy().hasHeightForWidth())
        self.lbl_update_date.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(8)
        self.lbl_update_date.setFont(font)
        self.lbl_update_date.setObjectName("lbl_update_date")
        self.gridLayout.addWidget(self.lbl_update_date, 2, 1, 1, 1)
        self.verticalLayout_3.addLayout(self.gridLayout)
        self.verticalLayout_4.addWidget(self.gbox_statistics)
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        spacerItem2 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_5.addItem(spacerItem2)
        self.btn_start = QtWidgets.QPushButton(self.tab)
        self.btn_start.setObjectName("btn_start")
        self.horizontalLayout_5.addWidget(self.btn_start)
        self.btn_stop = QtWidgets.QPushButton(self.tab)
        self.btn_stop.setObjectName("btn_stop")
        self.horizontalLayout_5.addWidget(self.btn_stop)
        self.verticalLayout_4.addLayout(self.horizontalLayout_5)
        self.tabWidget.addTab(self.tab, "")
        self.tab_2 = QtWidgets.QWidget()
        self.tab_2.setObjectName("tab_2")
        self.tableView = QtWidgets.QTableView(self.tab_2)
        self.tableView.setGeometry(QtCore.QRect(30, 10, 256, 192))
        self.tableView.setObjectName("tableView")
        self.pushButton_3 = QtWidgets.QPushButton(self.tab_2)
        self.pushButton_3.setGeometry(QtCore.QRect(351, 226, 86, 23))
        self.pushButton_3.setObjectName("pushButton_3")
        self.tabWidget.addTab(self.tab_2, "")
        self.verticalLayout_2.addWidget(self.tabWidget)
        self.verticalLayout_5.addWidget(self.gbox_outer)

        self.retranslateUi(SnsrGeneralWidget)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(SnsrGeneralWidget)

    def retranslateUi(self, SnsrGeneralWidget):
        _translate = QtCore.QCoreApplication.translate
        SnsrGeneralWidget.setWindowTitle(_translate("SnsrGeneralWidget", "Form"))
        self.gbox_outer.setTitle(_translate("SnsrGeneralWidget", "Sensor"))
        self.groupBox.setTitle(_translate("SnsrGeneralWidget", "General"))
        self.label.setText(_translate("SnsrGeneralWidget", "Sensor:"))
        self.lbl_snsr_name.setText(_translate("SnsrGeneralWidget", "None"))
        self.label_4.setText(_translate("SnsrGeneralWidget", "Id:"))
        self.lbl_snsr_id.setText(_translate("SnsrGeneralWidget", "None"))
        self.label_2.setText(_translate("SnsrGeneralWidget", "Type:"))
        self.lbl_snsr_type.setText(_translate("SnsrGeneralWidget", "None"))
        self.gbox_statistics.setTitle(_translate("SnsrGeneralWidget", "Real Time Statistics"))
        self.lbl_inst_name.setText(_translate("SnsrGeneralWidget", "Instance Value:"))
        self.lbl_snsr_inst_val.setText(_translate("SnsrGeneralWidget", "None"))
        self.lbl_assoc_name.setText(_translate("SnsrGeneralWidget", "Associated Value:"))
        self.lbl_snsr_assoc_val.setText(_translate("SnsrGeneralWidget", "None"))
        self.label_3.setText(_translate("SnsrGeneralWidget", "Update Time:"))
        self.lbl_update_date.setText(_translate("SnsrGeneralWidget", "None"))
        self.btn_start.setText(_translate("SnsrGeneralWidget", "Start"))
        self.btn_stop.setText(_translate("SnsrGeneralWidget", "Stop"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), _translate("SnsrGeneralWidget", "Monitor"))
        self.pushButton_3.setText(_translate("SnsrGeneralWidget", "About this sensor"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_2), _translate("SnsrGeneralWidget", "Brief"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    SnsrGeneralWidget = QtWidgets.QWidget()
    ui = Ui_SnsrGeneralWidget()
    ui.setupUi(SnsrGeneralWidget)
    SnsrGeneralWidget.show()
    sys.exit(app.exec_())
