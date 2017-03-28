// -*- C++ -*-
/*!
 * @file  StepFunction.h
 * @brief Step Function
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef STEPFUNCTION_H
#define STEPFUNCTION_H

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

class StepFunctionCompBase;

/*!
 * @class StepFunction
 * @brief Step Function
 *
 * ステップ関数を生成
 *
 */
class StepFunction
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  StepFunction(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~StepFunction();
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
   * - Constraint: (TimedDouble,TimedFloat,TimedDoubleSeq,TimedFlo
   *               atSeq)
   */
  std::string m_dataType;
  /*!
   * 初期値
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: initialValue initialValue
   * - DefaultValue: 0
   */
  std::string m_initialValue;
  /*!
   * 最終値
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: finalValue finalValue
   * - DefaultValue: 1
   */
  std::string m_finalValue;
  /*!
   * ステップ時間
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: stepTime stepTime
   * - DefaultValue: 1
   */
  std::string m_stepTime;
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
  /*!
   * シーケンス型で入力する際のデータ数
   * - Name: data_size data_size
   * - DefaultValue: 1
   * - Constraint: 1<=x<=1000
   */
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
	StepFunctionCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};

class StepFunctionCompBase : public RTCLogicBase
{
public:
	virtual void setSamplingTime(double s)
	{
	
	};
	virtual void setConfig(bool c)
	{

	};
	virtual void setInitialValue(std::string c)
	{

	};
	virtual void setFinalValue(std::string c)
	{

	};
	virtual void setStepTime(std::string s)
	{

	};
	virtual void setDataSize(int s)
	{

	};

};



template <class T, class T2>
class StepFunctionSingle : public StepFunctionCompBase
{
public:
	StepFunctionSingle(StepFunction *rtc)
	{
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~StepFunctionSingle()
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
	

	
	void setInitialValue(std::string c)
	{
		std::vector<T2> tmp_iv;
		if(getValueInString(c,tmp_iv))
		{
			func.setInitialValue(tmp_iv[0]);
		}
	};
	void setFinalValue(std::string c)
	{
		std::vector<T2> tmp_fv;
		if(getValueInString(c,tmp_fv))
		{
			func.setFinalValue(tmp_fv[0]);
		}
	};
	void setStepTime(std::string s)
	{
		std::vector<T2> tmp_st;
		if(getValueInString(s,tmp_st))
		{
			func.setStepTime(tmp_st[0]);
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
	RTStepFunction<T2> func;
	

};


template <class T, class T2>
class StepFunctionSeq : public StepFunctionCompBase
{
public:
	StepFunctionSeq(StepFunction *rtc)
	{
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~StepFunctionSeq()
	{
		delete m_outport;
	}
	void setSamplingTime(double s)
	{
		samplingTime = s;
		for (typename std::vector<RTStepFunction<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setSamplingTime(s);
		}
	};
	void setConfig(bool c)
	{
		realTime = c;
		for (typename std::vector<RTStepFunction<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setConfig(c);
		}
	};

	void setInitialValue(std::string c)
	{
		getValueInString(c,initialValue);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(initialValue,i,v))return;
			func[i].setInitialValue(v);
		}
	};
	void setFinalValue(std::string c)
	{
		getValueInString(c,finalValue);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(finalValue,i,v))return;
			func[i].setFinalValue(v);
		}
	};
	void setStepTime(std::string s)
	{
		getValueInString(s,stepTime);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(stepTime,i,v))return;
			func[i].setStepTime(v);
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
					RTStepFunction<T2> sw_tmp = RTStepFunction<T2>();
					sw_tmp.setSamplingTime(samplingTime);
					sw_tmp.setConfig(realTime);

					T2 v;
					if(!getValueInList(initialValue,i,v))return RTC::RTC_ERROR;
					sw_tmp.setInitialValue(v);
					if(!getValueInList(finalValue,i,v))return RTC::RTC_ERROR;
					sw_tmp.setFinalValue(v);
					if(!getValueInList(stepTime,i,v))return RTC::RTC_ERROR;
					sw_tmp.setStepTime(v);
					

					func.push_back(sw_tmp);
					
				}
				
			}
			std::vector<T2> ans;
			for (typename std::vector<RTStepFunction<T2>>::iterator it = func.begin(); it != func.end(); ++it)
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
		for (typename std::vector<RTStepFunction<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).reset();
		}
		return RTC::RTC_OK;
	};

	DataTypeOutPortSeq<T,T2>* m_outport;
	std::vector<RTStepFunction<T2>> func;
	bool realTime;
	double samplingTime;
	std::vector<T2> initialValue;
	std::vector<T2> finalValue;
	std::vector<T2> stepTime;
	int m_data_size;
};


extern "C"
{
  DLL_EXPORT void StepFunctionInit(RTC::Manager* manager);
};

#endif // STEPFUNCTION_H
