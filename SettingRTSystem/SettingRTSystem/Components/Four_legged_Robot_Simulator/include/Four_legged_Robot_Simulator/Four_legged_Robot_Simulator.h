// -*- C++ -*-
/*!
 * @file  Four_legged_Robot_Simulator.h
 * @brief Four legged Robot Simulator
 * @date  $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#ifndef FOUR_LEGGED_ROBOT_SIMULATOR_H
#define FOUR_LEGGED_ROBOT_SIMULATOR_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

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

#include "SimulatorObj_Four_legged_Robot.h"
#include "DrawThread_Four_legged_Robot.h"

using namespace RTC;

/*!
 * @class Four_legged_Robot_Simulator
 * @brief Four legged Robot Simulator
 *
 */
class Four_legged_Robot_Simulator
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Four_legged_Robot_Simulator(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Four_legged_Robot_Simulator();

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
  /*!
   * 描画の速さ
   * - Name: fps draw_time
   * - DefaultValue: 0.01
   * - Unit: s
   */
  double m_draw_time;
  /*!
   * シミュレーションのステップ時間
   * 0以下の場合は実行周期
   * - Name: sampling_time sampling_time
   * - DefaultValue: -1
   */
  double m_sampling_time;
  /*!
   * 重力加速度
   * - Name: gravity gravity
   * - DefaultValue: -9.8
   * - Unit: m/s^2
   */
  double m_gravity;
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
  * ボディの位置(X)
  * - Name: body_pos_x body_pos_x
  * - DefaultValue: 0
  * - Unit: m
  */
  double m_body_pos_x;
  /*!
  * ボディの位置(Y)
  * - Name: body_pos_y body_pos_y
  * - DefaultValue: 0
  * - Unit: m
  */
  double m_body_pos_y;
  /*!
  * ボディの位置(Z)
  * - Name: body_pos_z body_pos_z
  * - DefaultValue: 0.115
  * - Unit: m
  */
  double m_body_pos_z;
  /*!
  * ボディの重量
  * - Name: body_mass body_mass
  * - DefaultValue: 0.3
  * - Unit: kg
  */
  double m_body_mass;
  /*!
  * リンク0の長さ
  * - Name: leg0_length leg0_length
  * - DefaultValue: 0.02
  * - Unit: m
  */
  double m_leg0_length;
  /*!
  * リンク0の幅
  * - Name: leg0_width leg0_width
  * - DefaultValue: 0.02
  * - Unit: m
  */
  double m_leg0_width;
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
  * リンク1の幅
  * - Name: leg1_width leg1_width
  * - DefaultValue: 0.005
  * - Unit: m
  */
  double m_leg1_width;
  /*!
  * リンク1の長さ
  * - Name: leg1_height leg1_height
  * - DefaultValue: 0.01
  * - Unit: m
  */
  double m_leg1_height;
  /*!
  * リンク2の長さ
  * - Name: leg2_length leg2_length
  * - DefaultValue: 0.08
  * - Unit: m
  */
  double m_leg2_length;
  /*!
  * リンク2の幅
  * - Name: leg2_width leg2_width
  * - DefaultValue: 0.005
  * - Unit: m
  */
  double m_leg2_width;
  /*!
  * リンク2の高さ
  * - Name: leg2_height leg2_height
  * - DefaultValue: 0.005
  * - Unit: m
  */
  double m_leg2_height;
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
  * リンク0の重量
  * - Name: leg0_mass leg0_mass
  * - DefaultValue: 0.2
  * - Unit: kg
  */
  double m_leg0_mass;
  /*!
  * リンク1の重量
  * - Name: leg1_mass leg1_mass
  * - DefaultValue: 0.1
  * - Unit: kg
  */
  double m_leg1_mass;
  /*!
  * リンク2の重量
  * - Name: 0.001 leg2_mass
  * - DefaultValue: 0.001
  * - Unit: kg
  */
  double m_leg2_mass;
  /*!
  * 足裏の長さ
  * - Name: foot_length foot_length
  * - DefaultValue: 0.16
  * - Unit: m
  */
  double m_foot_length;
  /*!
  * 足裏の幅
  * - Name: foot_width foot_width
  * - DefaultValue: 0.12
  * - Unit: m
  */
  double m_foot_width;
  /*!
  *
  * - Name: foot_height foot_height
  * - DefaultValue: 0.005
  */
  double m_foot_height;
  /*!
  * 足裏の重量
  * - Name: foot_mass foot_mass
  * - DefaultValue: 0.1
  * - Unit: m
  */
  double m_foot_mass;
  /*!
  * 足裏を作成するかの設定。1で作成。
  * - Name: foot_exist foot_exist
  * - DefaultValue: 0
  * - Constraint: (0,1)
  */
  int m_foot_exist;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedDoubleSeq m_servo;
  /*!
   * 関節角度
   * - Type: RTC::TimedDoubleSeq
   * - Number: 12
   */
  InPort<RTC::TimedDoubleSeq> m_servoIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
	 SimulatorObj_Four_legged_Robot *m_so;
	 DrawThread_Four_legged_Robot *m_dt;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void Four_legged_Robot_SimulatorInit(RTC::Manager* manager);
};

#endif // FOUR_LEGGED_ROBOT_SIMULATOR_H
