// -*- C++ -*-
/*!
 * @file  ConstantValue.cpp
 * @brief Constant Value
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "ConstantValue.h"

// Module specification
// <rtc-template block="module_spec">
static const char* constantvalue_spec[] =
  {
    "implementation_id", "ConstantValue",
    "type_name",         "ConstantValue",
    "description",       "Constant Value",
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
    "conf.default.outputValue", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.outputValue", "text",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ConstantValue::ConstantValue(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
ConstantValue::~ConstantValue()
{
}

void ConstantValue::configUpdate()
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
			func = new ConstantValueSingle<TimedDouble, double>(this);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new ConstantValueSingle<TimedLong, int>(this);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new ConstantValueSingle<TimedFloat, float>(this);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new ConstantValueSingle<TimedShort, int>(this);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new ConstantValueSingle<TimedULong, int>(this);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new ConstantValueSingle<TimedUShort, int>(this);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new ConstantValueSeq<TimedDoubleSeq, double>(this);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new ConstantValueSeq<TimedLongSeq, int>(this);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new ConstantValueSeq<TimedFloatSeq, float>(this);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new ConstantValueSeq<TimedShortSeq, int>(this);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new ConstantValueSeq<TimedULongSeq, int>(this);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new ConstantValueSeq<TimedUShortSeq, int>(this);
		}
		
	}

	if(func)
	{
		func->setOutputValue(m_outputValue);

	}
}

RTC::ReturnCode_t ConstantValue::onInitialize()
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
  bindParameter("outputValue", m_outputValue, "1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ConstantValue::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void ConstantValueInit(RTC::Manager* manager)
  {
    coil::Properties profile(constantvalue_spec);
    manager->registerFactory(profile,
                             RTC::Create<ConstantValue>,
                             RTC::Delete<ConstantValue>);
  }
  
};


