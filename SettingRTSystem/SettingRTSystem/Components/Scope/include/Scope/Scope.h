// -*- C++ -*-
/*!
 * @file  Scope.h
 * @brief Scope
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef SCOPE_H
#define SCOPE_H

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
#include <qwt_plot.h>

#include "DyPortBase.h"
#include "RTMath.h"

class GraphDataPortBase;

/*!
 * @class Scope
 * @brief Scope
 *
 * 入力データをグラフで表示
 *
 */
class Scope
	: public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Scope(RTC::Manager* manager);
  void configUpdate();
  bool changeFlag;
  /*!
   * @brief destructor
   */
  ~Scope();
  void setDataPort(std::string s);
  static Scope *obj;
  bool update();
  void reset();
  void setMaxPointNum(int num);
  void setSamplingNum(int num);
  std::vector<QVector<QPointF>> getPointList();
  double getTimeRange();
  double getValueRange_low();
  double getValueRange_high();
  std::string getXAxis();
  std::string getYAxis();
  void setConfigParam_Name(std::string name, std::string value);
  coil::Mutex mutex_;
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
	 std::string m_dataType;
	 double m_timeRange;
	 double m_valueRange_low;
	 double m_valueRange_high;
	 int m_samplingNum;
	 std::string m_XAxis;
	 std::string m_YAxis;
	 int m_max_pointNum;
	 double m_samplingTime;
	 std::string m_realTime;
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">

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
	 GraphDataPortBase *func;
	 std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};

class GraphDataPortBase : public RTMath<double>
{
public:
	virtual ~GraphDataPortBase()
	{
	}
	
	virtual bool update()
	{
		return false;
	};
	virtual void reset()
	{
		sampleCount = 0;
		resetTime();
		plist.clear();
		plist.push_back(QVector<QPointF>());
	};
	virtual void updateList()
	{
		for (std::vector<QVector<QPointF>>::iterator it = plist.begin(); it != plist.end(); ++it)
		{
			/*for (QVector<QPointF>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2)
			{

			}*/
			if ((*it).size() > maxPointNum)
			{
				(*it).pop_front();
			}
		}

	};
	virtual std::vector<QVector<QPointF>> getPointList()
	{
		
		return plist;
	};
	
	virtual void setMaxPointNum(int num)
	{
		maxPointNum = num;
	};
	virtual void setSamplingNum(int num)
	{
		samplingNum = num;
	};
	std::vector<QVector<QPointF>>  plist;
	int maxPointNum;
	int samplingNum;
	int sampleCount;
};


template <class T, class T2>
class GraphDataPortSingle : public GraphDataPortBase
{
public:
	GraphDataPortSingle(Scope *rtc)
	{
		m_inport = new DataTypeInPort<T, T2>("in", rtc);
		reset();
	};
	~GraphDataPortSingle()
	{
		delete m_inport;
	}
	bool update()
	{
		
		updateList();
		if (!m_inport->isNew())return false;
		while (m_inport->isNew())
		{
			double data = (double)m_inport->getData();
			sampleCount++;
			double tm = getTime();
			if (sampleCount%samplingNum == 0)
			{
				QPointF point = QPointF(tm, data);
				plist[0].push_back(point);
			}
		}
		return true;
		
	};
	


	DataTypeInPort<T, T2>* m_inport;
	RTStepFunction<T2> func;


};



template <class T, class T2>
class GraphDataPortSeq : public GraphDataPortBase
{
public:
	GraphDataPortSeq(Scope *rtc)
	{
		m_inport = new DataTypeInPortSeq<T, T2>("in", rtc);
		reset();
	};
	~GraphDataPortSeq()
	{
		delete m_inport;
	}
	bool update()
	{
		updateList();
		if (!m_inport->isNew())return false;
		while (m_inport->isNew())
		{
			std::vector<T2> data = m_inport->getData();
			sampleCount++;
			double tm = getTime();
			if (sampleCount%samplingNum == 0)
			{
				
				for (int i = 0; i < data.size(); i++)
				{
					if ((int)plist.size() - 1 < i)
					{
						plist.push_back(QVector<QPointF>());
					}


					QPointF point = QPointF(tm, data[i]);
					plist[i].push_back(point);
				}
			}
			
		}
		return true;

	};



	DataTypeInPortSeq<T, T2>* m_inport;
	RTStepFunction<T2> func;


};




extern "C"
{
  DLL_EXPORT void ScopeInit(RTC::Manager* manager);
};

#endif // SCOPE_H
