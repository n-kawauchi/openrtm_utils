#include <QGraphicsScene> 

#include "Joint.h"
#include "JointMenu.h"


JointItem::JointItem(JointData *jd, QGraphicsItem *parent, QGraphicsScene *scene)
: QGraphicsPixmapItem(parent)
{
	setAcceptDrops(true);
	QPixmap pixmap(":/images/JointE.png");
	
	setPixmap(pixmap);
	setScale(0.5);
    setFlag(QGraphicsItem::ItemIsSelectable);
	m_param = jd;
	m_param->m_param.m_mode = MoveItem;
}


void JointItem::open()
{
    ActDialog dialog;
    dialog.exec();
}



int JointItem::returnJoint()
{

	return m_param->m_param.m_type;
}


JointData* JointItem::ReturnParam()
{
	 
	return m_param;


}



QString JointItem::ReturnName(){

	return m_param->m_param.NAME;

}

void JointItem::setJoint(JointData *jd)
{
	m_param = jd;
	if (m_param->m_param.m_type == Hinge)
	{
		setPixmap(QPixmap(":/images/Hinge.png"));
	}
	else if (m_param->m_param.m_type == Hinge)
	{
		setPixmap(QPixmap(":/images/Slider.png"));
	}
	else if(m_param->m_param.m_type == Hinge)
	{
		setPixmap(QPixmap(":/images/Fix.png"));
	}
	
	

}


void JointItem::setParam(JointParam jp)
{
	m_param->m_param = jp;
}

void JointItem::setBody(BodyData* i1, BodyData* i2)
{
	m_param->m_item1 = i1;
	m_param->m_item2 = i2;

}

ItemDataBase* JointItem::returnNUM1()
{
	return m_param->m_item1;
}
ItemDataBase* JointItem::returnNUM2()
{
	return m_param->m_item2;
}



