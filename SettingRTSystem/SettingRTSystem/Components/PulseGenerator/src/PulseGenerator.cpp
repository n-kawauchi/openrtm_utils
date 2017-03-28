// -*- C++ -*-
/*!
 * @file  PulseGenerator.cpp
 * @brief Pulse Generator
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "PulseGenerator.h"

// Module specification
// <rtc-template block="module_spec">
static const char* pulsegenerator_spec[] =
  {
    "implementation_id", "PulseGenerator",
    "type_name",         "PulseGenerator",
    "description",       "Pulse Generator",
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
    "conf.default.amplitude", "1",
    "conf.default.period", "1",
    "conf.default.pulseWidth", "5",
    "conf.default.phaseDelay", "0",
    "conf.default.samplingTime", "0.01",
    "conf.default.realTime", "OFF",
    "conf.default.data_size", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.amplitude", "text",
    "conf.__widget__.period", "text",
    "conf.__widget__.pulseWidth", "text",
    "conf.__widget__.phaseDelay", "text",
    "conf.__widget__.samplingTime", "text",
    "conf.__widget__.realTime", "radio",
    "conf.__widget__.data_size", "spin",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedFloat,TimedDoubleSeq,TimedFloatSeq)",
    "conf.__constraints__.realTime", "(ON,OFF)",
    "conf.__constraints__.data_size", "1<=x<=1000",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PulseGenerator::PulseGenerator(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
PulseGenerator::~PulseGenerator()
{
}



void PulseGenerator::configUpdate()
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
			func = new PulseGeneratorSingle<TimedDouble, double>(this);
		}
		
		else if(m_dataType == "TimedFloat")
		{
			func = new PulseGeneratorSingle<TimedFloat, float>(this);
		}
		


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new PulseGeneratorSeq<TimedDoubleSeq, double>(this);
		}
		
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new PulseGeneratorSeq<TimedFloatSeq, float>(this);
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
		func->setAmplitude(m_amplitude);
		func->setPeriod(m_period);
		func->setPulseWidth(m_pulseWidth);
		func->setPhaseDelay(m_phaseDelay);
		func->setDataSize(m_data_size);
	}
		
}

RTC::ReturnCode_t PulseGenerator::onInitialize()
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
  bindParameter("amplitude", m_amplitude, "1");
  bindParameter("period", m_period, "1");
  bindParameter("pulseWidth", m_pulseWidth, "5");
  bindParameter("phaseDelay", m_phaseDelay, "0");
  bindParameter("samplingTime", m_samplingTime, "0.01");
  bindParameter("realTime", m_realTime, "OFF");
  bindParameter("data_size", m_data_size, "1");
  // </rtc-template>
  
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onDeactivated(RTC::UniqueId ec_id)
{

  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PulseGenerator::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void PulseGeneratorInit(RTC::Manager* manager)
  {
    coil::Properties profile(pulsegenerator_spec);
    manager->registerFactory(profile,
                             RTC::Create<PulseGenerator>,
                             RTC::Delete<PulseGenerator>);
  }
  
};


