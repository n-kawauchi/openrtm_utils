// -*- C++ -*-
/*!
 * @file  Relay.h
 * @brief Relay
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef RELAY_H
#define RELAY_H

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


class RelayCompBase;

/*!
 * @class Relay
 * @brief Relay
 *
 * 2 つの定数間で出力を切り替え
 *
 */
class Relay
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Relay(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Relay();
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
   *               medULong,TimedUShort,TimedDoubleSeq,TimedLongSe
   *               q,TimedFloatSeq,TimedShortSeq,TimedULongSeq,Tim
   *               edUShortSeq)
   */
  std::string m_dataType;
  /*!
   * リレーのオンのしきい値
   * - Name: switchOnPoint switchOnPoint
   * - DefaultValue: 1
   */
  std::string m_switchOnPoint;
  /*!
   * リレーのオフのしきい値
   * - Name:  switchOffPoint
   * - DefaultValue: -1
   */
  std::string m_switchOffPoint;
  /*!
   * リレーがオンの場合の出力
   * - Name: outputWhenOn outputWhenOn
   * - DefaultValue: 1
   */
  std::string m_outputWhenOn;
  /*!
   * リレーがオンの場合の出力
   * - Name: outputWhenOff outputWhenOff
   * - DefaultValue: -1
   */
  std::string m_outputWhenOff;

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
	RelayCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


class RelayCompBase : public RTCLogicBase
{
public:
	virtual void setSwitchPoint(std::string on, std::string off)
	{

	};
	virtual void setOutput(std::string on, std::string off)
	{

	};
};



template <class T, class T2>
class RelaySingle : public RelayCompBase
{
public:
	RelaySingle(Relay *rtc)
	{
		m_inport = new DataTypeInPort<T,T2>("in", rtc);
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~RelaySingle()
	{
		delete m_inport;
		delete m_outport;
	}
	
	void setSwitchPoint(std::string on, std::string off)
	{
		std::vector<T2> tmp_on;
		std::vector<T2> tmp_off;
		if(getValueInString(on,tmp_on) && getValueInString(off,tmp_off))
		{
			func.setSwitchPoint(tmp_on[0],tmp_off[0]);
		}
		
	};
	void setOutput(std::string on, std::string off)
	{
		std::vector<T2> tmp_on;
		std::vector<T2> tmp_off;
		if(getValueInString(on,tmp_on) && getValueInString(off,tmp_off))
		{
			func.setOutput(tmp_on[0],tmp_off[0]);
		}
		
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport->isNew())
		{
			T2 ans = func.calc(m_inport->getData());
			
			//std::cout << ans << std::endl;
			m_outport->setData(ans);
			
		}
		
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){
		func.reset();
		return RTC::RTC_OK;
	};

	DataTypeInPort<T,T2>* m_inport;
	DataTypeOutPort<T,T2>* m_outport;
	RTRelay<T2> func;

};


template <class T, class T2>
class RelaySeq : public RelayCompBase
{
public:
	RelaySeq(Relay *rtc)
	{
		m_inport = new DataTypeInPortSeq<T,T2>("in", rtc);
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~RelaySeq()
	{
		delete m_inport;
		delete m_outport;
	}
	
	void setSwitchPoint(std::string on, std::string off)
	{
		getValueInString(on,switchOnPoint);
		getValueInString(off,switchOffPoint);
		for (int i=0;i < func.size();i++)
		{
			T2 on_tmp;
			T2 off_tmp;
			if(!getValueInList(switchOnPoint,i,on_tmp))return;
			if(!getValueInList(switchOffPoint,i,off_tmp))return;
			func[i].setSwitchPoint(on_tmp,off_tmp);
		}
		
		
	};

	void setOutput(std::string on, std::string off)
	{
		getValueInString(on,outputWhenOn);
		getValueInString(off,outputWhenOff);
		for (int i=0;i < func.size();i++)
		{
			T2 on_tmp;
			T2 off_tmp;
			if(!getValueInList(outputWhenOn,i,on_tmp))return;
			if(!getValueInList(outputWhenOff,i,off_tmp))return;
			func[i].setOutput(on_tmp,off_tmp);
		}
		
		
	};

	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport->isNew())
		{
			std::vector<T2> data = m_inport->getData();
			std::vector<T2> ans;
			for(int i=0;i < data.size();i++)
			{
				
				if((int)func.size()-1 < i)
				{
					T2 sonp;
					T2 soffp;
					if(!getValueInList(switchOnPoint,i,sonp))return RTC::RTC_ERROR;
					if(!getValueInList(switchOffPoint,i,soffp))return RTC::RTC_ERROR;
					T2 owon;
					T2 owoff;
					if(!getValueInList(outputWhenOn,i,owon))return RTC::RTC_ERROR;
					if(!getValueInList(outputWhenOff,i,owoff))return RTC::RTC_ERROR;

					RTRelay<T2> rtd_tmp = RTRelay<T2>();
					rtd_tmp.setSwitchPoint(sonp,soffp);
					rtd_tmp.setOutput(owon,owoff);

					
					func.push_back(rtd_tmp);
					
				}
				//std::cout << func.size() << "\t" << i << std::endl;
				//func[i].addData(data[i]);
				ans.push_back(func[i].calc(data[i]));
			}
			
			
			if(ans.size() > 0)
			{
				//for (typename std::vector<T2>::iterator it = ans.begin(); it != ans.end(); ++it)
				//	std::cout << (*it) << std::endl;
				m_outport->setData(ans);
			}
		}
		
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){
		for (typename std::vector<RTRelay<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).reset();
		}
		return RTC::RTC_OK;
	};

	DataTypeInPortSeq<T,T2>* m_inport;
	DataTypeOutPortSeq<T,T2>* m_outport;
	std::vector<RTRelay<T2>> func;
	std::vector<T2> switchOnPoint;
	std::vector<T2> switchOffPoint;
	std::vector<T2> outputWhenOn;
	std::vector<T2> outputWhenOff;

};

extern "C"
{
  DLL_EXPORT void RelayInit(RTC::Manager* manager);
};

#endif // RELAY_H
