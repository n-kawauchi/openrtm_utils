// -*- C++ -*-
/*!
 * @file  Polynomial.cpp
 * @brief Polynomial
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "Polynomial.h"

// Module specification
// <rtc-template block="module_spec">
static const char* polynomial_spec[] =
  {
    "implementation_id", "Polynomial",
    "type_name",         "Polynomial",
    "description",       "Polynomial",
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
    "conf.default.coefficients", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.coefficients", "text",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedFloat,TimedDoubleSeq,TimedFloatSeq)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Polynomial::Polynomial(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
Polynomial::~Polynomial()
{
}

void Polynomial::configUpdate()
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
			func = new PolynomialSingle<TimedDouble, double>(this);
		}
		
		else if(m_dataType == "TimedFloat")
		{
			func = new PolynomialSingle<TimedFloat, float>(this);
		}
		


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new PolynomialSeq<TimedDoubleSeq, double>(this);
		}
		
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new PolynomialSeq<TimedFloatSeq, float>(this);
		}
		
		
	}

	if(func)
	{
		func->setCoefficients(m_coefficients);
		
	}
		
}

RTC::ReturnCode_t Polynomial::onInitialize()
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
  bindParameter("coefficients", m_coefficients, "1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onExecute(RTC::UniqueId ec_id)
{
	
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Polynomial::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void PolynomialInit(RTC::Manager* manager)
  {
    coil::Properties profile(polynomial_spec);
    manager->registerFactory(profile,
                             RTC::Create<Polynomial>,
                             RTC::Delete<Polynomial>);
  }
  
};


