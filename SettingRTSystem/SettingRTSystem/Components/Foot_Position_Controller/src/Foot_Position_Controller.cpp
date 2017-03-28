// -*- C++ -*-
/*!
 * @file  Foot_Position_Controller.cpp
 * @brief Control the position of the foot
 * @date $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#include "Foot_Position_Controller.h"

#define _USE_MATH_DEFINES
#include <math.h>

// Module specification
// <rtc-template block="module_spec">
static const char* foot_position_controller_spec[] =
  {
    "implementation_id", "Foot_Position_Controller",
    "type_name",         "Foot_Position_Controller",
    "description",       "Control the position of the foot",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Controller",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
	// Configuration variables
	"conf.default.offset_lf0", "0",
	"conf.default.offset_lf1", "0",
	"conf.default.offset_lf2", "0",
	"conf.default.offset_lb0", "0",
	"conf.default.offset_lb1", "0",
	"conf.default.offset_lb2", "0",
	"conf.default.offset_rb0", "0",
	"conf.default.offset_rb1", "0",
	"conf.default.offset_rb2", "0",
	"conf.default.offset_rf0", "0",
	"conf.default.offset_rf1", "0",
	"conf.default.offset_rf2", "0",
	"conf.default.body_length", "0.07",
	"conf.default.body_width", "0.07",
	"conf.default.body_height", "0.005",
	"conf.default.leg0_length", "0.02",
	"conf.default.leg0_height", "0.025",
	"conf.default.leg1_length", "0.055",
	"conf.default.leg2_length", "0.08",
	"conf.default.leg0_offset_x", "0",
	"conf.default.leg0_offset_y", "0",
	"conf.default.leg0_offset_z", "0",
	"conf.default.leg1_offset_x", "0",
	"conf.default.leg1_offset_y", "0",
	"conf.default.leg1_offset_z", "0",
	"conf.default.leg2_offset_x", "0",
	"conf.default.leg2_offset_y", "0",
	"conf.default.leg2_offset_z", "0",
	"conf.default.dir_lf0", "1",
	"conf.default.dir_lf1", "1",
	"conf.default.dir_lf2", "1",
	"conf.default.dir_lb0", "1",
	"conf.default.dir_lb1", "1",
	"conf.default.dir_lb2", "1",
	"conf.default.dir_rb0", "1",
	"conf.default.dir_rb1", "1",
	"conf.default.dir_rb2", "1",
	"conf.default.dir_rf0", "1",
	"conf.default.dir_rf1", "1",
	"conf.default.dir_rf2", "1",
	"conf.default.upper_limit_motor0", "1.571796",
	"conf.default.upper_limit_motor1", "1.571796",
	"conf.default.upper_limit_motor2", "1.571796",
	"conf.default.lower_limit_motor0", "-1.571796",
	"conf.default.lower_limit_motor1", "-1.571796",
	"conf.default.lower_limit_motor2", "-1.571796",

	// Widget
	"conf.__widget__.offset_lf0", "text",
	"conf.__widget__.offset_lf1", "text",
	"conf.__widget__.offset_lf2", "text",
	"conf.__widget__.offset_lb0", "text",
	"conf.__widget__.offset_lb1", "text",
	"conf.__widget__.offset_lb2", "text",
	"conf.__widget__.offset_rb0", "text",
	"conf.__widget__.offset_rb1", "text",
	"conf.__widget__.offset_rb2", "text",
	"conf.__widget__.offset_rf0", "text",
	"conf.__widget__.offset_rf1", "text",
	"conf.__widget__.offset_rf2", "text",
	"conf.__widget__.body_length", "text",
	"conf.__widget__.body_width", "text",
	"conf.__widget__.body_height", "text",
	"conf.__widget__.leg0_length", "text",
	"conf.__widget__.leg0_height", "text",
	"conf.__widget__.leg1_length", "text",
	"conf.__widget__.leg2_length", "text",
	"conf.__widget__.leg0_offset_x", "text",
	"conf.__widget__.leg0_offset_y", "text",
	"conf.__widget__.leg0_offset_z", "text",
	"conf.__widget__.leg1_offset_x", "text",
	"conf.__widget__.leg1_offset_y", "text",
	"conf.__widget__.leg1_offset_z", "text",
	"conf.__widget__.leg2_offset_x", "text",
	"conf.__widget__.leg2_offset_y", "text",
	"conf.__widget__.leg2_offset_z", "text",
	"conf.__widget__.dir_lf0", "radio",
	"conf.__widget__.dir_lf1", "radio",
	"conf.__widget__.dir_lf2", "radio",
	"conf.__widget__.dir_lb0", "radio",
	"conf.__widget__.dir_lb1", "radio",
	"conf.__widget__.dir_lb2", "radio",
	"conf.__widget__.dir_rb0", "radio",
	"conf.__widget__.dir_rb1", "radio",
	"conf.__widget__.dir_rb2", "radio",
	"conf.__widget__.dir_rf0", "radio",
	"conf.__widget__.dir_rf1", "radio",
	"conf.__widget__.dir_rf2", "radio",
	"conf.__widget__.upper_limit_motor0", "text",
	"conf.__widget__.upper_limit_motor1", "text",
	"conf.__widget__.upper_limit_motor2", "text",
	"conf.__widget__.lower_limit_motor0", "text",
	"conf.__widget__.lower_limit_motor1", "text",
	"conf.__widget__.lower_limit_motor2", "text",
	// Constraints
	"conf.__constraints__.dir_lf0", "(1,-1)",
	"conf.__constraints__.dir_lf1", "(1,-1)",
	"conf.__constraints__.dir_lf2", "(1,-1)",
	"conf.__constraints__.dir_lb0", "(1,-1)",
	"conf.__constraints__.dir_lb1", "(1,-1)",
	"conf.__constraints__.dir_lb2", "(1,-1)",
	"conf.__constraints__.dir_rb0", "(1,-1)",
	"conf.__constraints__.dir_rb1", "(1,-1)",
	"conf.__constraints__.dir_rb2", "(1,-1)",
	"conf.__constraints__.dir_rf0", "(1,-1)",
	"conf.__constraints__.dir_rf1", "(1,-1)",
	"conf.__constraints__.dir_rf2", "(1,-1)",

	"conf.__type__.offset_lf0", "double",
	"conf.__type__.offset_lf1", "double",
	"conf.__type__.offset_lf2", "double",
	"conf.__type__.offset_lb0", "double",
	"conf.__type__.offset_lb1", "double",
	"conf.__type__.offset_lb2", "double",
	"conf.__type__.offset_rb0", "double",
	"conf.__type__.offset_rb1", "double",
	"conf.__type__.offset_rb2", "double",
	"conf.__type__.offset_rf0", "double",
	"conf.__type__.offset_rf1", "double",
	"conf.__type__.offset_rf2", "double",
	"conf.__type__.body_length", "double",
	"conf.__type__.body_width", "double",
	"conf.__type__.body_height", "double",
	"conf.__type__.leg0_length", "double",
	"conf.__type__.leg0_height", "double",
	"conf.__type__.leg1_length", "double",
	"conf.__type__.leg2_length", "double",
	"conf.__type__.leg0_offset_x", "double",
	"conf.__type__.leg0_offset_y", "double",
	"conf.__type__.leg0_offset_z", "double",
	"conf.__type__.leg1_offset_x", "double",
	"conf.__type__.leg1_offset_y", "double",
	"conf.__type__.leg1_offset_z", "double",
	"conf.__type__.leg2_offset_x", "double",
	"conf.__type__.leg2_offset_y", "double",
	"conf.__type__.leg2_offset_z", "double",
	"conf.__type__.dir_lf0", "int",
	"conf.__type__.dir_lf1", "int",
	"conf.__type__.dir_lf2", "int",
	"conf.__type__.dir_lb0", "int",
	"conf.__type__.dir_lb1", "int",
	"conf.__type__.dir_lb2", "int",
	"conf.__type__.dir_rb0", "int",
	"conf.__type__.dir_rb1", "int",
	"conf.__type__.dir_rb2", "int",
	"conf.__type__.dir_rf0", "int",
	"conf.__type__.dir_rf1", "int",
	"conf.__type__.dir_rf2", "int",
	"conf.__type__.upper_limit_motor0", "double",
	"conf.__type__.upper_limit_motor1", "double",
	"conf.__type__.upper_limit_motor2", "double",
	"conf.__type__.lower_limit_motor0", "double",
	"conf.__type__.lower_limit_motor1", "double",
	"conf.__type__.lower_limit_motor2", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Foot_Position_Controller::Foot_Position_Controller(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_TrajectoryIn("Trajectory", m_Trajectory),
    m_motor_posOut("motor_pos", m_motor_pos),
	m_motor_pos_0Out("motor_pos_0", m_motor_pos_0),
	m_motor_pos_1Out("motor_pos_1", m_motor_pos_1),
	m_motor_pos_2Out("motor_pos_2", m_motor_pos_2),
	m_motor_pos_3Out("motor_pos_3", m_motor_pos_3),
	m_LeggedRobotCommonInterface_Servo_1Port("LeggedRobotCommonInterface_Servo_1"),
	m_LeggedRobotCommonInterface_RobotPort("LeggedRobotCommonInterface_Robot"),
	m_LeggedRobotCommonInterface_Servo_2Port("LeggedRobotCommonInterface_Servo_2")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Foot_Position_Controller::~Foot_Position_Controller()
{
}



RTC::ReturnCode_t Foot_Position_Controller::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  addInPort("Trajectory", m_TrajectoryIn);

  // Set OutPort buffer
  addOutPort("motor_pos", m_motor_posOut);
  //addOutPort("motor_pos_0", m_motor_pos_0Out);
  //addOutPort("motor_pos_1", m_motor_pos_1Out);
  //addOutPort("motor_pos_2", m_motor_pos_2Out);
  //addOutPort("motor_pos_3", m_motor_pos_3Out);
 
  

  
  // Set service provider to Ports
  m_LeggedRobotCommonInterface_Servo_1Port.registerProvider("LeggedRobotCommonInterface_Servo", "RTC::LeggedRobotCommonInterface_Servo", m_LeggedRobotCommonInterface_Servo_1);
  m_LeggedRobotCommonInterface_RobotPort.registerProvider("LeggedRobotCommonInterface_Robot", "RTC::LeggedRobotCommonInterface_Robot", m_LeggedRobotCommonInterface_Robot);

  // Set service consumers to Ports
  m_LeggedRobotCommonInterface_Servo_2Port.registerConsumer("LeggedRobotCommonInterface_Servo", "RTC::LeggedRobotCommonInterface_Servo", m_LeggedRobotCommonInterface_Servo_2);

  // Set CORBA Service Ports
  addPort(m_LeggedRobotCommonInterface_Servo_1Port);
  addPort(m_LeggedRobotCommonInterface_RobotPort);
  addPort(m_LeggedRobotCommonInterface_Servo_2Port);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("offset_lf0", m_offset_lf0, "0");
  bindParameter("offset_lf1", m_offset_lf1, "0");
  bindParameter("offset_lf2", m_offset_lf2, "0");
  bindParameter("offset_lb0", m_offset_lb0, "0");
  bindParameter("offset_lb1", m_offset_lb1, "0");
  bindParameter("offset_lb2", m_offset_lb2, "0");
  bindParameter("offset_rb0", m_offset_rb0, "0");
  bindParameter("offset_rb1", m_offset_rb1, "0");
  bindParameter("offset_rb2", m_offset_rb2, "0");
  bindParameter("offset_rf0", m_offset_rf0, "0");
  bindParameter("offset_rf1", m_offset_rf1, "0");
  bindParameter("offset_rf2", m_offset_rf2, "0");
  bindParameter("body_length", m_body_length, "0.07");
  bindParameter("body_width", m_body_width, "0.07");
  bindParameter("body_height", m_body_height, "0.005");
  bindParameter("leg0_length", m_leg0_length, "0.02");
  bindParameter("leg0_height", m_leg0_height, "0.025");
  bindParameter("leg1_length", m_leg1_length, "0.055");
  bindParameter("leg2_length", m_leg2_length, "0.08");
  bindParameter("leg0_offset_x", m_leg0_offset_x, "0");
  bindParameter("leg0_offset_y", m_leg0_offset_y, "0");
  bindParameter("leg0_offset_z", m_leg0_offset_z, "0");
  bindParameter("leg1_offset_x", m_leg1_offset_x, "0");
  bindParameter("leg1_offset_y", m_leg1_offset_y, "0");
  bindParameter("leg1_offset_z", m_leg1_offset_z, "0");
  bindParameter("leg2_offset_x", m_leg2_offset_x, "0");
  bindParameter("leg2_offset_y", m_leg2_offset_y, "0");
  bindParameter("leg2_offset_z", m_leg2_offset_z, "0");
  bindParameter("dir_lf0", m_dir_lf0, "1");
  bindParameter("dir_lf1", m_dir_lf1, "1");
  bindParameter("dir_lf2", m_dir_lf2, "1");
  bindParameter("dir_lb0", m_dir_lb0, "1");
  bindParameter("dir_lb1", m_dir_lb1, "1");
  bindParameter("dir_lb2", m_dir_lb2, "1");
  bindParameter("dir_rb0", m_dir_rb0, "1");
  bindParameter("dir_rb1", m_dir_rb1, "1");
  bindParameter("dir_rb2", m_dir_rb2, "1");
  bindParameter("dir_rf0", m_dir_rf0, "1");
  bindParameter("dir_rf1", m_dir_rf1, "1");
  bindParameter("dir_rf2", m_dir_rf2, "1");
  bindParameter("upper_limit_motor0", m_upper_limit_motor0, "1.571796");
  bindParameter("upper_limit_motor1", m_upper_limit_motor1, "1.571796");
  bindParameter("upper_limit_motor2", m_upper_limit_motor2, "1.571796");
  bindParameter("lower_limit_motor0", m_lower_limit_motor0, "-1.571796");
  bindParameter("lower_limit_motor1", m_lower_limit_motor1, "-1.571796");
  bindParameter("lower_limit_motor2", m_lower_limit_motor2, "-1.571796");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onActivated(RTC::UniqueId ec_id)
{
	m_motor_pos.data.length(12);
	m_motor_pos_0.data.length(12);
	m_motor_pos_1.data.length(12);
	m_motor_pos_2.data.length(12);
	m_motor_pos_3.data.length(12);
	
	robot.setBodyParam(Vector3d(m_body_length, m_body_width, m_body_height), Vector3d(0, 0, 0), 0.01);
	robot.setLink0Param(Vector3d(m_leg0_length, 0.01, m_leg0_height), Vector3d(m_leg0_offset_x, m_leg0_offset_y, m_leg0_offset_z), 0.01);
	robot.setLink1Param(Vector3d(m_leg1_length, 0.01, 0.01), Vector3d(m_leg1_offset_x, m_leg1_offset_y, m_leg1_offset_z), 0.01);
	robot.setLink2Param(Vector3d(m_leg2_length, 0.01, 0.01), Vector3d(m_leg2_offset_x, m_leg2_offset_y, m_leg2_offset_z), 0.01);
	robot.setPose();

	robot.setMotorLimit(m_upper_limit_motor0, m_upper_limit_motor1, m_upper_limit_motor2, m_lower_limit_motor0, m_lower_limit_motor1, m_lower_limit_motor2);

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onExecute(RTC::UniqueId ec_id)
{
	if (m_TrajectoryIn.isNew())
	{
		m_TrajectoryIn.read();


		//std::cout << m_foot_pos_lf.data.position.x << "\t" << m_foot_pos_lf.data.position.y << "\t" << m_foot_pos_lf.data.position.z << std::endl;

		Vector3d pos_lf = Vector3d(m_Trajectory.leg_data[0].pose.position.x, m_Trajectory.leg_data[0].pose.position.y, m_Trajectory.leg_data[0].pose.position.z);
		Vector3d pos_lb = Vector3d(m_Trajectory.leg_data[1].pose.position.x, m_Trajectory.leg_data[1].pose.position.y, m_Trajectory.leg_data[1].pose.position.z);
		Vector3d pos_rb = Vector3d(m_Trajectory.leg_data[2].pose.position.x, m_Trajectory.leg_data[2].pose.position.y, m_Trajectory.leg_data[2].pose.position.z);
		Vector3d pos_rf = Vector3d(m_Trajectory.leg_data[3].pose.position.x, m_Trajectory.leg_data[3].pose.position.y, m_Trajectory.leg_data[3].pose.position.z);

		std::vector<double> angle_lf = robot.inverseKinematics(pos_lf, 0);
		std::vector<double> angle_lb = robot.inverseKinematics(pos_lb, 1);
		std::vector<double> angle_rb = robot.inverseKinematics(pos_rb, 2);
		std::vector<double> angle_rf = robot.inverseKinematics(pos_rf, 3);
		bool ret = robot.limitOver(angle_lf, angle_lb, angle_rb, angle_rf);
		if (ret)
		{
			return RTC::RTC_ERROR;
		}
		//std::cout << ret << std::endl;
		/*for (int i = 0; i < 3; i++)
		{
			std::cout << "lf\t" << i << "\t" << angle_lf[i] << std::endl;
		}
		for (int i = 0; i < 3; i++)
		{
			std::cout << "lf\t" << i << "\t" << angle_lb[i] << std::endl;
		}
		for (int i = 0; i < 3; i++)
		{
			std::cout << "lf\t" << i << "\t" << angle_rb[i] << std::endl;
		}
		for (int i = 0; i < 3; i++)
		{
			std::cout << "lf\t" << i << "\t" << angle_rf[i] << std::endl;
		}*/

		//m_motor_pos.data.length(3);
		m_motor_pos.data[0] = ((double)m_dir_lf0)*(angle_lf[0] + m_offset_lf0);
		m_motor_pos.data[1] = ((double)m_dir_lf1)*(angle_lf[1] + m_offset_lf1);
		m_motor_pos.data[2] = ((double)m_dir_lf2)*(angle_lf[2] + m_offset_lf2);
		m_motor_pos.data[3] = ((double)m_dir_lb0)*(angle_lb[0] + m_offset_lb0);
		m_motor_pos.data[4] = ((double)m_dir_lb1)*(angle_lb[1] + m_offset_lb1);
		m_motor_pos.data[5] = ((double)m_dir_lb2)*(angle_lb[2] + m_offset_lb2);
		m_motor_pos.data[6] = ((double)m_dir_rb0)*(angle_rb[0] + m_offset_rb0);
		m_motor_pos.data[7] = ((double)m_dir_rb1)*(angle_rb[1] + m_offset_rb1);
		m_motor_pos.data[8] = ((double)m_dir_rb2)*(angle_rb[2] + m_offset_rb2);
		m_motor_pos.data[9] = ((double)m_dir_rf0)*(angle_rf[0] + m_offset_rf0);
		m_motor_pos.data[10] = ((double)m_dir_rf1)*(angle_rf[1] + m_offset_rf1);
		m_motor_pos.data[11] = ((double)m_dir_rf2)*(angle_rf[2] + m_offset_rf2);

		m_motor_pos_0.data[0] = m_motor_pos.data[0];
		m_motor_pos_0.data[1] = m_motor_pos.data[1];
		m_motor_pos_0.data[2] = m_motor_pos.data[2];

		m_motor_pos_1.data[0] = m_motor_pos.data[3];
		m_motor_pos_1.data[1] = m_motor_pos.data[4];
		m_motor_pos_1.data[2] = m_motor_pos.data[5];

		m_motor_pos_2.data[0] = m_motor_pos.data[6];
		m_motor_pos_2.data[1] = m_motor_pos.data[7];
		m_motor_pos_2.data[2] = m_motor_pos.data[8];

		m_motor_pos_3.data[0] = m_motor_pos.data[9];
		m_motor_pos_3.data[1] = m_motor_pos.data[10];
		m_motor_pos_3.data[2] = m_motor_pos.data[11];

		//for (int i = 0; i < 3; i++)std::cout << 0 << "\t" << i << "\t" << m_motor_pos_0.data[i] << std::endl;
		//for (int i = 0; i < 3; i++)std::cout << 1 << "\t" << i << "\t" << m_motor_pos_1.data[i] << std::endl;
		//for (int i = 0; i < 3; i++)std::cout << 2 << "\t" << i << "\t" << m_motor_pos_2.data[i] << std::endl;
		//for (int i = 0; i < 3; i++)std::cout << 3 << "\t" << i << "\t" << m_motor_pos_3.data[i] << std::endl;
		
		/*for (int i = 0; i < 12; i++)
		{
			std::cout << i << "\t" << m_motor_pos.data[i] << std::endl;
		}*/

		setTimestamp(m_motor_pos);
		m_motor_posOut.write();

		setTimestamp(m_motor_pos_0);
		m_motor_pos_0Out.write();
		setTimestamp(m_motor_pos_1);
		m_motor_pos_1Out.write();
		setTimestamp(m_motor_pos_2);
		m_motor_pos_2Out.write();
		setTimestamp(m_motor_pos_3);
		m_motor_pos_3Out.write();
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Foot_Position_Controller::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void Foot_Position_ControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(foot_position_controller_spec);
    manager->registerFactory(profile,
                             RTC::Create<Foot_Position_Controller>,
                             RTC::Delete<Foot_Position_Controller>);
  }
  
};


