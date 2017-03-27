#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
import codecs
from PyQt4 import QtGui,QtWebKit,QtCore
import tempfile
import OpenRTM_aist


import struct




class ServicePortOperationDialog(QtGui.QDialog):
    def __init__(self, classlist, parent=None):
        super(ServicePortOperationDialog, self).__init__(parent)
        self.classlist = classlist
        self.setWindowTitle(u"関数一覧")
        self.mainLayout = QtGui.QVBoxLayout()
        self.setLayout(self.mainLayout)

        self.tables = []
        for k,v in classlist.items():
            widget = QtGui.QGroupBox(k)
            layout = QtGui.QVBoxLayout()
            widget.setLayout(layout)

            table = QtGui.QTableWidget(5,1)
            vheader = QtGui.QHeaderView(QtCore.Qt.Vertical)
            vheader.setResizeMode(QtGui.QHeaderView.ResizeToContents)
            table.setVerticalHeader(vheader)
            hheader = QtGui.QHeaderView(QtCore.Qt.Horizontal)
            hheader.setResizeMode(QtGui.QHeaderView.ResizeToContents)
            table.setHorizontalHeader(hheader)
            

            
            layout.addWidget(table)
            table.setRowCount(len(v))
            num = 0
            for func in v:
                table.setItem(num,0, QtGui.QTableWidgetItem(func))
                num += 1
            self.tables.append(widget)
            self.mainLayout.addWidget(widget)
            

        


class ServicePortSettingButton(QtGui.QPushButton):
    def __init__(self, name, profile):
        super(ServicePortSettingButton, self).__init__(name)
        self.profile = profile
        self.clicked.connect(self.pushSlot)
    def pushSlot(self):
        self.dialog = ServicePortOperationDialog(self.profile["class_list"])
        self.dialog.show()
        
        

class ServicePortTable(QtGui.QTableWidget):
    def __init__(self):
        super(ServicePortTable, self).__init__(5,3)
        horzHeaders=QtCore.QStringList()
        horzHeaders << u"名前" << u"変数名" << u"関数"
        self.setHorizontalHeaderLabels(horzHeaders)
        self.setSelectionMode(QtGui.QAbstractItemView.NoSelection)
    def list_update(self, ports):
        self.setRowCount(len(ports))
        num = 0
        for k,p in ports.items():
            if p.profile["portType"] == "ServicePort":
                data_variable = "self."+p.profile["data_variable"]
                self.setItem(num,0, QtGui.QTableWidgetItem(p.profile["portName"]))
                self.setItem(num,1, QtGui.QTableWidgetItem(data_variable))
                self.setCellWidget(num,2, ServicePortSettingButton(u"表示",p.profile))
                num += 1



