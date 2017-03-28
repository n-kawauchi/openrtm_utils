// -*- C++ -*-
/*!
 * @file  RateLimiter.cpp
 * @brief Rate Limiter
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "RateLimiter.h"

// Module specification
// <rtc-template block="module_spec">
static const char* ratelimiter_spec[] =
  {
    "implementation_id", "RateLimiter",
    "type_name",         "RateLimiter",
    "description",       "Rate Limiter",
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
    "conf.default.samplingTime", "0.01",
    "conf.default.realTime", "OFF",
    "conf.default.risingSlewRate", "1",
    "conf.default.fallingSlewRate", "-1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.samplingTime", "text",
    "conf.__widget__.realTime", "radio",
    "conf.__widget__.risingSlewRate", "text",
    "conf.__widget__.fallingSlewRate", "text",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedFloat,TimedDoubleSeq,TimedFloatSeq)",
    "conf.__constraints__.realTime", "(ON,OFF)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RateLimiter::RateLimiter(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
RateLimiter::~RateLimiter()
{
}


void RateLimiter::configUpdate()
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
			func = new RateLimiterSingle<TimedDouble, double>(this);
		}
		
		else if(m_dataType == "TimedFloat")
		{
			func = new RateLimiterSingle<TimedFloat, float>(this);
		}
		


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new RateLimiterSeq<TimedDoubleSeq, double>(this);
		}
		
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new RateLimiterSeq<TimedFloatSeq, float>(this);
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
		func->setSlewRate(m_risingSlewRate,m_fallingSlewRate);
	}
		
}

RTC::ReturnCode_t RateLimiter::onInitialize()
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
  bindParameter("samplingTime", m_samplingTime, "0.01");
  bindParameter("realTime", m_realTime, "OFF");
  bindParameter("risingSlewRate", m_risingSlewRate, "1");
  bindParameter("fallingSlewRate", m_fallingSlewRate, "-1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RateLimiter::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void RateLimiterInit(RTC::Manager* manager)
  {
    coil::Properties profile(ratelimiter_spec);
    manager->registerFactory(profile,
                             RTC::Create<RateLimiter>,
                             RTC::Delete<RateLimiter>);
  }
  
};


