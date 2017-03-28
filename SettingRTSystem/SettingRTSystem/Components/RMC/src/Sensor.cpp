

#include <QGraphicsScene>

#include "Sensor.h"




SensorItem::SensorItem(SensorData *sd, QGraphicsItem *parent, QGraphicsScene *scene)
: QGraphicsPixmapItem(parent)
{
	setAcceptDrops(true);
	setPixmap(QPixmap(":/images/SensorE.png"));
	setScale(0.5);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

	m_param = sd;
	setParam(sd->m_param);
}

int SensorItem::returnGeom()
{

	return m_param->m_param.m_type;
}

void SensorItem::setBodyNum(BodyData *bd)
{
	m_param->m_body = bd;
}

SensorData* SensorItem::ReturnParam()
{
	 
	return m_param;

}

void SensorItem::setData(SensorData *sd)
{
	m_param = sd;
}



int SensorItem::ReturnID()
{


	return m_param->m_param.ID;
}

BodyData*  SensorItem::ReturnBodyNUM()
{


	return m_param->m_body;
}


void SensorItem::setName(QString Name){
	
	m_param->m_param.NAME = Name;

}

QString SensorItem::ReturnName(){

	return m_param->m_param.NAME;

}


void SensorItem::setParam(SensorParam sp)
{
	if (m_param->m_param.m_type != sp.m_type)
	{
		m_param->setType(sp.m_type);
	}
	m_param->m_param = sp;
	
	

	if (m_param->m_param.m_type == Force || m_param->m_param.m_type == Torque)setPixmap(QPixmap(":/images/Force.png"));
	if (m_param->m_param.m_type == Gyro){
		setPixmap(QPixmap(":/images/Gyro.png"));
	}
	if (m_param->m_param.m_type == Range)setPixmap(QPixmap(":/images/Pressure.png"));
	if (m_param->m_param.m_type == Acceleration)setPixmap(QPixmap(":/images/Acce.png"));

}










