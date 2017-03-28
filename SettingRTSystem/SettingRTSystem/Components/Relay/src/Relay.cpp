// -*- C++ -*-
/*!
 * @file  Relay.cpp
 * @brief Relay
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "Relay.h"

// Module specification
// <rtc-template block="module_spec">
static const char* relay_spec[] =
  {
    "implementation_id", "Relay",
    "type_name",         "Relay",
    "description",       "Relay",
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
    "conf.default.switchOnPoint", "1",
    "conf.default.switchOffPoint", "-1",
    "conf.default.outputWhenOn", "1",
    "conf.default.outputWhenOff", "-1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.switchOnPoint", "text",
    "conf.__widget__.switchOffPoint", "text",
    "conf.__widget__.outputWhenOn", "text",
    "conf.__widget__.outputWhenOff", "text",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Relay::Relay(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
Relay::~Relay()
{
}

void Relay::configUpdate()
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
			func = new RelaySingle<TimedDouble, double>(this);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new RelaySingle<TimedLong, int>(this);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new RelaySingle<TimedFloat, float>(this);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new RelaySingle<TimedShort, int>(this);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new RelaySingle<TimedULong, int>(this);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new RelaySingle<TimedUShort, int>(this);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new RelaySeq<TimedDoubleSeq, double>(this);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new RelaySeq<TimedLongSeq, int>(this);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new RelaySeq<TimedFloatSeq, float>(this);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new RelaySeq<TimedShortSeq, int>(this);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new RelaySeq<TimedULongSeq, int>(this);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new RelaySeq<TimedUShortSeq, int>(this);
		}
		
	}

	if(func)
	{
		func->setSwitchPoint(m_switchOnPoint,m_switchOffPoint);
		func->setOutput(m_outputWhenOn,m_outputWhenOff);
	}
		
}

RTC::ReturnCode_t Relay::onInitialize()
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
  bindParameter("switchOnPoint", m_switchOnPoint, "1");
  bindParameter("switchOffPoint", m_switchOffPoint, "-1");
  bindParameter("outputWhenOn", m_outputWhenOn, "1");
  bindParameter("outputWhenOff", m_outputWhenOff, "-1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Relay::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void RelayInit(RTC::Manager* manager)
  {
    coil::Properties profile(relay_spec);
    manager->registerFactory(profile,
                             RTC::Create<Relay>,
                             RTC::Delete<Relay>);
  }
  
};


