// -*- C++ -*-
/*!
 * @file  CoulombAndViscousFriction.h
 * @brief Coulomb and Viscous Friction
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef COULOMBANDVISCOUSFRICTION_H
#define COULOMBANDVISCOUSFRICTION_H

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

class CoulombAndViscousFrictionCompBase;

/*!
 * @class CoulombAndViscousFriction
 * @brief Coulomb and Viscous Friction
 *
 * DataInportからの入力が零点で不連続性を、それ以外では線形ゲインの
 * データをDataOutPortから出力するRTC
 *
 */
class CoulombAndViscousFriction
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  CoulombAndViscousFriction(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~CoulombAndViscousFriction();
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
   * 
   * - Name: dataType dataType
   * - DefaultValue: TimedDouble
   * - Constraint: (TimedDouble,TimedLong,TimedFloat,TimedShort,Ti
   *               medULong,TimedUShort,TimedDoubleSeq,TimedLongSe
   *               q,TimedFloatSeq,TimedShortSeq,TimedULongSeq,Tim
   *               edUShortSeq)
   */
  std::string m_dataType;
  /*!
   * オフセット値
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name:  offset
   * - DefaultValue: 0
   */
  std::string m_offset;
  /*!
   * ゲイン
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: gain gain
   * - DefaultValue: 1
   */
  std::string m_gain;

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
	CoulombAndViscousFrictionCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


class CoulombAndViscousFrictionCompBase : public RTCLogicBase
{
public:
	virtual void setOffset(std::string o)
	{
	
	};
	virtual void setGain(std::string g)
	{

	};
};


template <class T, class T2>
class CoulombAndViscousFrictionSingle : public CoulombAndViscousFrictionCompBase
{
public:
	CoulombAndViscousFrictionSingle(CoulombAndViscousFriction *rtc)
	{
		m_inport = new DataTypeInPort<T,T2>("in", rtc);
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~CoulombAndViscousFrictionSingle()
	{
		delete m_inport;
		delete m_outport;
	};
	void setOffset(std::string o)
	{
		std::vector<T2> tmp;
		if(getValueInString(o,tmp))
		{
			offset = tmp[0];
		}
		
	};
	void setGain(std::string g)
	{
		std::vector<T2> tmp;
		if(getValueInString(g,tmp))
		{
			gain = tmp[0];
		}
		
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport->isNew())
		{
			T2 ans = RTCoulombAndViscousFriction<T2>(m_inport->getData(),offset,gain);
			
			//std::cout << ans << std::endl;
			m_outport->setData(ans);
			
			
		}
		return RTC::RTC_OK;
	};

	DataTypeInPort<T,T2>* m_inport;
	DataTypeOutPort<T,T2>* m_outport;
	T2 offset;
	T2 gain;

};



template <class T, class T2>
class CoulombAndViscousFrictionSeq : public CoulombAndViscousFrictionCompBase
{
public:
	CoulombAndViscousFrictionSeq(CoulombAndViscousFriction *rtc)
	{
		m_inport = new DataTypeInPortSeq<T,T2>("in", rtc);
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~CoulombAndViscousFrictionSeq()
	{
		delete m_inport;
		delete m_outport;
	}
	void setOffset(std::string o)
	{
		getValueInString(o,offset);
		
	};
	void setGain(std::string g)
	{
		getValueInString(g,gain);
		
	};
	
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport->isNew())
		{
			std::vector<T2> data = m_inport->getData();
			std::vector<T2> ans;
			for(int i=0;i < data.size();i++)
			{
				T2 ofs;
				T2 gn;
				if(!getValueInList(offset,i,ofs))return RTC::RTC_ERROR;
				if(!getValueInList(gain,i,gn))return RTC::RTC_ERROR;
				T2 value = RTCoulombAndViscousFriction<T2>(data[i],ofs,gn);
				ans.push_back(value);
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
	

	DataTypeInPortSeq<T,T2>* m_inport;
	DataTypeOutPortSeq<T,T2>* m_outport;
	std::vector<T2> offset;
	std::vector<T2> gain;

};

extern "C"
{
  DLL_EXPORT void CoulombAndViscousFrictionInit(RTC::Manager* manager);
};

#endif // COULOMBANDVISCOUSFRICTION_H
