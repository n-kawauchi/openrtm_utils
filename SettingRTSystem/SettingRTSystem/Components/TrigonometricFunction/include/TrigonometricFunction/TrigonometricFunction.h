// -*- C++ -*-
/*!
 * @file  TrigonometricFunction.h
 * @brief Trigonometric Function
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef TRIGONOMETRICFUNCTION_H
#define TRIGONOMETRICFUNCTION_H

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

class TrigonometricFunctionCompBase;

/*!
 * @class TrigonometricFunction
 * @brief Trigonometric Function
 *
 * 入力に対する指定された三角関数
 *
 */
class TrigonometricFunction
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  TrigonometricFunction(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~TrigonometricFunction();
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
   * 三角関数を指定する
   * - Name: function function
   * - DefaultValue: sin
   * - Constraint: (sin,cos,tan,asin,acos,atan,sinh,cosh,tanh,asin
   *               h,acosh,atanh)
   */
  std::string m_function;

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
	TrigonometricFunctionCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};



template <class T>
T(*getFunction(std::string name))(T)
{
	coil::eraseBlank(name);
	if(name == "sin")
	{
		return &std::sin;
	}
	else if(name == "cos")
	{
		return &std::cos;
	}
	else if(name == "tan")
	{
		return &std::tan;
	}
	else if(name == "asin")
	{
		return &std::asin;
	}
	else if(name == "acos")
	{
		return &std::acos;
	}
	else if(name == "atan")
	{
		return &std::atan;
	}
	else if(name == "sinh")
	{
		return &std::sinh;
	}
	else if(name == "cosh")
	{
		return &std::cosh;
	}
	else if(name == "tanh")
	{
		return &std::cosh;
	}
	else if(name == "asinh")
	{
		return &std::asinh;
	}
	else if(name == "acosh")
	{
		return &std::acosh;
	}
	else if(name == "atanh")
	{
		return &std::atanh;
	}
	return NULL;
};

class TrigonometricFunctionCompBase : public RTCLogicBase
{
public:
	
	virtual void setFunc(std::string name)
	{

	};
};



template <class T, class T2>
class TrigonometricFunctionSingle : public TrigonometricFunctionCompBase
{
public:
	TrigonometricFunctionSingle(TrigonometricFunction *rtc, std::string fname)
	{
		m_inport = new DataTypeInPort<T,T2>("in", rtc);
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		setFunc(fname);
	};
	~TrigonometricFunctionSingle()
	{
		delete m_inport;
		delete m_outport;
	};

	void setFunc(std::string name)
	{
		m_func = getFunction<T2>(name);
	};
	
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport->isNew())
		{
			T2 ans = m_func((T2)m_inport->getData());

			//std::cout << ans << std::endl;
			m_outport->setData(ans);
			
		}
		
		return RTC::RTC_OK;
	};
	

	DataTypeInPort<T,T2>* m_inport;
	DataTypeOutPort<T,T2>* m_outport;
	T2(*m_func)(T2);
};



template <class T, class T2>
class TrigonometricFunctionSeq : public TrigonometricFunctionCompBase
{
public:
	TrigonometricFunctionSeq(TrigonometricFunction *rtc, std::string fname)
	{
		m_inport = new DataTypeInPortSeq<T,T2>("in", rtc);
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		setFunc(fname);
	};
	~TrigonometricFunctionSeq()
	{
		delete m_inport;
		delete m_outport;
	};
	void setFunc(std::string name)
	{
		m_func = getFunction<T2>(name);
	};

	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport->isNew())
		{
			std::vector<T2> data = m_inport->getData();
			std::vector<T2> ans;
			for(int i=0;i < data.size();i++)
			{
				T2 tmp = m_func((T2)data[i]);
				ans.push_back(tmp);
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


	DataTypeInPortSeq<T,T2>* m_inport;
	DataTypeOutPortSeq<T,T2>* m_outport;
	T2(*m_func)(T2);
};





extern "C"
{
  DLL_EXPORT void TrigonometricFunctionInit(RTC::Manager* manager);
};

#endif // TRIGONOMETRICFUNCTION_H
