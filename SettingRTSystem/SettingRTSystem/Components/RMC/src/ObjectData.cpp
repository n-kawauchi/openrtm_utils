#include <QtWidgets>
#include "ObjectData.h"

colorFlag::colorFlag(float r, float g, float b, QString name)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	m_name = name;
}
QStringList::iterator PolygonData::setDiffuseColor(QStringList::iterator f, MeshData *md, QString name)
{
	colorFlag cf = colorFlag(0, 0, 0, name);
	//std::cout << (const char*)name.toLocal8Bit() << std::endl;
	while (true)
	{
		f++;
		if ((*f) == "diffuseColor")
		{
			for (int i = 0; i < 3;i++)
			{
				f++;
				cf.color[i] = (*f).toFloat();
				md->color[i] = cf.color[i];
			}
			colorList.push_back(cf);
			return f;
		}
		
	}
	return f;
}
QStringList::iterator PolygonData::setCoordinate(QStringList::iterator f, MeshData *md)
{
	while (true)
	{
		if ((*f) == "point")
		{
			f = setPoint(f, md);
			return f;
		}
		f++;
	}
	return f;
}
QStringList::iterator PolygonData::setPoint(QStringList::iterator f, MeshData *md)
{
	while (true)
	{
		f++;
		if ((*f) == "]"){

			return f;

		}
		else if ((*f) != "["){
			md->point.push_back((*f).toFloat());
			
		}
		
	}
	return f;
}
QStringList::iterator PolygonData::setCoordIndex(QStringList::iterator f, MeshData *md)
{
	md->coordIndex.push_back(std::vector<int>());
	while (true)
	{
		f++;
		if ((*f) == "]"){

			return f;
		}
		else if ((*f) != "[")
		{
			
			(*(md->coordIndex.end()-1)).push_back((*f).toInt());
			if ((*f).toInt() == -1)
			{
				md->coordIndex.push_back(std::vector<int>());
			}

		}
	}
	return f;
}
QStringList::iterator PolygonData::setDEF(QStringList::iterator f, MeshData *md)
{
	f++;
	f++;
	QString name = (*f);
	while (true)
	{
		f++;
		if ((*f) == "Appearance"){
			f = setDiffuseColor(f, md, name);
			return f;
		}
	}
	return f;
}
QStringList::iterator PolygonData::setShape(QStringList::iterator f, MeshData *md)
{
	return f;
}

QStringList::iterator PolygonData::setColor(QStringList::iterator f, MeshData *md)
{
	f++;
	f++;
	for (std::vector<colorFlag>::iterator it = colorList.begin(); it != colorList.end(); ++it)
	{
		if ((*it).m_name == (*f))
		{
			for (int i = 0; i < 3; i++)
			{
				md->color[i] = (*it).color[i];
			}
			
		}
	}
	return f;
}

void PolygonData::loadFile(const QString &fileName, QWidget *parent)
{
	QTextCodec* tc = QTextCodec::codecForLocale();
	NAME = fileName;
	int color_num = 0;
	int point_num = 0;
	int coord_num = 0;
	int transrotnum = 0;
	int STATUS = Source_NONE;


	std::vector<QString> TEMPDF;
	int DEFNUM = 0;
	std::vector<int> DNUM;
	std::vector<std::vector<float>> c_list;

	std::vector<float> tempPoint;
	std::vector<int> tempCoord;

	

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(parent, tc->toUnicode("Recent Files"),
			tc->toUnicode("Cannot write file %1:\n%2.")
			.arg(fileName)
			.arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
	QStringList TList;
	while (in.status() != QTextStream::ReadPastEnd) {


		QString XX;

		in >> XX;

		QStringList TXX;

		TXX = XX.split(","); //TXX.size()
		for (QStringList::iterator it = TXX.begin(); it != TXX.end(); ++it)
		{
			TList.push_back((*it));
		}
	}

	for (QStringList::iterator it = TList.begin(); it != TList.end(); ++it){
		if ((*it) != ""){


				


				

				//if(point == true){
				




				

				
				if ((*it) == "Coordinate")
				{
					it = setCoordinate(it, &Data[(int)Data.size() - 1]);
				}
				
				if ((*it) == "coordIndex")
				{
					it = setCoordIndex(it, &Data[(int)Data.size() - 1]);

				}
				
				if ((*it) == "appearance")
				{
					QString tmp = (*(it + 1));
					if (tmp == "DEF")
					{
						setDEF(it, &Data[(int)Data.size() - 1]);
					}
				}
				if ((*it) == "appearance")
				{
					QString tmp = (*(it + 1));
					if (tmp == "USE")
					{
						setColor(it, &Data[(int)Data.size() - 1]);
					}
				}


				if ((*it) == "Shape")Data.push_back(MeshData());







			
		}
	}


	file.close();
}

ItemDataBase::ItemDataBase()
{ 
	m_joint1 = NULL;
	m_joint2 = NULL;
}

MeshData::MeshData()
{

}

void MeshData::setColor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

PolygonData::PolygonData()
{

}


void ObjectParamBase::setPosition(double px, double py, double pz)
{
	m_px = px;
	m_py = py;
	m_pz = pz;
}

BodyParam::BodyParam()
{

}


void BodyParam::setSize(double length, double width, double height)
{
	m_length = length;
	m_width = width;
	m_height = height;
};
void BodyParam::setDirection(double slx, double sly, double slz)
{
	m_slx = slx;
	m_sly = sly;
	m_slz = slz;
};
void BodyParam::setColor(double red, double green, double blue)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
};



BodyData::BodyData(BodyParam param)
{
	m_param = param;
};


void BodyData::remove(JointData *jd)
{
	if (m_joint1 == jd)
		m_joint1 = NULL;
	else if (m_joint2 == jd)
		m_joint2 = NULL;

};


JointParam::JointParam(){
	rotorResistor = 0;
	torqueConst = 0;
	ulimitH = 1000;
	ulimitL = -1000;
	uvlimitH = 1000;
	uvlimitL = -1000;
	encoder = 0;
};


void JointParam::setAxis(double axisx, double axisy, double axisz)
{
	m_axisx = axisx;
	m_axisy = axisy;
	m_axisz = axisz;
};

void JointParam::setULimit(double h, double l)
{
	ulimitH = h;
	ulimitL = l;
};
void JointParam::setUVLimit(double h, double l)
{
	uvlimitH = h;
	uvlimitL = l;
};


JointData::JointData(BodyData *item1, BodyData *item2, JointParam param)
{
	m_item1 = item1;
	m_item2 = item2;
	m_param = param;
};
void JointData::setBody(BodyData *item1, BodyData *item2)
{
	m_item1 = item1;
	m_item2 = item2;
};
void JointData::remove(BodyData *item1)
{
	if (m_item1 == item1)
	{
		m_item1 = NULL;
	}
	if (m_item2 == item1)
	{
		m_item2 = NULL;
	}
};


SensorParam::SensorParam()
{

};

void SensorParam::setSize(double length, double width, double height)
{
	m_length = length;
	m_width = width;
	m_height = height;
};
void SensorParam::setDirection(double slx, double sly, double slz)
{
	m_slx = slx;
	m_sly = sly;
	m_slz = slz;
};


SensorData::SensorData(BodyData *body, SensorParam param)
{
	m_port = NULL;
	m_body = body;
	m_param = param;
	setType(m_param.m_type);
};
void SensorData::delPort()
{
	
	if (m_port)
	{
		
		delete m_port;
		m_port = NULL;
	}
}
void SensorData::setType(int type)
{
	
	delPort();
	m_param.m_type = type;
	
	if (type == Force || type == Range || type == Torque)
	{
		m_port = new FloatSeqSensorDataPort((const char*)m_param.NAME.toLocal8Bit(), RMC::obj);
	}
	else if (type == Range)
	{
		m_port = new FloatSensorDataPort((const char*)m_param.NAME.toLocal8Bit(), RMC::obj);
	}
	else if (type == Gyro)
	{
		m_port = new AngularVelocitySensorDataPort((const char*)m_param.NAME.toLocal8Bit(), RMC::obj);
	}
	else if (type == Acceleration)
	{
		m_port = new AccelerationSensorDataPort((const char*)m_param.NAME.toLocal8Bit(), RMC::obj);
	}
};

void SensorData::update()
{
	if (m_port)
	{
		if (m_port->isNew())
		{
			value = m_port->getValue();
		}
	}
	
}

CameraParam::CameraParam(){
	frontClipDistance = 0.01;
	backClipDistance = 10.0;
	fieldOfView = 0.785398;
	m_width = 320;
	m_height = 240;
	m_type = COLOR;
};
void CameraParam::setSize(double width, double height)
{
	m_width = width;
	m_height = height;
};
void CameraParam::setDirection(double slx, double sly, double slz)
{
	m_slx = slx;
	m_sly = sly;
	m_slz = slz;
};


CameraData::CameraData(JointData *joint, CameraParam param)
{
	m_joint1 = joint;
	m_param = param;
};