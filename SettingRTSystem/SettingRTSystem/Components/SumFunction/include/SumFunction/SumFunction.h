// -*- C++ -*-
/*!
 * @file  SumFunction.h
 * @brief Sum Function
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef SUMFUNCTION_H
#define SUMFUNCTION_H

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


class SumFunctionCompBase;

/*!
 * @class SumFunction
 * @brief Sum Function
 *
 * 入力を加算もしくは減算して出力します
 *
 */
class SumFunction
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  SumFunction(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~SumFunction();
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
   * 加算するデータを入力するデータポートの数
   * - Name: additionNum additionNum
   * - DefaultValue: 1
   * - Constraint: 0<=x<=30
   */
  int m_additionNum;
  /*!
   * 減算するデータを入力するデータポートの数
   * - Name: subtractionNum subtractionNum
   * - DefaultValue: 0
   * - Constraint: 0<=x<=30
   */
  int m_subtractionNum;

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
	SumFunctionCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};



class SumFunctionCompBase : public RTCLogicBase
{
public:
	virtual void changeAdditionNum(int num)
	{
	
	};
	virtual void changeSubtractionNum(int num)
	{
	
	};
	
};


template <class T, class T2>
class SumFunctionSingle : public SumFunctionCompBase
{
public:
	SumFunctionSingle(SumFunction *rtc, int mnum, int dnum)
	{
		//m_inport = new DataTypeInPort<T,T2>("in", rtc);
		m_rtc = rtc;
		updatePortList<DataTypeInPort<T,T2>>(m_AdditionInport,mnum,"a",m_rtc);
		updatePortList<DataTypeInPort<T,T2>>(m_SubtractionInport,dnum,"s",m_rtc);
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~SumFunctionSingle()
	{
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_AdditionInport.begin(); it != m_AdditionInport.end(); ++it)
		{
			delete *it;
		}
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_SubtractionInport.begin(); it != m_SubtractionInport.end(); ++it)
		{
			delete *it;
		}
		//delete m_inport;
		delete m_outport;
	};
	void changeAdditionNum(int num)
	{
		updatePortList<DataTypeInPort<T,T2>>(m_AdditionInport,num,"a",m_rtc);
	};
	void changeSubtractionNum(int num)
	{
		
		updatePortList<DataTypeInPort<T,T2>>(m_SubtractionInport,num,"s",m_rtc);
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_AdditionInport.begin(); it != m_AdditionInport.end(); ++it)
		{
			if(!(*it)->isNew())
			{
				return RTC::RTC_OK;
			}
		}
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_SubtractionInport.begin(); it != m_SubtractionInport.end(); ++it)
		{
			if(!(*it)->isNew())
			{
				return RTC::RTC_OK;
			}
		}
		T2 ans = 0;
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_AdditionInport.begin(); it != m_AdditionInport.end(); ++it)
		{
			ans += (*it)->getData();
		}
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_SubtractionInport.begin(); it != m_SubtractionInport.end(); ++it)
		{
			ans -= (*it)->getData();
		}
		//std::cout << ans << std::endl;
		m_outport->setData(ans);
		return RTC::RTC_OK;
	};
	

	std::vector<DataTypeInPort<T,T2>*> m_AdditionInport;
	std::vector<DataTypeInPort<T,T2>*> m_SubtractionInport;
	DataTypeOutPort<T,T2>* m_outport;
	SumFunction *m_rtc;

};


template <class T, class T2>
class SumFunctionSeq : public SumFunctionCompBase
{
public:
	SumFunctionSeq(SumFunction *rtc, int mnum, int dnum)
	{
		//m_inport = new DataTypeInPort<T,T2>("in", rtc);
		
		m_rtc = rtc;
		updatePortList<DataTypeInPortSeq<T,T2>>(m_AdditionInport,mnum,"a",m_rtc);
		updatePortList<DataTypeInPortSeq<T,T2>>(m_SubtractionInport,dnum,"s",m_rtc);
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~SumFunctionSeq()
	{
		for (typename std::vector<DataTypeInPortSeq<T,T2>*>::iterator it = m_AdditionInport.begin(); it != m_AdditionInport.end(); ++it)
		{
			delete *it;
		}
		for (typename std::vector<DataTypeInPortSeq<T,T2>*>::iterator it = m_SubtractionInport.begin(); it != m_SubtractionInport.end(); ++it)
		{
			delete *it;
		}
		//delete m_inport;
		delete m_outport;
	}
	void changeAdditionNum(int num)
	{
		updatePortList<DataTypeInPortSeq<T,T2>>(m_AdditionInport,num,"a",m_rtc);
	};
	void changeSubtractionNum(int num)
	{
		
		updatePortList<DataTypeInPortSeq<T,T2>>(m_SubtractionInport,num,"s",m_rtc);
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		
		for (typename std::vector<DataTypeInPortSeq<T,T2>*>::iterator it = m_AdditionInport.begin(); it != m_AdditionInport.end(); ++it)
		{
			if(!(*it)->isNew())
			{
				return RTC::RTC_OK;
			}
			
		}
		for (typename std::vector<DataTypeInPortSeq<T,T2>*>::iterator it = m_SubtractionInport.begin(); it != m_SubtractionInport.end(); ++it)
		{
			if(!(*it)->isNew())
			{
				return RTC::RTC_OK;
			}
		}

		int minLength=0;
		int p_count = 0;
		std::vector<std::vector<T2>> m_value;
		std::vector<std::vector<T2>> d_value;
		for (typename std::vector<DataTypeInPortSeq<T,T2>*>::iterator it = m_AdditionInport.begin(); it != m_AdditionInport.end(); ++it)
		{
			std::vector<T2> tmp = (*it)->getData();
			if(p_count==0)
			{
				minLength = tmp.size();
			}
			else if(minLength > tmp.size())
			{
				minLength = tmp.size();
			}
			m_value.push_back(tmp);
			p_count++;
		}
		for (typename std::vector<DataTypeInPortSeq<T,T2>*>::iterator it = m_SubtractionInport.begin(); it != m_SubtractionInport.end(); ++it)
		{
			
			std::vector<T2> tmp = (*it)->getData();
			if(p_count==0)
			{
				minLength = tmp.size();
			}
			else if(minLength > tmp.size())
			{
				minLength = tmp.size();
			}
			d_value.push_back(tmp);
			p_count++;
		}

		std::vector<T2> ans;
		for(int i=0;i < minLength;i++)
		{
			ans.push_back(0);
		}
		for (typename std::vector<std::vector<T2>>::iterator it = m_value.begin(); it != m_value.end(); ++it)
		{
			for(int i=0;i < ans.size();i++)
			{
				ans[i] += (*it)[i];
			}
		}
		for (typename std::vector<std::vector<T2>>::iterator it = d_value.begin(); it != d_value.end(); ++it)
		{
			for(int i=0;i < ans.size();i++)
			{
				ans[i] -= (*it)[i];
			}
		}
		//for (typename std::vector<T2>::iterator it = ans.begin(); it != ans.end(); ++it)
		//	std::cout << (*it) << std::endl;
		m_outport->setData(ans);
		return RTC::RTC_OK;
	};
	

	std::vector<DataTypeInPortSeq<T,T2>*> m_AdditionInport;
	std::vector<DataTypeInPortSeq<T,T2>*> m_SubtractionInport;
	DataTypeOutPortSeq<T,T2>* m_outport;
	SumFunction *m_rtc;

};

extern "C"
{
  DLL_EXPORT void SumFunctionInit(RTC::Manager* manager);
};

#endif // SUMFUNCTION_H
