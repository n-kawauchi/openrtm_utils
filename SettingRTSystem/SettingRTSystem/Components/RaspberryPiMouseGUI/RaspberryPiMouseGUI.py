#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file RaspberryPiMouseGUI.py
 @brief Raspberry Pi Mouse GUI
 @date $Date$

 @author 宮本　信彦　n-miyamoto@aist.go.jp
 産業技術総合研究所　ロボットイノベーション研究センター
 ロボットソフトウエアプラットフォーム研究チーム

"""
import sys
import time
sys.path.append(".")

# Import RTM module
import RTC
import OpenRTM_aist
import threading

from PyQt4 import QtGui
import RaspberryPiMouseGUIUtil
import math




# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
raspberrypimousegui_spec = ["implementation_id", "RaspberryPiMouseGUI", 
		 "type_name",         "RaspberryPiMouseGUI", 
		 "description",       "Raspberry Pi Mouse GUI", 
		 "version",           "1.0.0", 
		 "vendor",            "AIST", 
		 "category",          "GUI", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 ""]



class DataListener(OpenRTM_aist.ConnectorDataListenerT):
	def __init__(self):
		self._mutex = threading.RLock()
		self.px = 0
		self.py = 0
		self.rot = 0

		self.start_px = 0
		self.start_py = 0
		self.start_rot = 0

		self.start_flag = False
		self.tm = time.time()
		
	def __del__(self):
		pass
	
	def getPositon(self):
		guard = OpenRTM_aist.ScopedLock(self._mutex)
		x = self.px
		y = self.py
		r = self.rot
		del guard
		return x,y,r
		
	def setStartPosition(self, x, y, r):
		guard = OpenRTM_aist.ScopedLock(self._mutex)
		self.px = x
		self.py = y
		self.rot = r
		self.start_px = x
		self.start_py = y
		self.start_rot = r
		del guard
		
	def setPosition(self, x, y, r):
		guard = OpenRTM_aist.ScopedLock(self._mutex)
		self.px = x
		self.py = y
		self.rot = r
		del guard

	def setRotation(self, r):
		guard = OpenRTM_aist.ScopedLock(self._mutex)
		self.rot = r
		del guard
		
	def reset(self):
		guard = OpenRTM_aist.ScopedLock(self._mutex)
		self.start_flag = False
		del guard
	def __call__(self, info, cdrdata):
		
		guard = OpenRTM_aist.ScopedLock(self._mutex)
		if self.start_flag:
			data = OpenRTM_aist.ConnectorDataListenerT.__call__(self, info, cdrdata, RTC.TimedVelocity2D(RTC.Time(0,0),RTC.Velocity2D(0,0,0)))

			tm = time.time()
			dt = tm - self.tm

			self.tm = tm

			if dt < 0.5:
				lx = data.data.vx*dt
				self.px = self.px + lx*math.cos(self.rot)
				self.py = self.py + lx*math.sin(self.rot)
				self.rot = self.rot + data.data.va*dt


                        #print self.px,self.py,self.rot

			else:
				self.tm = time.time()
				self.start_flag = True
		del guard

# </rtc-template>

##
# @class RaspberryPiMouseGUI
# @brief Raspberry Pi Mouse GUI
# 
# Raspberry Pi Mouse操作用GUI
# 
# 
class RaspberryPiMouseGUI(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief constructor
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		self._d_current_velocity = RTC.TimedVelocity2D(RTC.Time(0,0),RTC.Velocity2D(0,0,0))
		"""
		ラズパイマウスの現在の速度
		 - Type: RTC::TimedVelocity2D
		 - Unit: m/s,rad/s
		"""
		self._current_velocityIn = OpenRTM_aist.InPort("current_velocity", self._d_current_velocity)
		self.dataListener = DataListener()
		self._current_velocityIn.addConnectorDataListener(OpenRTM_aist.ConnectorDataListenerType.ON_BUFFER_WRITE,
										self.dataListener)				  
		self._d_distance_sensor = RTC.TimedShortSeq(RTC.Time(0,0),[])
		"""
		距離センサの計測値
		 - Type: RTC::TimedShortSeq
		"""
		self._distance_sensorIn = OpenRTM_aist.InPort("distance_sensor", self._d_distance_sensor)
		self._d_orientation = RTC.TimedOrientation3D(RTC.Time(0,0),RTC.Orientation3D(0,0,0))
		"""
		ラズパイマウスの姿勢
		 - Type: RTC::TimedOrientation3D
		 - Unit: rad
		"""
		self._orientationIn = OpenRTM_aist.InPort("orientation", self._d_orientation)
		self._d_current_pose = RTC.TimedPose2D(RTC.Time(0,0),0)
		"""
		ラズパイマウスの現在の位置、姿勢
		 - Type: RTC::TimedPose2D
		 - Unit: m,rad
		"""
		self._current_poseIn = OpenRTM_aist.InPort("current_pose", self._d_current_pose)
		self._d_target_velocity = RTC.TimedVelocity2D(RTC.Time(0,0),RTC.Velocity2D(0,0,0))
		"""
		目標速度
		 - Type: RTC::TimedVelocity2D
		 - Unit: m/s、rad/s
		"""
		self._target_velocityOut = OpenRTM_aist.OutPort("target_velocity", self._d_target_velocity)
		self._d_target_position = RTC.TimedPoint2D(RTC.Time(0,0),RTC.Point2D(0,0))
		"""
		目標位置
		 - Type: RTC::TimedPoint2D
		"""
		self._target_positionOut = OpenRTM_aist.OutPort("target_position", self._d_target_position)
		self._d_update_pose = RTC.TimedPose2D(RTC.Time(0,0),RTC.Pose2D(RTC.Point2D(0,0),0))
		"""
		ラズパイマウスの位置を設定する
		 - Type: RTC::TimedPose2D
		 - Unit: m, rad
		"""
		self._update_poseOut = OpenRTM_aist.OutPort("update_pose", self._d_update_pose)





		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		
		# </rtc-template>

	def setTargetVelocity(self, v, r):
		self._d_target_velocity.data.vx = v
		self._d_target_velocity.data.vy = 0
		self._d_target_velocity.data.va = r
		OpenRTM_aist.setTimestamp(self._d_target_velocity)
		
		self._target_velocityOut.write()

	def setRotation(self, r):
		self.dataListener.setRotation(r)

	def getCurrentPosition(self):
		
		if self._current_poseIn.isNew():
			data = self._current_poseIn.read()
			#print data.data.position.x, data.data.position.y, data.data.heading
			self.dataListener.setPosition(data.data.position.x, data.data.position.y, data.data.heading)
		return self.dataListener.getPositon()
	
	
	def setStartPosition(self, x, y, r):
		self._d_update_pose.data.position.x = x
		self._d_update_pose.data.position.y = y
		self._d_update_pose.data.heading = r
		self._update_poseOut.write()
		
		self.dataListener.setStartPosition(x, y, r)

	def getSensorDataPort(self):
		return self._distance_sensorIn
	
	def getOrientationDataPort(self):
		return self._orientationIn



        def resetDataListener(self):
                self.dataListener.reset()



		
			

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
		self.addInPort("current_velocity",self._current_velocityIn)
		self.addInPort("current_pose",self._current_poseIn)
		self.addInPort("distance_sensor",self._distance_sensorIn)
		self.addInPort("orientation",self._orientationIn)
		
		
		# Set OutPort buffers
		self.addOutPort("target_velocity",self._target_velocityOut)
		self.addOutPort("target_position",self._target_positionOut)
		self.addOutPort("update_pose",self._update_poseOut)
		
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
		
		x = self.dataListener.start_px
		y = self.dataListener.start_py
		r = self.dataListener.start_rot
		self.setStartPosition(x,y,r)
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
	



def RaspberryPiMouseGUIInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=raspberrypimousegui_spec)
    manager.registerFactory(profile,
                            RaspberryPiMouseGUI,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    RaspberryPiMouseGUIInit(manager)

    # Create a component
    manager.createComponent("RaspberryPiMouseGUI")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	#mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager(True)


	RaspberryPiMouseGUIInit(mgr)
	comp = mgr.createComponent("RaspberryPiMouseGUI")
	
	
	app = QtGui.QApplication(sys.argv)
	window = RaspberryPiMouseGUIUtil.Window(comp)
	window.show()
	sys.exit(app.exec_())

if __name__ == "__main__":
	main()

