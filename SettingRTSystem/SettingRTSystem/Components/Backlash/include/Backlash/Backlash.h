// -*- C++ -*-
/*!
 * @file  Backlash.h
 * @brief Backlash
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef BACKLASH_H
#define BACKLASH_H

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

class BacklashCompBase;

/*!
 * @class Backlash
 * @brief Backlash
 *
 * 遊びのあるシステムの動作
 *
 */
class Backlash
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Backlash(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Backlash();
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
   * 初期出力
   * - Name: initialOutput initialOutput
   * - DefaultValue: 0
   */
  std::string m_initialOutput;
  /*!
   * 不感帯の幅
   * - Name: deadbandWidth deadbandWidth
   * - DefaultValue: 5
   */
  std::string m_deadbandWidth;

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
	BacklashCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


class BacklashCompBase : public RTCLogicBase
{
public:
	virtual void setDeadbandWidth(std::string w)
	{
	
	};
	virtual void setInitialOutput(std::string o)
	{

	};
};


template <class T, class T2>
class BacklashSingle : public BacklashCompBase
{
public:
	BacklashSingle(Backlash *rtc)
	{
		m_inport = new DataTypeInPort<T,T2>("in", rtc);
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~BacklashSingle()
	{
		delete m_inport;
		delete m_outport;
	};
	void setDeadbandWidth(std::string w)
	{
		std::vector<T2> tmp;
		if(getValueInString(w,tmp))
		{
			func.setDeadbandWidth(tmp[0]);
		}
		
	};
	void setInitialOutput(std::string o)
	{
		std::vector<T2> tmp;
		if(getValueInString(o,tmp))
		{
			func.setInitialOutput(tmp[0]);
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
	RTBacklash<T2> func;


};



template <class T, class T2>
class BacklashSeq : public BacklashCompBase
{
public:
	BacklashSeq(Backlash *rtc)
	{
		m_inport = new DataTypeInPortSeq<T,T2>("in", rtc);
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~BacklashSeq()
	{
		delete m_inport;
		delete m_outport;
	}
	void setDeadbandWidth(std::string w)
	{
		if(getValueInString(w,deadbandWidth))
		{
			for (int i=0;i < func.size();i++)
			{
				T2 dbw;
				if(getValueInList(deadbandWidth,i,dbw))
					func[i].setDeadbandWidth(dbw);
			}
		}
	};
	void setInitialOutput(std::string o)
	{
		if(getValueInString(o,initialOutput))
		{
			for (int i=0;i < func.size();i++)
			{
				T2 iop;
				if(getValueInList(initialOutput,i,iop))
					func[i].setInitialOutput(iop);
			}
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
					RTBacklash<T2> rtb_tmp = RTBacklash<T2>();
					T2 dbw;
					T2 iop;
					if(!getValueInList(deadbandWidth,i,dbw))return RTC::RTC_ERROR;
					if(!getValueInList(initialOutput,i,iop))return RTC::RTC_ERROR;
					rtb_tmp.setDeadbandWidth(dbw);
					rtb_tmp.setInitialOutput(iop);
					func.push_back(rtb_tmp);
					
				}
				ans.push_back(func[i].calc(data[i]));
				//std::cout << func.size() << "\t" << i << std::endl;
				
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
		for (typename std::vector<RTBacklash<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).reset();
		}
		return RTC::RTC_OK;
	};

	DataTypeInPortSeq<T,T2>* m_inport;
	DataTypeOutPortSeq<T,T2>* m_outport;
	std::vector<RTBacklash<T2>> func;
	std::vector<T2> initialOutput;
	std::vector<T2> deadbandWidth;

};

extern "C"
{
  DLL_EXPORT void BacklashInit(RTC::Manager* manager);
};

#endif // BACKLASH_H
