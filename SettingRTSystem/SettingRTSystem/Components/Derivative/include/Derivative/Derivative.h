// -*- C++ -*-
/*!
 * @file  Derivative.h
 * @brief Derivative
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef DERIVATIVE_H
#define DERIVATIVE_H

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

class DerivativeCompBase;

/*!
 * @class Derivative
 * @brief Derivative
 *
 * DataInPortから入力されたデータを積分してDataOutPortから出力しま
 * す。
 *
 */
class Derivative
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Derivative(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Derivative();
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
	DerivativeCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};



class DerivativeCompBase : public RTCLogicBase
{
public:
	virtual void setSamplingTime(double s)
	{
	
	};
	virtual void setConfig(bool c)
	{

	};
};




template <class T, class T2>
class DerivativeSingle : public DerivativeCompBase
{
public:
	DerivativeSingle(Derivative *rtc)
	{
		m_inport = new DataTypeInPort<T,T2>("in", rtc);
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~DerivativeSingle()
	{
		delete m_inport;
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
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport->isNew())
		{
			func.addData(m_inport->getData());
			T2 ans;
			if(func.calc(ans))
			{
				//std::cout << ans << std::endl;
				m_outport->setData(ans);
			}
		}
		
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){
		func.reset();
		return RTC::RTC_OK;
	};

	DataTypeInPort<T,T2>* m_inport;
	DataTypeOutPort<T,T2>* m_outport;
	RTDerivative<T2> func;

};


template <class T, class T2>
class DerivativeSeq : public DerivativeCompBase
{
public:
	DerivativeSeq(Derivative *rtc)
	{
		m_inport = new DataTypeInPortSeq<T,T2>("in", rtc);
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~DerivativeSeq()
	{
		delete m_inport;
		delete m_outport;
	}
	void setSamplingTime(double s)
	{
		samplingTime = s;
		for (typename std::vector<RTDerivative<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setSamplingTime(s);
		}
	};
	void setConfig(bool c)
	{
		realTime = c;
		for (typename std::vector<RTDerivative<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setConfig(c);
		}
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport->isNew())
		{
			std::vector<T2> data = m_inport->getData();
			for(int i=0;i < data.size();i++)
			{
				
				if((int)func.size()-1 < i)
				{
					RTDerivative<T2> rtd_tmp = RTDerivative<T2>();
					rtd_tmp.setSamplingTime(samplingTime);
					rtd_tmp.setConfig(realTime);
					func.push_back(rtd_tmp);
					
				}
				//std::cout << func.size() << "\t" << i << std::endl;
				func[i].addData(data[i]);
			}
			std::vector<T2> ans;
			for (typename std::vector<RTDerivative<T2>>::iterator it = func.begin(); it != func.end(); ++it)
			{
				T2 tmp;
				if((*it).calc(tmp))
				{
					ans.push_back(tmp);
				}
			}
			if(ans.size() > 0)
			{
				//std::cout << ans[0] << std::endl;
				m_outport->setData(ans);
			}
		}
		
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){
		for (typename std::vector<RTDerivative<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).reset();
		}
		return RTC::RTC_OK;
	};

	DataTypeInPortSeq<T,T2>* m_inport;
	DataTypeOutPortSeq<T,T2>* m_outport;
	std::vector<RTDerivative<T2>> func;
	bool realTime;
	double samplingTime;

};

extern "C"
{
  DLL_EXPORT void DerivativeInit(RTC::Manager* manager);
};

#endif // DERIVATIVE_H
