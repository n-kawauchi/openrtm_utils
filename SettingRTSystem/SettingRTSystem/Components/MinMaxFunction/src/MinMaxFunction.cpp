// -*- C++ -*-
/*!
 * @file  MinMaxFunction.cpp
 * @brief MinMax Function
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "MinMaxFunction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* minmaxfunction_spec[] =
  {
    "implementation_id", "MinMaxFunction",
    "type_name",         "MinMaxFunction",
    "description",       "MinMax Function",
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
    "conf.default.runningResettable", "OFF",
    "conf.default.maxmin", "Max",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.inportNum", "spin",
    "conf.__widget__.runningResettable", "radio",
    "conf.__widget__.maxmin", "radio",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
    "conf.__constraints__.inportNum", "0<=x<=30",
    "conf.__constraints__.runningResettable", "(ON,OFF)",
    "conf.__constraints__.maxmin", "(Max,Min)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
MinMaxFunction::MinMaxFunction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
MinMaxFunction::~MinMaxFunction()
{
}

void MinMaxFunction::configUpdate()
{
	this->m_configsets.update("default");
	coil::eraseBlank(m_dataType);
	coil::eraseBlank(m_runningResettable);
	coil::eraseBlank(m_maxmin);


	if(last_dataType != m_dataType)
	{
		last_dataType = m_dataType;
		if(func)
		{
			delete func;
		}

		if(m_dataType == "TimedDouble")
		{
			func = new MinMaxFunctionSingle<TimedDouble, double>(this,m_inportNum);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new MinMaxFunctionSingle<TimedLong, int>(this,m_inportNum);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new MinMaxFunctionSingle<TimedFloat, float>(this,m_inportNum);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new MinMaxFunctionSingle<TimedShort, int>(this,m_inportNum);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new MinMaxFunctionSingle<TimedULong, int>(this,m_inportNum);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new MinMaxFunctionSingle<TimedUShort, int>(this,m_inportNum);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new MinMaxFunctionSeq<TimedDoubleSeq, double>(this,m_inportNum);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new MinMaxFunctionSeq<TimedLongSeq, int>(this,m_inportNum);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new MinMaxFunctionSeq<TimedFloatSeq, float>(this,m_inportNum);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new MinMaxFunctionSeq<TimedShortSeq, int>(this,m_inportNum);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new MinMaxFunctionSeq<TimedULongSeq, int>(this,m_inportNum);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new MinMaxFunctionSeq<TimedUShortSeq, int>(this,m_inportNum);
		}
		
	}

	if(func)
	{
		func->changeInportNum(m_inportNum);
		if(m_runningResettable == "ON")
		{
			func->setRunningResettable(true);
		}
		else if(m_runningResettable == "OFF")
		{
			func->setRunningResettable(false);
		}

		if(m_maxmin == "Max")
		{
			func->setMaxMin(true);
		}
		else if(m_maxmin == "Min")
		{
			func->setMaxMin(false);
		}
	}
		
}


RTC::ReturnCode_t MinMaxFunction::onInitialize()
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
  bindParameter("runningResettable", m_runningResettable, "OFF");
  bindParameter("maxmin", m_maxmin, "MAX");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MinMaxFunction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void MinMaxFunctionInit(RTC::Manager* manager)
  {
    coil::Properties profile(minmaxfunction_spec);
    manager->registerFactory(profile,
                             RTC::Create<MinMaxFunction>,
                             RTC::Delete<MinMaxFunction>);
  }
  
};


