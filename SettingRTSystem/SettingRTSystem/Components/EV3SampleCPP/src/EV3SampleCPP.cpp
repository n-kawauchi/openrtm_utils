// -*- C++ -*-
/*!
 * @file  EV3SampleCPP.cpp
 * @brief EV3 Sample Component
 * @date $Date$
 *
 * @author 宮本信彦
 * n-miyamoto@aist.go.jp
 * 産業技術総合研究所　
 * ロボットイノベーション研究センター　
 * ロボットソフトウェアプラットフォーム研究チーム
 *
 * LGPL
 *
 * $Id$
 */

#include "EV3SampleCPP.h"

// Module specification
// <rtc-template block="module_spec">
static const char* ev3samplecpp_spec[] =
  {
    "implementation_id", "EV3SampleCPP",
    "type_name",         "EV3SampleCPP",
    "description",       "EV3 Sample Component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Controller",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.forward_velocity", "0.00",
    "conf.default.rotate_velocity", "0.0",

    // Widget
    "conf.__widget__.forward_velocity", "slider.0.04",
    "conf.__widget__.rotate_velocity", "slider.0.2",
    // Constraints
    "conf.__constraints__.forward_velocity", "-0.20<=x<=0.20",
    "conf.__constraints__.rotate_velocity", "-3.1<=x<=3.1",

    "conf.__type__.forward_velocity", "double.0.04",
    "conf.__type__.rotate_velocity", "double.0.2",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
EV3SampleCPP::EV3SampleCPP(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_touchIn("touch", m_touch),
    m_target_velocityOut("target_velocity", m_target_velocity),
    m_soundOut("sound", m_sound)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
EV3SampleCPP::~EV3SampleCPP()
{
}



RTC::ReturnCode_t EV3SampleCPP::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("touch", m_touchIn);
  
  // Set OutPort buffer
  addOutPort("target_velocity", m_target_velocityOut);
  addOutPort("sound", m_soundOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("forward_velocity", m_forward_velocity, "0.00");
  bindParameter("rotate_velocity", m_rotate_velocity, "0.0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onActivated(RTC::UniqueId ec_id)
{
	for (int i = 0; i < 2; i++)
	{
		m_last_sensor_data[i] = false;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onDeactivated(RTC::UniqueId ec_id)
{
	//停止する
	m_target_velocity.data.vx = 0;
	m_target_velocity.data.vy = 0;
	m_target_velocity.data.va = 0;
	setTimestamp(m_target_velocity);
	m_target_velocityOut.write();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onExecute(RTC::UniqueId ec_id)
{
	//データを新規に受信した場合に、データをm_last_sensor_dataを格納する
	if (m_touchIn.isNew())
	{
		m_touchIn.read();
		if (m_touch.data.length() == 2)
		{
			for (int i = 0; i < 2; i++)
			{
				//タッチセンサがOFFからONになった時に音を鳴らす
				if (!m_last_sensor_data[i] && m_touch.data[i])
				{
					m_sound.data = "beep";
					setTimestamp(m_sound);
					m_soundOut.write();

					
				}
				m_last_sensor_data[i] = m_touch.data[i];
			}
		}
	}
	//タッチセンサがONの時に前進しないようにする
	if (m_forward_velocity > 0)
	{
		for (int i = 0; i < 2; i++)
		{
			if (m_last_sensor_data[i])
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

  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t EV3SampleCPP::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void EV3SampleCPPInit(RTC::Manager* manager)
  {
    coil::Properties profile(ev3samplecpp_spec);
    manager->registerFactory(profile,
                             RTC::Create<EV3SampleCPP>,
                             RTC::Delete<EV3SampleCPP>);
  }
  
};


