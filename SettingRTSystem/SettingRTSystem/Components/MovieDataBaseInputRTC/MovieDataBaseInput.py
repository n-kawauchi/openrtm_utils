#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file MovieDataBaseInput.py
 @brief MovieData Input RTC
 @date $Date$


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
moviedatabaseinput_spec = ["implementation_id", "MovieDataBaseInput", 
		 "type_name",         "MovieDataBaseInput", 
		 "description",       "MovieData Input RTC", 
		 "version",           "1.0.0", 
		 "vendor",            "Miyamoto Nobuhiko", 
		 "category",          "Office", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
                 "conf.default.captureRTCPath", "localhost\\CapturePresentation0",
                 "conf.default.name", "Presentation1",
                 "conf.default.cameraImage", "image",
                 "conf.default.presentationRTCPath", "None",
                 "conf.default.slideNumberIn", "SlideNumberIn",
                 "conf.default.effectNumberIn", "EffectNumberIn",
                 "conf.default.pen", "Pen",
		 ""]
# </rtc-template>

##
# @class MovieDataBaseInput
# @brief MovieData Input RTC
# 
# 
class MovieDataBaseInput(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief constructor
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)


		"""
		"""
		self._DataBasePort = OpenRTM_aist.CorbaPort("DataBase")

		

		"""
		"""
		self._database = OpenRTM_aist.CorbaConsumer(interfaceType=DataBase.mDataBase)

                self.m_captureRTCPath = ["localhost\\CapturePresentation0"]
                self.m_name = ["Presentation1"]
                self.m_cameraImage = ["image"]
                self.m_presentationRTCPath = ["None"]
                self.m_slideNumberIn = ["SlideNumberIn"]
                self.m_effectNumberIn = ["EffectNumberIn"]
                self.m_pen = ["Pen"]
		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		
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
		
		# Set InPort buffers
		
		# Set OutPort buffers
		
		# Set service provider to Ports
		
		# Set service consumers to Ports
		self._DataBasePort.registerConsumer("database", "DataBase::mDataBase", self._database)
		
		# Set CORBA Service Ports
		self.addPort(self._DataBasePort)

		self.bindParameter("captureRTCPath", self.m_captureRTCPath, "localhost\\CapturePresentation0")
                self.bindParameter("name", self.m_name, "Presentation1")
                self.bindParameter("cameraImage", self.m_cameraImage, "image")
                self.bindParameter("presentationRTCPath", self.m_presentationRTCPath, "None")
                self.bindParameter("slideNumberIn", self.m_slideNumberIn, "SlideNumberIn")
                self.bindParameter("effectNumberIn", self.m_effectNumberIn, "EffectNumberIn")
                self.bindParameter("pen", self.m_pen, "Pen")


                
		
		return RTC.RTC_OK
	
	#	##
	#	# 
	#	# The finalize action (on ALIVE->END transition)
	#	# formaer rtc_exiting_entry()
	#	# 
	#	# @return RTC::ReturnCode_t
	#
	#	# 
	#def onFinalize(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The startup action when ExecutionContext startup
	#	# former rtc_starting_entry()
	#	# 
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onStartup(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The shutdown action when ExecutionContext stop
	#	# former rtc_stopping_entry()
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onShutdown(self, ec_id):
	#
	#	return RTC.RTC_OK
	
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
                try:
                        
                        f1 = self._database._ptr().setConnection("Presentation","","")
                        
                        if f1 == False:
                                return RTC.RTC_ERROR
                        
                        sql = "INSERT INTO LIST(NAME, CAPTURERTCPATH, CAMERAIMAGE, PRESENTATIONRTC, SLIDENUMBERIN, EFFECTNUMBERIN,PEN) VALUES("
                        sql += "'"
                        sql += self.m_name[0]
                        sql += "', '"
                        sql += self.m_captureRTCPath[0]
                        sql += "', '"
                        sql += self.m_cameraImage[0]
                        sql += "', '"
                        sql += self.m_presentationRTCPath[0]
                        sql += "', '"
                        sql += self.m_slideNumberIn[0]
                        sql += "', '"
                        sql += self.m_effectNumberIn[0]
                        sql += "', '"
                        sql += self.m_pen[0]
                        sql += "'"
                        sql += ")"
                        
                        
                        f2 = self._database._ptr().executeUpdate("Presentation", sql)
                        
                        if f2 == False:
                                return RTC.RTC_ERROR

                except:
                        return RTC.RTC_ERROR
                
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
                try:
                        sql = "DELETE FROM LIST WHERE NAME = "
                        sql += "'"
                        sql += self.m_name[0]
                        sql += "'"
                        
                        f2 = self._database._ptr().executeUpdate("Presentation", sql)
                        
                        if f2 == False:
                                return RTC.RTC_ERROR

                except:
                        return RTC.RTC_ERROR
                
		return RTC.RTC_OK
	
	#	##
	#	#
	#	# The execution action that is invoked periodically
	#	# former rtc_active_do()
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onExecute(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The aborting action when main logic error occurred.
	#	# former rtc_aborting_entry()
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onAborting(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The error action in ERROR state
	#	# former rtc_error_do()
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onError(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The reset action that is invoked resetting
	#	# This is same but different the former rtc_init_entry()
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onReset(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The state update action that is invoked after onExecute() action
	#	# no corresponding operation exists in OpenRTm-aist-0.2.0
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#

	#	#
	#def onStateUpdate(self, ec_id):
	#
	#	return RTC.RTC_OK
	
	#	##
	#	#
	#	# The action that is invoked when execution context's rate is changed
	#	# no corresponding operation exists in OpenRTm-aist-0.2.0
	#	#
	#	# @param ec_id target ExecutionContext Id
	#	#
	#	# @return RTC::ReturnCode_t
	#	#
	#	#
	#def onRateChanged(self, ec_id):
	#
	#	return RTC.RTC_OK
	



def MovieDataBaseInputInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=moviedatabaseinput_spec)
    manager.registerFactory(profile,
                            MovieDataBaseInput,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    MovieDataBaseInputInit(manager)

    # Create a component
    comp = manager.createComponent("MovieDataBaseInput")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager()

if __name__ == "__main__":
	main()

