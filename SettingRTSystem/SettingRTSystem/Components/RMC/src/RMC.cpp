// -*- C++ -*-
/*!
 * @file  RMC.cpp
 * @brief Robot Model Creator
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "RMC.h"

RMC *RMC::obj = NULL;

std::vector<float> SensorDataPort::getValue()
{
	std::vector<float> ans;
	return ans;
}

bool SensorDataPort::isNew()
{
	return false;
}

SensorDataPort::~SensorDataPort()
{

}


FloatSeqSensorDataPort::FloatSeqSensorDataPort(std::string name, RTC::DataFlowComponentBase *rtc)
{
	
	In = new TimedFloatSeq();
	inIn = new RTC::InPort<TimedFloatSeq>(name.c_str(), *In);
	m_rtc = rtc;
	
	m_rtc->addInPort(name.c_str(), *inIn);
	
};
FloatSeqSensorDataPort::~FloatSeqSensorDataPort()
{

	m_rtc->removePort(*inIn);
}
std::vector<float> FloatSeqSensorDataPort::getValue()
{
	std::vector<float> ans;
	inIn->read();
	for (int i = 0; i < In->data.length(); i++)
	{
		ans.push_back(In->data[i]);
	}
	return ans;
};
bool FloatSeqSensorDataPort::isNew()
{
	return inIn->isNew();
}




FloatSensorDataPort::FloatSensorDataPort(std::string name, RTC::DataFlowComponentBase *rtc)
{

	In = new TimedFloat();
	inIn = new RTC::InPort<TimedFloat>(name.c_str(), *In);
	m_rtc = rtc;

	m_rtc->addInPort(name.c_str(), *inIn);

};
FloatSensorDataPort::~FloatSensorDataPort()
{

	m_rtc->removePort(*inIn);
}
std::vector<float> FloatSensorDataPort::getValue()
{
	std::vector<float> ans;
	inIn->read();
	ans.push_back(In->data);
	
	return ans;
};
bool FloatSensorDataPort::isNew()
{
	return inIn->isNew();
}


AccelerationSensorDataPort::AccelerationSensorDataPort(std::string name, RTC::DataFlowComponentBase *rtc)
{
	In = new TimedAcceleration3D();
	inIn = new RTC::InPort<TimedAcceleration3D>(name.c_str(), *In);
	m_rtc = rtc;
	m_rtc->addInPort(name.c_str(), *inIn);
};
AccelerationSensorDataPort::~AccelerationSensorDataPort()
{
	m_rtc->removePort(*inIn);
}
std::vector<float> AccelerationSensorDataPort::getValue()
{
	std::vector<float> ans;
	inIn->read();
	ans.push_back(In->data.ax);
	ans.push_back(In->data.ay);
	ans.push_back(In->data.az);
	return ans;
};
bool AccelerationSensorDataPort::isNew()
{
	return inIn->isNew();
}

AngularVelocitySensorDataPort::AngularVelocitySensorDataPort(std::string name, RTC::DataFlowComponentBase *rtc)
{
	In = new TimedAngularVelocity3D();
	inIn = new RTC::InPort<TimedAngularVelocity3D>(name.c_str(), *In);
	m_rtc = rtc;
	m_rtc->addInPort(name.c_str(), *inIn);
};
AngularVelocitySensorDataPort::~AngularVelocitySensorDataPort()
{
	m_rtc->removePort(*inIn);
}
std::vector<float> AngularVelocitySensorDataPort::getValue()
{
	std::vector<float> ans;
	inIn->read();
	ans.push_back(In->data.avx);
	ans.push_back(In->data.avy);
	ans.push_back(In->data.avz);
	return ans;
};
bool AngularVelocitySensorDataPort::isNew()
{
	return inIn->isNew();
}

// Module specification
// <rtc-template block="module_spec">
static const char* rmc_spec[] =
  {
    "implementation_id", "RMC",
    "type_name",         "RMC",
    "description",       "Robot Model Creator",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Viewer",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.file_path", "None",
    // Widget
    "conf.__widget__.file_path", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RMC::RMC(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_posIn("pos", m_pos)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RMC::~RMC()
{
}



RTC::ReturnCode_t RMC::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("pos", m_posIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("file_path", m_file_path, "None");
  // </rtc-template>
  this->m_configsets.update("default");
  RMC::obj = this;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RMC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

std::string RMC::getFileName()
{
	if (m_file_path == "None")
	{
		return "";
	}
	return m_file_path;
}
bool RMC::angleIsNew()
{
	return m_posIn.isNew();
}
std::vector<float> RMC::getAngle()
{
	std::vector<float> ans;
	m_posIn.read();
	for (int i = 0; i < m_pos.data.length(); i++)
	{
		ans.push_back(m_pos.data[i]);
	}
	return ans;
}


extern "C"
{
 
  void RMCInit(RTC::Manager* manager)
  {
    coil::Properties profile(rmc_spec);
    manager->registerFactory(profile,
                             RTC::Create<RMC>,
                             RTC::Delete<RMC>);
  }
  
};


