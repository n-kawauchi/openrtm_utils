// -*- C++ -*-
/*!
 * @file  RaspberryPiMouseController_DistanceSensor.cpp
 * @brief Raspberry Pi Mouse Controller
 * @date $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * LGPL
 *
 * $Id$
 */

#include <math.h>
#include "RaspberryPiMouseController_DistanceSensor.h"

// Module specification
// <rtc-template block="module_spec">
static const char* raspberrypimousecontroller_distancesensor_spec[] =
  {
    "implementation_id", "RaspberryPiMouseController_DistanceSensor",
    "type_name",         "RaspberryPiMouseController_DistanceSensor",
    "description",       "Raspberry Pi Mouse Controller",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Controller",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.sensor_limit", "10",
    "conf.default.rotational_speed", "1.6",
    "conf.default.stop_velocity", "0.01",
    // Widget
    "conf.__widget__.sensor_limit", "text",
    "conf.__widget__.rotational_speed", "text",
    "conf.__widget__.stop_velocity", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RaspberryPiMouseController_DistanceSensor::RaspberryPiMouseController_DistanceSensor(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_target_velocity_inIn("target_velocity_in", m_target_velocity_in),
    m_ir_sensorIn("ir_sensor", m_ir_sensor),
    m_target_velocity_outOut("target_velocity_out", m_target_velocity_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RaspberryPiMouseController_DistanceSensor::~RaspberryPiMouseController_DistanceSensor()
{
}



RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("target_velocity_in", m_target_velocity_inIn);
  addInPort("ir_sensor", m_ir_sensorIn);
  
  // Set OutPort buffer
  addOutPort("target_velocity_out", m_target_velocity_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("sensor_limit", m_sensor_limit, "10");
  bindParameter("rotational_speed", m_rotational_speed, "1.6");
  bindParameter("stop_velocity", m_stop_velocity, "0.01");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onActivated(RTC::UniqueId ec_id)
{
	m_target_vx = 0;
	m_target_vy = 0;
	m_target_va = 0;

	m_ir_sensor_r0 = 0;
	m_ir_sensor_r1 = 0;
	m_ir_sensor_l1 = 0;
	m_ir_sensor_l0 = 0;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onDeactivated(RTC::UniqueId ec_id)
{
	m_target_velocity_out.data.vx = 0;
	m_target_velocity_out.data.vy = 0;
	m_target_velocity_out.data.va = 0;


	m_target_velocity_outOut.write();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onExecute(RTC::UniqueId ec_id)
{
	if (m_ir_sensorIn.isNew())
	{
		m_ir_sensorIn.read();
		if (m_ir_sensor.data.length() >= 4)
		{
			m_ir_sensor_r0 = m_ir_sensor.data[0];
			m_ir_sensor_r1 = m_ir_sensor.data[1];
			m_ir_sensor_l1 = m_ir_sensor.data[2];
			m_ir_sensor_l0 = m_ir_sensor.data[3];
		}

	}
	if (m_target_velocity_inIn.isNew())
	{
		m_target_velocity_inIn.read();
		m_target_vx = m_target_velocity_in.data.vx;
		m_target_vy = m_target_velocity_in.data.vy;
		m_target_va = m_target_velocity_in.data.va;
	}

	double vel = sqrt(m_target_vx*m_target_vx);
	if (((m_ir_sensor_r0 > m_sensor_limit) || (m_ir_sensor_r1 > m_sensor_limit)) && (vel > m_stop_velocity))
	{
		m_target_velocity_out.data.vx = 0;
		m_target_velocity_out.data.vy = 0;
		m_target_velocity_out.data.va = m_rotational_speed;
		setTimestamp(m_target_velocity_out);

		m_target_velocity_outOut.write();
	}
	else if (((m_ir_sensor_l0 > m_sensor_limit) || (m_ir_sensor_l1 > m_sensor_limit)) && (vel > m_stop_velocity))
	{
		m_target_velocity_out.data.vx = 0;
		m_target_velocity_out.data.vy = 0;
		m_target_velocity_out.data.va = -m_rotational_speed;
		setTimestamp(m_target_velocity_out);


		m_target_velocity_outOut.write();
	}
	else
	{
		m_target_velocity_out.data.vx = m_target_vx;
		m_target_velocity_out.data.vy = m_target_vy;
		m_target_velocity_out.data.va = m_target_va;
		setTimestamp(m_target_velocity_out);

		//std::cout << m_target_velocity_out.data.vx << "\t" << m_target_velocity_out.data.vy << "\t" << m_target_velocity_out.data.va << std::endl;
		m_target_velocity_outOut.write();
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseController_DistanceSensor::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void RaspberryPiMouseController_DistanceSensorInit(RTC::Manager* manager)
  {
    coil::Properties profile(raspberrypimousecontroller_distancesensor_spec);
    manager->registerFactory(profile,
                             RTC::Create<RaspberryPiMouseController_DistanceSensor>,
                             RTC::Delete<RaspberryPiMouseController_DistanceSensor>);
  }
  
};


