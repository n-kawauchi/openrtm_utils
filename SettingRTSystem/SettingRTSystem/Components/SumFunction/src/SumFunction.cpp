// -*- C++ -*-
/*!
 * @file  SumFunction.cpp
 * @brief Sum Function
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "SumFunction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* sumfunction_spec[] =
  {
    "implementation_id", "SumFunction",
    "type_name",         "SumFunction",
    "description",       "Sum Function",
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
    "conf.default.additionNum", "1",
    "conf.default.subtractionNum", "0",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.additionNum", "spin",
    "conf.__widget__.subtractionNum", "spin",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
    "conf.__constraints__.additionNum", "0<=x<=30",
    "conf.__constraints__.subtractionNum", "0<=x<=30",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SumFunction::SumFunction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
SumFunction::~SumFunction()
{
}

void SumFunction::configUpdate()
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
			func = new SumFunctionSingle<TimedDouble, double>(this,m_additionNum,m_subtractionNum);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new SumFunctionSingle<TimedLong, int>(this,m_additionNum,m_subtractionNum);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new SumFunctionSingle<TimedFloat, float>(this,m_additionNum,m_subtractionNum);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new SumFunctionSingle<TimedShort, int>(this,m_additionNum,m_subtractionNum);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new SumFunctionSingle<TimedULong, int>(this,m_additionNum,m_subtractionNum);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new SumFunctionSingle<TimedUShort, int>(this,m_additionNum,m_subtractionNum);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new SumFunctionSeq<TimedDoubleSeq, double>(this,m_additionNum,m_subtractionNum);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new SumFunctionSeq<TimedLongSeq, int>(this,m_additionNum,m_subtractionNum);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new SumFunctionSeq<TimedFloatSeq, float>(this,m_additionNum,m_subtractionNum);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new SumFunctionSeq<TimedShortSeq, int>(this,m_additionNum,m_subtractionNum);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new SumFunctionSeq<TimedULongSeq, int>(this,m_additionNum,m_subtractionNum);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new SumFunctionSeq<TimedUShortSeq, int>(this,m_additionNum,m_subtractionNum);
		}
		
	}

	if(func)
	{
		func->changeAdditionNum(m_additionNum);
		func->changeSubtractionNum(m_subtractionNum);
	}
		
}

RTC::ReturnCode_t SumFunction::onInitialize()
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
  bindParameter("additionNum", m_additionNum, "1");
  bindParameter("subtractionNum", m_subtractionNum, "0");
  // </rtc-template>

  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SumFunction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void SumFunctionInit(RTC::Manager* manager)
  {
    coil::Properties profile(sumfunction_spec);
    manager->registerFactory(profile,
                             RTC::Create<SumFunction>,
                             RTC::Delete<SumFunction>);
  }
  
};


