// -*- C++ -*-
/*!
 * @file  RasPiMouseSampleCPP.cpp
 * @brief Raspberry Pi Mouse Sample
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

#include "RasPiMouseSampleCPP.h"

// Module specification
// <rtc-template block="module_spec">
static const char* raspimousesamplecpp_spec[] =
  {
    "implementation_id", "RasPiMouseSampleCPP",
    "type_name",         "RasPiMouseSampleCPP",
    "description",       "Raspberry Pi Mouse Sample",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "TEST",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.forward_velocity", "0",
    "conf.default.rotate_velocity", "0",
    "conf.default.stop_distance", "300",
    // Widget
    "conf.__widget__.forward_velocity", "slider.0.02",
    "conf.__widget__.rotate_velocity", "slider.0.2",
    "conf.__widget__.stop_distance", "text",
    // Constraints
    "conf.__constraints__.forward_velocity", "-0.20<=x<=0.20",
    "conf.__constraints__.rotate_velocity", "-1.6<=x<=1.6",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RasPiMouseSampleCPP::RasPiMouseSampleCPP(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_distance_sensorIn("distance_sensor", m_distance_sensor),
    m_target_velocityOut("target_velocity", m_target_velocity)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RasPiMouseSampleCPP::~RasPiMouseSampleCPP()
{
}



RTC::ReturnCode_t RasPiMouseSampleCPP::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("distance_sensor", m_distance_sensorIn);
  
  // Set OutPort buffer
  addOutPort("target_velocity", m_target_velocityOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("forward_velocity", m_forward_velocity, "0");
  bindParameter("rotate_velocity", m_rotate_velocity, "0");
  bindParameter("stop_distance", m_stop_distance, "300");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onActivated(RTC::UniqueId ec_id)
{
	for (int i = 0; i < 4; i++)
	{
		m_last_sensor_data[i] = 0;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onDeactivated(RTC::UniqueId ec_id)
{
	//停止する
	m_target_velocity.data.vx = 0;
	m_target_velocity.data.vy = 0;
	m_target_velocity.data.va = 0;
	setTimestamp(m_target_velocity);
	m_target_velocityOut.write();

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onExecute(RTC::UniqueId ec_id)
{
	//データを新規に受信した場合に、データをm_last_sensor_dataを格納する
	if (m_distance_sensorIn.isNew())
	{
		m_distance_sensorIn.read();
		if (m_distance_sensor.data.length() == 4)
		{
			for (int i = 0; i < 4; i++)
			{
				m_last_sensor_data[i] = m_distance_sensor.data[i];
			}
		}
	}
	//センサの計測値がstop_distance以上の時に前進しないようにする
	if (m_forward_velocity > 0)
	{
		for (int i = 0; i < 4; i++)
		{
			if (m_last_sensor_data[i] > m_stop_distance)
			{
				m_target_velocity.data.vx = 0;
				m_target_velocity.data.vy = 0;
				m_target_velocity.data.va = 0;
				setTimestamp(m_target_velocity);
				m_target_velocityOut.write();
				return RTC::RTC_OK;
			}
		}
	}
	//コンフィギュレーションパラメータで設定した速度を送信する
	m_target_velocity.data.vx = m_forward_velocity;
	m_target_velocity.data.vy = 0;
	m_target_velocity.data.va = m_rotate_velocity;
	setTimestamp(m_target_velocity);
	m_target_velocityOut.write();


	//std::cout << m_forward_velocity << "\t" << m_rotate_velocity << std::endl;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseSampleCPP::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void RasPiMouseSampleCPPInit(RTC::Manager* manager)
  {
    coil::Properties profile(raspimousesamplecpp_spec);
    manager->registerFactory(profile,
                             RTC::Create<RasPiMouseSampleCPP>,
                             RTC::Delete<RasPiMouseSampleCPP>);
  }
  
};


