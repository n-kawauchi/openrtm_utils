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



import BaseTab
class addServicePortTab(BaseTab.BaseTab):

    def __init__(self, comp, viewWidget, listWidget, parent=None):
        super(addServicePortTab, self).__init__(parent)
        self.comp = comp
        self.viewWidget = viewWidget
        self.listWidget = listWidget

    

        
        self.portNameTextbox = self.addTextBox("portName",u"ポート名",[], "port")
        self.interfaceNameTextbox = self.addTextBox("interfaceName",u"インターフェース名",[], "")
        self.interfaceDirCombox = self.addCombox("interfaceDir",u"方向",[],["Required","Provided"], "Required")
        self.IDLTextbox = self.addTextBox("IDL",u"IDLファイル",[], "")
        self.IDLFileButton = QtGui.QPushButton(u"開く")
        self.IDLFileButton.clicked.connect(self.IDLFileButtonSlot)
        self.IDLTextbox["Layout"].addWidget(self.IDLFileButton)
        
        self.interfaceTypeCombox = self.addCombox("interfaceType",u"インターフェース型",[],[], "")
        self.IDLPathTextbox = self.addTextBox("IDLPath",u"IDLパス",[], "")
        self.IDLPathButton = QtGui.QPushButton(u"開く")
        self.IDLPathButton.clicked.connect(self.IDLPathButtonSlot)
        self.IDLPathTextbox["Layout"].addWidget(self.IDLPathButton)
        self.createButton = QtGui.QPushButton(u"作成")
        self.createButton.clicked.connect(self.createButtonSlot)
        self.subLayouts[-1].addWidget(self.createButton)
        self.mainLayout.addStretch()

    def IDLFileButtonSlot(self):
        fileName = QtGui.QFileDialog.getOpenFileName(self,u"開く","","IDL File (*.idl);;All Files (*)")
        if fileName.isEmpty():
            return ""
        filepath = str(fileName.toLocal8Bit())
        self.IDLTextbox["Widget"].setText(fileName)
        s = str(self.IDLTextbox["Widget"].text().toLocal8Bit())
        
        if self.comp is not None:
            self.interfaceTypeCombox["Widget"].clear()
            filename = str(self.IDLTextbox["Widget"].text().toLocal8Bit())
            filelist, classlist = self.comp.getServiceNameList(filename,"","")
            
            for k,v in classlist.items():
                self.interfaceTypeCombox["Widget"].addItem(k)
        

    def IDLPathButtonSlot(self):
        dirName = QtGui.QFileDialog.getExistingDirectory(self,u"開く")
        if dirName.isEmpty():
            return ""

        self.IDLPathTextbox["Widget"].setText(dirName)
        

    def searchPort(self, name):
        ports = self.comp.get_ports()
        for p in ports:
            pp = p.get_port_profile()
            pname = self.comp.getInstanceName()+"."+name
            if pp.name == pname:
                return p
        return None
    def addPort(self, profile):
        if self.comp is not None:
            
            if not self.searchPort(profile["portName"]):
                data_name, port_name, filelist, classlist, importlist = self.comp.setServicePort(profile["portName"], profile["interfaceName"], profile["interfaceDir"], profile["IDL"], profile["interfaceType"], profile["IDLPath"])

                profile["data_variable"] = data_name
                profile["port_variable"] = port_name
                profile["file_list"] = filelist
                profile["class_list"] = classlist
                profile["import_list"] = importlist
                
                self.viewWidget.renderWindow.addServicePort(profile)
                self.listWidget.list_update(self.viewWidget.renderWindow.ports)
            


    def createButtonSlot(self):
        profile = {}
        profile["portName"] = str(self.portNameTextbox["Widget"].text().toLocal8Bit())
        p = profile["portName"].replace(" ","")
        p = p.replace("\t","")
        if p == "":
             QtGui.QMessageBox.question(self, u"作成失敗", u"名前が入力されていません", QtGui.QMessageBox.Ok)
             return

        profile["interfaceName"] = str(self.interfaceNameTextbox["Widget"].text().toLocal8Bit())
        p = profile["interfaceName"].replace(" ","")
        p = p.replace("\t","")
        if p == "":
             QtGui.QMessageBox.question(self, u"作成失敗", u"インターフェース名が入力されていません", QtGui.QMessageBox.Ok)
             return

        profile["interfaceDir"] = str(self.interfaceDirCombox["Widget"].currentText().toLocal8Bit())
        
        profile["IDL"] = str(self.IDLTextbox["Widget"].text().toLocal8Bit())
        p = profile["IDL"].replace(" ","")
        p = p.replace("\t","")
        if p == "":
             QtGui.QMessageBox.question(self, u"作成失敗", u"IDLファイル名が入力されていません", QtGui.QMessageBox.Ok)
             return
        profile["interfaceType"] = str(self.interfaceTypeCombox["Widget"].currentText().toLocal8Bit())
        
        profile["IDLPath"] = str(self.IDLPathTextbox["Widget"].text().toLocal8Bit())

        self.addPort(profile)
