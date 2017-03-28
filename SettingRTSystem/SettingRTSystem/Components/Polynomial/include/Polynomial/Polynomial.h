// -*- C++ -*-
/*!
 * @file  Polynomial.h
 * @brief Polynomial
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

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

class PolynomialCompBase;

/*!
 * @class Polynomial
 * @brief Polynomial
 *
 * 多項式係数を設定してDataInPortからデータを入力すると多項式の計算
 * 結果を出力
 *
 */
class Polynomial
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Polynomial(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Polynomial();
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
   * 多項式係数
   * ”,”区切りで右からXのN～0乗の係数を設定します。
   * - Name: coefficients coefficients
   * - DefaultValue: 1
   */
  std::string m_coefficients;

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
	PolynomialCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


class PolynomialCompBase : public RTCLogicBase
{
public:
	
	virtual void setCoefficients(std::string cf)
	{

	};
};



template <class T, class T2>
class PolynomialSingle : public PolynomialCompBase
{
public:
	PolynomialSingle(Polynomial *rtc)
	{
		m_inport = new DataTypeInPort<T,T2>("in", rtc);
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~PolynomialSingle()
	{
		delete m_inport;
		delete m_outport;
	}
	
	
	void setCoefficients(std::string cf)
	{
		m_coefficients.clear();
		std::vector<T2> tmp;
		getValueInString(cf,tmp);
		for (typename std::vector<T2>::iterator it = tmp.end(); it != tmp.begin();)
		{
			--it;
			m_coefficients.push_back((*it));
			
		}
		
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport->isNew())
		{
			T2 ans = 0;
			T2 value = m_inport->getData();
			for(int i=0;i < m_coefficients.size();i++)
			{
				
				ans += m_coefficients[i]*std::pow((T2)value,(T2)(i+1));
			}
			

			//std::cout << ans << std::endl;
			m_outport->setData(ans);
			
		}
		
		return RTC::RTC_OK;
	};
	

	DataTypeInPort<T,T2>* m_inport;
	DataTypeOutPort<T,T2>* m_outport;
	std::vector<T2> m_coefficients;
};



template <class T, class T2>
class PolynomialSeq : public PolynomialCompBase
{
public:
	PolynomialSeq(Polynomial *rtc)
	{
		m_inport = new DataTypeInPortSeq<T,T2>("in", rtc);
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~PolynomialSeq()
	{
		delete m_inport;
		delete m_outport;
	}
	
	void setCoefficients(std::string cf)
	{
		m_coefficients.clear();
		std::vector<T2> tmp;
		getValueInString(cf,tmp);
		for (typename std::vector<T2>::iterator it = tmp.end(); it != tmp.begin(); --it)
		{
			m_coefficients.push_back((*it));
		}
		
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport->isNew())
		{
			std::vector<T2> data = m_inport->getData();
			std::vector<T2> ans;
			for(int i=0;i < data.size();i++)
			{
				T2 tmp = 0;
				for(int j=0;j < m_coefficients.size();j++)
				{
					
					tmp += m_coefficients[j]*std::pow((T2)data[i],(T2)(j+1));
				}
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
	std::vector<T2> m_coefficients;

};

extern "C"
{
  DLL_EXPORT void PolynomialInit(RTC::Manager* manager);
};

#endif // POLYNOMIAL_H
