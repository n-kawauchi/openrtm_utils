// -*- C++ -*-
/*!
 * @file  IfElse.cpp
 * @brief If Else
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "IfElse.h"

// Module specification
// <rtc-template block="module_spec">
static const char* ifelse_spec[] =
  {
    "implementation_id", "IfElse",
    "type_name",         "IfElse",
    "description",       "If Else",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Logic",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.if_condition", "None",
    "conf.default.ifelse_condition", "None",
    "conf.default.dataType", "TimedDouble",
    "conf.default.imputNum", "1",
    // Widget
    "conf.__widget__.if_condition", "text",
    "conf.__widget__.ifelse_condition", "text",
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.imputNum", "spin",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedLong,TimedFloat,TimedShort,TimedULong,TimedUShort)",
    "conf.__constraints__.imputNum", "1<=x<=30",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
IfElse::IfElse(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager),
    m_IfOutOut("IfOut", m_IfOut),
    m_IfElseOutOut("IfElseOut", m_IfElseOut),
    m_ElseOutOut("ElseOut", m_ElseOut)

    // </rtc-template>
{
	func = NULL;

}

/*!
 * @brief destructor
 */
IfElse::~IfElse()
{
}


void IfElse::configUpdate()
{
	this->m_configsets.update("default");
	coil::eraseBlank(m_if_condition);
	coil::eraseBlank(m_ifelse_condition);
	coil::eraseBlank(m_dataType);
	


	if(last_dataType != m_dataType)
	{
		last_dataType = m_dataType;

		/*std::cout << m_if_condition << std::endl;
		std::cout << m_ifelse_condition << std::endl;
		std::cout << m_dataType << std::endl;
		std::cout << m_imputNum << std::endl;*/

		if(func)
		{
			delete func;
		}
		
		if(m_dataType == "TimedDouble")
		{
			func = new IfElseComp<TimedDouble, double>(this, m_imputNum);
		}
		else if(m_dataType == "TimedLong")
		{
			func = new IfElseComp<TimedLong, int>(this, m_imputNum);
		}
		else if(m_dataType == "TimedFloat")
		{
			func = new IfElseComp<TimedFloat, float>(this, m_imputNum);
		}
		else if(m_dataType == "TimedShort")
		{
			func = new IfElseComp<TimedShort, int>(this, m_imputNum);
		}
		else if(m_dataType == "TimedULong")
		{
			func = new IfElseComp<TimedULong, int>(this, m_imputNum);
		}
		else if(m_dataType == "TimedUShort")
		{
			func = new IfElseComp<TimedUShort, int>(this, m_imputNum);
		}
	}
	func->setCondition(m_if_condition,m_ifelse_condition);
	func->changeNum(m_imputNum);
}

void IfElse::writeData(bool if_ans, bool ifelse_ans, bool else_ans)
{
	m_IfOut.data = if_ans;
	m_IfOutOut.write();
	m_IfElseOut.data = ifelse_ans;
	m_IfElseOutOut.write();
	m_ElseOut.data = else_ans;
	m_ElseOutOut.write();
	//std::cout << if_ans << "\t" << ifelse_ans << "\t" << else_ans << std::endl;
}

RTC::ReturnCode_t IfElse::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("IfOut", m_IfOutOut);
  addOutPort("IfElseOut", m_IfElseOutOut);
  addOutPort("ElseOut", m_ElseOutOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("if_condition", m_if_condition, "None");
  bindParameter("ifelse_condition", m_ifelse_condition, "None");
  bindParameter("dataType", m_dataType, "TimedDouble");
  bindParameter("imputNum", m_imputNum, "1");
  // </rtc-template>
	//func = new IfElseCompBase<TimedDouble, double>(this, 4);
  configUpdate();
  this->addConfigurationSetListener(ON_SET_CONFIG_SET, new DynamicPortConfigUpdateParam(this));
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onDeactivated(RTC::UniqueId ec_id)
{

  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t IfElse::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void IfElseInit(RTC::Manager* manager)
  {
    coil::Properties profile(ifelse_spec);
    manager->registerFactory(profile,
                             RTC::Create<IfElse>,
                             RTC::Delete<IfElse>);
  }
  
};


