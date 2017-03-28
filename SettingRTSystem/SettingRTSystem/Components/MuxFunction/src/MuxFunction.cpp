// -*- C++ -*-
/*!
 * @file  MuxFunction.cpp
 * @brief Mux Function
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "MuxFunction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* muxfunction_spec[] =
  {
    "implementation_id", "MuxFunction",
    "type_name",         "MuxFunction",
    "description",       "Mux Function",
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
    "conf.default.inportNum", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.inportNum", "spin",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort)",
    "conf.__constraints__.inportNum", "1<=x<=30",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
MuxFunction::MuxFunction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
MuxFunction::~MuxFunction()
{
}


void MuxFunction::configUpdate()
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
			func = new MuxFunctionComp<TimedDouble, TimedDoubleSeq, double>(this,m_inportNum);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new MuxFunctionComp<TimedLong, TimedLongSeq, int>(this,m_inportNum);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new MuxFunctionComp<TimedFloat, TimedFloatSeq, float>(this,m_inportNum);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new MuxFunctionComp<TimedShort, TimedShortSeq, int>(this,m_inportNum);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new MuxFunctionComp<TimedULong, TimedULongSeq, int>(this,m_inportNum);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new MuxFunctionComp<TimedUShort, TimedUShortSeq, int>(this,m_inportNum);
		}

		
	}

	if(func)
	{
		func->changeInPortNum(m_inportNum);
	}
		
}


RTC::ReturnCode_t MuxFunction::onInitialize()
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
  bindParameter("inportNum", m_inportNum, "1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MuxFunction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void MuxFunctionInit(RTC::Manager* manager)
  {
    coil::Properties profile(muxfunction_spec);
    manager->registerFactory(profile,
                             RTC::Create<MuxFunction>,
                             RTC::Delete<MuxFunction>);
  }
  
};


