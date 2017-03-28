// -*- C++ -*-
/*!
 * @file  DemuxFunction.cpp
 * @brief DemuxFunction
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "DemuxFunction.h"

// Module specification
// <rtc-template block="module_spec">
static const char* demuxfunction_spec[] =
  {
    "implementation_id", "DemuxFunction",
    "type_name",         "DemuxFunction",
    "description",       "DemuxFunction",
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
    "conf.default.outportNum", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.outportNum", "spin",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort)",
    "conf.__constraints__.outportNum", "1<=x<=30",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
DemuxFunction::DemuxFunction(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
DemuxFunction::~DemuxFunction()
{
}



void DemuxFunction::configUpdate()
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
			func = new DemuxFunctionComp<TimedDouble, TimedDoubleSeq, double>(this,m_outportNum);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new DemuxFunctionComp<TimedLong, TimedLongSeq, int>(this,m_outportNum);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new DemuxFunctionComp<TimedFloat, TimedFloatSeq, float>(this,m_outportNum);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new DemuxFunctionComp<TimedShort, TimedShortSeq, int>(this,m_outportNum);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new DemuxFunctionComp<TimedULong, TimedULongSeq, int>(this,m_outportNum);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new DemuxFunctionComp<TimedUShort, TimedUShortSeq, int>(this,m_outportNum);
		}

		
	}

	if(func)
	{
		func->changeOutPortNum(m_outportNum);
	}
		
}

RTC::ReturnCode_t DemuxFunction::onInitialize()
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
  bindParameter("outportNum", m_outportNum, "1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t DemuxFunction::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void DemuxFunctionInit(RTC::Manager* manager)
  {
    coil::Properties profile(demuxfunction_spec);
    manager->registerFactory(profile,
                             RTC::Create<DemuxFunction>,
                             RTC::Delete<DemuxFunction>);
  }
  
};


