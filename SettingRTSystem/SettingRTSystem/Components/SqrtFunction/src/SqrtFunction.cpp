// -*- C++ -*-
/*!
 * @file  SqrtFunction.cpp
 * @brief Sqrt Function
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "SqrtFunction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* sqrtfunction_spec[] =
  {
    "implementation_id", "SqrtFunction",
    "type_name",         "SqrtFunction",
    "description",       "Sqrt Function",
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
    // Widget
    "conf.__widget__.dataType", "radio",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedFloat,TimedDoubleSeq,TimedFloatSeq)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SqrtFunction::SqrtFunction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
SqrtFunction::~SqrtFunction()
{
}


void SqrtFunction::configUpdate()
{
	this->m_configsets.update("default");
	coil::eraseBlank(m_dataType);


	if(last_dataType != m_dataType)
	{
		last_dataType = m_dataType;
		if(func)
		{
			delete func;
		}

		if(m_dataType == "TimedDouble")
		{
			func = new SqrtFunctionSingle<TimedDouble, double>(this);
		}
		
		else if(m_dataType == "TimedFloat")
		{
			func = new SqrtFunctionSingle<TimedFloat, float>(this);
		}
		


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new SqrtFunctionSeq<TimedDoubleSeq, double>(this);
		}
		
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new SqrtFunctionSeq<TimedFloatSeq, float>(this);
		}
		
		
	}

	
		
}


RTC::ReturnCode_t SqrtFunction::onInitialize()
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
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SqrtFunction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void SqrtFunctionInit(RTC::Manager* manager)
  {
    coil::Properties profile(sqrtfunction_spec);
    manager->registerFactory(profile,
                             RTC::Create<SqrtFunction>,
                             RTC::Delete<SqrtFunction>);
  }
  
};


