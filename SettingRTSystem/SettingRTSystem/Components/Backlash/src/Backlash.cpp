// -*- C++ -*-
/*!
 * @file  Backlash.cpp
 * @brief Backlash
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "Backlash.h"

// Module specification
// <rtc-template block="module_spec">
static const char* backlash_spec[] =
  {
    "implementation_id", "Backlash",
    "type_name",         "Backlash",
    "description",       "Backlash",
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
    "conf.default.initialOutput", "0",
    "conf.default.deadbandWidth", "5",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.initialOutput", "text",
    "conf.__widget__.deadbandWidth", "text",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Backlash::Backlash(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
Backlash::~Backlash()
{
}



void Backlash::configUpdate()
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
			func = new BacklashSingle<TimedDouble, double>(this);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new BacklashSingle<TimedLong, int>(this);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new BacklashSingle<TimedFloat, float>(this);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new BacklashSingle<TimedShort, int>(this);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new BacklashSingle<TimedULong, int>(this);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new BacklashSingle<TimedUShort, int>(this);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new BacklashSeq<TimedDoubleSeq, double>(this);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new BacklashSeq<TimedLongSeq, int>(this);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new BacklashSeq<TimedFloatSeq, float>(this);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new BacklashSeq<TimedShortSeq, int>(this);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new BacklashSeq<TimedULongSeq, int>(this);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new BacklashSeq<TimedUShortSeq, int>(this);
		}
		
	}

	if(func)
	{
		func->setDeadbandWidth(m_deadbandWidth);
		func->setInitialOutput(m_initialOutput);

	}
		
}


RTC::ReturnCode_t Backlash::onInitialize()
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
  bindParameter("initialOutput", m_initialOutput, "0");
  bindParameter("deadbandWidth", m_deadbandWidth, "5");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Backlash::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void BacklashInit(RTC::Manager* manager)
  {
    coil::Properties profile(backlash_spec);
    manager->registerFactory(profile,
                             RTC::Create<Backlash>,
                             RTC::Delete<Backlash>);
  }
  
};


