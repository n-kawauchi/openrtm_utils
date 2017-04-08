// -*- C++ -*-
/*!
 * @file  Four_legged_Robot_Simulator.cpp
 * @brief Four legged Robot Simulator
 * @date $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#include "Four_legged_Robot_Simulator.h"

// Module specification
// <rtc-template block="module_spec">
static const char* four_legged_robot_simulator_spec[] =
  {
    "implementation_id", "Four_legged_Robot_Simulator",
    "type_name",         "Four_legged_Robot_Simulator",
    "description",       "Four legged Robot Simulator",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Simulator",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
	// Configuration variables
	"conf.default.draw_time", "0.01",
	"conf.default.sampling_time", "-1",
	"conf.default.gravity", "-9.8",
	"conf.default.body_length", "0.07",
	"conf.default.body_width", "0.07",
	"conf.default.body_height", "0.005",
	"conf.default.body_pos_x", "0",
	"conf.default.body_pos_y", "0",
	"conf.default.body_pos_z", "0.115",
	"conf.default.body_mass", "0.3",
	"conf.default.leg0_length", "0.02",
	"conf.default.leg0_width", "0.02",
	"conf.default.leg0_height", "0.025",
	"conf.default.leg1_length", "0.055",
	"conf.default.leg1_width", "0.005",
	"conf.default.leg1_height", "0.01",
	"conf.default.leg2_length", "0.08",
	"conf.default.leg2_width", "0.005",
	"conf.default.leg2_height", "0.005",
	"conf.default.leg0_offset_x", "0",
	"conf.default.leg0_offset_y", "0",
	"conf.default.leg0_offset_z", "0",
	"conf.default.leg1_offset_x", "0",
	"conf.default.leg1_offset_y", "0",
	"conf.default.leg1_offset_z", "0",
	"conf.default.leg2_offset_x", "0",
	"conf.default.leg2_offset_y", "0",
	"conf.default.leg2_offset_z", "0",
	"conf.default.leg0_mass", "0.2",
	"conf.default.leg1_mass", "0.1",
	"conf.default.leg2_mass", "0.001",
	"conf.default.foot_length", "0.16",
	"conf.default.foot_width", "0.12",
	"conf.default.foot_height", "0.005",
	"conf.default.foot_mass", "0.1",
	"conf.default.foot_exist", "0",

	// Widget
	"conf.__widget__.draw_time", "text",
	"conf.__widget__.sampling_time", "text",
	"conf.__widget__.gravity", "text",
	"conf.__widget__.body_length", "text",
	"conf.__widget__.body_width", "text",
	"conf.__widget__.body_height", "text",
	"conf.__widget__.body_pos_x", "text",
	"conf.__widget__.body_pos_y", "text",
	"conf.__widget__.body_pos_z", "text",
	"conf.__widget__.body_mass", "text",
	"conf.__widget__.leg0_length", "text",
	"conf.__widget__.leg0_width", "text",
	"conf.__widget__.leg0_height", "text",
	"conf.__widget__.leg1_length", "text",
	"conf.__widget__.leg1_width", "text",
	"conf.__widget__.leg1_height", "text",
	"conf.__widget__.leg2_length", "text",
	"conf.__widget__.leg2_width", "text",
	"conf.__widget__.leg2_height", "text",
	"conf.__widget__.leg0_offset_x", "text",
	"conf.__widget__.leg0_offset_y", "text",
	"conf.__widget__.leg0_offset_z", "text",
	"conf.__widget__.leg1_offset_x", "text",
	"conf.__widget__.leg1_offset_y", "text",
	"conf.__widget__.leg1_offset_z", "text",
	"conf.__widget__.leg2_offset_x", "text",
	"conf.__widget__.leg2_offset_y", "text",
	"conf.__widget__.leg2_offset_z", "text",
	"conf.__widget__.leg0_mass", "text",
	"conf.__widget__.leg1_mass", "text",
	"conf.__widget__.leg2_mass", "text",
	"conf.__widget__.foot_length", "text",
	"conf.__widget__.foot_width", "text",
	"conf.__widget__.foot_height", "text",
	"conf.__widget__.foot_mass", "text",
	"conf.__widget__.foot_exist", "radio",
	// Constraints
	"conf.__constraints__.foot_exist", "(0,1)",

	"conf.__type__.draw_time", "double",
	"conf.__type__.sampling_time", "double",
	"conf.__type__.gravity", "double",
	"conf.__type__.body_length", "double",
	"conf.__type__.body_width", "double",
	"conf.__type__.body_height", "double",
	"conf.__type__.body_pos_x", "double",
	"conf.__type__.body_pos_y", "double",
	"conf.__type__.body_pos_z", "double",
	"conf.__type__.body_mass", "double",
	"conf.__type__.leg0_length", "double",
	"conf.__type__.leg0_width", "double",
	"conf.__type__.leg0_height", "double",
	"conf.__type__.leg1_length", "double",
	"conf.__type__.leg1_width", "double",
	"conf.__type__.leg1_height", "double",
	"conf.__type__.leg2_length", "double",
	"conf.__type__.leg2_width", "double",
	"conf.__type__.leg2_height", "double",
	"conf.__type__.leg0_offset_x", "double",
	"conf.__type__.leg0_offset_y", "double",
	"conf.__type__.leg0_offset_z", "double",
	"conf.__type__.leg1_offset_x", "double",
	"conf.__type__.leg1_offset_y", "double",
	"conf.__type__.leg1_offset_z", "double",
	"conf.__type__.leg2_offset_x", "double",
	"conf.__type__.leg2_offset_y", "double",
	"conf.__type__.leg2_offset_z", "double",
	"conf.__type__.leg0_mass", "double",
	"conf.__type__.leg1_mass", "double",
	"conf.__type__.leg2_mass", "double",
	"conf.__type__.foot_length", "double",
	"conf.__type__.foot_width", "double",
	"conf.__type__.foot_height", "double",
	"conf.__type__.foot_mass", "double",
	"conf.__type__.foot_exist", "int",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Four_legged_Robot_Simulator::Four_legged_Robot_Simulator(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_servoIn("servo", m_servo)

    // </rtc-template>
{
	m_so = new SimulatorObj_Four_legged_Robot();
	m_dt = NULL;
}

/*!
 * @brief destructor
 */
Four_legged_Robot_Simulator::~Four_legged_Robot_Simulator()
{
	delete m_so;
	if (m_dt)
	{
		delete m_dt;
	}
}



RTC::ReturnCode_t Four_legged_Robot_Simulator::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("servo", m_servoIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("draw_time", m_draw_time, "0.01");
  bindParameter("sampling_time", m_sampling_time, "-1");
  bindParameter("gravity", m_gravity, "-9.8");
  bindParameter("body_length", m_body_length, "0.07");
  bindParameter("body_width", m_body_width, "0.07");
  bindParameter("body_height", m_body_height, "0.005");
  bindParameter("body_pos_x", m_body_pos_x, "0");
  bindParameter("body_pos_y", m_body_pos_y, "0");
  bindParameter("body_pos_z", m_body_pos_z, "0.115");
  bindParameter("body_mass", m_body_mass, "0.3");
  bindParameter("leg0_length", m_leg0_length, "0.02");
  bindParameter("leg0_width", m_leg0_width, "0.02");
  bindParameter("leg0_height", m_leg0_height, "0.025");
  bindParameter("leg1_length", m_leg1_length, "0.055");
  bindParameter("leg1_width", m_leg1_width, "0.005");
  bindParameter("leg1_height", m_leg1_height, "0.01");
  bindParameter("leg2_length", m_leg2_length, "0.08");
  bindParameter("leg2_width", m_leg2_width, "0.005");
  bindParameter("leg2_height", m_leg2_height, "0.005");
  bindParameter("leg0_offset_x", m_leg0_offset_x, "0");
  bindParameter("leg0_offset_y", m_leg0_offset_y, "0");
  bindParameter("leg0_offset_z", m_leg0_offset_z, "0");
  bindParameter("leg1_offset_x", m_leg1_offset_x, "0");
  bindParameter("leg1_offset_y", m_leg1_offset_y, "0");
  bindParameter("leg1_offset_z", m_leg1_offset_z, "0");
  bindParameter("leg2_offset_x", m_leg2_offset_x, "0");
  bindParameter("leg2_offset_y", m_leg2_offset_y, "0");
  bindParameter("leg2_offset_z", m_leg2_offset_z, "0");
  bindParameter("leg0_mass", m_leg0_mass, "0.2");
  bindParameter("leg1_mass", m_leg1_mass, "0.1");
  bindParameter("leg2_mass", m_leg2_mass, "0.001");
  bindParameter("foot_length", m_foot_length, "0.16");
  bindParameter("foot_width", m_foot_width, "0.12");
  bindParameter("foot_height", m_foot_height, "0.005");
  bindParameter("foot_mass", m_foot_mass, "0.1");
  bindParameter("foot_exist", m_foot_exist, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onActivated(RTC::UniqueId ec_id)
{
	m_so->destroyRobot();
	m_so->rb->setBodyParam(Vector3d(m_body_length, m_body_width, m_body_height), Vector3d(m_body_pos_x, m_body_pos_y, m_body_pos_z), m_body_mass);
	m_so->rb->setLink0Param(Vector3d(m_leg0_length, m_leg0_width, m_leg0_height), Vector3d(m_leg0_offset_x, m_leg0_offset_y, m_leg0_offset_z), m_leg0_mass);
	m_so->rb->setLink1Param(Vector3d(m_leg1_length, m_leg1_width, m_leg1_height), Vector3d(m_leg1_offset_x, m_leg1_offset_y, m_leg1_offset_z), m_leg0_mass);
	m_so->rb->setLink2Param(Vector3d(m_leg2_length, m_leg2_width, m_leg2_height), Vector3d(m_leg2_offset_x, m_leg2_offset_y, m_leg2_offset_z), m_leg0_mass);
	m_so->rb->setFootParam(Vector3d(m_foot_length, m_foot_width, m_foot_height), Vector3d(0, 0, 0), m_foot_mass);
	if (m_foot_exist == 1)
	{
		m_so->setFoot(true);
	}
	else
	{
		m_so->setFoot(false);
	}
	m_so->rb->setPose();
	m_so->makeParam();
	m_so->makeRobot();
	
	if(m_sampling_time > 0)
	{
		m_so->setSamplingTime(m_sampling_time);
	}
	else
	{
		m_so->setSamplingTime(1.0 / this->getExecutionContext(0)->get_rate());
	}

	if (m_dt == NULL)
	{
		m_dt = new DrawThread_Four_legged_Robot(m_so);
		
		m_dt->activate();
	}

	if (m_dt)
	{
		m_dt->fps = 1.0/m_draw_time;
		m_dt->setRCPFlag();
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onExecute(RTC::UniqueId ec_id)
{
	if (m_servoIn.isNew())
	{
		m_servoIn.read();
		if (m_servo.data.length() >= 12)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					m_so->legs[i][j].the = m_servo.data[i * 3 + j];
				}
			}
			if (m_dt == NULL || (m_dt && m_dt->m_pause == 0))
			{
				m_so->update();
			}
		}
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Four_legged_Robot_Simulator::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void Four_legged_Robot_SimulatorInit(RTC::Manager* manager)
  {
    coil::Properties profile(four_legged_robot_simulator_spec);
    manager->registerFactory(profile,
                             RTC::Create<Four_legged_Robot_Simulator>,
                             RTC::Delete<Four_legged_Robot_Simulator>);
  }
  
};


