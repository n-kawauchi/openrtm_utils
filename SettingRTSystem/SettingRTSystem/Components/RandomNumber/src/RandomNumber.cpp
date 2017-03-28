// -*- C++ -*-
/*!
 * @file  RandomNumber.cpp
 * @brief Random Number
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "RandomNumber.h"

// Module specification
// <rtc-template block="module_spec">
static const char* randomnumber_spec[] =
  {
    "implementation_id", "RandomNumber",
    "type_name",         "RandomNumber",
    "description",       "Random Number",
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
    "conf.default.mean", "1",
    "conf.default.variance", "1",
    "conf.default.seed", "0",
    "conf.default.randomSeedGenerator", "OFF",
    "conf.default.data_size", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.mean", "text",
    "conf.__widget__.variance", "text",
    "conf.__widget__.seed", "text",
    "conf.__widget__.randomSeedGenerator", "radio",
    "conf.__widget__.data_size", "spin",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
    "conf.__constraints__.randomSeedGenerator", "(ON,OFF)",
    "conf.__constraints__.data_size", "1<=x<=1000",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RandomNumber::RandomNumber(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
RandomNumber::~RandomNumber()
{
}



void RandomNumber::configUpdate()
{
	this->m_configsets.update("default");
	coil::eraseBlank(m_dataType);
	coil::eraseBlank(m_randomSeedGenerator);


	if(last_dataType != m_dataType)
	{
		last_dataType = m_dataType;
		if(func)
		{
			delete func;
		}

		if(m_dataType == "TimedDouble")
		{
			func = new RandomNumberSingle<TimedDouble, double>(this);
		}
		
		else if(m_dataType == "TimedFloat")
		{
			func = new RandomNumberSingle<TimedFloat, float>(this);
		}
		


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new RandomNumberSeq<TimedDoubleSeq, double>(this);
		}
		
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new RandomNumberSeq<TimedFloatSeq, float>(this);
		}
		
		
	}

	if(func)
	{
		if(m_randomSeedGenerator == "ON")
		{
			func->setRandomSeedGenerator(true);
		}
		else
		{
			func->setRandomSeedGenerator(false);
		}
		func->setMean(m_mean);
		func->setVariable(m_variance);
		func->setSeed(m_seed);
		func->setDataSize(m_data_size);
	}
		
}


RTC::ReturnCode_t RandomNumber::onInitialize()
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
  bindParameter("mean", m_mean, "1");
  bindParameter("variance", m_variance, "1");
  bindParameter("seed", m_seed, "0");
  bindParameter("randomSeedGenerator", m_randomSeedGenerator, "OFF");
  bindParameter("data_size", m_data_size, "1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RandomNumber::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void RandomNumberInit(RTC::Manager* manager)
  {
    coil::Properties profile(randomnumber_spec);
    manager->registerFactory(profile,
                             RTC::Create<RandomNumber>,
                             RTC::Delete<RandomNumber>);
  }
  
};


