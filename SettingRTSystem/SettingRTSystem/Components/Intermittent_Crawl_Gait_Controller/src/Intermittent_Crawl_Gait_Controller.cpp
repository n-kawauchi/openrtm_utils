// -*- C++ -*-
/*!
 * @file  Intermittent_Crawl_Gait_Controller.cpp
 * @brief Intermittent Crawl Walk Controller Component
 * @date $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#include "Intermittent_Crawl_Gait_Controller.h"

// Module specification
// <rtc-template block="module_spec">
static const char* intermittent_crawl_gait_controller_spec[] =
  {
    "implementation_id", "Intermittent_Crawl_Gait_Controller",
    "type_name",         "Intermittent_Crawl_Gait_Controller",
    "description",       "Intermittent Crawl Walk Controller Component",
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
	"conf.default.min_stability_margin", "0.01",
	"conf.default.side_move_distance", "0.03",
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
	"conf.__widget__.min_stability_margin", "text",
	"conf.__widget__.side_move_distance", "text",
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
	"conf.__type__.min_stability_margin", "double",
	"conf.__type__.side_move_distance", "double",
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
Intermittent_Crawl_Gait_Controller::Intermittent_Crawl_Gait_Controller(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
  m_target_velocityIn("target_velocity", m_target_velocity),
  m_update_poseIn("update_pose", m_update_pose),
    m_TrajectoryOut("Trajectory", m_Trajectory),
  m_current_poseOut("current_pose", m_current_pose),
  m_stability_marginOut("stability_margin", m_stability_margin),
  m_NE_stability_marginOut("NE_stability_margin", m_NE_stability_margin),
  m_LeggedRobotCommonInterface_RobotPort("LeggedRobotCommonInterface_Robot")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Intermittent_Crawl_Gait_Controller::~Intermittent_Crawl_Gait_Controller()
{
}



RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("target_velocity", m_target_velocityIn);
	addInPort("update_pose", m_update_poseIn);

	// Set OutPort buffer
	addOutPort("Trajectory", m_TrajectoryOut);
	addOutPort("current_pose", m_current_poseOut);
	addOutPort("stability_margin", m_stability_marginOut);
	addOutPort("NE_stability_margin", m_NE_stability_marginOut);

	// Set service provider to Ports

	// Set service consumers to Ports
	m_LeggedRobotCommonInterface_RobotPort.registerConsumer("LeggedRobotCommonInterface_Robot", "RTC::LeggedRobotCommonInterface_Robot", m_LeggedRobotCommonInterface_Robot);

	// Set CORBA Service Ports

	addPort(m_LeggedRobotCommonInterface_RobotPort);

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("sampling_time", m_sampling_time, "-1");
	bindParameter("stride", m_stride, "0.08");
	bindParameter("center_pos_x", m_center_pos_x, "0.077");
	bindParameter("center_pos_y", m_center_pos_y, "0.096");
	bindParameter("center_pos_z", m_center_pos_z, "-0.079");
	bindParameter("min_stability_margin", m_min_stability_margin, "0.01");
	bindParameter("side_move_distance", m_side_move_distance, "0.03");
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


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onActivated(RTC::UniqueId ec_id)
{
	if (m_sampling_time > 0)
	{
		robot.setSamplingTime(m_sampling_time);
	}
	else
	{
		robot.setSamplingTime(1.0 / this->getExecutionContext(0)->get_rate());
	}
	robot.setCenterPosition(m_center_pos_x, m_center_pos_y, m_center_pos_z);
	
	robot.icw_obj->setSideMoveDistance(m_side_move_distance);
	robot.setLiftHeight(m_lift_height);

	m_Trajectory.leg_data.length(4);

	m_target_velocity.data.vx = 0;
	m_target_velocity.data.va = 0;
	m_target_velocity.data.va = 0;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onExecute(RTC::UniqueId ec_id)
{
	robot.setMinMargin(m_min_stability_margin);

	if (m_update_poseIn.isNew())
	{
		m_update_poseIn.read();
		robot.body.current_pos(0) = m_update_pose.data.position.x;
		robot.body.current_pos(1) = m_update_pose.data.position.y;
		robot.body.current_rot(2) = m_update_pose.data.heading;
	}
	if (m_target_velocityIn.isNew()){
		while (m_target_velocityIn.isNew())m_target_velocityIn.read();
	}
	robot.intermittent_crawl_gait(m_target_velocity.data.vx, m_target_velocity.data.vy, m_target_velocity.data.va, m_stride);
	/*m_Trajectory.leg_data[0].pose.position.x = robot.legs[0].current_pos(0);
	m_Trajectory.leg_data[0].pose.position.y = robot.legs[0].current_pos(1);
	m_Trajectory.leg_data[0].pose.position.z = robot.legs[0].current_pos(2);

	m_Trajectory.leg_data[1].pose.position.x = robot.legs[1].current_pos(0);
	m_Trajectory.leg_data[1].pose.position.y = robot.legs[1].current_pos(1);
	m_Trajectory.leg_data[1].pose.position.z = robot.legs[1].current_pos(2);

	m_Trajectory.leg_data[2].pose.position.x = robot.legs[2].current_pos(0);
	m_Trajectory.leg_data[2].pose.position.y = robot.legs[2].current_pos(1);
	m_Trajectory.leg_data[2].pose.position.z = robot.legs[2].current_pos(2);

	m_Trajectory.leg_data[3].pose.position.x = robot.legs[3].current_pos(0);
	m_Trajectory.leg_data[3].pose.position.y = robot.legs[3].current_pos(1);
	m_Trajectory.leg_data[3].pose.position.z = robot.legs[3].current_pos(2);*/
	
	for(int i=0;i < 4;i++)
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


	
	m_current_pose.data.position.x = robot.body.current_pos(0);
	m_current_pose.data.position.y = robot.body.current_pos(1);
	m_current_pose.data.heading = robot.body.current_rot(2);

	setTimestamp(m_current_pose);
	m_current_poseOut.write();

	m_stability_margin.data = robot.getStabilityMargin();
	setTimestamp(m_stability_margin);
	m_stability_marginOut.write();

	m_NE_stability_margin.data = robot.getNEStabilityMargin();
	setTimestamp(m_NE_stability_margin);
	m_NE_stability_marginOut.write();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Intermittent_Crawl_Gait_Controller::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void Intermittent_Crawl_Gait_ControllerInit(RTC::Manager* manager)
  {
	  coil::Properties profile(intermittent_crawl_gait_controller_spec);
    manager->registerFactory(profile,
                             RTC::Create<Intermittent_Crawl_Gait_Controller>,
                             RTC::Delete<Intermittent_Crawl_Gait_Controller>);
  }
  
};


