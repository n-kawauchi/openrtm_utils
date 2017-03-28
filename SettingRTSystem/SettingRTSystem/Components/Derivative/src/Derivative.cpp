// -*- C++ -*-
/*!
 * @file  Derivative.cpp
 * @brief Derivative
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "Derivative.h"

// Module specification
// <rtc-template block="module_spec">
static const char* derivative_spec[] =
  {
    "implementation_id", "Derivative",
    "type_name",         "Derivative",
    "description",       "Derivative",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Math",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.dataType", "TimedDouble",
    "conf.default.samplingTime", "0.01",
    "conf.default.realTime", "OFF",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.samplingTime", "text",
    "conf.__widget__.realTime", "radio",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedFloat,TimedDoubleSeq,TimedFloatSeq)",
    "conf.__constraints__.realTime", "(ON,OFF)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Derivative::Derivative(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
Derivative::~Derivative()
{
}

void Derivative::configUpdate()
{
	this->m_configsets.update("default");
	coil::eraseBlank(m_dataType);
	coil::eraseBlank(m_realTime);

	if(last_dataType != m_dataType)
	{
		last_dataType = m_dataType;
		if(func)
		{
			delete func;
		}

		if(m_dataType == "TimedDouble")
		{
			func = new DerivativeSingle<TimedDouble, double>(this);
		}
		
		else if(m_dataType == "TimedFloat")
		{
			func = new DerivativeSingle<TimedFloat, float>(this);
		}
		


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new DerivativeSeq<TimedDoubleSeq, double>(this);
		}
		
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new DerivativeSeq<TimedFloatSeq, float>(this);
		}
		
		
	}

	if(func)
	{
		func->setSamplingTime(m_samplingTime);
		if(m_realTime == "ON")
		{
			func->setConfig(true);
		}
		else
		{
			func->setConfig(false);
		}
	}
		
}

RTC::ReturnCode_t Derivative::onInitialize()
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
  // Bind variables and configuration variable
  bindParameter("dataType", m_dataType, "TimedDouble");
  bindParameter("samplingTime", m_samplingTime, "0.01");
  bindParameter("realTime", m_realTime, "OFF");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Derivative::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void DerivativeInit(RTC::Manager* manager)
  {
    coil::Properties profile(derivative_spec);
    manager->registerFactory(profile,
                             RTC::Create<Derivative>,
                             RTC::Delete<Derivative>);
  }
  
};


