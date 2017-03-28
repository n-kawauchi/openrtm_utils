#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file RasPiMouseSamplePy.py
 @brief Raspberry Pi Mouse Sample
 @date $Date$

 @author 宮本　信彦　n-miyamoto@aist.go.jp
 産業技術総合研究所　ロボットイノベーション研究センター
 ロボットソフトウエアプラットフォーム研究チーム

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
raspimousesamplepy_spec = ["implementation_id", "RasPiMouseSamplePy", 
		 "type_name",         "RasPiMouseSamplePy", 
		 "description",       "Raspberry Pi Mouse Sample", 
		 "version",           "1.0.0", 
		 "vendor",            "AIST", 
		 "category",          "TEST", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 "conf.default.forward_velocity", "0.00",
		 "conf.default.rotate_velocity", "0.0",
		 "conf.default.stop_distance", "300",
		 "conf.__widget__.forward_velocity", "slider.0.02",
		 "conf.__widget__.rotate_velocity", "slider.0.2",
		 "conf.__widget__.stop_distance", "text",
		 "conf.__constraints__.forward_velocity", "-0.20<=x<=0.20",
		 "conf.__constraints__.rotate_velocity", "-1.6<=x<=1.6",
		 ""]
# </rtc-template>

##
# @class RasPiMouseSamplePy
# @brief Raspberry Pi Mouse Sample
# 
# Raspberry Pi Mouseの制御RTCのサンプルです
# 
# 
class RasPiMouseSamplePy(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief constructor
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		#センサのデータを格納する変数
		self._last_sensor_data = [0, 0, 0, 0]



		self._d_distance_sensor = RTC.TimedShortSeq(RTC.Time(0,0),[])
		"""
		距離センサの計測値を入力します
		 - Type: RTC::TimedShortSeq
		 - Number: 4
		"""
		self._distance_sensorIn = OpenRTM_aist.InPort("distance_sensor", self._d_distance_sensor)
		self._d_target_velocity = RTC.TimedVelocity2D(RTC.Time(0,0),RTC.Velocity2D(0,0,0))
		"""
		目標速度
		 - Type: RTC::TimedVelocity2D
		 - Unit: m/s, rad/s
		"""
		self._target_velocityOut = OpenRTM_aist.OutPort("target_velocity", self._d_target_velocity)


		


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
		"""
		距離センサで物体を検知した場合に、前進しないようにする距離センサの計測値
		 - Name: stop_distance stop_distance
		 - DefaultValue: 300
		"""
		self._stop_distance = [300]
		
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
		self.bindParameter("forward_velocity", self._forward_velocity, "0")
		self.bindParameter("rotate_velocity", self._rotate_velocity, "0")
		self.bindParameter("stop_distance", self._stop_distance, "300")
		
		# Set InPort buffers
		self.addInPort("distance_sensor",self._distance_sensorIn)
		
		# Set OutPort buffers
		self.addOutPort("target_velocity",self._target_velocityOut)
		
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
		self._last_sensor_data = [0, 0, 0, 0]
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
		if self._distance_sensorIn.isNew():
			data = self._distance_sensorIn.read()
			if len(data.data) == 4:
				self._last_sensor_data = data.data[:]

		#センサの計測値がstop_distance以上の時に前進しないようにする
		if self._forward_velocity[0] > 0:
			for d in self._last_sensor_data:
				if d > self._stop_distance[0]:
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
	



def RasPiMouseSamplePyInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=raspimousesamplepy_spec)
    manager.registerFactory(profile,
                            RasPiMouseSamplePy,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    RasPiMouseSamplePyInit(manager)

    # Create a component
    manager.createComponent("RasPiMouseSamplePy")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager()

if __name__ == "__main__":
	main()

