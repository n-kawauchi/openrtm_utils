// -*- C++ -*-
/*!
 * @file  UniformRandomNumber.h
 * @brief Uniform Random Number
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef UNIFORMRANDOMNUMBER_H
#define UNIFORMRANDOMNUMBER_H

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

class UniformRandomNumberCompBase;

/*!
 * @class UniformRandomNumber
 * @brief Uniform Random Number
 *
 * 一様分布する乱数を生成
 *
 */
class UniformRandomNumber
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  UniformRandomNumber(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~UniformRandomNumber();
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
   * 最大値
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: maximum maximum
   * - DefaultValue: 1
   */
  std::string m_maximum;
  /*!
   * 最小値
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: minimum minimum
   * - DefaultValue: -1
   */
  std::string m_minimum;
  /*!
   * 初期シード
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: seed seed
   * - DefaultValue: 0
   */
  std::string m_seed;
  /*!
   * ONの時は初期シードを非決定的乱数生成器で生成します。
   * - Name: randomSeedGenerator randomSeedGenerator
   * - DefaultValue: OFF
   * - Constraint: (ON,OFF)
   */
  std::string m_randomSeedGenerator;
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
	UniformRandomNumberCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


class UniformRandomNumberCompBase : public RTCLogicBase
{
public:
	virtual void setMaximum(std::string m)
	{
	
	};
	virtual void setMinimum(std::string m)
	{

	};
	virtual void setSeed(std::string s)
	{

	};
	virtual void setRandomSeedGenerator(bool p)
	{

	};
	virtual void setDataSize(int s)
	{

	};
};



template <class T, class T2, class T3>
class UniformRandomNumberSingle : public UniformRandomNumberCompBase
{
public:
	UniformRandomNumberSingle(UniformRandomNumber *rtc)
	{
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~UniformRandomNumberSingle()
	{
		delete m_outport;
	}
	
	

	
	void setMaximum(std::string m)
	{
		std::vector<T2> tmp_mm;
		if(getValueInString(m,tmp_mm))
		{
			func.setMaximum(tmp_mm[0]);
		}
	};
	void setMinimum(std::string m)
	{
		std::vector<T2> tmp_mm;
		if(getValueInString(m,tmp_mm))
		{
			func.setMinimum(tmp_mm[0]);
		}
	};
	void setSeed(std::string s)
	{
		std::vector<unsigned int> tmp_sd;
		if(getValueInString(s,tmp_sd))
		{
			func.setSeed(tmp_sd[0]);
		}
	};
	void setRandomSeedGenerator(bool p)
	{
		func.setRandomSeedGenerator(p);
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
	}


	DataTypeOutPort<T,T2>* m_outport;
	RTUniformRandomNumber<T2,T3> func;
	

};


template <class T, class T2, class T3>
class UniformRandomNumberSeq : public UniformRandomNumberCompBase
{
public:
	UniformRandomNumberSeq(UniformRandomNumber *rtc)
	{
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~UniformRandomNumberSeq()
	{
		delete m_outport;
	}
	
	void setMaximum(std::string m)
	{
		getValueInString(m,m_maximum);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(m_maximum,i,v))return;
			func[i].setMaximum(v);
		}
	};
	void setMinimum(std::string m)
	{
		getValueInString(m,m_minimum);
		for (int i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(m_minimum,i,v))return;
			func[i].setMinimum(v);
		}
	};
	void setSeed(std::string s)
	{
		getValueInString(s,m_seed);
		for (int i=0;i < func.size();i++)
		{
			unsigned int v;
			if(!getValueInList<unsigned int>(m_seed,i,v))return;
			func[i].setSeed(v);
		}
	};
	void setRandomSeedGenerator(bool p)
	{
		m_randomSeedGenerator = p;
		for (typename std::vector<RTUniformRandomNumber<T2,T3>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setRandomSeedGenerator(p);
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
					RTUniformRandomNumber<T2,T3> sw_tmp = RTUniformRandomNumber<T2,T3>();

					T2 v;
					if(!getValueInList(m_maximum,i,v))return RTC::RTC_ERROR;
					sw_tmp.setMaximum(v);
					if(!getValueInList(m_minimum,i,v))return RTC::RTC_ERROR;
					sw_tmp.setMinimum(v);
					
					unsigned int v2;
					if(!getValueInList(m_seed,i,v2))return RTC::RTC_ERROR;
					sw_tmp.setSeed(v2);
					sw_tmp.setRandomSeedGenerator(m_randomSeedGenerator);
					

					func.push_back(sw_tmp);
					
				}
				
			}
			std::vector<T2> ans;
			for (typename std::vector<RTUniformRandomNumber<T2,T3>>::iterator it = func.begin(); it != func.end(); ++it)
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
		for (typename std::vector<RTUniformRandomNumber<T2,T3>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).reset();
		}
		return RTC::RTC_OK;
	}

	DataTypeOutPortSeq<T,T2>* m_outport;
	std::vector<RTUniformRandomNumber<T2,T3>> func;

	std::vector<T2> m_maximum;
	std::vector<T2> m_minimum;
	std::vector<unsigned int> m_seed;
	bool m_randomSeedGenerator;
	int m_data_size;
};


extern "C"
{
  DLL_EXPORT void UniformRandomNumberInit(RTC::Manager* manager);
};

#endif // UNIFORMRANDOMNUMBER_H
