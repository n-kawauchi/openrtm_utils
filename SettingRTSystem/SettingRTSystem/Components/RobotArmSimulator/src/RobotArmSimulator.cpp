// -*- C++ -*-
/*!
 * @file  RobotArmSimulator.cpp
 * @brief Robot Arm Simulator
 * @date $Date$
 *
 * $Id$
 */

#include "RobotArmSimulator.h"

// Module specification
// <rtc-template block="module_spec">
static const char* robotarmsimulator_spec[] =
  {
    "implementation_id", "RobotArmSimulator",
    "type_name",         "RobotArmSimulator",
    "description",       "Robot Arm Simulator",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Manipulator",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
	// Configuration variables
	"conf.default.drawWindow", "1",
	"conf.default.draw_time", "0.01",

	// Widget
	"conf.__widget__.drawWindow", "radio",
	"conf.__widget__.draw_time", "text",
	// Constraints
	"conf.__constraints__.drawWindow", "(0,1)",

	"conf.__type__.drawWindow", "int",
	"conf.__type__.draw_time", "double",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RobotArmSimulator::RobotArmSimulator(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_jposOut("jpos", m_jpos),
    m_ManipulatorCommonInterface_CommonPort("ManipulatorCommonInterface_Common"),
    m_ManipulatorCommonInterface_MiddlePort("ManipulatorCommonInterface_Middle")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RobotArmSimulator::~RobotArmSimulator()
{
}



RTC::ReturnCode_t RobotArmSimulator::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("jpos", m_jposOut);

  m_so = new SimulatorObj();
  m_dt = NULL;
  

  m_ManipulatorCommonInterface_Common = new ManipulatorCommonInterface_CommonSVC_impl(m_so->rb);
  m_ManipulatorCommonInterface_Middle = new ManipulatorCommonInterface_MiddleSVC_impl(m_so->rb);
  // Set service provider to Ports
  m_ManipulatorCommonInterface_CommonPort.registerProvider("ManipulatorCommonInterface_Common", "JARA_ARM::ManipulatorCommonInterface_Common", (*m_ManipulatorCommonInterface_Common));
  m_ManipulatorCommonInterface_MiddlePort.registerProvider("ManipulatorCommonInterface_Middle", "JARA_ARM::ManipulatorCommonInterface_Middle", (*m_ManipulatorCommonInterface_Middle));
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_ManipulatorCommonInterface_CommonPort);
  addPort(m_ManipulatorCommonInterface_MiddlePort);
  
  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("drawWindow", m_drawWindow, "1");
  bindParameter("draw_time", m_draw_time, "0.01");


  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmSimulator::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmSimulator::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RobotArmSimulator::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmSimulator::onActivated(RTC::UniqueId ec_id)
{
	m_so->destroyRobot();
	m_so->makeRobot();

	if (m_drawWindow == 1 && m_dt == NULL)
	{
		m_dt = new DrawThread(m_so, m_draw_time);

  		m_dt->activate();
	}

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmSimulator::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RobotArmSimulator::onExecute(RTC::UniqueId ec_id)
{
	m_so->update();
	if(m_so->rb->stopFalg)
		return RTC::RTC_OK;
		//return RTC::RTC_ERROR;
	
	m_jpos.data.length(m_so->rb->axisNum);
	for(int i=0;i < m_so->rb->axisNum;i++)
		m_jpos.data[i] = m_so->rb->theta[i];
	m_jposOut.write();

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RobotArmSimulator::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmSimulator::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmSimulator::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmSimulator::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RobotArmSimulator::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RobotArmSimulatorInit(RTC::Manager* manager)
  {
    coil::Properties profile(robotarmsimulator_spec);
    manager->registerFactory(profile,
                             RTC::Create<RobotArmSimulator>,
                             RTC::Delete<RobotArmSimulator>);
  }
  
};


