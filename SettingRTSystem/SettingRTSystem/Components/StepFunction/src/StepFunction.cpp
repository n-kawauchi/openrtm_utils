// -*- C++ -*-
/*!
 * @file  StepFunction.cpp
 * @brief Step Function
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "StepFunction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* stepfunction_spec[] =
  {
    "implementation_id", "StepFunction",
    "type_name",         "StepFunction",
    "description",       "Step Function",
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
    "conf.default.initialValue", "0",
    "conf.default.finalValue", "1",
    "conf.default.stepTime", "1",
    "conf.default.samplingTime", "0.01",
    "conf.default.realTime", "OFF",
    "conf.default.data_size", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.initialValue", "text",
    "conf.__widget__.finalValue", "text",
    "conf.__widget__.stepTime", "text",
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
StepFunction::StepFunction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
StepFunction::~StepFunction()
{
}




void StepFunction::configUpdate()
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
			func = new StepFunctionSingle<TimedDouble, double>(this);
		}
		
		else if(m_dataType == "TimedFloat")
		{
			func = new StepFunctionSingle<TimedFloat, float>(this);
		}
		


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new StepFunctionSeq<TimedDoubleSeq, double>(this);
		}
		
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new StepFunctionSeq<TimedFloatSeq, float>(this);
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
		func->setInitialValue(m_initialValue);
		func->setFinalValue(m_finalValue);
		func->setStepTime(m_stepTime);
		func->setDataSize(m_data_size);
	}
		
}

RTC::ReturnCode_t StepFunction::onInitialize()
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
  bindParameter("initialValue", m_initialValue, "0");
  bindParameter("finalValue", m_finalValue, "1");
  bindParameter("stepTime", m_stepTime, "1");
  bindParameter("samplingTime", m_samplingTime, "0.01");
  bindParameter("realTime", m_realTime, "OFF");
  bindParameter("data_size", m_data_size, "1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t StepFunction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void StepFunctionInit(RTC::Manager* manager)
  {
    coil::Properties profile(stepfunction_spec);
    manager->registerFactory(profile,
                             RTC::Create<StepFunction>,
                             RTC::Delete<StepFunction>);
  }
  
};


