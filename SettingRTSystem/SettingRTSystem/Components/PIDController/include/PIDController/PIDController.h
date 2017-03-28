// -*- C++ -*-
/*!
 * @file  PIDController.h
 * @brief PID Controller
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

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

class PIDControllerCompBase;

/*!
 * @class PIDController
 * @brief PID Controller
 *
 * PID制御
 *
 */
class PIDController
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  PIDController(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~PIDController();
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
   * 比例項
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: P proportional
   * - DefaultValue: 1
   */
  std::string m_proportional;
  /*!
   * 微分項
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: D derivative
   * - DefaultValue: 0
   */
  std::string m_derivative;
  /*!
   * 積分項
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: I integral
   * - DefaultValue: 0
   */
  std::string m_integral;
  /*!
   * コントローラーのタイプ
   * - Name: type type
   * - DefaultValue: P
   */
  std::string m_type;
  /*!
   * 比例設定点の重み
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: alpha alpha
   * - DefaultValue: 0
   */
  std::string m_alpha;
  /*!
   * 微分設定点の重み
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: beta beta
   * - DefaultValue: 0
   */
  std::string m_beta;

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
	PIDControllerCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


class PIDControllerCompBase : public RTCLogicBase
{
public:
	virtual void setSamplingTime(double s)
	{
	
	};
	virtual void setConfig(bool c)
	{

	};
	virtual void setProportionalValue(std::string v)
	{
	};
	virtual void setIntegralValue(std::string v)
	{

	};
	virtual void setDerivativeValue(std::string v)
	{

	};
	virtual void setAlpha(std::string v)
	{

	};
	virtual void setBeta(std::string v)
	{

	};
	virtual void setFunction(std::string name)
	{

	};
};



template <class T, class T2>
class PIDControllerSingle : public PIDControllerCompBase
{
public:
	PIDControllerSingle(PIDController *rtc)
	{
		m_inport_SP = new DataTypeInPort<T,T2>("sp", rtc);
		m_inport_PV = new DataTypeInPort<T,T2>("pv", rtc);
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		func = new RTPController<T2>();
		func_name = "P";
	};
	~PIDControllerSingle()
	{
		delete m_inport_SP;
		delete m_inport_PV;
		delete m_outport;
	};
	RTController<T2> *getFunction(std::string name)
	{
		if(name == "P")
		{
			return new RTPController<T2>();
		}
		else if(name == "PD")
		{
			return new RTPDController<T2>();
		}
		else if(name == "PI")
		{
			return new RTPIController<T2>();
		}
		else if(name == "I")
		{
			return new RTIController<T2>();
		}
		else if(name == "PID")
		{
			return new RTPIDController<T2>();
		}
		return NULL;
	};
	void setFunction(std::string name)
	{
		coil::eraseBlank(name);
		if(func_name != name)
		{
			func_name = name;
			if(func)
			{
				delete func;
			}
			func = getFunction(func_name);
		}
	};
	void setSamplingTime(double s)
	{
		func->setSamplingTime(s);
	};
	void setConfig(bool c)
	{
		func->setConfig(c);
	};

	void setProportionalValue(std::string v)
	{
		std::vector<T2> tmp_v;
		if(getValueInString(v,tmp_v))
		{
			func->setProportionalValue(tmp_v[0]);
		}
	};
	void setIntegralValue(std::string v)
	{
		std::vector<T2> tmp_v;
		if(getValueInString(v,tmp_v))
		{
			func->setIntegralValue(tmp_v[0]);
		}
	};
	void setDerivativeValue(std::string v)
	{
		std::vector<T2> tmp_v;
		if(getValueInString(v,tmp_v))
		{
			func->setDerivativeValue(tmp_v[0]);
		}
	};
	void setAlpha(std::string v)
	{
		std::vector<T2> tmp_v;
		if(getValueInString(v,tmp_v))
		{
			func->setAlpha(tmp_v[0]);
		}
	};
	void setBeta(std::string v)
	{
		std::vector<T2> tmp_v;
		if(getValueInString(v,tmp_v))
		{
			func->setBeta(tmp_v[0]);
		}
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport_SP->isNew() && m_inport_PV->isNew())
		{
			T2 ans;
			if(func->calc(m_inport_SP->getData(), m_inport_PV->getData(), ans))
			{
				//std::cout << ans << std::endl;
				m_outport->setData(ans);
			}
		}
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){
		//last_realTime = coil::TimeValue(coil::gettimeofday());
		func->reset();
		return RTC::RTC_OK;
	};

	DataTypeInPort<T,T2>* m_inport_SP;
	DataTypeInPort<T,T2>* m_inport_PV;
	DataTypeOutPort<T,T2>* m_outport;
	RTController<T2> *func;
	std::string func_name;
};



template <class T, class T2>
class PIDControllerSeq : public PIDControllerCompBase
{
public:
	PIDControllerSeq(PIDController *rtc)
	{
		m_inport_SP = new DataTypeInPortSeq<T,T2>("sp", rtc);
		m_inport_PV = new DataTypeInPortSeq<T,T2>("pv", rtc);
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~PIDControllerSeq()
	{
		delete m_inport_SP;
		delete m_inport_PV;
		delete m_outport;
		for (typename std::vector<RTController<T2>*>::iterator it = func.begin(); it != func.end(); ++it)
		{
			delete (*it);
		}
	}
	RTController<T2> *getFunction(std::string name)
	{
		if(name == "P")
		{
			return new RTPController<T2>();
		}
		else if(name == "PD")
		{
			return new RTPDController<T2>();
		}
		else if(name == "PI")
		{
			return new RTPIController<T2>();
		}
		else if(name == "I")
		{
			return new RTIController<T2>();
		}
		else if(name == "PID")
		{
			return new RTPIDController<T2>();
		}
		return NULL;
	};
	void setFunction(std::string name)
	{
		coil::eraseBlank(name);
		if(func_name != name)
		{
			func_name = name;
			for (typename std::vector<RTController<T2>*>::iterator it = func.begin(); it != func.end(); ++it)
			{
				if(*it)
				{
					delete (*it);
				}
				(*it) = getFunction(func_name);
			}
			
		}
	};
	void setSamplingTime(double s)
	{
		samplingTime = s;
		for (typename std::vector<RTController<T2>*>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it)->setSamplingTime(s);
		}
	};
	void setConfig(bool c)
	{
		realTime = c;
		for (typename std::vector<RTController<T2>*>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it)->setConfig(c);
		}
	};
	
	void setProportionalValue(std::string v)
	{
		getValueInString(v,m_proportional);
		for (int i=0;i < func.size();i++)
		{
			T2 p;
			if(!getValueInList<T2>(m_proportional,i,p))return;
			
			func[i]->setProportionalValue(p);
		}
	};
	void setIntegralValue(std::string v)
	{
		getValueInString(v,m_integral);
		for (int i=0;i < func.size();i++)
		{
			T2 p;
			if(!getValueInList<T2>(m_integral,i,p))return;
			
			func[i]->setIntegralValue(p);
		}
	};
	void setDerivativeValue(std::string v)
	{
		getValueInString(v,m_derivative);
		for (int i=0;i < func.size();i++)
		{
			T2 p;
			if(!getValueInList<T2>(m_derivative,i,p))return;
			
			func[i]->setDerivativeValue(p);
		}
	};
	void setAlpha(std::string v)
	{
		getValueInString(v,m_alpha);
		for (int i=0;i < func.size();i++)
		{
			T2 p;
			if(!getValueInList<T2>(m_alpha,i,p))return;
			
			func[i]->setAlpha(p);
		}
	};
	void setBeta(std::string v)
	{
		getValueInString(v,m_beta);
		for (int i=0;i < func.size();i++)
		{
			T2 p;
			if(!getValueInList<T2>(m_beta,i,p))return;
			
			func[i]->setBeta(p);
		}
	};
	
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		if(m_inport_SP->isNew() && m_inport_PV->isNew())
		{
			std::vector<T2> data_SP = m_inport_SP->getData();
			std::vector<T2> data_PV = m_inport_PV->getData();

			int dataSize = (int)data_SP.size();
			if(dataSize > (int)data_PV.size())
			{
				dataSize = (int)data_PV.size();
			}

			for(int i=0;i < dataSize;i++)
			{
				
				if((int)func.size()-1 < i)
				{
					RTController<T2> *rti_tmp = getFunction(func_name);
					rti_tmp->setSamplingTime(samplingTime);
					rti_tmp->setConfig(realTime);
					T2 v;
					if(!getValueInList(m_proportional,i,v))return RTC::RTC_ERROR;
					rti_tmp->setProportionalValue(v);
					if(!getValueInList(m_integral,i,v))return RTC::RTC_ERROR;
					rti_tmp->setIntegralValue(v);
					if(!getValueInList(m_derivative,i,v))return RTC::RTC_ERROR;
					rti_tmp->setDerivativeValue(v);
					if(!getValueInList(m_alpha,i,v))return RTC::RTC_ERROR;
					rti_tmp->setAlpha(v);
					if(!getValueInList(m_beta,i,v))return RTC::RTC_ERROR;
					rti_tmp->setBeta(v);
					

					func.push_back(rti_tmp);
					
				}

			}
			std::vector<T2> ans;
			for(int i=0;i < func.size();i++)
			{
				T2 tmp;
				if(func[i]->calc(data_SP[i], data_PV[i], tmp))
				{
					ans.push_back(tmp);
				}
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
		for (typename std::vector<RTController<T2>*>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it)->reset();
		}
		return RTC::RTC_OK;
	};

	DataTypeInPortSeq<T,T2>* m_inport_SP;
	DataTypeInPortSeq<T,T2>* m_inport_PV;
	DataTypeOutPortSeq<T,T2>* m_outport;
	std::vector<RTController<T2>*> func;
	bool realTime;
	double samplingTime;
	std::vector<T2> m_proportional;
	std::vector<T2> m_integral;
	std::vector<T2> m_derivative;
	std::vector<T2> m_alpha;
	std::vector<T2> m_beta;
	std::string func_name;

};

extern "C"
{
  DLL_EXPORT void PIDControllerInit(RTC::Manager* manager);
};

#endif // PIDCONTROLLER_H
