// -*- C++ -*-
/*!
 * @file  RMC.h
 * @brief Robot Model Creator
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef RMC_H
#define RMC_H

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

using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>


class SensorDataPort
{
public:
	virtual ~SensorDataPort();
	virtual std::vector<float> getValue();
	virtual bool isNew();
};


class FloatSeqSensorDataPort : public SensorDataPort
{
public:
	FloatSeqSensorDataPort(std::string name, RTC::DataFlowComponentBase *rtc);
	~FloatSeqSensorDataPort();
	std::vector<float> getValue();
	bool isNew();
	TimedFloatSeq *In;
	RTC::InPort<TimedFloatSeq> *inIn;
	RTC::DataFlowComponentBase *m_rtc;
};


class FloatSensorDataPort : public SensorDataPort
{
public:
	FloatSensorDataPort(std::string name, RTC::DataFlowComponentBase *rtc);
	~FloatSensorDataPort();
	std::vector<float> getValue();
	bool isNew();
	TimedFloat *In;
	RTC::InPort<TimedFloat> *inIn;
	RTC::DataFlowComponentBase *m_rtc;
};


class AccelerationSensorDataPort : public SensorDataPort
{
public:
	AccelerationSensorDataPort(std::string name, RTC::DataFlowComponentBase *rtc);
	~AccelerationSensorDataPort();
	std::vector<float> getValue();
	bool isNew();
	TimedAcceleration3D *In;
	RTC::InPort<TimedAcceleration3D> *inIn;
	RTC::DataFlowComponentBase *m_rtc;
};

class AngularVelocitySensorDataPort : public SensorDataPort
{
public:
	AngularVelocitySensorDataPort(std::string name, RTC::DataFlowComponentBase *rtc);
	~AngularVelocitySensorDataPort();
	std::vector<float> getValue();
	bool isNew();
	TimedAngularVelocity3D *In;
	RTC::InPort<TimedAngularVelocity3D> *inIn;
	RTC::DataFlowComponentBase *m_rtc;
};


/*!
 * @class RMC
 * @brief Robot Model Creator
 *
 * ロボットの3Dモデルを表示します
 *
 */
class RMC
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  RMC(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~RMC();
  static RMC *obj;
  bool angleIsNew();
  std::vector<float> getAngle();
  std::string getFileName();
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
   * モデルファイル名
   * - Name: file_path file_path
   * - DefaultValue: None
   */
  std::string m_file_path;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedFloatSeq m_pos;
  /*!
   * 関節角度
   * - Type: RTC::TimedFloatSeq
   * - Unit: rad
   */
  InPort<RTC::TimedFloatSeq> m_posIn;
  
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
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void RMCInit(RTC::Manager* manager);
};

#endif // RMC_H
