// -*- C++ -*-
/*!
 * @file  PIDController.cpp
 * @brief PID Controller
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "PIDController.h"

// Module specification
// <rtc-template block="module_spec">
static const char* pidcontroller_spec[] =
  {
    "implementation_id", "PIDController",
    "type_name",         "PIDController",
    "description",       "PID Controller",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Control",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.dataType", "TimedDouble",
    "conf.default.samplingTime", "0.01",
    "conf.default.realTime", "OFF",
    "conf.default.proportional", "1",
    "conf.default.derivative", "0",
    "conf.default.integral", "0",
    "conf.default.type", "P",
    "conf.default.alpha", "1",
    "conf.default.beta", "0",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.samplingTime", "text",
    "conf.__widget__.realTime", "radio",
    "conf.__widget__.proportional", "text",
    "conf.__widget__.derivative", "text",
    "conf.__widget__.integral", "text",
    "conf.__widget__.type", "radio",
    "conf.__widget__.alpha", "text",
    "conf.__widget__.beta", "text",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedFloat,TimedDoubleSeq,TimedFloatSeq)",
    "conf.__constraints__.realTime", "(ON,OFF)",
    "conf.__constraints__.type", "(P,PD,PI,I,PID)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PIDController::PIDController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
PIDController::~PIDController()
{
}



void PIDController::configUpdate()
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
			func = new PIDControllerSingle<TimedDouble, double>(this);
		}
		
		else if(m_dataType == "TimedFloat")
		{
			func = new PIDControllerSingle<TimedFloat, float>(this);
		}
		


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new PIDControllerSeq<TimedDoubleSeq, double>(this);
		}
		
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new PIDControllerSeq<TimedFloatSeq, float>(this);
		}
		
	}

	if(func)
	{
		func->setFunction(m_type);

		func->setSamplingTime(m_samplingTime);
		if(m_realTime == "ON")
		{
			func->setConfig(true);
		}
		else
		{
			func->setConfig(false);
		}
		
		func->setProportionalValue(m_proportional);
		func->setIntegralValue(m_integral);
		func->setDerivativeValue(m_derivative);
		func->setAlpha(m_alpha);
		func->setBeta(m_beta);


	}
		
}


RTC::ReturnCode_t PIDController::onInitialize()
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
  bindParameter("proportional", m_proportional, "1");
  bindParameter("derivative", m_derivative, "0");
  bindParameter("integral", m_integral, "0");
  bindParameter("type", m_type, "P");
  bindParameter("alpha", m_alpha, "1");
  bindParameter("beta", m_beta, "0");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PIDController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void PIDControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(pidcontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<PIDController>,
                             RTC::Delete<PIDController>);
  }
  
};


