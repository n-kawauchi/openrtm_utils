// -*- C++ -*-
/*!
 * @file  Foot_Position_Controller.h
 * @brief Control the position of the foot
 * @date  $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#ifndef FOOT_POSITION_CONTROLLER_H
#define FOOT_POSITION_CONTROLLER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>



// Service implementation headers
// <rtc-template block="service_impl_h">
#include "LeggedRobotSVC_impl.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "ServoControllerServiceStub.h"
#include "LeggedRobotStub.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include "Four_legged_Robot.h"

using namespace RTC;

/*!
 * @class Foot_Position_Controller
 * @brief Control the position of the foot
 *
 */
class Foot_Position_Controller
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Foot_Position_Controller(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Foot_Position_Controller();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">

  // </rtc-template>
  /*!
   * RCサーボのオフセット(左前0番目)
   * - Name: offset_lf0 offset_lf0
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_lf0;
  /*!
   * RCサーボのオフセット(左前1番目)
   * - Name: offset_lf1 offset_lf1
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_lf1;
  /*!
   * RCサーボのオフセット(左前2番目)
   * - Name: offset_lf2 offset_lf2
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_lf2;
  /*!
   * RCサーボのオフセット(左後0番目)
   * - Name: offset_lb0 offset_lb0
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_lb0;
  /*!
   * RCサーボのオフセット(左後1番目)
   * - Name: offset_lb1 offset_lb1
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_lb1;
  /*!
   * RCサーボのオフセット(左後2番目)
   * - Name: offset_lb2 offset_lb2
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_lb2;
  /*!
   * RCサーボのオフセット(右後0番目)
   * - Name: offset_rb0 offset_rb0
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_rb0;
  /*!
   * RCサーボのオフセット(右後1番目)
   * - Name: offset_rb1 offset_rb1
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_rb1;
  /*!
   * RCサーボのオフセット(右後2番目)
   * - Name: offset_rb2 offset_rb2
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_rb2;
  /*!
   * RCサーボのオフセット(右前0番目)
   * - Name: offset_rf0 offset_rf0
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_rf0;
  /*!
   * RCサーボのオフセット(右前1番目)
   * - Name: offset_rf1 offset_rf1
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_rf1;
  /*!
   * RCサーボのオフセット(右前2番目)
   * - Name: offset_rf2 offset_rf2
   * - DefaultValue: 0
   * - Unit: rad
   */
  double m_offset_rf2;
  /*!
  * ボディの長さ
  * - Name: body_length body_length
  * - DefaultValue: 0.07
  * - Unit: m
  */
  double m_body_length;
  /*!
  * ボディの幅
  * - Name: body_width body_width
  * - DefaultValue: 0.07
  * - Unit: m
  */
  double m_body_width;
  /*!
  * ボディの高さ
  * - Name: body_height body_height
  * - DefaultValue: 0.005
  * - Unit: m
  */
  double m_body_height;
  /*!
  * リンク0の長さ
  * - Name: leg0_length leg0_length
  * - DefaultValue: 0.02
  * - Unit: m
  */
  double m_leg0_length;
  /*!
  * リンク0の高さ
  * - Name: leg0_height leg0_height
  * - DefaultValue: 0.025
  * - Unit: m
  */
  double m_leg0_height;
  /*!
  * リンク1の長さ
  * - Name: leg1_length leg1_length
  * - DefaultValue: 0.055
  * - Unit: m
  */
  double m_leg1_length;
  /*!
  * リンク2の長さ
  * - Name: leg2_length leg2_length
  * - DefaultValue: 0.08
  * - Unit: m
  */
  double m_leg2_length;
  /*!
  * リンク0根元のオフセット(X)
  * - Name: leg0_offset_x leg0_offset_x
  * - DefaultValue: 0
  * - Unit: 0
  */
  double m_leg0_offset_x;
  /*!
  * リンク0根元のオフセット(Y)
  * - Name: leg0_offset_y leg0_offset_y
  * - DefaultValue: 0
  * - Unit: m
  */
  double m_leg0_offset_y;
  /*!
  * リンク0根元のオフセット(Z)
  * - Name: leg0_offset_z leg0_offset_z
  * - DefaultValue: 0
  * - Unit: m
  */
  double m_leg0_offset_z;
  /*!
  * リンク1根元のオフセット(X)
  * - Name: leg1_offset_x leg1_offset_x
  * - DefaultValue: 0
  * - Unit: m
  */
  double m_leg1_offset_x;
  /*!
  * リンク1根元のオフセット(Y)
  * - Name: leg1_offset_y leg1_offset_y
  * - DefaultValue: 0
  * - Unit: m
  */
  double m_leg1_offset_y;
  /*!
  * リンク1根元のオフセット(Z)
  * - Name: leg1_offset_z leg1_offset_z
  * - DefaultValue: 0
  * - Unit: m
  */
  double m_leg1_offset_z;
  /*!
  * リンク2根元のオフセット(X)
  * - Name: leg2_offset_x leg2_offset_x
  * - DefaultValue: 0
  * - Unit: m
  */
  double m_leg2_offset_x;
  /*!
  * リンク2根元のオフセット(Y)
  * - Name: leg2_offset_y leg2_offset_y
  * - DefaultValue: 0
  * - Unit: m
  */
  double m_leg2_offset_y;
  /*!
  * リンク2根元のオフセット(Z)
  * - Name: leg2_offset_z leg2_offset_z
  * - DefaultValue: 0
  * - Unit: m
  */
  double m_leg2_offset_z;
  /*!
  * RCサーボの回転方向(左前0番目)
  * - Name: dir_lf0 dir_lf0
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_lf0;
  /*!
  * RCサーボの回転方向(左前1番目)
  * - Name: dir_lf1 dir_lf1
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_lf1;
  /*!
  * RCサーボの回転方向(左前2番目)
  * - Name: dir_lf2 dir_lf2
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_lf2;
  /*!
  * RCサーボの回転方向(左後0番目)
  * - Name: dir_lb0 dir_lb0
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_lb0;
  /*!
  * RCサーボの回転方向(左後0番目)
  * - Name: dir_lb1 dir_lb1
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_lb1;
  /*!
  * RCサーボの回転方向(左後0番目)
  * - Name: dir_lb2 dir_lb2
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_lb2;
  /*!
  * RCサーボの回転方向(右後0番目)
  * - Name: dir_rb0 dir_rb0
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_rb0;
  /*!
  * RCサーボの回転方向(右後0番目)
  * - Name: dir_rb1 dir_rb1
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_rb1;
  /*!
  * RCサーボの回転方向(右後2番目)
  * - Name: dir_lf2 dir_rb2
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_rb2;
  /*!
  * RCサーボの回転方向(右前0番目)
  * - Name: dir_rf0 dir_rf0
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_rf0;
  /*!
  * RCサーボの回転方向(右前1番目)
  * - Name: dir_lf0 dir_rf1
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_rf1;
  /*!
  * RCサーボの回転方向(右前2番目)
  * - Name: dir_rf2 dir_rf2
  * - DefaultValue: 1
  * - Constraint: (1,-1)
  */
  int m_dir_rf2;
  /*!
  * 関節0の角度限界値上限
  * - Name: upper_limit_motor0 upper_limit_motor0
  * - DefaultValue: 1.571796
  * - Unit: rad
  */
  double m_upper_limit_motor0;
  /*!
  * 関節1の角度限界値上限
  * - Name: upper_limit_motor1 upper_limit_motor1
  * - DefaultValue: 1.571796
  * - Unit: rad
  */
  double m_upper_limit_motor1;
  /*!
  * 関節2の角度限界値上限
  * - Name: upper_limit_motor2 upper_limit_motor2
  * - DefaultValue: 1.571796
  * - Unit: rad
  */
  double m_upper_limit_motor2;
  /*!
  * 関節0の角度限界値下限
  * - Name: lower_limit_motor0 lower_limit_motor0
  * - DefaultValue: -1.571796
  * - Unit: rad
  */
  double m_lower_limit_motor0;
  /*!
  * 関節1の角度限界値下限
  * - Name: lower_limit_motor1 lower_limit_motor1
  * - DefaultValue: -1.571796
  * - Unit: rad
  */
  double m_lower_limit_motor1;
  /*!
  * 関節2の角度限界値下限
  * - Name: lower_limit_motor2 lower_limit_motor2
  * - DefaultValue: -1.571796
  * - Unit: rad
  */
  double m_lower_limit_motor2;
  // DataInPort declaration
  // <rtc-template block="inport_declare">
  WalkingRobot::LeggedRobot m_Trajectory;
  /*!
   * 足先軌道
   * - Type: RTC::LeggedRobot
   */
  InPort<WalkingRobot::LeggedRobot> m_TrajectoryIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedDoubleSeq m_motor_pos;
  /*!
   * RCサーボの角度
   * - Type: RTC::TimedDoubleSeq
   * - Number: 12
   * - Unit: rad
   */
  OutPort<RTC::TimedDoubleSeq> m_motor_posOut;
  RTC::TimedDoubleSeq m_motor_pos_0;
  /*!
  * 脚0のRCサーボの角度
  * - Type: RTC::TimedDouble
  * - Number: 3
  * - Unit: rad
  */
  OutPort<RTC::TimedDoubleSeq> m_motor_pos_0Out;
  RTC::TimedDoubleSeq m_motor_pos_1;
  /*!
  * 脚1のRCサーボの角度
  * - Type: RTC::TimedDoubleSeq
  * - Number: 3
  * - Unit: rad
  */
  OutPort<RTC::TimedDoubleSeq> m_motor_pos_1Out;
  RTC::TimedDoubleSeq m_motor_pos_2;
  /*!
  * 脚1のRCサーボの角度
  * - Type: RTC::TimedDoubleSeq
  * - Number: 3
  * - Unit: rad
  */
  OutPort<RTC::TimedDoubleSeq> m_motor_pos_2Out;
  RTC::TimedDoubleSeq m_motor_pos_3;
  /*!
  * 脚3のRCサーボの角度
  * - Type: RTC::TimedDoubleSeq
  * - Number: 3
  * - Unit: rad
  */
  OutPort<RTC::TimedDoubleSeq> m_motor_pos_3Out;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">

  /*!
  * ロボット操作コマンド
  */
  RTC::CorbaPort m_LeggedRobotCommonInterface_RobotPort;
  /*!
   * サーボ操作コマンド
   */
  RTC::CorbaPort m_ServoControllerServicePort;

  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">

  /*!
  * ロボット操作コマンド
  */
  WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl m_LeggedRobotCommonInterface_Robot;

  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  /*!
   * サーボ操作コマンド
   */
  RTC::CorbaConsumer<OpenHRP::ServoControllerService> m_ServoControllerService;
  
  // </rtc-template>

 private:
	 Four_legged_Robot robot;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void Foot_Position_ControllerInit(RTC::Manager* manager);
};

#endif // FOOT_POSITION_CONTROLLER_H
