// -*- C++ -*-
/*!
 * @file  Scope.cpp
 * @brief Scope
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "Scope.h"

Scope *Scope::obj = NULL;

// Module specification
// <rtc-template block="module_spec">
static const char* scope_spec[] =
  {
    "implementation_id", "Scope",
    "type_name",         "Scope",
    "description",       "Scope",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Viewer",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
	"conf.default.dataType", "TimedDouble",
	"conf.default.timeRange", "10",
	"conf.default.valueRange_low", "-5",
	"conf.default.valueRange_high", "5",
	"conf.default.samplingNum", "1",
	"conf.default.XAxis", "X",
	"conf.default.YAxis", "Y",
	"conf.default.max_pointNum", "100",
	"conf.default.samplingTime", "0.01",
	"conf.default.realTime", "OFF",
	"conf.__widget__.dataType", "radio",
	"conf.__widget__.timeRange", "spin",
	"conf.__widget__.valueRange_low", "spin",
	"conf.__widget__.valueRange_high", "spin",
	"conf.__widget__.samplingNum", "spin",
	"conf.__widget__.XAxis", "text",
	"conf.__widget__.YAxis", "text",
	"conf.__widget__.max_pointNum", "spin",
	"conf.__widget__.samplingTime", "text",
	"conf.__widget__.realTime", "radio",
	"conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
	"conf.__constraints__.timeRange", "0<=x<=10000",
	"conf.__constraints__.valueRange_low", "-10000<=x<=10000",
	"conf.__constraints__.valueRange_high", "-10000<=x<=10000",
	"conf.__constraints__.samplingNum", "1<=x<=1000",
	"conf.__constraints__.max_pointNum", "1<=x<=100000",
	"conf.__constraints__.realTime", "(ON,OFF)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Scope::Scope(RTC::Manager* manager)
    // <rtc-template block="initializer">
	: DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
	changeFlag = false;

}

/*!
 * @brief destructor
 */
Scope::~Scope()
{
}

void Scope::setConfigParam_Name(std::string name, std::string value)
{
	coil::Properties confSet("default");
	confSet.setProperty(name, value);
	this->m_configsets.setConfigurationSetValues(confSet);
	this->m_configsets.activateConfigurationSet("default");
	this->m_configsets.update("default");
}

void Scope::configUpdate()
{
	this->m_configsets.update("default");
	
	coil::eraseBlank(m_dataType);
	setDataPort(m_dataType);

	mutex_.lock();
	if (func)
	{
		
		func->setSamplingTime(m_samplingTime);
		if (m_realTime == "ON")
		{
			func->setConfig(true);
		}
		else
		{
			func->setConfig(false);
		}
		//func->setMaxPointNum(m_valueRange_low);
		//func->setMaxPointNum(m_valueRange_high);
		
		func->setSamplingNum(m_samplingNum);
		//func->setMaxPointNum(m_XAxis);
		//func->setMaxPointNum(m_YAxis);
		func->setMaxPointNum(m_max_pointNum);
		
	}
	mutex_.unlock();
}

double Scope::getTimeRange()
{
	return m_timeRange;
}

double Scope::getValueRange_low()
{
	return m_valueRange_low;
}
double Scope::getValueRange_high()
{
	return m_valueRange_high;
}
std::string Scope::getXAxis()
{
	return m_XAxis;
}
std::string Scope::getYAxis()
{
	return m_YAxis;
}


void Scope::setDataPort(std::string s)
{
	mutex_.lock();
	if (last_dataType != s)
	{
		last_dataType = s;
		if (func)
		{
			delete func;
		}

		if (last_dataType == "TimedDouble")
		{
			func = new GraphDataPortSingle<TimedDouble, double>(this);
		}
		else if (last_dataType == "TimedLong")
		{
			func = new GraphDataPortSingle<TimedLong, int>(this);
		}
		else if (last_dataType == "TimedFloat")
		{
			func = new GraphDataPortSingle<TimedFloat, float>(this);
		}
		else if (last_dataType == "TimedShort")
		{
			func = new GraphDataPortSingle<TimedShort, int>(this);
		}
		else if (last_dataType == "TimedULong")
		{
			func = new GraphDataPortSingle<TimedULong, int>(this);
		}
		else if (last_dataType == "TimedUShort")
		{
			func = new GraphDataPortSingle<TimedUShort, int>(this);
		}


		else if (last_dataType == "TimedDoubleSeq")
		{
			func = new GraphDataPortSeq<TimedDoubleSeq, double>(this);
		}
		else if (last_dataType == "TimedLongSeq")
		{
			func = new GraphDataPortSeq<TimedLongSeq, int>(this);
		}
		else if (last_dataType == "TimedFloatSeq")
		{
			func = new GraphDataPortSeq<TimedFloatSeq, float>(this);
		}
		else if (last_dataType == "TimedShortSeq")
		{
			func = new GraphDataPortSeq<TimedShortSeq, int>(this);
		}
		else if (last_dataType == "TimedULongSeq")
		{
			func = new GraphDataPortSeq<TimedULongSeq, int>(this);
		}
		else if (last_dataType == "TimedUShortSeq")
		{
			func = new GraphDataPortSeq<TimedUShortSeq, int>(this);
		}


	}
	
	mutex_.unlock();
	
}

void Scope::setMaxPointNum(int num)
{
	mutex_.lock();
	if (func)
	{
		
		func->setMaxPointNum(num);
		
	}
	mutex_.unlock();
}
void Scope::setSamplingNum(int num)
{
	mutex_.lock();
	if (func)
	{
		
		func->setSamplingNum(num);
		
	}
	mutex_.unlock();
}

bool Scope::update()
{
	bool ans = false;
	mutex_.lock();
	if (func)
	{
		
		ans = func->update();
		
	}
	mutex_.unlock();
	return ans;

}
void Scope::reset()
{
	mutex_.lock();
	if (func)
	{
		
		func->reset();
		
	}
	mutex_.unlock();
	
}
std::vector<QVector<QPointF>> Scope::getPointList()
{
	std::vector<QVector<QPointF>> ans;
	mutex_.lock();
	if (func)
	{
		
		ans = func->getPointList();
		
		
	}
	mutex_.unlock();
	
	return ans;
}

RTC::ReturnCode_t Scope::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
	//setDataPort("TimedDouble");
	bindParameter("dataType", m_dataType, "TimedDouble");
	bindParameter("timeRange", m_timeRange, "10");
	bindParameter("valueRange_low", m_valueRange_low, "-5");
	bindParameter("valueRange_high", m_valueRange_high, "5");
	bindParameter("samplingNum", m_samplingNum, "1");
	bindParameter("XAxis", m_XAxis, "X");
	bindParameter("YAxis", m_YAxis, "Y");
	bindParameter("max_pointNum", m_max_pointNum, "100");
	bindParameter("samplingTime", m_samplingTime, "0.01");
	bindParameter("realTime", m_realTime, "OFF");

	Scope::obj = this;
	configUpdate();
	this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onFinalize()
{
	Scope::obj = NULL;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onActivated(RTC::UniqueId ec_id)
{
	reset();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Scope::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void ScopeInit(RTC::Manager* manager)
  {
    coil::Properties profile(scope_spec);
    manager->registerFactory(profile,
                             RTC::Create<Scope>,
                             RTC::Delete<Scope>);
  }
  
};


