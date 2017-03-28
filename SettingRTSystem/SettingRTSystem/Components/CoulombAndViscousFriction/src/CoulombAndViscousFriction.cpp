// -*- C++ -*-
/*!
 * @file  CoulombAndViscousFriction.cpp
 * @brief Coulomb and Viscous Friction
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "CoulombAndViscousFriction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* coulombandviscousfriction_spec[] =
  {
    "implementation_id", "CoulombAndViscousFriction",
    "type_name",         "CoulombAndViscousFriction",
    "description",       "Coulomb and Viscous Friction",
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
    "conf.default.offset", "0",
    "conf.default.gain", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.offset", "text",
    "conf.__widget__.gain", "text",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CoulombAndViscousFriction::CoulombAndViscousFriction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
CoulombAndViscousFriction::~CoulombAndViscousFriction()
{
}

void CoulombAndViscousFriction::configUpdate()
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
			func = new CoulombAndViscousFrictionSingle<TimedDouble, double>(this);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new CoulombAndViscousFrictionSingle<TimedLong, int>(this);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new CoulombAndViscousFrictionSingle<TimedFloat, float>(this);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new CoulombAndViscousFrictionSingle<TimedShort, int>(this);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new CoulombAndViscousFrictionSingle<TimedULong, int>(this);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new CoulombAndViscousFrictionSingle<TimedUShort, int>(this);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new CoulombAndViscousFrictionSeq<TimedDoubleSeq, double>(this);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new CoulombAndViscousFrictionSeq<TimedLongSeq, int>(this);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new CoulombAndViscousFrictionSeq<TimedFloatSeq, float>(this);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new CoulombAndViscousFrictionSeq<TimedShortSeq, int>(this);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new CoulombAndViscousFrictionSeq<TimedULongSeq, int>(this);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new CoulombAndViscousFrictionSeq<TimedUShortSeq, int>(this);
		}
		
	}

	if(func)
	{
		func->setOffset(m_offset);
		func->setGain(m_gain);

	}
}

RTC::ReturnCode_t CoulombAndViscousFriction::onInitialize()
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
  bindParameter("offset", m_offset, "0");
  bindParameter("gain", m_gain, "1");
  // </rtc-template>

  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CoulombAndViscousFriction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void CoulombAndViscousFrictionInit(RTC::Manager* manager)
  {
    coil::Properties profile(coulombandviscousfriction_spec);
    manager->registerFactory(profile,
                             RTC::Create<CoulombAndViscousFriction>,
                             RTC::Delete<CoulombAndViscousFriction>);
  }
  
};


