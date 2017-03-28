

#include <QGraphicsScene>

#include "Camera.h"
#include "diagramscene.h"
#include "mainwindow.h" 



CameraItem::CameraItem(CameraData *cd, QGraphicsItem *parent, QGraphicsScene *scene)
: QGraphicsPixmapItem(parent)
{
	setAcceptDrops(true);
	setPixmap(QPixmap(":/images/VS.png"));
	setScale(0.5);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

	m_param = cd;

}

int CameraItem::returnType()
{

	return m_param->m_param.m_type;
}

void CameraItem::setJointNum(JointData* jd)
{
	m_param->m_joint1 = jd;
}

void CameraItem::setParam(CameraParam cd)
{
	m_param->m_param = cd;
}

CameraData*  CameraItem::ReturnParam()
{
	return m_param;


}

int CameraItem::ReturnID()
{


	return m_param->m_param.ID;
}

JointData* CameraItem::ReturnJointNUM()
{


	return m_param->m_joint1;
}


void CameraItem::setName(QString Name){
	
	m_param->m_param.NAME = Name;

}

QString CameraItem::ReturnName(){

	return m_param->m_param.NAME;

}


void CameraItem::setData(CameraData *cd)
{
	m_param = cd;
}










