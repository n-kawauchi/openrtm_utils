#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file EV3SamplePy.py
 @brief EV3 Sample Component
 @date $Date$

 @author 宮本信彦
 n-miyamoto@aist.go.jp
 産業技術総合研究所　
 ロボットイノベーション研究センター　
 ロボットソフトウェアプラットフォーム研究チーム

 LGPL

"""
import sys

sys.path.append(".")

# Import RTM module
import RTC
import OpenRTM_aist


# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
ev3samplepy_spec = ["implementation_id", "EV3SamplePy", 
		 "type_name",         "EV3SamplePy", 
		 "description",       "EV3 Sample Component", 
		 "version",           "1.0.0", 
		 "vendor",            "AIST", 
		 "category",          "Controller", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 "conf.default.forward_velocity", "0.00",
		 "conf.default.rotate_velocity", "0.0",

         #"conf.default.__forward_velocity", "double.0.04",
         #"conf.default.__rotate_velocity", "double.0.2",

		 "conf.__widget__.forward_velocity", "slider.0.04",
		 "conf.__widget__.rotate_velocity", "slider.0.2",
		 "conf.__constraints__.forward_velocity", "-0.20<=x<=0.20",
		 "conf.__constraints__.rotate_velocity", "-3.1<=x<=3.1",

         "conf.__type__.forward_velocity", "double.0.04",
         "conf.__type__.rotate_velocity", "double.0.2",

		 ""]
# </rtc-template>

##
# @class EV3SamplePy
# @brief EV3 Sample Component
# 
# EV3サンプルコンポーネント
# 
# 
class EV3SamplePy(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief constructor
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		#タッチセンサのデータを格納する変数
		self._last_sensor_data = [False, False]

		touch_arg = [None] * ((len(RTC._d_TimedBooleanSeq) - 4) / 2)
		self._d_touch = RTC.TimedBooleanSeq(*touch_arg)
		"""
		タッチセンサの計測値
		 - Type: RTC::TimedBooleanSeq
		 - Number: 2
		"""
		self._touchIn = OpenRTM_aist.InPort("touch", self._d_touch)
		#target_velocity_arg = [None] * ((len(RTC._d_TimedVelocity2D) - 4) / 2)
		#self._d_target_velocity = RTC.TimedVelocity2D(*target_velocity_arg)
		self._d_target_velocity = RTC.TimedVelocity2D(RTC.Time(0,0),RTC.Velocity2D(0,0,0))
		"""
		目標速度
		 - Type: RTC::TimedVelocity2D
		 - Unit: m/s, rad/s
		"""
		self._target_velocityOut = OpenRTM_aist.OutPort("target_velocity", self._d_target_velocity)
		#sound_arg = [None] * ((len(RTC._d_TimedString) - 4) / 2)
		#self._d_sound = RTC.TimedString(*sound_arg)
		self._d_sound = RTC.TimedString(RTC.Time(0,0),[])
		"""
		音声
		 - Type: RTC::TimedString
		"""
		self._soundOut = OpenRTM_aist.OutPort("sound", self._d_sound)


		


		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		"""
		直進速度
		 - Name: forward_velocity forward_velocity
		 - DefaultValue: 0.0
		 - Unit: m/s
		 - Constraint: -0.2<=x<=0.2
		"""
		self._forward_velocity = [0.00]
		"""
		回転速度
		 - Name: rotate_velocity rotate_velocity
		 - DefaultValue: 0.0
		 - Unit: rad/s
		 - Constraint: -1.6<=x<=1.6
		"""
		self._rotate_velocity = [0.0]
		
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
		self.bindParameter("forward_velocity", self._forward_velocity, "0.0")
		self.bindParameter("rotate_velocity", self._rotate_velocity, "0.0")
		
		# Set InPort buffers
		self.addInPort("touch",self._touchIn)
		
		# Set OutPort buffers
		self.addOutPort("target_velocity",self._target_velocityOut)
		self.addOutPort("sound",self._soundOut)
		
		# Set service provider to Ports
		
		# Set service consumers to Ports
		
		# Set CORBA Service Ports
		
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
		self._last_sensor_data = [False, False]
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
		#停止する
		self._d_target_velocity.data.vx = 0
		self._d_target_velocity.data.vy = 0
		self._d_target_velocity.data.va = 0
		OpenRTM_aist.setTimestamp(self._d_target_velocity)
		self._target_velocityOut.write()
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
		#データを新規に受信した場合に、データをm_last_sensor_dataを格納する
		if self._touchIn.isNew():
			data = self._touchIn.read()
			if len(data.data) == 2:
				for i in range(2):
					#タッチセンサがOFFからONになった時に音を鳴らす
					if not self._last_sensor_data[i] and data.data[i]:
						self._d_sound.data = "beep"
						OpenRTM_aist.setTimestamp(self._d_sound)
						self._soundOut.write()
				self._last_sensor_data = data.data[:]


		#タッチセンサがONの時に前進しないようにする
		if self._forward_velocity[0] > 0:
			for d in self._last_sensor_data:
				if d:
					self._d_target_velocity.data.vx = 0
					self._d_target_velocity.data.vy = 0
					self._d_target_velocity.data.va = 0
					OpenRTM_aist.setTimestamp(self._d_target_velocity)
					self._target_velocityOut.write()
					return RTC.RTC_OK

		#コンフィギュレーションパラメータで設定した速度を送信する
		self._d_target_velocity.data.vx = self._forward_velocity[0]
		self._d_target_velocity.data.vy = 0
		self._d_target_velocity.data.va = self._rotate_velocity[0]
		OpenRTM_aist.setTimestamp(self._d_target_velocity)
		self._target_velocityOut.write()	
			
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
	



def EV3SamplePyInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=ev3samplepy_spec)
    manager.registerFactory(profile,
                            EV3SamplePy,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    EV3SamplePyInit(manager)

    # Create a component
    manager.createComponent("EV3SamplePy")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager()

if __name__ == "__main__":
	main()

