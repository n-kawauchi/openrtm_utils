// -*- C++ -*-
/*!
 * @file  ProductFunction.cpp
 * @brief Product Function
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "ProductFunction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* productfunction_spec[] =
  {
    "implementation_id", "ProductFunction",
    "type_name",         "ProductFunction",
    "description",       "Product Function",
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
    "conf.default.multiplicationNum", "1",
    "conf.default.divisionNum", "0",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.multiplicationNum", "spin",
    "conf.__widget__.divisionNum", "spin",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort,TimedDoubleSeq,TimedLongSeq,TimedFloatSeq,TimedShortSeq,TimedULongSeq,TimedUShortSeq)",
    "conf.__constraints__.multiplicationNum", "0<=x<=30",
    "conf.__constraints__.divisionNum", "0<=x<=30",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ProductFunction::ProductFunction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
ProductFunction::~ProductFunction()
{
}



void ProductFunction::configUpdate()
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
			func = new ProductFunctionSingle<TimedDouble, double>(this,m_multiplicationNum,m_divisionNum);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new ProductFunctionSingle<TimedLong, int>(this,m_multiplicationNum,m_divisionNum);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new ProductFunctionSingle<TimedFloat, float>(this,m_multiplicationNum,m_divisionNum);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new ProductFunctionSingle<TimedShort, int>(this,m_multiplicationNum,m_divisionNum);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new ProductFunctionSingle<TimedULong, int>(this,m_multiplicationNum,m_divisionNum);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new ProductFunctionSingle<TimedUShort, int>(this,m_multiplicationNum,m_divisionNum);
		}


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new ProductFunctionSeq<TimedDoubleSeq, double>(this,m_multiplicationNum,m_divisionNum);
		}
		else if(m_dataType == "TimedLongSeq")
		{
			func = new ProductFunctionSeq<TimedLongSeq, int>(this,m_multiplicationNum,m_divisionNum);
		}
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new ProductFunctionSeq<TimedFloatSeq, float>(this,m_multiplicationNum,m_divisionNum);
		}
		else if(m_dataType == "TimedShortSeq")
		{
			func = new ProductFunctionSeq<TimedShortSeq, int>(this,m_multiplicationNum,m_divisionNum);
		}
		else if(m_dataType == "TimedULongSeq")
		{
			func = new ProductFunctionSeq<TimedULongSeq, int>(this,m_multiplicationNum,m_divisionNum);
		}
		else if(m_dataType == "TimedUShortSeq")
		{
			func = new ProductFunctionSeq<TimedUShortSeq, int>(this,m_multiplicationNum,m_divisionNum);
		}
		
	}

	if(func)
	{
		func->changeMultiplicationNum(m_multiplicationNum);
		func->changeDivisionNum(m_divisionNum);
	}
		
}


RTC::ReturnCode_t ProductFunction::onInitialize()
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
  bindParameter("multiplicationNum", m_multiplicationNum, "1");
  bindParameter("divisionNum", m_divisionNum, "0");
  // </rtc-template>

  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ProductFunction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void ProductFunctionInit(RTC::Manager* manager)
  {
    coil::Properties profile(productfunction_spec);
    manager->registerFactory(profile,
                             RTC::Create<ProductFunction>,
                             RTC::Delete<ProductFunction>);
  }
  
};


