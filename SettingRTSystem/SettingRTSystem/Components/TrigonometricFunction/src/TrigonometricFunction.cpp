// -*- C++ -*-
/*!
 * @file  TrigonometricFunction.cpp
 * @brief Trigonometric Function
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "TrigonometricFunction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* trigonometricfunction_spec[] =
  {
    "implementation_id", "TrigonometricFunction",
    "type_name",         "TrigonometricFunction",
    "description",       "Trigonometric Function",
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
    "conf.default.function", "sin",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.function", "radio",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedFloat,TimedDoubleSeq,TimedFloatSeq)",
    "conf.__constraints__.function", "(sin,cos,tan,asin,acos,atan,sinh,cosh,tanh,asinh,acosh,atanh)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
TrigonometricFunction::TrigonometricFunction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
TrigonometricFunction::~TrigonometricFunction()
{
}


void TrigonometricFunction::configUpdate()
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
			func = new TrigonometricFunctionSingle<TimedDouble, double>(this,m_function);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new TrigonometricFunctionSingle<TimedFloat, float>(this,m_function);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new TrigonometricFunctionSeq<TimedDoubleSeq, double>(this,m_function);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new TrigonometricFunctionSeq<TimedFloatSeq, float>(this,m_function);
		}
		
		
	}
	if(func)
	{
		func->setFunc(m_function);
	}
}


RTC::ReturnCode_t TrigonometricFunction::onInitialize()
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
  bindParameter("function", m_function, "sin");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t TrigonometricFunction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void TrigonometricFunctionInit(RTC::Manager* manager)
  {
    coil::Properties profile(trigonometricfunction_spec);
    manager->registerFactory(profile,
                             RTC::Create<TrigonometricFunction>,
                             RTC::Delete<TrigonometricFunction>);
  }
  
};


