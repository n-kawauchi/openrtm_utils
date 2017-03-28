// -*- C++ -*-
/*!
 * @file  PulseGenerator.h
 * @brief Pulse Generator
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef PULSEGENERATOR_H
#define PULSEGENERATOR_H

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

class PulseGeneratorCompBase;


/*!
 * @class PulseGenerator
 * @brief Pulse Generator
 *
 * 一定の間隔で矩形波パルスを生成
 *
 */
class PulseGenerator
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  PulseGenerator(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~PulseGenerator();
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
   * パルス振幅
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: amplitude amplitude
   * - DefaultValue: 1
   */
  std::string m_amplitude;
  /*!
   * パルス周期
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: period period
   * - DefaultValue: 1
   * - Unit: s
   */
  std::string m_period;
  /*!
   * パルス幅(％で指定)
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: pulseWidth pulseWidth
   * - DefaultValue: 5
   * - Unit: %
   */
  std::string m_pulseWidth;
  /*!
   * 位相遅れ
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: phaseDelay phaseDelay
   * - DefaultValue: 0
   */
  std::string m_phaseDelay;
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
	PulseGeneratorCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};



class PulseGeneratorCompBase : public RTCLogicBase
{
public:
	virtual void setSamplingTime(double s)
	{
	
	};
	virtual void setConfig(bool c)
	{

	};
	virtual void setAmplitude(std::string a)
	{

	};
	virtual void setPeriod(std::string p)
	{

	};
	virtual void setPulseWidth(std::string p)
	{

	};
	virtual void setPhaseDelay(std::string p)
	{

	};
	virtual void setDataSize(int s)
	{

	};
};



template <class T, class T2>
class PulseGeneratorSingle : public PulseGeneratorCompBase
{
public:
	PulseGeneratorSingle(PulseGenerator *rtc)
	{
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~PulseGeneratorSingle()
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
	

	void setAmplitude(std::string a)
	{
		std::vector<T2> tmp_ap;
		if(getValueInString(a,tmp_ap))
		{
			func.setAmplitude(tmp_ap[0]);
		}
	};
	void setPeriod(std::string p)
	{
		std::vector<T2> tmp_pd;
		if(getValueInString(p,tmp_pd))
		{
			func.setPeriod(tmp_pd[0]);
		}
	};
	void setPulseWidth(std::string p)
	{
		std::vector<T2> tmp_pw;
		if(getValueInString(p,tmp_pw))
		{
			func.setPulseWidth(tmp_pw[0]);
		}
	};
	void setPhaseDelay(std::string p)
	{
		std::vector<T2> tmp_pd;
		if(getValueInString(p,tmp_pd))
		{
			func.setPhaseDelay(tmp_pd[0]);
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
	RTPulseGenerator<T2> func;
	

};


template <class T, class T2>
class PulseGeneratorSeq : public PulseGeneratorCompBase
{
public:
	PulseGeneratorSeq(PulseGenerator *rtc)
	{
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~PulseGeneratorSeq()
	{
		delete m_outport;
	}
	void setSamplingTime(double s)
	{
		samplingTime = s;
		for (typename std::vector<RTPulseGenerator<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setSamplingTime(s);
		}
	};
	void setConfig(bool c)
	{
		realTime = c;
		for (typename std::vector<RTPulseGenerator<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setConfig(c);
		}
	};
	
	void setAmplitude(std::string a)
	{
		getValueInString(a,amplitude);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(amplitude,i,v))return;
			func[i].setAmplitude(v);
		}
	};
	void setPeriod(std::string p)
	{
		getValueInString(p,period);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(period,i,v))return;
			func[i].setPeriod(v);
		}
	};
	void setPulseWidth(std::string p)
	{
		getValueInString(p,pulseWidth);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(pulseWidth,i,v))return;
			func[i].setPulseWidth(v);
		}
	};
	void setPhaseDelay(std::string p)
	{
		getValueInString(p,phaseDelay);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(phaseDelay,i,v))return;
			func[i].setPhaseDelay(v);
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
					RTPulseGenerator<T2> sw_tmp = RTPulseGenerator<T2>();
					sw_tmp.setSamplingTime(samplingTime);
					sw_tmp.setConfig(realTime);

					T2 v;
					if(!getValueInList(amplitude,i,v))return RTC::RTC_ERROR;
					sw_tmp.setAmplitude(v);
					if(!getValueInList(period,i,v))return RTC::RTC_ERROR;
					sw_tmp.setPeriod(v);
					if(!getValueInList(pulseWidth,i,v))return RTC::RTC_ERROR;
					sw_tmp.setPulseWidth(v);
					if(!getValueInList(phaseDelay,i,v))return RTC::RTC_ERROR;
					sw_tmp.setPhaseDelay(v);
					

					func.push_back(sw_tmp);
					
				}
				
			}
			std::vector<T2> ans;
			for (typename std::vector<RTPulseGenerator<T2>>::iterator it = func.begin(); it != func.end(); ++it)
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
		for (typename std::vector<RTPulseGenerator<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).reset();
		}
		return RTC::RTC_OK;
	};

	DataTypeOutPortSeq<T,T2>* m_outport;
	std::vector<RTPulseGenerator<T2>> func;
	bool realTime;
	double samplingTime;
	std::vector<T2> amplitude;
	std::vector<T2> period;
	std::vector<T2> pulseWidth;
	std::vector<T2> phaseDelay;
	int m_data_size;
};


extern "C"
{
  DLL_EXPORT void PulseGeneratorInit(RTC::Manager* manager);
};

#endif // PULSEGENERATOR_H
