// -*- C++ -*-
/*!
 * @file  Intermittent_Crawl_Gait_Controller.h
 * @brief Intermittent Crawl Walk Controller Component
 * @date  $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#ifndef Intermittent_Crawl_Gait_Controller_H
#define Intermittent_Crawl_Gait_Controller_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>
#include "LeggedRobotStub.h"

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

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
 * @class Intermittent_Crawl_Gait_Controller
 * @brief Intermittent Crawl Walk Controller Component
 *
 * 間歇クロール歩容により四足歩行ロボットを制御するためのコンポーネ
 * ント
 *
 */
class Intermittent_Crawl_Gait_Controller
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Intermittent_Crawl_Gait_Controller(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Intermittent_Crawl_Gait_Controller();

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
	 /*!
	 * シミュレーションのステップ時間
	 * 0以下の場合は実行周期
	 * - Name: sampling_time sampling_time
	 * - DefaultValue: -1
	 * - Unit: s
	 */
	 double m_sampling_time;
	 /*!
	 * 歩幅
	 * - Name: stride stride
	 * - DefaultValue: 0.08
	 * - Unit: m
	 */
	 double m_stride;
	 /*!
	 * 脚先基準位置(X軸)
	 * - Name: offset_center_pos_x center_pos_x
	 * - DefaultValue: 0.077
	 * - Unit: m
	 */
	 double m_center_pos_x;
	 /*!
	 * 脚先基準位置(Y軸)
	 * - Name: offset_center_pos_y center_pos_y
	 * - DefaultValue: 0.096
	 * - Unit: m
	 */
	 double m_center_pos_y;
	 /*!
	 * 脚先基準位置(Z軸)
	 * - Name: offset_center_pos_z center_pos_z
	 * - DefaultValue: -0.079
	 * - Unit: m
	 */
	 double m_center_pos_z;
	 /*!
	 * 最低安定余裕
	 * - Name: min_stability_margin min_stability_margin
	 * - DefaultValue: 0.01
	 * - Unit: m
	 */
	 double m_min_stability_margin;
	 /*!
	 * 横方向への移動距離
	 * - Name: side_move_distance side_move_distance
	 * - DefaultValue: 0.03
	 * - Unit: m
	 */
	 double m_side_move_distance;
	 /*!
	 * 遊脚高さ
	 * - Name: lift_height lift_height
	 * - DefaultValue: 0.05
	 * - Unit: m
	 */
	 double m_lift_height;
	 /*!
	 * 脚基準位置からみた可動範囲上限(X軸)
	 * - Name: upper_limit_x upper_limit_x
	 * - DefaultValue: 0.04
	 * - Unit: m
	 */
	 double m_upper_limit_x;
	 /*!
	 * 脚基準位置からみた可動範囲上限(Y軸)
	 * - Name: upper_limit_y upper_limit_y
	 * - DefaultValue: 0.04
	 * - Unit: m
	 */
	 double m_upper_limit_y;
	 /*!
	 * 脚基準位置からみた可動範囲上限(Z軸)
	 * - Name: upper_limit_z upper_limit_z
	 * - DefaultValue: 0.04
	 * - Unit: m
	 */
	 double m_upper_limit_z;
	 /*!
	 * 脚基準位置からみた可動範囲下限(X軸)
	 * - Name: lower_limit_x lower_limit_x
	 * - DefaultValue: -0.04
	 * - Unit: m
	 */
	 double m_lower_limit_x;
	 /*!
	 * 脚基準位置からみた可動範囲下限(Y軸)
	 * - Name: lower_limit_y lower_limit_y
	 * - DefaultValue: -0.04
	 * - Unit: m
	 */
	 double m_lower_limit_y;
	 /*!
	 * 脚基準位置からみた可動範囲下限(Z軸)
	 * - Name: lower_limit_z lower_limit_z
	 * - DefaultValue: -0.04
	 * - Unit: m
	 */
	 double m_lower_limit_z;
	 /*!
	 * 脚の可動範囲を制御時に考慮するかの設定。
	 * 1の時に可動範囲を考慮した制御を行う。
	 * - Name: move_limit move_limit
	 * - DefaultValue: 0
	 */
	 short int m_move_limit;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">

  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedVelocity2D m_target_velocity;
  /*!
  * 目標速度
  * - Type: RTC::TimedVelocity2D
  * - Unit: m/s, rad/s
  */
  InPort<RTC::TimedVelocity2D> m_target_velocityIn;
  RTC::TimedPose2D m_update_pose;
  /*!
  * 位置の再設定
  * - Type: RTC::TimedPose2D
  * - Unit: m、rad/s
  */
  InPort<RTC::TimedPose2D> m_update_poseIn;

  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  WalkingRobot::LeggedRobot m_Trajectory;
  /*!
   * 足先軌道
   * - Type: RTC::LeggedRobot
   */
  OutPort<WalkingRobot::LeggedRobot> m_TrajectoryOut;
  RTC::TimedPose2D m_current_pose;
  /*!
  * 現在位置
  * - Type: RTC::TimedPose3D
  * - Unit: m,rad
  */
  OutPort<RTC::TimedPose2D> m_current_poseOut;
  RTC::TimedDouble m_stability_margin;
  /*!
  * 安定余裕
  * - Type: RTC::TimedDouble
  * - Unit: m
  */
  OutPort<RTC::TimedDouble> m_stability_marginOut;
  RTC::TimedDouble m_NE_stability_margin;
  /*!
  * NE安定余裕
  * - Type: RTC::TimedDouble
  * - Unit: m
  */
  OutPort<RTC::TimedDouble> m_NE_stability_marginOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  /*!
  * サーボ操作コマンド
  */
  RTC::CorbaPort m_LeggedRobotCommonInterface_ServoPort;
  /*!
  * ロボット操作コマンド
  */
  RTC::CorbaPort m_LeggedRobotCommonInterface_RobotPort;

  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">

  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  /*!
  * サーボ操作コマンド
  */
  RTC::CorbaConsumer<WalkingRobot::LeggedRobotCommonInterface_Servo> m_LeggedRobotCommonInterface_Servo;
  /*!
  * ロボット操作コマンド
  */
  RTC::CorbaConsumer<WalkingRobot::LeggedRobotCommonInterface_Robot> m_LeggedRobotCommonInterface_Robot;
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
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
  DLL_EXPORT void Intermittent_Crawl_Gait_ControllerInit(RTC::Manager* manager);
};

#endif // Intermittent_Crawl_Gait_Controller_H
