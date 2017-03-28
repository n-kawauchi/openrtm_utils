#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file DataBaseOutPut.py
 @brief DataBaseOutPut
 @date $Date$


 LGPL

"""
import sys
import time
sys.path.append(".")

# Import RTM module
import RTC
import OpenRTM_aist

import DataBase_idl

# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
import DataBase, DataBase__POA


# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
databaseoutput_spec = ["implementation_id", "DataBaseOutPut", 
		 "type_name",         "DataBaseOutPut", 
		 "description",       "DataBaseOutPut", 
		 "version",           "1.0.0", 
		 "vendor",            "Miyamoto Nobuhiko", 
		 "category",          "Office", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 "conf.default.DataBase_Name", "None",
		 "conf.default.Table_Name", "None",
		 "conf.default.row_out", "None",
		 "conf.default.row_in", "None",
		 "conf.default.OutPortDataType", "TimedStringSeq",
		 "conf.default.InPortDataType", "TimedString",
		 "conf.default.conditional", "0",

		 "conf.__widget__.DataBase_Name", "text",
		 "conf.__widget__.Table_Name", "text",
		 "conf.__widget__.row_out", "text",
		 "conf.__widget__.row_in", "text",
		 "conf.__widget__.OutPortDataType", "radio",
		 "conf.__widget__.InPortDataType", "radio",
		 "conf.__widget__.conditional", "radio",
		 "conf.__constraints__.OutPortDataType", "(TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq,TimedCharSeq,TimedWCharSeq)",
		 "conf.__constraints__.InPortDataType", "(TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq,TimedCharSeq,TimedWCharSeq)",
		 "conf.__constraints__.conditional", "(0,1)",

         "conf.__type__.DataBase_Name", "string",
         "conf.__type__.Table_Name", "string",
         "conf.__type__.row_out", "string",
         "conf.__type__.row_in", "string",
         "conf.__type__.OutPortDataType", "string",
         "conf.__type__.InPortDataType", "string",
         "conf.__type__.conditional", "string",

		 ""]
# </rtc-template>

##
# @class DataBaseOutPut
# @brief DataBaseOutPut
# 
# DataBaseOutputComponentはコンフィギュレーションパラメータrow_inで指定したフィー
	ルドでDataInPortからの入力データと指定した条件に合致するデータを持つデータレコー
	ドの内、コンフィギュレーションパラメータrow_outで指定したフィールドのデータを出
	力するコンポーネントです。 http://ooortc.shime-saba.com/
# 
# 
class DataBaseOutPut(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief constructor
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		in_arg = [None] * ((len(RTC._d_TimedString) - 4) / 2)
		self._d_in = RTC.TimedString(*in_arg)
		"""
		条件式の左辺になります。
		条件式の右辺はコンフィギュレーションパラメータrow_inで設定したフィールドのデ
		ータです。
		 - Type: RTC::TimedString
		"""
		self._inIn = OpenRTM_aist.InPort("in", self._d_in)
		out_arg = [None] * ((len(RTC._d_TimedString) - 4) / 2)
		self._d_out = RTC.TimedString(*out_arg)
		"""
		抽出条件と合致したデータを全て配列に格納して出力します。
		 - Type: RTC::TimedString
		"""
		self._outOut = OpenRTM_aist.OutPort("out", self._d_out)

		"""
		"""
		self._DataBasePort = OpenRTM_aist.CorbaPort("DataBase")

		

		"""
		データベースへの接続、抽出、更新、追加、削除、テーブルの追加、削除のインター
		フェースです。
		"""
		self._database = OpenRTM_aist.CorbaConsumer(interfaceType=DataBase.mDataBase)

		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		"""
		接続するデータベースの登録名
		 - Name: DataBase_Name DataBase_Name
		 - DefaultValue: None
		"""
		self._DataBase_Name = ['None']
		"""
		データを抽出するテーブルの名前
		 - Name: Table_Name Table_Name
		 - DefaultValue: None
		"""
		self._Table_Name = ['None']
		"""
		出力するデータのフィールドの名前
		 - Name: row_out row_out
		 - DefaultValue: None
		"""
		self._row_out = ['None']
		"""
		入力データと条件に合致するか調べるフィールドの名前
		 - Name: row_in row_in
		 - DefaultValue: None
		"""
		self._row_in = ['None']
		"""
		outのデータ型
		 - Name: OutPortDataType OutPortDataType
		 - DefaultValue: TimedStringSeq
		"""
		self._OutPortDataType = ['TimedStringSeq']
		"""
		inのデータ型
		 - Name: InPortDataType InPortDataType
		 - DefaultValue: TimedString
		"""
		self._InPortDataType = ['TimedString']
		"""
		条件式
		 - Name: conditional conditional
		 - DefaultValue: 0
		"""
		self._conditional = ['0']
		
		# </rtc-template>


		 
	##
	#
	# The initialize action (on CREATED->ALIVE transition)
	# formaer rtc_init_entry() 
	# 
	# @return RTC::ReturnCode_t
	# 
	#
	def onInitialize(self):
		# Bind variables and configuration variable
		self.bindParameter("DataBase_Name", self._DataBase_Name, "None")
		self.bindParameter("Table_Name", self._Table_Name, "None")
		self.bindParameter("row_out", self._row_out, "None")
		self.bindParameter("row_in", self._row_in, "None")
		self.bindParameter("OutPortDataType", self._OutPortDataType, "TimedStringSeq")
		self.bindParameter("InPortDataType", self._InPortDataType, "TimedString")
		self.bindParameter("conditional", self._conditional, "0")
		
		# Set InPort buffers
		self.addInPort("in",self._inIn)
		
		# Set OutPort buffers
		self.addOutPort("out",self._outOut)
		
		# Set service provider to Ports
		
		# Set service consumers to Ports
		self._DataBasePort.registerConsumer("database", "DataBase::mDataBase", self._database)
		
		# Set CORBA Service Ports
		self.addPort(self._DataBasePort)
		
		return RTC.RTC_OK
	
		##
		# 
		# The finalize action (on ALIVE->END transition)
		# formaer rtc_exiting_entry()
		# 
		# @return RTC::ReturnCode_t
	
		# 
	def onFinalize(self):
	
		return RTC.RTC_OK
	
		##
		#
		# The startup action when ExecutionContext startup
		# former rtc_starting_entry()
		# 
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onStartup(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The shutdown action when ExecutionContext stop
		# former rtc_stopping_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onShutdown(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The activated action (Active state entry action)
		# former rtc_active_entry()
		#
		# @param ec_id target ExecutionContext Id
		# 
		# @return RTC::ReturnCode_t
		#
		#
	def onActivated(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The deactivated action (Active state exit action)
		# former rtc_active_exit()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onDeactivated(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The execution action that is invoked periodically
		# former rtc_active_do()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onExecute(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The aborting action when main logic error occurred.
		# former rtc_aborting_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onAborting(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The error action in ERROR state
		# former rtc_error_do()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onError(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The reset action that is invoked resetting
		# This is same but different the former rtc_init_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onReset(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The state update action that is invoked after onExecute() action
		# no corresponding operation exists in OpenRTm-aist-0.2.0
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#

		#
	def onStateUpdate(self, ec_id):
	
		return RTC.RTC_OK
	
		##
		#
		# The action that is invoked when execution context's rate is changed
		# no corresponding operation exists in OpenRTm-aist-0.2.0
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onRateChanged(self, ec_id):
	
		return RTC.RTC_OK
	



def DataBaseOutPutInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=databaseoutput_spec)
    manager.registerFactory(profile,
                            DataBaseOutPut,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    DataBaseOutPutInit(manager)

    # Create a component
    comp = manager.createComponent("DataBaseOutPut")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager()

if __name__ == "__main__":
	main()

