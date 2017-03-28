// -*- C++ -*-
/*!
 * @file  RampFunction.cpp
 * @brief Ramp Function
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "RampFunction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* rampfunction_spec[] =
  {
    "implementation_id", "RampFunction",
    "type_name",         "RampFunction",
    "description",       "Ramp Function",
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
    "conf.default.slope", "1",
    "conf.default.startTime", "0",
    "conf.default.initialOutput", "0",
    "conf.default.samplingTime", "0.01",
    "conf.default.realTime", "OFF",
    "conf.default.data_size", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.slope", "text",
    "conf.__widget__.startTime", "text",
    "conf.__widget__.initialOutput", "text",
    "conf.__widget__.samplingTime", "text",
    "conf.__widget__.realTime", "radio",
    "conf.__widget__.data_size", "spin",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedFloat,TimedDoubleSeq,TimedFloatSeq)",
    "conf.__constraints__.realTime", "(ON,OFF)",
    "conf.__constraints__.data_size", "1<=x<=1000",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RampFunction::RampFunction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
RampFunction::~RampFunction()
{
}



void RampFunction::configUpdate()
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
			func = new RampFunctionSingle<TimedDouble, double>(this);
		}
		
		else if(m_dataType == "TimedFloat")
		{
			func = new RampFunctionSingle<TimedFloat, float>(this);
		}
		


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new RampFunctionSeq<TimedDoubleSeq, double>(this);
		}
		
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new RampFunctionSeq<TimedFloatSeq, float>(this);
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
		func->setSlope(m_slope);
		func->setStartTime(m_startTime);
		func->setInitialOutput(m_initialOutput);
		func->setDataSize(m_data_size);
	}
		
}

RTC::ReturnCode_t RampFunction::onInitialize()
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
  bindParameter("slope", m_slope, "1");
  bindParameter("startTime", m_startTime, "0");
  bindParameter("initialOutput", m_initialOutput, "0");
  bindParameter("samplingTime", m_samplingTime, "0.01");
  bindParameter("realTime", m_realTime, "OFF");
  bindParameter("data_size", m_data_size, "1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RampFunction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void RampFunctionInit(RTC::Manager* manager)
  {
    coil::Properties profile(rampfunction_spec);
    manager->registerFactory(profile,
                             RTC::Create<RampFunction>,
                             RTC::Delete<RampFunction>);
  }
  
};


