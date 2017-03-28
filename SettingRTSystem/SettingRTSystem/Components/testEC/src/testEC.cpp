// -*- C++ -*-
/*!
 * @file  testEC.cpp
 * @brief test EC
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "testEC.h"

// Module specification
// <rtc-template block="module_spec">
static const char* testec_spec[] =
  {
    "implementation_id", "testEC",
    "type_name",         "testEC",
    "description",       "test EC",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "TEST",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
testEC::testEC(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
testEC::~testEC()
{
}



RTC::ReturnCode_t testEC::onInitialize()
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
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onExecute(RTC::UniqueId ec_id)
{
	getchar();
	

	std::cout << this->getNamingNames()[0] << std::endl;
	
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t testEC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void testECInit(RTC::Manager* manager)
  {
    coil::Properties profile(testec_spec);
    manager->registerFactory(profile,
                             RTC::Create<testEC>,
                             RTC::Delete<testEC>);
  }
  
};


