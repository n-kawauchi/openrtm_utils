// -*- C++ -*-
/*!
 * @file  PresentationView.cpp
 * @brief Presentation View Component
 * @date $Date$
 *
 * $Id$
 */


#include "PresentationView.h"

PresentationView* comp = NULL;

// Module specification
// <rtc-template block="module_spec">
static const char* presentationview_spec[] =
  {
    "implementation_id", "PresentationView",
    "type_name",         "PresentationView",
    "description",       "Presentation View Component",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Presentation",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PresentationView::PresentationView(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_EffectNumberOutOut("EffectNumberOut", m_EffectNumberOut),
	m_SlideNumberOutOut("SlideNumberOut", m_SlideNumberOut),
	m_PenOut("Pen", m_Pen),
    m_imageIn("image", m_image),
	m_DataBasePort("DataBase")

    // </rtc-template>
{
	imageIsNew = false;
	m_manager = manager;
}

/*!
 * @brief destructor
 */
PresentationView::~PresentationView()
{
}



RTC::ReturnCode_t PresentationView::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addOutPort("SlideNumberOut", m_SlideNumberOutOut);
  addOutPort("EffectNumberOut", m_EffectNumberOutOut);
  addOutPort("Pen", m_PenOut);
  addInPort("image", m_imageIn);

  m_DataBasePort.registerConsumer("database", "DataBase::mDataBase", m_database);
  addPort(m_DataBasePort);
  
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

	coil::UUID_Generator *m_uuid = new coil::UUID_Generator();
	coil::UUID* m_generateUUID = m_uuid->generateUUID(0, 0);
	
	m_uuidstr = m_generateUUID->to_string();

	delete m_uuid;
	delete m_generateUUID;

  comp = this;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t PresentationView::onFinalize()
{
	comp = NULL;
  return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t PresentationView::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationView::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t PresentationView::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

int PresentationView::getRate()
{
	RTC::ExecutionContextList_var ecs;
    ecs = this->get_owned_contexts();
	return (int)(1/ecs[(CORBA::ULong)0]->get_rate());
}

void PresentationView::putPenData(std::vector<int>*dt)
{
	
	if(dt->size() > 3)
	{
		m_Pen.data.length(dt->size());
		for(int i=0;i < dt->size();i++)
		{
			m_Pen.data[i] = (*dt)[i];
		}
		m_PenOut.write();
	}
}

RTC::ReturnCode_t PresentationView::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PresentationView::onExecute(RTC::UniqueId ec_id)
{
	if(m_imageIn.isNew())
	{
		//coil::TimeValue t1(coil::gettimeofday());
		m_imageIn.read();
		//coil::TimeValue t2(coil::gettimeofday());
		//std::cout << t2 - t1 << std::endl;
		imageIsNew = true;
	}
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PresentationView::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationView::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationView::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationView::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PresentationView::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

CameraImage *PresentationView::getImage()
{
	return &m_image;
}

void PresentationView::writeSlideNumberOut(int num)
{
	m_SlideNumberOut.data = num;
	m_SlideNumberOutOut.write();
}

void PresentationView::writeEffectNumberOut(int num)
{
	m_EffectNumberOut.data = num;
	m_EffectNumberOutOut.write();
}

std::vector<std::string> PresentationView::getPath(const char *name, std::vector<std::vector<std::string>> m_List)
{
	std::vector<std::string> ans;
	for(int i=0;i < m_List.size();i++)
	{
		
		if(m_List[i].size() >= 2)
		{
			
			
			std::string tmp = name;
			if(m_List[i][0] == tmp)
			{
				return m_List[i];
			}
		}

	}
	return ans;
}



bool PresentationView::getRTC(std::vector<std::string> name, std::vector<OtherPort> ops, OtherPort &op)
{
	for(int i=0;i < ops.size();i++)
	{
		
		bool flag = true;
		if(ops[i].buff.size() != name.size())
			flag = false;
		for(int j=0;j < name.size();j++)
		{
			
			if(name[j] != ops[i].buff[j])
			{
				flag = false;
			}
		}

		if(flag)
		{
			op = ops[i];
			return true;
			
		}
	}
	return false;
}

bool PresentationView::connectDPorts(std::string m_path, std::string pname, PortService_ptr p1)
{
	std::vector<std::string> vrp = split(m_path, "\\");
	if(vrp.size() > 1)
	{
			
		RTC::CorbaNaming namingserver(m_manager->getORB(), vrp[0].c_str());
		TreeObject *to = new TreeObject(vrp[0].c_str());
		std::vector<OtherPort> ops;
			
		rtc_get_rtclist(namingserver, ops, to, vrp[0]);
			
		RTC::PortService_var p;
		std::vector<std::string> s;
		OtherPort op = OtherPort(p, s);
		vrp.push_back(pname);
			
		if(getRTC(vrp, ops, op))
		{
				
			//std::string tname = op.pb->get_port_profile()->name;
				
			PortService_var p = op.pb;
			//std::vector<std::string> pn = split(tname, ".");
			portConnect(p1, p);
				
			return true;
				
		}
			
		
	}
	return false;
}

bool PresentationView::connectDPort(const char *name, std::vector<std::vector<std::string>> m_List)
{
	m_imageIn.disconnect_all();
	m_SlideNumberOutOut.disconnect_all();
	m_EffectNumberOutOut.disconnect_all();
	m_PenOut.disconnect_all();

	
	std::vector<std::string> rp = getPath(name, m_List);
	
	if(rp.size() >= 7)
	{
		if(!connectDPorts(rp[1],rp[2],m_imageIn.getPortRef()))
			return false;
		if(rp[3] != "None")
		{
			connectDPorts(rp[3],rp[4],m_SlideNumberOutOut.getPortRef());
			connectDPorts(rp[3],rp[5],m_EffectNumberOutOut.getPortRef());
			connectDPorts(rp[3],rp[6],m_PenOut.getPortRef());
		}
		
	}
	return true;
}

std::vector<std::vector<std::string>> PresentationView::getList()
{
	
	std::vector<std::vector<std::string>> m_list;
	try
	{
		m_database._ptr()->setConnection("Presentation","","");
		
		
		
		m_database._ptr()->executeQuery(m_uuidstr.c_str(), "Presentation", "select * from LIST");
		
	}
	catch(...)
	{
		return m_list;
	}

	try
	{
		while(m_database._ptr()->ResultSetNext(m_uuidstr.c_str()))
		{
			std::vector<std::string> sv;
			sv.push_back(m_database._ptr()->getString(m_uuidstr.c_str(),1));
			//std::cout << sv[0] << std::endl;
			sv.push_back(m_database._ptr()->getString(m_uuidstr.c_str(),2));
			sv.push_back(m_database._ptr()->getString(m_uuidstr.c_str(),3));
			sv.push_back(m_database._ptr()->getString(m_uuidstr.c_str(),4));
			sv.push_back(m_database._ptr()->getString(m_uuidstr.c_str(),5));
			sv.push_back(m_database._ptr()->getString(m_uuidstr.c_str(),6));
			sv.push_back(m_database._ptr()->getString(m_uuidstr.c_str(),7));
			m_list.push_back(sv);
		}
	}
	catch(...)
	{
		return m_list;
	}
	return m_list;
}


extern "C"
{
 
  void PresentationViewInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentationview_spec);
    manager->registerFactory(profile,
                             RTC::Create<PresentationView>,
                             RTC::Delete<PresentationView>);
  }
  
};


