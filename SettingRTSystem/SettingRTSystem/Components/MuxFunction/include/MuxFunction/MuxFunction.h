// -*- C++ -*-
/*!
 * @file  MuxFunction.h
 * @brief Mux Function
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef MUXFUNCTION_H
#define MUXFUNCTION_H

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

#include "DyPortBase.h"
#include "RTMath.h"

class MuxFunctionCompBase;

/*!
 * @class MuxFunction
 * @brief Mux Function
 *
 * 複数の入力を組み合わせてシーケンス型にする
 *
 */
class MuxFunction
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  MuxFunction(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~MuxFunction();
  void configUpdate();
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
   * データ型
   * - Name: dataType dataType
   * - DefaultValue: TimedDouble
   * - Constraint: (TimedDouble,TimedLong,TimedFloat,TimedShort,Ti
   *               medULong,TimedUShort)
   */
  std::string m_dataType;
  /*!
   * DataInPortの数
   * - Name: inportNum inportNum
   * - DefaultValue: 1
   * - Constraint: 1<=x<=30
   */
  int m_inportNum;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
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
	MuxFunctionCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


class MuxFunctionCompBase : public RTCLogicBase
{
public:
	virtual void changeInPortNum(int num)
	{
	
	};
	
	
};


template <class T, class T3, class T2>
class MuxFunctionComp : public MuxFunctionCompBase
{
public:
	MuxFunctionComp(MuxFunction *rtc, int num)
	{
		m_rtc = rtc;
		m_outport = new DataTypeOutPortSeq<T3,T2>("out", rtc);
		updatePortList<DataTypeInPort<T,T2>>(m_inport,num,"u",m_rtc);
		
	};
	~MuxFunctionComp()
	{
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_inport.begin(); it != m_inport.end(); ++it)
		{
			delete *it;
		}
		
		delete m_outport;
		
	};
	
	void changeInPortNum(int num)
	{
		updatePortList<DataTypeInPort<T,T2>>(m_inport,num,"u",m_rtc);
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_inport.begin(); it != m_inport.end(); ++it)
		{
			if(!(*it)->isNew())return RTC::RTC_OK;
		}
		std::vector<T2> ans;
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_inport.begin(); it != m_inport.end(); ++it)
		{
			ans.push_back((*it)->getData());
			
		}
		//for (typename std::vector<T2>::iterator it = ans.begin(); it != ans.end(); ++it)
		//	std::cout << (*it) << std::endl;
		m_outport->setData(ans);
		
		return RTC::RTC_OK;
	};
	


	DataTypeOutPortSeq<T3,T2>* m_outport;
	std::vector<DataTypeInPort<T,T2>*> m_inport;
	MuxFunction *m_rtc;

};


extern "C"
{
  DLL_EXPORT void MuxFunctionInit(RTC::Manager* manager);
};

#endif // MUXFUNCTION_H
