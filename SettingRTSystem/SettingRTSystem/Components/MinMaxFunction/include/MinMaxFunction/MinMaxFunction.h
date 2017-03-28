// -*- C++ -*-
/*!
 * @file  MinMaxFunction.h
 * @brief MinMax Function
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef MINMAXFUNCTION_H
#define MINMAXFUNCTION_H

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


class MinMaxFunctionCompBase;

/*!
 * @class MinMaxFunction
 * @brief MinMax Function
 *
 * 最小入力値または最大入力値を出力
 *
 */
class MinMaxFunction
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  MinMaxFunction(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~MinMaxFunction();
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
   * DataInPortの数
   * - Name: inportNum inportNum
   * - DefaultValue: 1
   * - Constraint: 0<=x<=30
   */
  int m_inportNum;
  /*!
   * ONの時は過去の入力の中で最大、最少の値を出力する。OFFの時は現
   * 在の入力のみで判定する。
   * - Name: runningResettable runningResettable
   * - DefaultValue: OFF
   * - Constraint: (ON,OFF)
   */
  std::string m_runningResettable;
  std::string m_maxmin;

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
	MinMaxFunctionCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


class MinMaxFunctionCompBase : public RTCLogicBase
{
public:
	virtual void changeInportNum(int num)
	{
	
	};
	virtual void setRunningResettable(bool type)
	{
	
	};
	virtual void setMaxMin(bool type)
	{
	
	};
	
};


template <class T, class T2>
class MinMaxFunctionSingle : public MinMaxFunctionCompBase
{
public:
	MinMaxFunctionSingle(MinMaxFunction *rtc, int num)
	{
		//m_inport = new DataTypeInPort<T,T2>("in", rtc);
		m_rtc = rtc;
		updatePortList<DataTypeInPort<T,T2>>(m_inport,num,"u",m_rtc);
		
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~MinMaxFunctionSingle()
	{
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_inport.begin(); it != m_inport.end(); ++it)
		{
			delete *it;
		}
		
		//delete m_inport;
		delete m_outport;
	};
	void changeInportNum(int num)
	{
		updatePortList<DataTypeInPort<T,T2>>(m_inport,num,"u",m_rtc);
	};
	void setRunningResettable(bool type)
	{
		runningResettable = type;
	};
	void setMaxMin(bool type)
	{
		m_minmax = type;
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_inport.begin(); it != m_inport.end(); ++it)
		{
			if(!(*it)->isNew())
			{
				return RTC::RTC_OK;
			}
		}
		
		int port_count = 0;
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = m_inport.begin(); it != m_inport.end(); ++it)
		{
			if(!runningResettable&&port_count==0)
			{
				maxminValue = (*it)->getData();
			}
			else if(runningResettable&&port_count==0&&count==0)
			{
				maxminValue = (*it)->getData();
			}
			else
			{
				T2 tmp = (*it)->getData();
				if(m_minmax)
				{
					if(maxminValue < tmp)
					{
						maxminValue = tmp;
					}
				}
				else
				{
					if(maxminValue > tmp)
					{
						maxminValue = tmp;
					}
				}
			}
			port_count++;
		}
		count++;
		
		//std::cout << maxminValue << std::endl;
		m_outport->setData(maxminValue);
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id)
	{
		count = 0;
		return RTC::RTC_OK;
	};

	std::vector<DataTypeInPort<T,T2>*> m_inport;
	DataTypeOutPort<T,T2>* m_outport;
	MinMaxFunction *m_rtc;
	bool runningResettable;
	T2 maxminValue;
	bool m_minmax;
	int count;

};


template <class T, class T2>
class MinMaxFunctionSeq : public MinMaxFunctionCompBase
{
public:
	MinMaxFunctionSeq(MinMaxFunction *rtc, int num)
	{
		m_rtc = rtc;
		updatePortList<DataTypeInPortSeq<T,T2>>(m_inport,num,"u",m_rtc);
		
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~MinMaxFunctionSeq()
	{
		for (typename std::vector<DataTypeInPortSeq<T,T2>*>::iterator it = m_inport.begin(); it != m_inport.end(); ++it)
		{
			delete *it;
		}
		
		//delete m_inport;
		delete m_outport;
	}
	void changeInportNum(int num)
	{
		updatePortList<DataTypeInPortSeq<T,T2>>(m_inport,num,"u",m_rtc);
	};
	void setRunningResettable(bool type)
	{
		runningResettable = type;
	};
	void setMaxMin(bool type)
	{
		m_minmax = type;
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		
		for (typename std::vector<DataTypeInPortSeq<T,T2>*>::iterator it = m_inport.begin(); it != m_inport.end(); ++it)
		{
			if(!(*it)->isNew())
			{
				return RTC::RTC_OK;
			}
			
		}
		

		int minLength=0;
		int p_count = 0;
		std::vector<std::vector<T2>> m_value;
		for (typename std::vector<DataTypeInPortSeq<T,T2>*>::iterator it = m_inport.begin(); it != m_inport.end(); ++it)
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
		

		if(maxminValue.size() != minLength)
		{
			for(int i=maxminValue.size();i < minLength;i++)
			{
				maxminValue.push_back(0);
			}
		}
		int port_count = 0;
		for (typename std::vector<std::vector<T2>>::iterator it = m_value.begin(); it != m_value.end(); ++it)
		{
			
			for(int i=0;i < maxminValue.size();i++)
			{
				
				if(!runningResettable&&port_count==0)
				{
					maxminValue[i] = (*it)[i];
					
				}
				else if(runningResettable&&port_count==0&&count==0)
				{
					maxminValue[i] = (*it)[i];
				}
				else
				{
					T2 tmp = (*it)[i];
					
					if(m_minmax)
					{
						
						if(maxminValue[i] < tmp)
						{
							maxminValue[i] = tmp;
						}
					}
					else
					{
						if(maxminValue[i] > tmp)
						{
							maxminValue[i] = tmp;
						}
					}
				}
				
			}
			port_count++;
		}
		count++;
		
		//for (typename std::vector<T2>::iterator it = maxminValue.begin(); it != maxminValue.end(); ++it)
		//	std::cout << (*it) << std::endl;
		m_outport->setData(maxminValue);
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id)
	{
		count = 0;
		maxminValue.clear();
		return RTC::RTC_OK;
	};

	std::vector<DataTypeInPortSeq<T,T2>*> m_inport;
	DataTypeOutPortSeq<T,T2>* m_outport;
	MinMaxFunction *m_rtc;
	bool runningResettable;
	std::vector<T2> maxminValue;
	bool m_minmax;
	int count;
};

extern "C"
{
  DLL_EXPORT void MinMaxFunctionInit(RTC::Manager* manager);
};

#endif // MINMAXFUNCTION_H
