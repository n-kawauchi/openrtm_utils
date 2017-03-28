
#include <QGraphicsScene>


#include "Body.h"
#include "diagramscene.h"




BodyItem::BodyItem(BodyData *bd, QGraphicsItem *parent, QGraphicsScene *scene)
: QGraphicsPixmapItem(parent)
{
	m_param = bd;

	setAcceptDrops(true);
	setPixmap(QPixmap(":/images/Body.png"));
	setScale(0.5);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
	m_param->m_mode = MoveItem;
	m_param->tip = false;

}

int BodyItem::returnGeom()
{

	return m_param->m_param.m_type;
}

BodyData* BodyItem::ReturnParam()
{
	 
	return m_param;

}

void BodyItem::setName(QString Name){
	
	m_param->m_param.NAME = Name;

}

QString BodyItem::ReturnName(){

	return m_param->m_param.NAME;

}

void BodyItem::SetTip(bool Tip){

	m_param->tip = Tip;

}

void BodyItem::setGeom(BodyData *bd)
{
	m_param = bd;
	if (m_param->m_param.m_type == Body_Box)
	{
		setPixmap(QPixmap(":/images/Box.png"));
	}
	else if (m_param->m_param.m_type == Body_Sphere)
	{
		setPixmap(QPixmap(":/images/Sphere.png"));
	}
	else if (m_param->m_param.m_type == Body_Cone)
	{
		setPixmap(QPixmap(":/images/Cone.png"));
	}
	else if (m_param->m_param.m_type == Body_Cylinder)
	{
		setPixmap(QPixmap(":/images/Cylinder.png"));
	}
	else if (m_param->m_param.m_type == Body_Polygon)
	{
		setPixmap(QPixmap(":/images/Polygon.png"));
	}
	
	
	
	
}


void BodyItem::setParam(BodyParam bp)
{
	m_param->m_param = bp;
}

void BodyItem::open()
{
    BodyDialog dialog;
    dialog.exec();
}




