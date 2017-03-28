// -*- C++ -*-
/*!
 * @file  Saturation.cpp
 * @brief Saturation
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "Saturation.h"

// Module specification
// <rtc-template block="module_spec">
static const char* saturation_spec[] =
  {
    "implementation_id", "Saturation",
    "type_name",         "Saturation",
    "description",       "Saturation",
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
    "conf.default.UpperLimit", "10",
    "conf.default.LowerLimit", "-10",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.UpperLimit", "text",
    "conf.__widget__.LowerLimit", "text",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Saturation::Saturation(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
Saturation::~Saturation()
{
}

void Saturation::configUpdate()
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
			func = new SaturationSingle<TimedDouble, double>(this);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new SaturationSingle<TimedLong, int>(this);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new SaturationSingle<TimedFloat, float>(this);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new SaturationSingle<TimedShort, int>(this);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new SaturationSingle<TimedULong, int>(this);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new SaturationSingle<TimedUShort, int>(this);
		}
		

		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new SaturationSeq<TimedDoubleSeq, double>(this);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new SaturationSeq<TimedLongSeq, int>(this);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new SaturationSeq<TimedFloatSeq, float>(this);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new SaturationSeq<TimedShortSeq, int>(this);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new SaturationSeq<TimedULongSeq, int>(this);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new SaturationSeq<TimedUShortSeq, int>(this);
		}
	}

	if(func)
	{
		func->setLimit(m_UpperLimit,m_LowerLimit);
		
	}
}

RTC::ReturnCode_t Saturation::onInitialize()
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
  bindParameter("UpperLimit", m_UpperLimit, "10");
  bindParameter("LowerLimit", m_LowerLimit, "-10");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Saturation::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void SaturationInit(RTC::Manager* manager)
  {
    coil::Properties profile(saturation_spec);
    manager->registerFactory(profile,
                             RTC::Create<Saturation>,
                             RTC::Delete<Saturation>);
  }
  
};


