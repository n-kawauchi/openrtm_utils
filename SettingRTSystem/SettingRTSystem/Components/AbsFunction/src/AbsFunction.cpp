// -*- C++ -*-
/*!
 * @file  AbsFunction.cpp
 * @brief Abs Function
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "AbsFunction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* absfunction_spec[] =
  {
    "implementation_id", "AbsFunction",
    "type_name",         "AbsFunction",
    "description",       "Abs Function",
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
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
AbsFunction::AbsFunction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
AbsFunction::~AbsFunction()
{
}


void AbsFunction::configUpdate()
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
			func = new AbsFunctionSingle<TimedDouble, double>(this);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new AbsFunctionSingle<TimedLong, int>(this);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new AbsFunctionSingle<TimedFloat, float>(this);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new AbsFunctionSingle<TimedShort, int>(this);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new AbsFunctionSingle<TimedULong, int>(this);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new AbsFunctionSingle<TimedUShort, int>(this);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new AbsFunctionSeq<TimedDoubleSeq, double>(this);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new AbsFunctionSeq<TimedLongSeq, int>(this);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new AbsFunctionSeq<TimedFloatSeq, float>(this);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new AbsFunctionSeq<TimedShortSeq, int>(this);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new AbsFunctionSeq<TimedULongSeq, int>(this);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new AbsFunctionSeq<TimedUShortSeq, int>(this);
		}
		
	}


		
}



RTC::ReturnCode_t AbsFunction::onInitialize()
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





RTC::ReturnCode_t AbsFunction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AbsFunction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AbsFunction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AbsFunction::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AbsFunction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AbsFunction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AbsFunction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AbsFunction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AbsFunction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AbsFunction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AbsFunction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void AbsFunctionInit(RTC::Manager* manager)
  {
    coil::Properties profile(absfunction_spec);
    manager->registerFactory(profile,
                             RTC::Create<AbsFunction>,
                             RTC::Delete<AbsFunction>);
  }
  
};


