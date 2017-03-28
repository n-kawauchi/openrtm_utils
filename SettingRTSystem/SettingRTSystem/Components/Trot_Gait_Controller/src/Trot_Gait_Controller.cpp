// -*- C++ -*-
/*!
 * @file  Trot_Gait_Controller.cpp
 * @brief Trot Gait Controller Component
 * @date $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#include "Trot_Gait_Controller.h"

// Module specification
// <rtc-template block="module_spec">
static const char* trot_gait_controller_spec[] =
  {
    "implementation_id", "Trot_Gait_Controller",
    "type_name",         "Trot_Gait_Controller",
    "description",       "Trot Gait Controller Component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Controller",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.sampling_time", "-1",
    "conf.default.stride", "0.08",
    "conf.default.center_pos_x", "0.077",
    "conf.default.center_pos_y", "0.096",
    "conf.default.center_pos_z", "-0.079",
    "conf.default.lift_height", "0.05",
    "conf.default.upper_limit_x", "0.04",
    "conf.default.upper_limit_y", "0.04",
    "conf.default.upper_limit_z", "0.04",
    "conf.default.lower_limit_x", "-0.04",
    "conf.default.lower_limit_y", "-0.04",
    "conf.default.lower_limit_z", "-0.04",
    "conf.default.move_limit", "0",

    // Widget
    "conf.__widget__.sampling_time", "text",
    "conf.__widget__.stride", "text",
    "conf.__widget__.center_pos_x", "text",
    "conf.__widget__.center_pos_y", "text",
    "conf.__widget__.center_pos_z", "text",
    "conf.__widget__.lift_height", "text",
    "conf.__widget__.upper_limit_x", "text",
    "conf.__widget__.upper_limit_y", "text",
    "conf.__widget__.upper_limit_z", "text",
    "conf.__widget__.lower_limit_x", "text",
    "conf.__widget__.lower_limit_y", "text",
    "conf.__widget__.lower_limit_z", "text",
    "conf.__widget__.move_limit", "radio",
    // Constraints
    "conf.__constraints__.move_limit", "(0,1)",

    "conf.__type__.sampling_time", "double",
    "conf.__type__.stride", "double",
    "conf.__type__.center_pos_x", "double",
    "conf.__type__.center_pos_y", "double",
    "conf.__type__.center_pos_z", "double",
    "conf.__type__.lift_height", "double",
    "conf.__type__.upper_limit_x", "double",
    "conf.__type__.upper_limit_y", "double",
    "conf.__type__.upper_limit_z", "double",
    "conf.__type__.lower_limit_x", "double",
    "conf.__type__.lower_limit_y", "double",
    "conf.__type__.lower_limit_z", "double",
    "conf.__type__.move_limit", "short",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Trot_Gait_Controller::Trot_Gait_Controller(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_target_velocityIn("target_velocity", m_target_velocity),
    m_update_poseIn("update_pose", m_update_pose),
    m_TrajectoryOut("Trajectory", m_Trajectory),
    m_current_poseOut("current_pose", m_current_pose),
	m_LeggedRobotCommonInterface_ServoPort("LeggedRobotCommonInterface_Servo"),
	m_LeggedRobotCommonInterface_RobotPort("LeggedRobotCommonInterface_Robot")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Trot_Gait_Controller::~Trot_Gait_Controller()
{
}



RTC::ReturnCode_t Trot_Gait_Controller::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("target_velocity", m_target_velocityIn);
  addInPort("update_pose", m_update_poseIn);
  
  // Set OutPort buffer
  addOutPort("Trajectory", m_TrajectoryOut);
  addOutPort("current_pose", m_current_poseOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_LeggedRobotCommonInterface_ServoPort.registerConsumer("LeggedRobotCommonInterface_Servo", "RTC::LeggedRobotCommonInterface_Servo", m_LeggedRobotCommonInterface_Servo);
  m_LeggedRobotCommonInterface_RobotPort.registerConsumer("LeggedRobotCommonInterface_Robot", "RTC::LeggedRobotCommonInterface_Robot", m_LeggedRobotCommonInterface_Robot);

  // Set CORBA Service Ports
  addPort(m_LeggedRobotCommonInterface_ServoPort);
  addPort(m_LeggedRobotCommonInterface_RobotPort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("sampling_time", m_sampling_time, "-1");
  bindParameter("stride", m_stride, "0.08");
  bindParameter("center_pos_x", m_center_pos_x, "0.077");
  bindParameter("center_pos_y", m_center_pos_y, "0.096");
  bindParameter("center_pos_z", m_center_pos_z, "-0.079");
  bindParameter("lift_height", m_lift_height, "0.05");
  bindParameter("upper_limit_x", m_upper_limit_x, "0.04");
  bindParameter("upper_limit_y", m_upper_limit_y, "0.04");
  bindParameter("upper_limit_z", m_upper_limit_z, "0.04");
  bindParameter("lower_limit_x", m_lower_limit_x, "-0.04");
  bindParameter("lower_limit_y", m_lower_limit_y, "-0.04");
  bindParameter("lower_limit_z", m_lower_limit_z, "-0.04");
  bindParameter("move_limit", m_move_limit, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onActivated(RTC::UniqueId ec_id)
{
	if (m_sampling_time > 0)
	{
		robot.setSamplingTime(m_sampling_time);
	}
	else
	{
		robot.setSamplingTime(1.0 / this->getExecutionContext(0)->get_rate());
	}
	//std::cout << 1.0 / this->getExecutionContext(0)->get_rate() << std::endl;
	robot.setCenterPosition(m_center_pos_x, m_center_pos_y, m_center_pos_z);
	robot.setLiftHeight(m_lift_height);

	m_Trajectory.leg_data.length(4);
	m_target_velocity.data.vx = 0;
	m_target_velocity.data.va = 0;
	m_target_velocity.data.va = 0;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onExecute(RTC::UniqueId ec_id)
{
	if (m_update_poseIn.isNew())
	{
		m_update_poseIn.read();
		robot.body.current_pos(0) = m_update_pose.data.position.x;
		robot.body.current_pos(1) = m_update_pose.data.position.y;
		robot.body.current_rot(2) = m_update_pose.data.heading;
	}
	if (m_target_velocityIn.isNew()){
		while (m_target_velocityIn.isNew())m_target_velocityIn.read();
		robot.trot_gait(m_target_velocity.data.vx, m_target_velocity.data.vy, m_target_velocity.data.va, m_stride);
		
		for (int i = 0; i < 4; i++)
		{
			m_Trajectory.leg_data[i].pose.position.x = robot.legs[i].current_pos(0);
			m_Trajectory.leg_data[i].pose.position.y = robot.legs[i].current_pos(1);
			m_Trajectory.leg_data[i].pose.position.z = robot.legs[i].current_pos(2);
		}

		m_Trajectory.body_pose.position.x = robot.body.current_pos(0);
		m_Trajectory.body_pose.position.y = robot.body.current_pos(1);
		m_Trajectory.body_pose.position.z = robot.body.current_pos(2);

		setTimestamp(m_Trajectory);
		m_TrajectoryOut.write();



	}

	m_current_pose.data.position.x = robot.body.current_pos(0);
	m_current_pose.data.position.y = robot.body.current_pos(1);
	m_current_pose.data.heading = robot.body.current_rot(2);

	setTimestamp(m_current_pose);
	m_current_poseOut.write();


  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Trot_Gait_Controller::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void Trot_Gait_ControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(trot_gait_controller_spec);
    manager->registerFactory(profile,
                             RTC::Create<Trot_Gait_Controller>,
                             RTC::Delete<Trot_Gait_Controller>);
  }
  
};


