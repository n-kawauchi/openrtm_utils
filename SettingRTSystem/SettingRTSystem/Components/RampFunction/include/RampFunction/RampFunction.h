// -*- C++ -*-
/*!
 * @file  RampFunction.h
 * @brief Ramp Function
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef RAMPFUNCTION_H
#define RAMPFUNCTION_H

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

class RampFunctionCompBase;

/*!
 * @class RampFunction
 * @brief Ramp Function
 *
 * 常に増加または減少しているデータを生成
 *
 */
class RampFunction
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  RampFunction(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~RampFunction();
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
   * 生成する値の変化率
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: slope slope
   * - DefaultValue: 1
   */
  std::string m_slope;
  /*!
   * 変化し始める時間
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: startTime startTime
   * - DefaultValue: 0
   */
  std::string m_startTime;
  /*!
   * 初期出力
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: initialOutput initialOutput
   * - DefaultValue: 0
   */
  std::string m_initialOutput;
  /*!
   * ステップ幅
   * - Name: samplingTime samplingTime
   * - DefaultValue: 0.01
   */
  double m_samplingTime;
  /*!
   * 
   * - Name: realTime realTime
   * - DefaultValue: OFF
   * - Constraint: (ON,OFF)
   */
  std::string m_realTime;
  int m_data_size;
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
	RampFunctionCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};



class RampFunctionCompBase : public RTCLogicBase
{
public:
	virtual void setSamplingTime(double s)
	{
	
	};
	virtual void setConfig(bool c)
	{

	};
	virtual void setSlope(std::string s)
	{

	};
	virtual void setStartTime(std::string s)
	{

	};
	virtual void setInitialOutput(std::string t)
	{

	};
	virtual void setDataSize(int s)
	{

	};
};



template <class T, class T2>
class RampFunctionSingle : public RampFunctionCompBase
{
public:
	RampFunctionSingle(RampFunction *rtc)
	{
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~RampFunctionSingle()
	{
		delete m_outport;
	}
	void setSamplingTime(double s)
	{
		func.setSamplingTime(s);
	};
	void setConfig(bool c)
	{
		func.setConfig(c);
	};
	
	void setSlope(std::string s)
	{
		std::vector<T2> tmp_sl;
		if(getValueInString(s,tmp_sl))
		{
			func.setSlope(tmp_sl[0]);
		}
	};
	void setStartTime(std::string s)
	{
		std::vector<T2> tmp_st;
		if(getValueInString(s,tmp_st))
		{
			func.setStartTime(tmp_st[0]);
		}
	};
	void setInitialOutput(std::string t)
	{
		std::vector<T2> tmp_io;
		if(getValueInString(t,tmp_io))
		{
			func.setInitialOutput(tmp_io[0]);
		}
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){

		T2 ans = func.calc();

		//std::cout << ans << std::endl;
		m_outport->setData(ans);
			
		
		
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){
		func.reset();
		return RTC::RTC_OK;
	};


	DataTypeOutPort<T,T2>* m_outport;
	RTRampFunction<T2> func;
	

};


template <class T, class T2>
class RampFunctionSeq : public RampFunctionCompBase
{
public:
	RampFunctionSeq(RampFunction *rtc)
	{
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~RampFunctionSeq()
	{
		delete m_outport;
	}
	void setSamplingTime(double s)
	{
		samplingTime = s;
		for (typename std::vector<RTRampFunction<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setSamplingTime(s);
		}
	};
	void setConfig(bool c)
	{
		realTime = c;
		for (typename std::vector<RTRampFunction<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setConfig(c);
		}
	};
	
	void setSlope(std::string s)
	{
		getValueInString(s,slope);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(slope,i,v))return;
			func[i].setSlope(v);
		}
	};
	void setStartTime(std::string s)
	{
		getValueInString(s,startTime);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(startTime,i,v))return;
			func[i].setStartTime(v);
		}
	};
	void setInitialOutput(std::string t)
	{
		getValueInString(t,initialOutput);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(initialOutput,i,v))return;
			func[i].setInitialOutput(v);
		}
	};
	void setDataSize(int s)
	{
		m_data_size = s;
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){


			for(int i=0;i < m_data_size;i++)
			{
				
				if((int)func.size()-1 < i)
				{
					RTRampFunction<T2> sw_tmp = RTRampFunction<T2>();
					sw_tmp.setSamplingTime(samplingTime);
					sw_tmp.setConfig(realTime);

					T2 v;
					if(!getValueInList(slope,i,v))return RTC::RTC_ERROR;
					sw_tmp.setSlope(v);
					if(!getValueInList(startTime,i,v))return RTC::RTC_ERROR;
					sw_tmp.setStartTime(v);
					if(!getValueInList(initialOutput,i,v))return RTC::RTC_ERROR;
					sw_tmp.setInitialOutput(v);
					

					func.push_back(sw_tmp);
					
				}
				
			}
			std::vector<T2> ans;
			for (typename std::vector<RTRampFunction<T2>>::iterator it = func.begin(); it != func.end(); ++it)
			{

				ans.push_back((*it).calc());
				
			}
			if(ans.size() > 0)
			{
				//for (typename std::vector<T2>::iterator it = ans.begin(); it != ans.end(); ++it)
				//	std::cout << (*it) << std::endl;
				m_outport->setData(ans);
			}
		
		
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){
		for (typename std::vector<RTRampFunction<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).reset();
		}
		return RTC::RTC_OK;
	};

	DataTypeOutPortSeq<T,T2>* m_outport;
	std::vector<RTRampFunction<T2>> func;
	bool realTime;
	double samplingTime;
	std::vector<T2> slope;
	std::vector<T2> startTime;
	std::vector<T2> initialOutput;
	int m_data_size;
};

extern "C"
{
  DLL_EXPORT void RampFunctionInit(RTC::Manager* manager);
};

#endif // RAMPFUNCTION_H
