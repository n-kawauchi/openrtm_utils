// -*- C++ -*-
/*!
 * @file  UniformRandomNumber.cpp
 * @brief Uniform Random Number
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "UniformRandomNumber.h"

// Module specification
// <rtc-template block="module_spec">
static const char* uniformrandomnumber_spec[] =
  {
    "implementation_id", "UniformRandomNumber",
    "type_name",         "UniformRandomNumber",
    "description",       "Uniform Random Number",
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
    "conf.default.maximum", "1",
    "conf.default.minimum", "-1",
    "conf.default.seed", "0",
    "conf.default.randomSeedGenerator", "OFF",
    "conf.default.data_size", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.maximum", "text",
    "conf.__widget__.minimum", "text",
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
UniformRandomNumber::UniformRandomNumber(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
UniformRandomNumber::~UniformRandomNumber()
{
}



void UniformRandomNumber::configUpdate()
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
			func = new UniformRandomNumberSingle<TimedDouble, double, std::uniform_real_distribution<double>>(this);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new UniformRandomNumberSingle<TimedLong, int, std::uniform_int_distribution<int>>(this);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new UniformRandomNumberSingle<TimedFloat, float, std::uniform_real_distribution<float>>(this);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new UniformRandomNumberSingle<TimedShort, int, std::uniform_int_distribution<int>>(this);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new UniformRandomNumberSingle<TimedULong, int, std::uniform_int_distribution<int>>(this);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new UniformRandomNumberSingle<TimedUShort, int, std::uniform_int_distribution<int>>(this);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new UniformRandomNumberSeq<TimedDoubleSeq, double, std::uniform_real_distribution<double>>(this);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new UniformRandomNumberSeq<TimedLongSeq, int, std::uniform_int_distribution<int>>(this);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new UniformRandomNumberSeq<TimedFloatSeq, float, std::uniform_real_distribution<float>>(this);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new UniformRandomNumberSeq<TimedShortSeq, int, std::uniform_int_distribution<int>>(this);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new UniformRandomNumberSeq<TimedULongSeq, int, std::uniform_int_distribution<int>>(this);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new UniformRandomNumberSeq<TimedUShortSeq, int, std::uniform_int_distribution<int>>(this);
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
		func->setMaximum(m_maximum);
		func->setMinimum(m_minimum);
		func->setSeed(m_seed);
		func->setDataSize(m_data_size);
	}
		
}

RTC::ReturnCode_t UniformRandomNumber::onInitialize()
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
  bindParameter("maximum", m_maximum, "1");
  bindParameter("minimum", m_minimum, "-1");
  bindParameter("seed", m_seed, "0");
  bindParameter("randomSeedGenerator", m_randomSeedGenerator, "OFF");
  bindParameter("data_size", m_data_size, "1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}





RTC::ReturnCode_t UniformRandomNumber::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UniformRandomNumber::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UniformRandomNumber::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UniformRandomNumber::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UniformRandomNumber::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UniformRandomNumber::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UniformRandomNumber::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UniformRandomNumber::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UniformRandomNumber::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UniformRandomNumber::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t UniformRandomNumber::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void UniformRandomNumberInit(RTC::Manager* manager)
  {
    coil::Properties profile(uniformrandomnumber_spec);
    manager->registerFactory(profile,
                             RTC::Create<UniformRandomNumber>,
                             RTC::Delete<UniformRandomNumber>);
  }
  
};


