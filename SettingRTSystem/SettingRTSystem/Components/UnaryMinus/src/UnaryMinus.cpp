// -*- C++ -*-
/*!
 * @file  UnaryMinus.cpp
 * @brief Unary Minus
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "UnaryMinus.h"

// Module specification
// <rtc-template block="module_spec">
static const char* unaryminus_spec[] =
  {
    "implementation_id", "UnaryMinus",
    "type_name",         "UnaryMinus",
    "description",       "Unary Minus",
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
UnaryMinus::UnaryMinus(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
UnaryMinus::~UnaryMinus()
{
}



void UnaryMinus::configUpdate()
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
			func = new UnaryMinusSingle<TimedDouble, double>(this);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new UnaryMinusSingle<TimedLong, int>(this);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new UnaryMinusSingle<TimedFloat, float>(this);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new UnaryMinusSingle<TimedShort, int>(this);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new UnaryMinusSingle<TimedULong, int>(this);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new UnaryMinusSingle<TimedUShort, int>(this);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new UnaryMinusSeq<TimedDoubleSeq, double>(this);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new UnaryMinusSeq<TimedLongSeq, int>(this);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new UnaryMinusSeq<TimedFloatSeq, float>(this);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new UnaryMinusSeq<TimedShortSeq, int>(this);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new UnaryMinusSeq<TimedULongSeq, int>(this);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new UnaryMinusSeq<TimedUShortSeq, int>(this);
		}
		
	}


		
}

RTC::ReturnCode_t UnaryMinus::onInitialize()
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


RTC::ReturnCode_t UnaryMinus::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UnaryMinus::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UnaryMinus::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UnaryMinus::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UnaryMinus::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UnaryMinus::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UnaryMinus::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UnaryMinus::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UnaryMinus::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UnaryMinus::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UnaryMinus::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void UnaryMinusInit(RTC::Manager* manager)
  {
    coil::Properties profile(unaryminus_spec);
    manager->registerFactory(profile,
                             RTC::Create<UnaryMinus>,
                             RTC::Delete<UnaryMinus>);
  }
  
};


