#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

##
#   @file RaspberryPiMouseGUIUtil.py
#   @brief ラズパイマウス操作GUI基本クラス群

from PyQt4 import QtCore, QtGui
import math





##
# @class Robot
# @brief ロボット管理クラス
#
class Robot:
	##
	# @brief コンストラクタ
	# @param self 
	# @param parent 親ウィジェット
	def __init__(self, parent):
		self.parent = parent
		self.robot_scale = 0.1
		self.robot_size = 0.1 * self.robot_scale
		self.createRobotDrawPath()
		self.pos_x = 0
		self.pos_y = 0
		self.rot = 0

		self.scale_pos_x = 0
		self.scale_pos_y = 0
		self.scale_rot = 0

		self.sensor_pos = []
		self.sensor_pos.append([self.robot_size/4.0, self.robot_size/2.0,0])
		self.sensor_pos.append([self.robot_size/2.0, self.robot_size/4.0,math.pi*45./180.])
		self.sensor_pos.append([self.robot_size/2.0, -self.robot_size/4.0,-math.pi*45./180.])
		self.sensor_pos.append([self.robot_size/4.0, -self.robot_size/2.0,0])
		
		
		

		self.sensor_draw = True

		self.distance_sensor_data = [0,0,0,0]


	##
	# @brief 姿勢の設定
	# @param self 
	# @param r 回転角度
	def setRotation(self, r):
		self.rot = -r
		self.setScalePosition()
		self.parent.update()

	##
	# @brief 位置、姿勢の設定
	# @param self
	# @param x X座標
	# @param y Y座標
	# @param r 回転角度	
	def setPosition(self, x, y, r):
		self.pos_x = x
		self.pos_y = -y
		self.rot = -r


		
		self.setScalePosition()
		
		
		self.parent.update()

	##
	# @brief 位置、姿勢を描画ウィンドウのスケールに変換
	# @param self
	def setScalePosition(self):
		width = self.parent.width()
		height = self.parent.height()
		
		gridscale = self.getScale()
		self.scale_pos_x = width/2.0+gridscale*100*self.robot_scale*self.pos_x
		self.scale_pos_y = height/2.0+gridscale*100*self.robot_scale*self.pos_y
		self.scale_rot = self.rot*180/math.pi

		x_upper_limit = float(width)*0.7
		y_upper_limit = float(height)*0.7
		x_under_limit = float(width)*0.3
		y_under_limit = float(height)*0.3
		if x_upper_limit <  self.scale_pos_x + self.parent.camera_position_x:
				self.parent.camera_position_x = -self.scale_pos_x + x_upper_limit
		elif x_under_limit >  self.scale_pos_x + self.parent.camera_position_x:
				self.parent.camera_position_x = -self.scale_pos_x + x_under_limit
		if y_upper_limit <  self.scale_pos_y + self.parent.camera_position_y:
				self.parent.camera_position_y = -self.scale_pos_y + y_upper_limit
		elif y_under_limit >  self.scale_pos_y + self.parent.camera_position_y:
				self.parent.camera_position_y = -self.scale_pos_y + y_under_limit

		#print x_upper_limit,self.scale_pos_x,self.parent.camera_position_x

		self.scale_pos_x += self.parent.camera_position_x
		self.scale_pos_y += self.parent.camera_position_y
		
		#print self.parent.camera_position_x, self.parent.camera_position_y

	##
	# @brief ロボットの描画パスを設定
	# @param self
	def createRobotDrawPath(self):
		
		self.rectPath = QtGui.QPainterPath()
		
		self.rectPath.moveTo(-self.robot_size/2.0, self.robot_size/2.0)

		self.rectPath.lineTo(-self.robot_size/2.0,  -self.robot_size/2.0)
		
		

		self.rectPath.lineTo(0, -self.robot_size/2.0)
		self.rectPath.arcTo(0,  -self.robot_size/2.0, self.robot_size/2.0, self.robot_size, 90, -180.0)
		#self.rectPath.lineTo(self.robot_size/2.0, self.robot_size/2.0)
		
		self.rectPath.closeSubpath()

	##
	# @brief 距離センサのデータを設定
	# @param self
	# @param data 距離センサの計測値
	def setDistanceSensorData(self, data):
		self.distance_sensor_data = data[:]
		self.parent.update()

	##
	# @brief 距離センサのデータを描画する
	# @param self
	def drawDistanceSensorData(self):
		self.sensor_draw = True
		if self.sensor_draw:
			gridscale = self.getScale()

			self.setScalePosition()

			painter = QtGui.QPainter(self.parent)
			#painter.setPen(QtCore.Qt.red)
			painter.setPen(QtGui.QPen(QtCore.Qt.red, 10,
					QtCore.Qt.SolidLine, QtCore.Qt.RoundCap, QtCore.Qt.RoundJoin))
			painter.setRenderHint(QtGui.QPainter.Antialiasing)
			painter.translate(self.scale_pos_x, self.scale_pos_y)
			painter.rotate(self.scale_rot)
			#painter.scale(gridscale, gridscale)
			
			scale = gridscale*100
			for i in range(0,len(self.sensor_pos)):
				if len(self.distance_sensor_data) > i:
					pos = self.sensor_pos[i]
					sensor_data = self.distance_sensor_data[i]*self.robot_scale
					painter.drawLine(pos[0]*scale,pos[1]*scale,(pos[0]+sensor_data*math.cos(pos[2]))*scale,(pos[1]+sensor_data*math.sin(pos[2]))*scale)
			self.sensor_draw = False


		else:
			self.sensor_draw = True
		
	##
	# @brief ロボットの描画サイズ取得
	# @param self
	# @return ロボットの描画サイズ
	def getScale(self):
		width = self.parent.width()
		#height = self.parent.height()
		
		line_num = self.parent.default_line_num/self.parent.scale
		return width/line_num

	##
	# @brief ロボットを描画する
	# @param self
	def drawRobot(self):
		#width = self.parent.width()
		#height = self.parent.height()

		
		gridscale = self.getScale()
		
		self.setScalePosition()
		
		painter = QtGui.QPainter(self.parent)
		painter.setRenderHint(QtGui.QPainter.Antialiasing)
		painter.translate(self.scale_pos_x, self.scale_pos_y)
		painter.rotate(self.scale_rot)
		painter.scale(gridscale*100, gridscale*100)
		
		painter.setPen(QtGui.QPen(QtCore.Qt.darkGray, 0.001,
				QtCore.Qt.SolidLine, QtCore.Qt.RoundCap, QtCore.Qt.RoundJoin))
		painter.setBrush(QtCore.Qt.darkGreen)
		painter.drawPath(self.rectPath)

		self.drawDistanceSensorData()


##
# @class RenderArea
# @brief 描画領域管理ウィジェット
#
class RenderArea(QtGui.QWidget):
	##
	# @brief コンストラクタ
	# @param self 
	# @param parent 親ウィジェット
	def __init__(self, parent=None):
		super(RenderArea, self).__init__(parent)
		
		self.camera_position_x = 0
		self.camera_position_y = 0

		
		self.default_line_num = 10
		

		self.scale = 1.0


		newFont = self.font()
		newFont.setPixelSize(12)
		self.setFont(newFont)
		fontMetrics = QtGui.QFontMetrics(newFont)
		self.xBoundingRect = fontMetrics.boundingRect("x")
		self.yBoundingRect = fontMetrics.boundingRect("y")

		

		self.robot = Robot(self)
		
		self.timer = QtCore.QTimer(self)
		self.timer.timeout.connect(self.update)
		self.timer.start(250)
		
	##
	# @brief 視点を設定
	# @param self 
	# @param x X座標
	# @param y Y座標
	def setCameraPosition(self, x, y):
		self.camera_position_x = x
		self.camera_position_y = y

	##
	# @brief ウィジェットの最小サイズ取得
	# @param self 
	# @return サイズ
	def minimumSizeHint(self):
		return QtCore.QSize(540, 540)


	##
	# @brief 描画イベント
	# @param self 
	# @param event イベント
	def paintEvent(self, event):
		painter = QtGui.QPainter(self)
		painter.setRenderHint(QtGui.QPainter.Antialiasing)
		painter.fillRect(event.rect(), QtGui.QBrush(QtCore.Qt.white))
		painter.setPen(QtCore.Qt.darkGreen)
		painter.setBrush(QtCore.Qt.NoBrush)
		
		
		self.drawGrid()
		self.drawAxis()
		self.robot.drawRobot()

	##
	# @brief 座標軸を描画する
	# @param self 
	def drawAxis(self):
		width = self.width()
		height = self.height()

		painter = QtGui.QPainter(self)
		painter.setRenderHint(QtGui.QPainter.Antialiasing)
		painter.scale(width/100.0, height/100.0)
		
		painter.setPen(QtGui.QPen(QtCore.Qt.blue, 3*self.scale,
				QtCore.Qt.SolidLine, QtCore.Qt.RoundCap, QtCore.Qt.RoundJoin))
		
		
		painter.drawLine(50 + self.camera_position_x*100.0/width, 0, 50 + self.camera_position_x*100.0/width, 100)
		painter.drawLine(0, 50 + self.camera_position_y*100.0/height, 100, 50 + self.camera_position_y*100.0/height)

		painter.drawText(90 + self.xBoundingRect.width() / 2,
			55 + self.xBoundingRect.height() / 2 + self.camera_position_y*100.0/width, "x")
		painter.drawText(55 - self.yBoundingRect.width() / 2 + self.camera_position_x*100.0/height,
			self.yBoundingRect.height() / 2, "y")


	##
	# @brief スケールを設定する
	# @param self
	# @param scale スケール
	def setScale(self, scale):
		
		self.scale = float(scale)/30.0
		
		
		self.update()

	

	##
	# @brief グリッドを描画する
	# @param self
	def drawGrid(self):
		
		line_num = float(self.default_line_num)/self.scale
		
		
		painter = QtGui.QPainter(self)
		painter.setPen(QtCore.Qt.black)
		width = self.width()
		height = self.height()
		line_space = float(width)/line_num
		upper_x_line_num = float(width/2 - self.camera_position_x)/width*line_num
		under_x_line_num = float(width/2 + self.camera_position_x)/width*line_num
		upper_y_line_num = float(height/2 - self.camera_position_y)/height*line_num
		under_y_line_num = float(height/2 + self.camera_position_y)/height*line_num
		
		#print upper_x_line_num,under_x_line_num,upper_y_line_num,under_y_line_num
		for i in range(0,int(upper_x_line_num)):
			painter.drawLine(line_space*i+width/2+self.camera_position_x, 0, line_space*i+width/2+self.camera_position_x, height)
		for i in range(1,int(under_x_line_num)+1):
			painter.drawLine(-line_space*i+width/2+self.camera_position_x, 0, -line_space*i+width/2+self.camera_position_x, height)
		for i in range(0,int(upper_y_line_num)):
			painter.drawLine(0, line_space*i+height/2+self.camera_position_y, width, line_space*i+height/2+self.camera_position_y)
		for i in range(1,int(under_y_line_num)+1):
			painter.drawLine(0, -line_space*i+height/2+self.camera_position_y, width, -line_space*i+height/2+self.camera_position_y)

			
				

		
		
##
# @class Window
# @brief メインウィンドウ
#
class Window(QtGui.QWidget):
	##
	# @brief コンストラクタ
	# @param self
	# @param comp RTC
	def __init__(self, comp):
		super(Window, self).__init__()
		self.setWindowTitle(u"ラズパイマウス操作GUI")

		self.comp = comp
		self.RenderArea = RenderArea()
		layout = QtGui.QHBoxLayout()
		layout.addWidget(self.RenderArea)

                self.setVelocityFlag = True

		sublayout = QtGui.QVBoxLayout()

		self.scale_slider = self.createScaleSlider()
		sublayout.addLayout(self.scale_slider)




		self.position_button = self.createPositionButton()
		sublayout.addWidget(self.position_button)


		self.control_slider = self.createControlSlider()
		sublayout.addWidget(self.control_slider)


		sublayout.addStretch(0)


		layout.addLayout(sublayout)
		

		self.setLayout(layout)


		

		

		self.timer = QtCore.QTimer(self)
		self.timer.timeout.connect(self.update_component)
		self.timer.start(100)
		#self.x = 0

	##
	# @brief RTCからロボットの現在位置などを取得する
	# @param self
	def update_component(self):
		x,y,r = self.comp.getCurrentPosition()
		
		self.RenderArea.robot.setPosition(x,y,r)
		#self.RenderArea.robot.setPosition(0.1,0,0)
		

		sensorDataPort = self.comp.getSensorDataPort()
		
		if sensorDataPort.isNew():
			convert_data = []
			data = sensorDataPort.read()
			for d in data.data:
				convert_data.append(self.convertSensorData(d))
			self.RenderArea.robot.setDistanceSensorData(convert_data)

		orientationDataPort = self.comp.getOrientationDataPort()
		if orientationDataPort.isNew():
			data = orientationDataPort.read()
			self.RenderArea.robot.setRotation(data.data.y)
			self.comp.setRotation(data.data.y)


                

		
	##
	# @brief 距離センサのデータを距離に変換する
	# @param self
	# @param data 変換前のデータ
	# @return 変換後のデータ
	def convertSensorData(self, data):
		if data > 792:
			return -0.0000166 * data + 0.033156146
		elif data > 525:
			return -0.0000375 * data + 0.0496629
		elif data > 373:
			return -0.0000658 * data + 0.0645395
		elif data > 299:
			return -0.0001351 * data + 0.0904054
		elif data > 260:
			return -0.0002564 * data + 0.1266667
		elif data > 222:
			return -0.0002632 * data + 0.1284211
		elif data > 181:
			return -0.0002439 * data + 0.1241463
		elif data > 135:
			return -0.0002174 * data + 0.1193478
		elif data > 100:
			return -0.0002857 * data + 0.1285714
		elif data > 81:
			return -0.0026316 * data + 0.3631579
		elif data > 36:
			return -0.0011111 * data + 0.2400000
		elif data > 17:
			return -0.0026316 * data + 0.2947368
		else:
			return -0.0500000 * data + 1.1000000
		

	##
	# @brief スピンボックスで設定した初期位置を反映させる
	# @param self
	def setPosition(self):
		x = self.x_spinBox.value()
		y = self.y_spinBox.value()
		r = self.r_spinBox.value()
		self.comp.resetDataListener()
		self.comp.setStartPosition(x, y, r)
		self.RenderArea.robot.setPosition(x, y, r)
		
	##
	# @brief 初期位置X座標設定スピンボックスのスロット
	# @param self
	# @param スピンボックスの値
	def setPosition_X(self, v):
		pass
		#self.setPosition()
	##
	# @brief 初期位置Y座標設定スピンボックスのスロット
	# @param self
	# @param スピンボックスの値
	def setPosition_Y(self, v):
		pass
		#self.setPosition()
	##
	# @brief 初期姿勢設定スピンボックスのスロット
	# @param self
	# @param スピンボックスの値
	def setPosition_R(self, v):
		pass
		#self.setPosition()

	##
	# @brief 初期位置設定スピンボックス、ボタンの作成
	# @param self
	def createPositionButton(self):
		
		groupbox = QtGui.QGroupBox(u"位置設定")
		layout = QtGui.QVBoxLayout()


		x_layout = QtGui.QHBoxLayout()
		
		x_label = QtGui.QLabel(u"X軸")
		x_layout.addWidget(x_label)

		self.x_spinBox = QtGui.QDoubleSpinBox()
		self.x_spinBox.setRange(-100, 100)
		self.x_spinBox.setSingleStep(0.1)
		self.x_spinBox.valueChanged.connect(self.setPosition_X)
		
		x_layout.addWidget(self.x_spinBox)
		layout.addLayout(x_layout)





		y_layout = QtGui.QHBoxLayout()
		
		y_label = QtGui.QLabel(u"Y軸")
		y_layout.addWidget(y_label)

		self.y_spinBox = QtGui.QDoubleSpinBox()
		self.y_spinBox.setRange(-100, 100)
		self.y_spinBox.setSingleStep(0.1)
		self.y_spinBox.valueChanged.connect(self.setPosition_Y)
		y_layout.addWidget(self.y_spinBox)
		layout.addLayout(y_layout)


		r_layout = QtGui.QHBoxLayout()
		
		r_label = QtGui.QLabel(u"姿勢")
		r_layout.addWidget(r_label)

		self.r_spinBox = QtGui.QDoubleSpinBox()
		self.r_spinBox.setRange(-100, 100)
		self.r_spinBox.setSingleStep(0.1)
		self.r_spinBox.valueChanged.connect(self.setPosition_R)
		r_layout.addWidget(self.r_spinBox)
		layout.addLayout(r_layout)


		
		button = QtGui.QPushButton(u"初期位置設定")
		layout.addWidget(button)
		button.clicked.connect(self.setPosition)

		
		groupbox.setLayout(layout)

		return groupbox

	##
	# @brief 目標一設定スライダーの値を反映させる
	# @param self
	def setTargetVelocity(self):
		if self.setVelocityFlag:
			vx = float(self.v_slider.value()-50)/50.0*0.2
			va = float(self.r_slider.value()-50)/50.0*math.pi
			self.comp.setTargetVelocity(vx,va)

	##
	# @brief 目標位置設定スライダーの値を反映させる
	# @param self
	def setTargetForwardVelocity(self, v):
		self.setTargetVelocity()
		
	##
	# @brief 目標位置設定スライダーのスロット
	# @param self
	# @param v 
	def setTargetTangentialVelocity(self, v):
		self.setTargetVelocity()

        

	##
	# @brief 前進ボタンのスロット
	# @param self 
	def setForwatd(self):
		self.setVelocityFlag = False
		self.v_slider.setValue(100)
		self.r_slider.setValue(50)
		self.setVelocityFlag = True
		self.setTargetVelocity()

	##
	# @brief 後退ボタンのスロット
	# @param self 
	def setBack(self):
		self.setVelocityFlag = False
		self.v_slider.setValue(0)
		self.r_slider.setValue(50)
		self.setVelocityFlag = True
		self.setTargetVelocity()

	##
	# @brief 右前進ボタンのスロット
	# @param self 
	def setRightForwatd(self):
		self.setVelocityFlag = False
		self.v_slider.setValue(100)
		self.r_slider.setValue(0)
		self.setVelocityFlag = True
		self.setTargetVelocity()

	##
	# @brief 左前進ボタンのスロット
	# @param self 
	def setLeftForwatd(self):
		self.setVelocityFlag = False
		self.v_slider.setValue(100)
		self.r_slider.setValue(100)
		self.setVelocityFlag = True
		self.setTargetVelocity()

	##
	# @brief 右旋回ボタンのスロット
	# @param self 
	def setRightRotate(self):
		self.setVelocityFlag = False
		self.v_slider.setValue(50)
		self.r_slider.setValue(0)
		self.setVelocityFlag = True
		self.setTargetVelocity()

	##
	# @brief 左旋回ボタンのスロット
	# @param self
	def setLeftRotate(self):
		self.setVelocityFlag = False
		self.v_slider.setValue(50)
		self.r_slider.setValue(100)
		self.setVelocityFlag = True
		self.setTargetVelocity()

	##
	# @brief 右後退ボタンのスロット
	# @param self 
	def setRightBack(self):
		self.setVelocityFlag = False
		self.v_slider.setValue(0)
		self.r_slider.setValue(100)
		self.setVelocityFlag = True
		self.setTargetVelocity()

	##
	# @brief 左後退ボタンのスロット
	# @param self 
	def setLeftBack(self):
		self.setVelocityFlag = False
		self.v_slider.setValue(0)
		self.r_slider.setValue(0)
		self.setVelocityFlag = True
		self.setTargetVelocity()

	##
	# @brief 停止ボタンのスロット
	# @param self 
	def setStop(self):
		self.setVelocityFlag = False
		self.v_slider.setValue(50)
		self.r_slider.setValue(50)
		self.setVelocityFlag = True
		self.setTargetVelocity()

	##
	# @brief 目標速度設定スライダー、ボタンの作成
	# @param self 
	def createControlSlider(self):
		groupbox = QtGui.QGroupBox(u"目標速度設定")

		layout = QtGui.QVBoxLayout()

		sublayout = QtGui.QHBoxLayout()


		v_layout = QtGui.QVBoxLayout()
		
		v_label = QtGui.QLabel(u"移動速度")
		v_layout.addWidget(v_label)
		
		self.v_slider = QtGui.QSlider(QtCore.Qt.Vertical)
		self.v_slider.setRange(0, 100)
		self.v_slider.setValue(50)
		self.v_slider.valueChanged.connect(self.setTargetTangentialVelocity)
		v_layout.addWidget(self.v_slider)
		sublayout.addLayout(v_layout)



		r_layout = QtGui.QVBoxLayout()
		
		r_label = QtGui.QLabel(u"回転速度")
		r_layout.addWidget(r_label)
		
		self.r_slider = QtGui.QSlider(QtCore.Qt.Vertical)
		self.r_slider.setRange(0, 100)
		self.r_slider.setValue(50)
		self.r_slider.valueChanged.connect(self.setTargetForwardVelocity)
		r_layout.addWidget(self.r_slider)
		sublayout.addLayout(r_layout)
		layout.addLayout(sublayout)

		gridLayout = QtGui.QGridLayout()

		forwordButton = QtGui.QPushButton(u"前進")
		gridLayout.addWidget(forwordButton, 0, 1)
		forwordButton.clicked.connect(self.setForwatd)

		backButton = QtGui.QPushButton(u"後退")
		gridLayout.addWidget(backButton, 2, 1)
		backButton.clicked.connect(self.setBack)

		rightforwordButton = QtGui.QPushButton(u"右前進")
		gridLayout.addWidget(rightforwordButton, 0, 2)
		rightforwordButton.clicked.connect(self.setRightForwatd)

		leftforwordButton = QtGui.QPushButton(u"左前進")
		gridLayout.addWidget(leftforwordButton, 0, 0)
		leftforwordButton.clicked.connect(self.setLeftForwatd)

		rightrotateButton = QtGui.QPushButton(u"右旋回")
		gridLayout.addWidget(rightrotateButton, 1, 2)
		rightrotateButton.clicked.connect(self.setRightRotate)

		leftrotateButton = QtGui.QPushButton(u"左旋回")
		gridLayout.addWidget(leftrotateButton, 1, 0)
		leftrotateButton.clicked.connect(self.setLeftRotate)

		rightbackButton = QtGui.QPushButton(u"右後退")
		gridLayout.addWidget(rightbackButton, 2, 2)
		rightbackButton.clicked.connect(self.setRightBack)

		leftbackButton = QtGui.QPushButton(u"左後退")
		gridLayout.addWidget(leftbackButton, 2, 0)
		leftbackButton.clicked.connect(self.setLeftBack)

		stopButton = QtGui.QPushButton(u"停止")
		gridLayout.addWidget(stopButton, 1, 1)
		stopButton.clicked.connect(self.setStop)
		
		layout.addLayout(gridLayout)

		groupbox.setLayout(layout)

		return groupbox



	##
	# @brief スケール設定スライダーの作成
	# @param self 
	def createScaleSlider(self):
		layout = QtGui.QHBoxLayout()
		
		label = QtGui.QLabel("Scale")
		layout.addWidget(label)
		
		slider = QtGui.QSlider(QtCore.Qt.Horizontal)
		slider.setRange(1, 100)
		
		slider.setSingleStep(1)
		slider.setPageStep(10)
		
		slider.setValue(30)
		
		
		slider.valueChanged.connect(self.RenderArea.setScale)
		layout.addWidget(slider)
		
		return layout
		



