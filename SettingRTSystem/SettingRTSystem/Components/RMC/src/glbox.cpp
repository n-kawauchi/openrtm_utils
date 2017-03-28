#include <QtWidgets>
#include "glbox.h"

#include <QUuid>
#include <math.h>
#include <QPainter>
#include <iostream>


#include "Body.h"





#if defined(Q_CC_MSVC)
#pragma warning(disable:4305)
#endif

#define LIGHTX (1.0f)
#define LIGHTY (0.4f)




static float color[4] = {0.2,0.6,0.6,0.4};
static int tnum = 0;
bool BodyOrJoint;

static float testan = 0.0;

#define dCROSS(a,op,b,c) \
do { \
  (a)[0] op ((b)[1]*(c)[2] - (b)[2]*(c)[1]); \
  (a)[1] op ((b)[2]*(c)[0] - (b)[0]*(c)[2]); \
  (a)[2] op ((b)[0]*(c)[1] - (b)[1]*(c)[0]); \
} while(0)

static void normalizeVector3 (float v[3])
{
  float len = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
  if (len <= 0.0f) {
    v[0] = 1;
    v[1] = 0;
    v[2] = 0;
  }
  else {
    len = 1.0f / (float)sqrt(len);
    v[0] *= len;
    v[1] *= len;
    v[2] *= len;
  }
}

static void drawBox (const float sides[3])
{
  float lx = sides[0]*0.5f;
  float ly = sides[1]*0.5f;
  float lz = sides[2]*0.5f;

  glBegin (GL_TRIANGLE_STRIP);
  glNormal3f (-1,0,0);
  glVertex3f (-lx,-ly,-lz);
  glVertex3f (-lx,-ly,lz);
  glVertex3f (-lx,ly,-lz);
  glVertex3f (-lx,ly,lz);
  glNormal3f (0,1,0);
  glVertex3f (lx,ly,-lz);
  glVertex3f (lx,ly,lz);
  glNormal3f (1,0,0);
  glVertex3f (lx,-ly,-lz);
  glVertex3f (lx,-ly,lz);
  glNormal3f (0,-1,0);
  glVertex3f (-lx,-ly,-lz);
  glVertex3f (-lx,-ly,lz);
  glEnd();

  glBegin (GL_TRIANGLE_FAN);
  glNormal3f (0,0,1);
  glVertex3f (-lx,-ly,lz);
  glVertex3f (lx,-ly,lz);
  glVertex3f (lx,ly,lz);
  glVertex3f (-lx,ly,lz);
  glEnd();


  glBegin (GL_TRIANGLE_FAN);
  glNormal3f (0,0,-1);
  glVertex3f (-lx,-ly,-lz);
  glVertex3f (-lx,ly,-lz);
  glVertex3f (lx,ly,-lz);
  glVertex3f (lx,-ly,-lz);
  glEnd();
}

static void setColor (float r, float g, float b, float alpha)
{
  static GLfloat light_ambient[4],light_diffuse[4],light_specular[4];
  light_ambient[0] = r*0.7f;
  light_ambient[1] = g*0.7f;
  light_ambient[2] = b*0.7f;
  light_ambient[3] = alpha;
  light_diffuse[0] = r*1.0f;
  light_diffuse[1] = g*1.0f;
  light_diffuse[2] = b*1.0f;
  light_diffuse[3] = alpha;
  light_specular[0] = r*0.2f;
  light_specular[1] = g*0.2f;
  light_specular[2] = b*0.2f;
  light_specular[3] = alpha;

  

  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, light_ambient);
  glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
  
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, light_specular);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 5.0f);






}

GLBox::GLBox( QWidget* parent, const char* name )
    : QGLWidget( parent )
{
	jointnum = 0;
	bodynum = 0;
	sensornum = 0;
	cameranum = 0;
    xRot = yRot = zRot = 0.0;
	xRot = -90;
    scale = 1.25;		
    object = 0;
	xWe = 0;
	yWe = 0;
	BorT = 0;
	CHECK = false;
	bodynum = 0;
	anim = new QTimeLine(750, this);
    anim->setUpdateInterval(20);
    connect(anim, SIGNAL(valueChanged(qreal)), SLOT(animate(qreal)));
    connect(anim, SIGNAL(finished()), SLOT(animFinished()));
	anim->start();

	startTimer(30);
	RotNum = 100;
	GeoNum = 100;
	SSNum = 100;
	CCNum = 100;
	BCL = 1.0;
	JScale = 1.0;
	SScale = 1.0;
	AScale = 1.0;
	GScale = 1.0;
	TScale = 1.0;
	RScale = 1.0;
	FScale = 1.0;

        //initializeGL();

}

void GLBox::animFinished()
{
    if (anim->direction() == QTimeLine::Forward)
        anim->setDirection(QTimeLine::Backward);
    else
        anim->setDirection(QTimeLine::Forward);
}

void GLBox::setRotation(int rot)
{
	if(CHECK){
		if(RotNum != 100){
			
			if (m_Joint.size() > ANGLE.size())
			{
				for (int i = ANGLE.size(); i < m_Joint.size(); i++)
				{
					ANGLE.push_back(0);
				}
			}
			ANGLE[RotNum] = ((float)((rot - 180) % 360)) / 360 * 3.14 * 2;
			
			moveBody(ANGLE);
	
			updateGL();
		}
		/*if(SSNum != 100){
			if(Sensor[SSNum].type == Force)
			{
				FORCE88[Sensor[SSNum].ID*3] = ((float)((rot-180)))/360;
				FORCE88[Sensor[SSNum].ID*3+1] = ((float)((rot-180)))/360;
				FORCE88[Sensor[SSNum].ID*3+2] = ((float)((rot-180)))/360;
			}
			if(Sensor[SSNum].type == Gyro)
			{
				GYRO88[Sensor[SSNum].ID*3] = ((float)((rot-180)))/360;
				GYRO88[Sensor[SSNum].ID*3+1] = ((float)((rot-180)))/360;
				GYRO88[Sensor[SSNum].ID*3+2] = ((float)((rot-180)))/360;
			}
			if(Sensor[SSNum].type == Range)
			PRE88[Sensor[SSNum].ID] = ((float)((rot-180)))/360;
			if(Sensor[SSNum].type == Acceleration)
			{
				ACCE88[Sensor[SSNum].ID*3] = ((float)((rot-180)))/360;
				ACCE88[Sensor[SSNum].ID*3+1] = ((float)((rot-180)))/360;
				ACCE88[Sensor[SSNum].ID*3+2] = ((float)((rot-180)))/360;
			}
			if(Sensor[SSNum].type == Torque)
			{
				TORQUE88[Sensor[SSNum].ID*3] = ((float)((rot-180)))/360;
				TORQUE88[Sensor[SSNum].ID*3+1] = ((float)((rot-180)))/360;
				TORQUE88[Sensor[SSNum].ID*3+2] = ((float)((rot-180)))/360;
			}
	
			updateGL();
		}*/
	}
}

void GLBox::setAccArrowScale(int rot)
{
	AScale = ((float)rot)/80;
	
			updateGL();
}

void GLBox::setRangeArrowScale(int rot)
{
	RScale = ((float)rot)/80;
	
			updateGL();
}

void GLBox::setTorqueArrowScale(int rot)
{
	TScale = ((float)rot)/80;
	
			updateGL();
}

void GLBox::setForceArrowScale(int rot)
{
	FScale = ((float)rot)/80;
	
			updateGL();
}

void GLBox::setGyroArrowScale(int rot)
{
	GScale = ((float)rot)/80;
	
			updateGL();
}

void GLBox::setJointScale(int rot)
{
			JScale = ((float)rot)/20;
	
			updateGL();

}

void GLBox::setSensorScale(int rot)
{
			SScale = ((float)rot)/20;
	
			updateGL();
}

void GLBox::timerEvent(QTimerEvent *)
{
	if(CHECK){
		if (RMC::obj->angleIsNew())
		{
			moveBody(RMC::obj->getAngle());
		}
		
	//moveBody(ANGLE88);
	
	updateGL();
	}
	
}


void GLBox::animate(qreal val)
{


	updateGL();
}

static void setupDrawingMode()
{
	
  glEnable (GL_LIGHTING);

    glDisable (GL_TEXTURE_2D);

  setColor (color[0],color[1],color[2],color[3]);

  if (color[3] < 1) {
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  }
  else {
    glDisable (GL_BLEND);
  }
}

static void setTransform (const float pos[3], const float R[12])
{
  GLfloat matrix[16];
  matrix[0]=R[0];
  matrix[4]=R[4];
  matrix[8]=R[8];
  matrix[3]=0;
  matrix[1]=R[1];
  matrix[5]=R[5];
  matrix[9]=R[9];
  matrix[7]=0;
  matrix[2]=R[2];
  matrix[6]=R[6];
  matrix[10]=R[10];
  matrix[11]=0;
  matrix[12]=pos[0];
  matrix[13]=pos[1];
  matrix[14]=pos[2];
  matrix[15]=1;
  glPushMatrix();
  glMultMatrixf (matrix);
}

static void drawTriangleD (const double *v0, const double *v1, const double *v2, int solid)
{
  float u[3],v[3],normal[3];
  u[0] = float( v1[0] - v0[0] );
  u[1] = float( v1[1] - v0[1] );
  u[2] = float( v1[2] - v0[2] );
  v[0] = float( v2[0] - v0[0] );
  v[1] = float( v2[1] - v0[1] );
  v[2] = float( v2[2] - v0[2] );
  dCROSS (normal,=,u,v);
  normalizeVector3 (normal);

  glBegin(solid ? GL_TRIANGLES : GL_LINE_STRIP);
  glNormal3fv (normal);
  glVertex3dv (v0);
  glVertex3dv (v1);
  glVertex3dv (v2);
  glEnd();
}

static void drawTriangle (const float *v0, const float *v1, const float *v2, int solid)
{
  float u[3],v[3],normal[3];
  u[0] = v1[0] - v0[0];
  u[1] = v1[1] - v0[1];
  u[2] = v1[2] - v0[2];
  v[0] = v2[0] - v0[0];
  v[1] = v2[1] - v0[1];
  v[2] = v2[2] - v0[2];
  dCROSS (normal,=,u,v);
  normalizeVector3 (normal);

  glBegin(solid ? GL_TRIANGLES : GL_LINE_STRIP);
  glNormal3fv (normal);
  glVertex3fv (v0);
  glVertex3fv (v1);
  glVertex3fv (v2);
  glEnd();
}

void dsDrawTriangle (const float pos[3], const float R[12],
				const float *v0, const float *v1,
				const float *v2, int solid)
{

  setTransform (pos,R);
  drawTriangle (v0, v1, v2, solid);
  glPopMatrix();
  
}

void GLBox::DrawPolygon(PolygonData P1, const float pos[3], const float R[12], bool SEL)
{


	int count = 0;

	for(int i=0;i<P1.Data.size();i++)
	{
		if(SEL){
		color[3] = 1.0;
		color[0] = 2.0;
		color[2] = 2.0;
		color[1] = 2.0;
		}
		else{
		color[3] = BCL;
		color[0] = P1.Data[i].color[0];
		color[2] = P1.Data[i].color[2];
		color[1] = P1.Data[i].color[1];
		//std::cout << i << "\t" << P1.Data[i].coordIndex.size() << "\t" << P1.Data[i].color[0] << std::endl;
		//std::cout << i << "\t" << P1.Data[i].coordIndex.size() << "\t" << P1.Data[i].color[1] << std::endl;
		//std::cout << i << "\t" << P1.Data[i].coordIndex.size() << "\t" << P1.Data[i].color[2] << std::endl;
		}

		
		glShadeModel (GL_SMOOTH);
		setupDrawingMode();
		for(int j=0;j<P1.Data[i].coordIndex.size();j++)
		{
			

			if(P1.Data[i].coordIndex[j].size() == 4){
				
			const float TempPoint1[3] = {P1.Data[i].point[P1.Data[i].coordIndex[j][0]*3],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][0]*3+1],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][0]*3+2]};
			const float TempPoint2[3] = {P1.Data[i].point[P1.Data[i].coordIndex[j][1]*3],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][1]*3+1],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][1]*3+2]};
			const float TempPoint3[3] = {P1.Data[i].point[P1.Data[i].coordIndex[j][2]*3],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][2]*3+1],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][2]*3+2]};
			dsDrawTriangle(pos,R,TempPoint1,TempPoint2,TempPoint3,1);

			}
			else if(P1.Data[i].coordIndex[j].size() == 5){
				const float TempPoint1[3] = {P1.Data[i].point[P1.Data[i].coordIndex[j][0]*3],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][0]*3+1],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][0]*3+2]};
			const float TempPoint2[3] = {P1.Data[i].point[P1.Data[i].coordIndex[j][1]*3],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][1]*3+1],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][1]*3+2]};
			const float TempPoint3[3] = {P1.Data[i].point[P1.Data[i].coordIndex[j][2]*3],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][2]*3+1],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][2]*3+2]};
			dsDrawTriangle(pos,R,TempPoint1,TempPoint2,TempPoint3,1);
				const float TempPoint4[3] = {P1.Data[i].point[P1.Data[i].coordIndex[j][0]*3],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][0]*3+1],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][0]*3+2]};
				const float TempPoint5[3] = {P1.Data[i].point[P1.Data[i].coordIndex[j][2]*3],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][2]*3+1],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][2]*3+2]};
				const float TempPoint6[3] = {P1.Data[i].point[P1.Data[i].coordIndex[j][3]*3],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][3]*3+1],
										  P1.Data[i].point[P1.Data[i].coordIndex[j][3]*3+2]};
				dsDrawTriangle(pos,R,TempPoint4,TempPoint5,TempPoint6,6);

				j += 4;

			}
			else
			{
				
			}

			
		}
	}
	//glPopMatrix();

}

void dsDrawTriangleD (const double pos[3], const double R[12],
				 const double *v0, const double *v1,
				 const double *v2, int solid)
{
  int i;
  float pos2[3],R2[12];
  for (i=0; i<3; i++) pos2[i]=(float)pos[i];
  for (i=0; i<12; i++) R2[i]=(float)R[i];

  setupDrawingMode();
  glShadeModel (GL_FLAT);
  setTransform (pos2,R2);
  drawTriangleD (v0, v1, v2, solid);
  glPopMatrix();
}

void dsDrawBox (const float pos[3], const float R[12],
			   const float sides[3])
{
  setupDrawingMode();
  glShadeModel (GL_FLAT);
  setTransform (pos,R);
  drawBox (sides);
  glPopMatrix();
}

static void drawPatch (float p1[3], float p2[3], float p3[3], int level)
{
	int i;
	if (level > 0) {
		float q1[3],q2[3],q3[3];		 
			for (i=0; i<3; i++) {
		q1[i] = 0.5f*(p1[i]+p2[i]);
		q2[i] = 0.5f*(p2[i]+p3[i]);
		q3[i] = 0.5f*(p3[i]+p1[i]);
		}
		float length1 = (float)(1.0/sqrt(q1[0]*q1[0]+q1[1]*q1[1]+q1[2]*q1[2]));
		float length2 = (float)(1.0/sqrt(q2[0]*q2[0]+q2[1]*q2[1]+q2[2]*q2[2]));
		float length3 = (float)(1.0/sqrt(q3[0]*q3[0]+q3[1]*q3[1]+q3[2]*q3[2]));
		for (i=0; i<3; i++) {
		q1[i] *= length1;
		q2[i] *= length2;
		q3[i] *= length3;
		}
		drawPatch (p1,q1,q3,level-1);
		drawPatch (q1,p2,q2,level-1);
		drawPatch (q1,q2,q3,level-1);
		drawPatch (q3,q2,p3,level-1);
	}
	else {
		glNormal3f (p1[0],p1[1],p1[2]);
		glVertex3f (p1[0],p1[1],p1[2]);
		glNormal3f (p2[0],p2[1],p2[2]);
		glVertex3f (p2[0],p2[1],p2[2]);
	    glNormal3f (p3[0],p3[1],p3[2]);
		glVertex3f (p3[0],p3[1],p3[2]);
	}
}


static int sphere_quality = 1;

static void drawSphere()
{
# define ICX 0.525731112119133606f
# define ICZ 0.850650808352039932f
  static GLfloat idata[12][3] = {
    {-ICX, 0, ICZ},
    {ICX, 0, ICZ},
    {-ICX, 0, -ICZ},
    {ICX, 0, -ICZ},
    {0, ICZ, ICX},
    {0, ICZ, -ICX},
    {0, -ICZ, ICX},
    {0, -ICZ, -ICX},
    {ICZ, ICX, 0},
    {-ICZ, ICX, 0},
    {ICZ, -ICX, 0},
    {-ICZ, -ICX, 0}
  };

  static int index[20][3] = {
    {0, 4, 1},	  {0, 9, 4},
    {9, 5, 4},	  {4, 5, 8},
    {4, 8, 1},	  {8, 10, 1},
    {8, 3, 10},   {5, 3, 8},
    {5, 2, 3},	  {2, 7, 3},
    {7, 10, 3},   {7, 6, 10},
    {7, 11, 6},   {11, 0, 6},
    {0, 1, 6},	  {6, 1, 10},
    {9, 0, 11},   {9, 11, 2},
    {9, 2, 5},	  {7, 2, 11},
  };

  static GLuint listnum = 0;
  if (listnum==0) {
    listnum = glGenLists (1);
    glNewList (listnum,GL_COMPILE);
    glBegin (GL_TRIANGLES);
    for (int i=0; i<20; i++) {
      drawPatch (&idata[index[i][2]][0],&idata[index[i][1]][0],
		 &idata[index[i][0]][0],sphere_quality);
    }
    glEnd();
    glEndList();
  }
  glCallList (listnum);
}

void dsDrawSphere (const float pos[3], const float R[12],
			      float radius)
{
  setupDrawingMode();
  glEnable (GL_NORMALIZE);
  glShadeModel (GL_SMOOTH);
  setTransform (pos,R);

  GLUquadricObj *sphere;

  sphere = gluNewQuadric(); 

  gluQuadricDrawStyle(sphere, GLU_FILL); 

  gluSphere(sphere,radius, 10.0, 10.0);


  glPopMatrix();
  glDisable (GL_NORMALIZE);
  glShadeModel (GL_FLAT);
  glDepthRange (0,1);
  gluDeleteQuadric(sphere);
  
}

static void drawCone (float l, float r, float zoffset)
{
  int i;
  float tmp,ny,nz,a,ca,sa;
  const int n = 24;

  l *= 0.5;
  a = float(M_PI*2.0)/float(n);
  sa = (float) sin(a);
  ca = (float) cos(a);


  ny=1; nz=0;
  glBegin (GL_TRIANGLE_FAN);
  glNormal3d (ny,nz,0);
  glVertex3d (0,0,l+zoffset);
  for (i=0; i<=n; i++) {
	glNormal3d (ny,nz,0);
    glVertex3d (ny*r,nz*r,-l+zoffset);
	tmp = ca*ny - sa*nz;
    nz = sa*ny + ca*nz;
    ny = tmp;
	glNormal3d (ny,nz,0);
    glVertex3d (ny*r,nz*r,-l+zoffset);
  }
  glEnd();



  ny=1; nz=0;	
  glBegin (GL_TRIANGLE_FAN);
  glNormal3d (0,0,-1);
  glVertex3d (0,0,-l+zoffset);
  for (i=0; i<=n; i++) {
    glNormal3d (0,0,-1);
    glVertex3d (ny*r,nz*r,-l+zoffset);
    tmp = ca*ny + sa*nz;
    nz = -sa*ny + ca*nz;
    ny = tmp;
  }
  glEnd();
}

void dsDrawCone (const float pos[3], const float R[12],
				float length, float radius)
{
  setupDrawingMode();
  glShadeModel (GL_SMOOTH);
  setTransform (pos,R);
  drawCone (length,radius,0);
  glPopMatrix();


}

static void drawCylinder (float l, float r, float zoffset)
{
  int i;
  float tmp,ny,nz,a,ca,sa;
  const int n = 24;

  l *= 0.5;
  a = float(M_PI*2.0)/float(n);
  sa = (float) sin(a);
  ca = (float) cos(a);


  ny=1; nz=0;
  glBegin (GL_TRIANGLE_STRIP);
  for (i=0; i<=n; i++) {
    glNormal3d (ny,nz,0);
    glVertex3d (ny*r,nz*r,l+zoffset);
    glNormal3d (ny,nz,0);
    glVertex3d (ny*r,nz*r,-l+zoffset);
    tmp = ca*ny - sa*nz;
    nz = sa*ny + ca*nz;
    ny = tmp;
  }
  glEnd();


  glShadeModel (GL_FLAT);
  ny=1; nz=0;
  glBegin (GL_TRIANGLE_FAN);
  glNormal3d (0,0,1);
  glVertex3d (0,0,l+zoffset);
  for (i=0; i<=n; i++) {
        glNormal3d (0,0,1);
		glVertex3d (ny*r,nz*r,l+zoffset);

    tmp = ca*ny - sa*nz;
    nz = sa*ny + ca*nz;
    ny = tmp;
  }
  glEnd();

  ny=1; nz=0;	
  glBegin (GL_TRIANGLE_FAN);
  glNormal3d (0,0,-1);
  glVertex3d (0,0,-l+zoffset);
  for (i=0; i<=n; i++) {
    glNormal3d (0,0,-1);
    glVertex3d (ny*r,nz*r,-l+zoffset);
    tmp = ca*ny + sa*nz;
    nz = -sa*ny + ca*nz;
    ny = tmp;
  }
  glEnd();
}

void dsDrawCylinder (const float pos[3], const float R[12],
				float length, float radius)
{
  setupDrawingMode();
  glShadeModel (GL_SMOOTH);
  setTransform (pos,R);
  drawCylinder (length,radius,0);
  glPopMatrix();


}

static int capped_cylinder_quality = 3;

static void drawCapsule (float l, float r)
{
  int i,j;
  float tmp,nx,ny,nz,start_nx,start_ny,a,ca,sa;
  const int n = capped_cylinder_quality*4;

  l *= 0.5;
  a = float(M_PI*2.0)/float(n);
  sa = (float) sin(a);
  ca = (float) cos(a);

  ny=1; nz=0;
  glBegin (GL_TRIANGLE_STRIP);
  for (i=0; i<=n; i++) {
    glNormal3d (ny,nz,0);
    glVertex3d (ny*r,nz*r,l);
    glNormal3d (ny,nz,0);
    glVertex3d (ny*r,nz*r,-l);
    tmp = ca*ny - sa*nz;
    nz = sa*ny + ca*nz;
    ny = tmp;
  }
  glEnd();

  start_nx = 0;
  start_ny = 1;
  for (j=0; j<(n/4); j++) {
    float start_nx2 =  ca*start_nx + sa*start_ny;
    float start_ny2 = -sa*start_nx + ca*start_ny;
    nx = start_nx; ny = start_ny; nz = 0;
    float nx2 = start_nx2, ny2 = start_ny2, nz2 = 0;
    glBegin (GL_TRIANGLE_STRIP);
    for (i=0; i<=n; i++) {
      glNormal3d (ny2,nz2,nx2);
      glVertex3d (ny2*r,nz2*r,l+nx2*r);
      glNormal3d (ny,nz,nx);
      glVertex3d (ny*r,nz*r,l+nx*r);
      tmp = ca*ny - sa*nz;
      nz = sa*ny + ca*nz;
      ny = tmp;
      tmp = ca*ny2- sa*nz2;
      nz2 = sa*ny2 + ca*nz2;
      ny2 = tmp;
    }
    glEnd();
    start_nx = start_nx2;
    start_ny = start_ny2;
  }

  start_nx = 0;
  start_ny = 1;
  for (j=0; j<(n/4); j++) {

    float start_nx2 = ca*start_nx - sa*start_ny;
    float start_ny2 = sa*start_nx + ca*start_ny;

    nx = start_nx; ny = start_ny; nz = 0;
    float nx2 = start_nx2, ny2 = start_ny2, nz2 = 0;
    glBegin (GL_TRIANGLE_STRIP);
    for (i=0; i<=n; i++) {
      glNormal3d (ny,nz,nx);
      glVertex3d (ny*r,nz*r,-l+nx*r);
      glNormal3d (ny2,nz2,nx2);
      glVertex3d (ny2*r,nz2*r,-l+nx2*r);

      tmp = ca*ny - sa*nz;
      nz = sa*ny + ca*nz;
      ny = tmp;
      tmp = ca*ny2- sa*nz2;
      nz2 = sa*ny2 + ca*nz2;
      ny2 = tmp;
    }
    glEnd();
    start_nx = start_nx2;
    start_ny = start_ny2;
  }

  glPopMatrix();
}

void dsDrawCapsule (const float pos[3], const float R[12],
				      float length, float radius)
{
  setupDrawingMode();
  glShadeModel (GL_SMOOTH);
  setTransform (pos,R);
  drawCapsule (length,radius);
  glPopMatrix();

}

void dsDrawArrow (const float pos[3], int axis,
				float length, float radius)
{
	glPushMatrix();
	if(axis == 0)glRotatef( 90, 0.0, 1.0, 0.0 );
	if(axis == 1)glRotatef( -90, 1.0, 0.0, 0.0 );
	glTranslatef( 0.0, 0.0, length/2 );

	const float R[12] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
	const float POS[3] = {pos[0], pos[1], pos[2] - length/3*2};
			dsDrawCylinder(POS,R,length/3*4,radius);
	const float POS2[3] = {pos[0], pos[1], pos[2] + length/3};
			dsDrawCone(POS2,R,length/3*2,radius*2);
	
	glPopMatrix();


}





void dot3X3(float *T3, float *T1, float *T2)
{

	T3[0] = T1[0]*T2[0]+T1[1]*T2[4]+T1[2]*T2[8];
	T3[1] = T1[0]*T2[1]+T1[1]*T2[5]+T1[2]*T2[9];
	T3[2] = T1[0]*T2[2]+T1[1]*T2[6]+T1[2]*T2[10];
	T3[3] = T1[0]*T2[3]+T1[1]*T2[7]+T1[2]*T2[11]+T1[3];
	T3[4] = T1[4]*T2[0]+T1[5]*T2[4]+T1[6]*T2[8];
	T3[5] = T1[4]*T2[1]+T1[5]*T2[5]+T1[6]*T2[9];
	T3[6] = T1[4]*T2[2]+T1[5]*T2[6]+T1[6]*T2[10];
	T3[7] = T1[4]*T2[3]+T1[5]*T2[7]+T1[6]*T2[11]+T1[7];
	T3[8] = T1[8]*T2[0]+T1[9]*T2[4]+T1[10]*T2[8];
	T3[9] = T1[8]*T2[1]+T1[9]*T2[5]+T1[10]*T2[9];
	T3[10] = T1[8]*T2[2]+T1[9]*T2[6]+T1[10]*T2[10];
	T3[11] = T1[8]*T2[3]+T1[9]*T2[7]+T1[10]*T2[11]+T1[11];



}

void Return3X3(float *T4, float *T3)
{
	

	T4[0]=T3[0];
	T4[4]=T3[1];
	T4[8]=T3[2];
	T4[3]=0;
	T4[1]=T3[4];
	T4[5]=T3[5];
	T4[9]=T3[6];
	T4[7]=0;
	T4[2]=T3[8];
	T4[6]=T3[9];
	T4[10]=T3[10];
	T4[11]=0;

}

void RotX(float *T3, float rad, float *T1)
{
	float T2[12] = {1.0, 0.0, 0.0, 0.0, 
					0.0, cos(rad), -sin(rad), 0.0,
					0.0, sin(rad), cos(rad), 0.0};


	float  T5[12];
	dot3X3(T5, T2, T1);

	for(int i=0;i < 12;i++)T3[i] = T5[i];


}

void RotY(float *T3, float rad, float *T1)
{
	float T2[12] = {cos(rad), 0.0, sin(rad), 0.0,
					0.0, 1.0, 0.0, 0.0,
					-sin(rad), 0.0, cos(rad), 0.0};


	float  T5[12];
	dot3X3(T5, T2, T1);

	for(int i=0;i < 12;i++)T3[i] = T5[i];


}

void RotZ(float *T3, float rad, float *T1)
{
	float T2[12] = {cos(rad), -sin(rad), 0.0, 0.0,
					sin(rad), cos(rad), 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0};

	float  T5[12];
	dot3X3(T5, T2, T1);

	for(int i=0;i < 12;i++)T3[i] = T5[i];


}

void Silde(float *T3, float x, float y, float z, float *T1)
{

	for(int i=0;i<12;i++)T3[i] = T1[i];
	T3[3] += x;
	T3[7] += y;
	T3[11] += z;




}

void RotT(float *R4, float roll, float pitch, float yaw, float *R)
{
	float RKK[12];
	float RKKK[12];
	float R2[12];
	float R3[12];

	RotX(R2,roll, R);
	for(int i=0;i<12;i++)RKK[i] = R2[i];
	RotY(R3,pitch, RKK);
	for(int i=0;i<12;i++)RKKK[i] = R3[i];
	RotZ(R4,yaw, RKKK);



}


void RotTSL(float *R6, float roll, float pitch, float yaw, float x, float y, float z, float *R)
{
	
	float R2[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	float R3[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	float R4[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	float R5[12]={0,0,0,0,0,0,0,0,0,0,0,0};

	Silde(R2,x,y,z,R);
	RotX(R3,roll, R2);
	RotY(R4,pitch, R3);
	RotZ(R5,yaw, R4);

	for(int i=0;i < 12;i++)R6[i] = R5[i];



}

void dsDrawArrow2 (const float pos[3], const float R[12],
				float length, float radius)
{
	if(length >= 0){
	const float POS[3] = {pos[0], pos[1], pos[2]};
			setTransform (POS,R);
			const float sides[3] = {0.2, 0.2, 0.2};
			const float RTE[12] = {1,0,0,0,0,1,0,0,0,0,1,0};
			const float pos1[3] = {0,0,length/2};
			dsDrawCylinder(pos1,RTE,length,radius);
			glPopMatrix();

			const float pos2[3] = {0,0,length*7/6};
			setTransform (POS,R);
			dsDrawCone(pos2,RTE,length/3,radius*2);
			glPopMatrix();
	}
	else{
		const float POS[3] = {pos[0], pos[1], pos[2]};
			setTransform (POS,R);
			const float sides[3] = {0.2, 0.2, 0.2};
			const float RTE[12] = {1,0,0,0,0,1,0,0,0,0,1,0};
			const float pos1[3] = {0,0,length/2};
			dsDrawCylinder(pos1,RTE,-length,radius);
			glPopMatrix();
			const float pos2[3] = {0,0,length*7/6};
			setTransform (POS,R);
			const float RTE2[12] = {-1,0,0,0,0,1,0,0,0,0,-1,0};
			dsDrawCone(pos2,RTE2,-length/3,radius*2);
			glPopMatrix();


	}


		

			



}

void dsDrawArrow3 (const float pos[3], const float R[12],
				float length, float radius)
{
	const float POS[3] = {pos[0], pos[1], pos[2]};
			setTransform (POS,R);
			const float sides[3] = {0.2, 0.2, 0.2};
			const float RTE[12] = {1,0,0,0,0,1,0,0,0,0,1,0};
			const float pos1[3] = {0,0,length/2};
			dsDrawCylinder(pos1,RTE,length,radius);
			glPopMatrix();
			const float pos2[3] = {0,0,length*7/6};
			setTransform (POS,R);
			dsDrawCone(pos2,RTE,length/3,radius*2);
			glPopMatrix();

	


}

GLBox::~GLBox()
{
	for(int i=0;i<6;i++)testANGLE[i] = 0.0;
    makeCurrent();
    glDeleteLists( object, 1 );
	MoveFlag = true;
	
}





void GLBox::paintGL()
{
	
	glClearColor (0.9,0.75,1.0,0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();



	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	GLfloat fovy = 30.0f; 

	gluPerspective(fovy,(GLfloat)width()/height(),0.1,1000.0);

	glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
 



	GLdouble GLZ = 10.0 * cos(xRot * 3.141592 / 180) - 5.0 * sin(xRot * 3.141592 / 180);
    GLdouble GLY = 10.0 * sin(xRot * 3.141592 / 180) + 5.0 * cos(xRot * 3.141592 / 180);
    GLdouble GLX = -GLZ * sin(yRot * 3.141592 / 180) + 5.0 * cos(yRot * 3.141592 / 180);
    GLdouble GLZ2 = GLZ * cos(yRot * 3.141592 / 180) + 5.0 * sin(yRot * 3.141592 / 180);

    GLfloat light_position[] = { GLX, GLY, GLZ2, 0.0 };
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	


	float Arrowlength = 0.6;
	float Arrowradius = 0.05;
	float ArrowPosX = -1.8;
	float ArrowPosY = -1.8;


	glTranslatef( xWe, yWe, -10.0*scale );

	


    glRotatef( xRot, 1.0, 0.0, 0.0 ); 
    glRotatef( yRot, 0.0, 1.0, 0.0 ); 
    glRotatef( zRot, 0.0, 0.0, 1.0 );



	




	

	float R3[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	float R4[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	

	for(int i=0;i<m_Sensor.size();i++)
	{


			float R5[12] = {1,0,0,0,
					0,1,0,0,
					0,0,1,0};
			if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
		color[3] = 0.8;
		color[0] = 0.0;
		color[1] = 0.0;
		color[2] = 0.0;
			}
		

		{
			

			float RX[12] = { 1, 0, 0, -m_Sensor[i]->m_body->m_param.m_px + m_Sensor[i]->m_param.m_px, 0, 1, 0, -m_Sensor[i]->m_body->m_param.m_py + m_Sensor[i]->m_param.m_py, 0, 0, 1, -m_Sensor[i]->m_body->m_param.m_pz + m_Sensor[i]->m_param.m_pz };

			if(!MoveFlag && CHECK){
			float RTEMP[12]={0,0,0,0,0,0,0,0,0,0,0,0};
			dot3X3(RTEMP, m_Sensor[i]->m_body->ROT,RX);
			
			for(int z=0;z<12;z++)R5[z] = RTEMP[z];

			
		}

		

		const float POSR[3] = {R5[3], R5[7], R5[11]};

		float RTW[12] = {1,0,0,0,0,1,0,0,0,0,1,0};

		if (m_Sensor[i]->m_param.m_slx>0 && m_Sensor[i]->m_param.m_slz == 0.0 && m_Sensor[i]->m_param.m_sly == 0.0)RotTSL(R4, 0.0, 1.57, 0.0, 0, 0, 0, RTW);
		else if (m_Sensor[i]->m_param.m_slx <= 0 && m_Sensor[i]->m_param.m_slz == 0.0 && m_Sensor[i]->m_param.m_sly == 0.0)RotTSL(R4, 0.0, -1.57, 0.0, 0, 0, 0, RTW);
		else if (m_Sensor[i]->m_param.m_sly>0 && m_Sensor[i]->m_param.m_slz == 0.0 && m_Sensor[i]->m_param.m_slx == 0.0)RotTSL(R4, -1.57, 0.0, 0.0, 0, 0, 0, RTW);
		else if (m_Sensor[i]->m_param.m_sly <= 0 && m_Sensor[i]->m_param.m_slz == 0.0 && m_Sensor[i]->m_param.m_slx == 0.0)RotTSL(R4, 1.57, 0.0, 0.0, 0, 0, 0, RTW);
		else if (m_Sensor[i]->m_param.m_slz>0 && m_Sensor[i]->m_param.m_slx == 0.0 && m_Sensor[i]->m_param.m_sly == 0.0)RotTSL(R4, 0.0, 0.0, 0.0, 0, 0, 0, RTW);
		else if (m_Sensor[i]->m_param.m_slz <= 0 && m_Sensor[i]->m_param.m_slx == 0.0 && m_Sensor[i]->m_param.m_sly == 0.0)RotTSL(R4, 3.14, 0.0, 0.0, 0, 0, 0, RTW);

		else if (m_Sensor[i]->m_param.m_slx != 0.0){
			float TEMPX = m_Sensor[i]->m_param.m_slx;
			float TEMPY = m_Sensor[i]->m_param.m_sly;
			float TEMPZ = m_Sensor[i]->m_param.m_slz;
				float TEMPXY = sqrt(TEMPZ * TEMPZ + TEMPY * TEMPY);
				float TEMPRZ = atan2(TEMPY, TEMPZ);
				float TEMPRY = atan2(-TEMPX, TEMPXY);

				RotTSL(R4,TEMPRZ, TEMPRY, 0.0, 0,0,0,RTW);
			}
		else if (m_Sensor[i]->m_param.m_sly != 0.0)
			{
				float TEMPY = m_Sensor[i]->m_param.m_sly;
				float TEMPZ = m_Sensor[i]->m_param.m_slz;
				float TEMPRX = atan2(TEMPY, TEMPZ);
				RotTSL(R4,-TEMPRX, 0.0, 0.0, 0,0,0,RTW);
			}
			float RTW3[12]={0,0,0,0,0,0,0,0,0,0,0,0};

			

			

			dot3X3(RTW3, R5, R4);
			
			

			
		const float Rpp[12] = {R5[0],R5[1],R5[2],R5[3],R5[4],R5[5],R5[6],R5[7],R5[8],R5[9],R5[10],R5[11]};
		for(int z=0;z<12;z++)R5[z] = RTW3[z];
		
		
			
			


		Return3X3(R3,R5);

		const float R[12] = {R3[0],R3[1],R3[2],R3[3],R3[4],R3[5],R3[6],R3[7],R3[8],R3[9],R3[10],R3[11]};

		

		m_Sensor[i]->update();

		if(!MoveFlag && CHECK){
		if(m_Sensor[i]->m_param.m_type == Force){


			dsDrawCylinder(POSR,R,0.01*SScale,0.01*SScale);
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 1.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			dsDrawCylinder(POSR,R,0.011*SScale,0.008*SScale);
			//const float POS[3] = {POSR[0], POSR[1], POSR[2]};
			//setTransform (POS,R);
			color[3] = 0.8;
			color[0] = 1.0;
			color[1] = 0.0;
			color[2] = 0.0;

			float RGY[12] = {Rpp[0],Rpp[1],Rpp[2],Rpp[3],Rpp[4],Rpp[5],Rpp[6],Rpp[7],Rpp[8],Rpp[9],Rpp[10],Rpp[11]};
			float RGY4[12]={0,0,0,0,0,0,0,0,0,0,0,0};

		
			float R6[12];

			Return3X3(R6,RGY);

			std::vector<float> v = m_Sensor[i]->value;
			if (v.size() >= 3)
			{
				dsDrawArrow3(POSR, R6, v[0] * FScale, 0.05*FScale);
				RotTSL(RGY4, -1.57, 0.0, 0.0, 0, 0, 0, RGY);
				Return3X3(R6, RGY4);
				dsDrawArrow3(POSR, R6, v[1] * FScale, 0.05*FScale);
				RotTSL(RGY4, 0.0, 1.57, 0.0, 0, 0, 0, RGY);
				Return3X3(R6, RGY4);
				dsDrawArrow3(POSR, R6, v[2] * FScale, 0.05*FScale);

			}
			
		}
		if(m_Sensor[i]->m_param.m_type == Torque){


			dsDrawCylinder(POSR,R,0.01*SScale,0.01*SScale);
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 0.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			dsDrawCylinder(POSR,R,0.011*SScale,0.008*SScale);
			//const float POS[3] = {POSR[0], POSR[1], POSR[2]};
			//setTransform (POS,R);

			float RGY[12] = {Rpp[0],Rpp[1],Rpp[2],Rpp[3],Rpp[4],Rpp[5],Rpp[6],Rpp[7],Rpp[8],Rpp[9],Rpp[10],Rpp[11]};
			float RGY4[12]={0,0,0,0,0,0,0,0,0,0,0,0};

			color[3] = 0.8;
			color[0] = 1.0;
			color[1] = 0.0;
			color[2] = 0.0;
			
		
			float R6[12];

			Return3X3(R6,RGY);

			std::vector<float> v = m_Sensor[i]->value;
			if (v.size() >= 3)
			{
				dsDrawArrow3(POSR, R6, v[0] * FScale, 0.05*FScale);
				RotTSL(RGY4, -1.57, 0.0, 0.0, 0, 0, 0, RGY);
				Return3X3(R6, RGY4);
				dsDrawArrow3(POSR, R6, v[1] * FScale, 0.05*FScale);
				RotTSL(RGY4, 0.0, 1.57, 0.0, 0, 0, 0, RGY);
				Return3X3(R6, RGY4);
				dsDrawArrow3(POSR, R6, v[2] * FScale, 0.05*FScale);

			}

		}
		else if(m_Sensor[i]->m_param.m_type == Gyro){


			const float sides[3] = {0.02*SScale, 0.02*SScale, 0.02*SScale};
			dsDrawBox(POSR,R,sides);
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 1.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			const float sides2[3] = {0.019*SScale, 0.019*SScale, 0.021*SScale};
			dsDrawBox(POSR,R,sides2);

			float RGY[12] = {1,0,0,0,0,1,0,0,0,0,1,0};
			float RGY4[12]={0,0,0,0,0,0,0,0,0,0,0,0};

			
			
			

		
			color[3] = 0.8;
			color[0] = 1.0;
			color[1] = 1.0;
			color[2] = 0.0;
			float R6[12];

			Return3X3(R6,RGY);

			std::vector<float> v = m_Sensor[i]->value;
			if (v.size() >= 3)
			{
				dsDrawArrow3(POSR, R6, v[0] * FScale, 0.05*FScale);
				RotTSL(RGY4, -1.57, 0.0, 0.0, 0, 0, 0, RGY);
				Return3X3(R6, RGY4);
				dsDrawArrow3(POSR, R6, v[1] * FScale, 0.05*FScale);
				RotTSL(RGY4, 0.0, 1.57, 0.0, 0, 0, 0, RGY);
				Return3X3(R6, RGY4);
				dsDrawArrow3(POSR, R6, v[2] * FScale, 0.05*FScale);

			}
			

		}
		else if(m_Sensor[i]->m_param.m_type == Range){ 

			const float POS[3] = {POSR[0], POSR[1], POSR[2]};

			setTransform (POS,R);
			const float sides[3] = {0.02*SScale, 0.02*SScale, 0.02*SScale};
			const float RTE[12] = {1,0,0,0,0,1,0,0,0,0,1,0};
			const float pos1[3] = {0,0,0};
			dsDrawBox(pos1,RTE,sides);
			glPopMatrix();
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 1.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			const float pos2[3] = {0,0,0.01*SScale};
			//setTransform (POS,R);
			dsDrawCylinder(pos2,RTE,0.01*SScale,0.005*SScale);
			glPopMatrix();
			color[3] = 0.8;
			color[0] = 0.0;
			color[1] = 0.0;
			color[2] = 1.0;
			
			std::vector<float> v = m_Sensor[i]->value;
			if (v.size() >= 1)
			{
				
				dsDrawArrow2(POSR, R, v[0], 0.05*RScale);
			}
			

		}
		else if(m_Sensor[i]->m_param.m_type == Acceleration){ 
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 0.0;
				color[1] = 0.0;
				color[2] = 1.0;
			}
			const float sides[3] = {0.02*SScale, 0.02*SScale, 0.02*SScale};
			dsDrawBox(POSR,R,sides);
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 1.0;
				color[1] = 0.0;
				color[2] = 0.0;
			}
			const float sides2[3] = {0.019*SScale, 0.019*SScale, 0.0205*SScale};
			dsDrawBox(POSR,R,sides2);

			float RGY[12] = {1,0,0,0,0,1,0,0,0,0,1,0};
			float RGY4[12]={0,0,0,0,0,0,0,0,0,0,0,0};

			

			
			

			color[3] = 0.8;
			color[0] = 0.0;
			color[1] = 1.0;
			color[2] = 1.0;

			float R6[12];

			Return3X3(R6,RGY);

			std::vector<float> v = m_Sensor[i]->value;
			if (v.size() >= 3)
			{
				dsDrawArrow3(POSR, R6, v[0] * FScale, 0.05*FScale);
				RotTSL(RGY4, -1.57, 0.0, 0.0, 0, 0, 0, RGY);
				Return3X3(R6, RGY4);
				dsDrawArrow3(POSR, R6, v[1] * FScale, 0.05*FScale);
				RotTSL(RGY4, 0.0, 1.57, 0.0, 0, 0, 0, RGY);
				Return3X3(R6, RGY4);
				dsDrawArrow3(POSR, R6, v[2] * FScale, 0.05*FScale);

			}
		
		}

		}

		else{

			//std::cout << m_Sensor[i]->m_param.m_type << std::endl;
			if(m_Sensor[i]->m_param.m_type == Force){
				//std::cout << m_Sensor[i]->m_param.m_px << "\t" << m_Sensor[i]->m_param.m_py << "\t" << m_Sensor[i]->m_param.m_pz << std::endl;
			const float POS[3] = {m_Sensor[i]->m_param.m_px, m_Sensor[i]->m_param.m_py, m_Sensor[i]->m_param.m_pz};
			dsDrawCylinder(POS,R,0.01*SScale,0.01*SScale);
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 1.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			dsDrawCylinder(POS,R,0.011*SScale,0.008*SScale);

		}
		if(m_Sensor[i]->m_param.m_type == Torque){

			const float POS[3] = {m_Sensor[i]->m_param.m_px, m_Sensor[i]->m_param.m_py, m_Sensor[i]->m_param.m_pz};
			dsDrawCylinder(POS,R,0.01*SScale,0.01*SScale);
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 0.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			dsDrawCylinder(POS,R,0.011*SScale,0.008*SScale);

		}
		else if(m_Sensor[i]->m_param.m_type == Gyro){

			const float POS[3] = {m_Sensor[i]->m_param.m_px, m_Sensor[i]->m_param.m_py, m_Sensor[i]->m_param.m_pz};
			const float sides[3] = {0.02*SScale, 0.02*SScale, 0.02*SScale};
			dsDrawBox(POS,R,sides);
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 1.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			const float sides2[3] = {0.019*SScale, 0.019*SScale, 0.021*SScale};
			dsDrawBox(POS,R,sides2);


		}
		else if(m_Sensor[i]->m_param.m_type == Range){ 
			

			const float POS[3] = {m_Sensor[i]->m_param.m_px, m_Sensor[i]->m_param.m_py, m_Sensor[i]->m_param.m_pz};
			setTransform (POS,R);
			const float sides[3] = {0.02*SScale, 0.02*SScale, 0.02*SScale};
			const float RTE[12] = {1,0,0,0,0,1,0,0,0,0,1,0};
			const float pos1[3] = {0,0,0};
			dsDrawBox(pos1,RTE,sides);
			glPopMatrix();
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 1.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			const float pos2[3] = {0,0,0.01*SScale};
			setTransform (POS,R);
			dsDrawCylinder(pos2,RTE,0.01*SScale,0.005*SScale);
			glPopMatrix();

		}
		else if(m_Sensor[i]->m_param.m_type == Acceleration){ 
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 0.0;
				color[1] = 0.0;
				color[2] = 1.0;
			}
			const float POS[3] = {m_Sensor[i]->m_param.m_px, m_Sensor[i]->m_param.m_py, m_Sensor[i]->m_param.m_pz};
			const float sides[3] = {0.02*SScale, 0.02*SScale, 0.02*SScale};
			dsDrawBox(POS,R,sides);
						if(i == SSNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 1.0;
				color[1] = 0.0;
				color[2] = 0.0;
			}
			const float sides2[3] = {0.019*SScale, 0.019*SScale, 0.0205*SScale};
			dsDrawBox(POS,R,sides2);

		
		}
		}
	}
	}

	for(int i=0;i<m_Vision.size();i++)
	{
			float RX2;
			float RY;
			float RZ;

			float R5[12] = {1,0,0,0,
					0,1,0,0,
					0,0,1,0};
			if(i == CCNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
		color[3] = 0.8;
		color[0] = 0.0;
		color[1] = 0.0;
		color[2] = 0.0;
			}
			
		{
			float RX[12] = {1,0,0,-m_Vision[i]->m_joint1->m_param.m_px + m_Vision[i]->m_param.m_px,0,1,0,-m_Vision[i]->m_joint1->m_param.m_py + m_Vision[i]->m_param.m_py,0,0,1,-m_Vision[i]->m_joint1->m_param.m_pz + m_Vision[i]->m_param.m_pz};
		if(!MoveFlag && CHECK){
			float RTEMP[12]={0,0,0,0,0,0,0,0,0,0,0,0};
			float RTEMP2[12]={0,0,0,0,0,0,0,0,0,0,0,0};
			
			if(m_Vision[i]->m_joint1->m_param.m_axisy == 0.0
				 && m_Vision[i]->m_joint1->m_param.m_axisz == 0.0)
			{
				RX2 = m_Vision[i]->m_joint1->angle;
				RY = 0.0;
				RZ = 0.0;
			}
			else if(m_Vision[i]->m_joint1->m_param.m_axisx == 0.0
				 && m_Vision[i]->m_joint1->m_param.m_axisz == 0.0)
			{
				RX2 = 0.0;
				RY = m_Vision[i]->m_joint1->angle;
				RZ = 0.0;
			}
			else if(m_Vision[i]->m_joint1->m_param.m_axisy == 0.0
				 && m_Vision[i]->m_joint1->m_param.m_axisx == 0.0)
			{
				RX2 = 0.0;
				RY = 0.0;
				RZ = m_Vision[i]->m_joint1->angle;
			}
			else if(m_Vision[i]->m_joint1->m_param.m_axisx != 0)
			{
				float TEMPX = m_Vision[i]->m_joint1->m_param.m_axisx;
				float TEMPY = m_Vision[i]->m_joint1->m_param.m_axisy;
				float TEMPZ = m_Vision[i]->m_joint1->m_param.m_axisz;
				float TEMPXY = sqrt(TEMPX*TEMPX + TEMPY*TEMPY);
				RZ = atan2(m_Vision[i]->m_joint1->m_param.m_axisx, m_Vision[i]->m_joint1->m_param.m_axisy);
				RY = atan2(TEMPZ,TEMPXY);
				RX2 = m_Vision[i]->m_joint1->angle;

			}
			
			else if(m_Vision[i]->m_joint1->m_param.m_axisy != 0)
			{
				RX2 = atan2(m_Vision[i]->m_joint1->m_param.m_axisy, m_Vision[i]->m_joint1->m_param.m_axisz);
				RY = m_Vision[i]->m_joint1->angle;

			}

			
			if(m_Vision[i]->m_joint1->m_param.m_type == Hinge)
				{
					if((m_Vision[i]->m_joint1->m_param.m_axisy == 0.0
						&& m_Vision[i]->m_joint1->m_param.m_axisz == 0.0)
						|| (m_Vision[i]->m_joint1->m_param.m_axisx == 0.0
						 && m_Vision[i]->m_joint1->m_param.m_axisz == 0.0)
						|| (m_Vision[i]->m_joint1->m_param.m_axisy == 0.0
						&& m_Vision[i]->m_joint1->m_param.m_axisx == 0.0)){

								RotTSL(RTEMP2,RX2,RY,RZ,0,0,0,RX);
								for(int d = 0;d<12;d++)RX[d] = RTEMP2[d];
					
						}
					else if(m_Vision[i]->m_joint1->m_param.m_axisx != 0)
					{
								float LN[12]={0,0,0,0,0,0,0,0,0,0,0,0};
								float GN[12]={0,0,0,0,0,0,0,0,0,0,0,0};
								float AN[12]={0,0,0,0,0,0,0,0,0,0,0,0};
								float BN[12]={0,0,0,0,0,0,0,0,0,0,0,0};

								RotTSL(GN,0.0,0.0,-RZ,0,0,0,RX);
								for(int d = 0;d<12;d++)RX[d] = GN[d];
								RotTSL(LN,0.0,RY,0.0,0,0,0,RX);
								for(int d = 0;d<12;d++)RX[d] = LN[d];
								RotTSL(RTEMP2,RX2,-RY,RZ,0,0,0,RX);
								for(int d = 0;d<12;d++)RX[d] = RTEMP2[d];
								

					}
					else if(m_Vision[i]->m_joint1->m_param.m_axisy != 0)
					{
								float LN[12]={0,0,0,0,0,0,0,0,0,0,0,0};
								float GN[12]={0,0,0,0,0,0,0,0,0,0,0,0};
								float AN[12]={0,0,0,0,0,0,0,0,0,0,0,0};
								float BN[12]={0,0,0,0,0,0,0,0,0,0,0,0};

								RotTSL(GN,RX2,0.0,0.0,0,0,0,RX);
								for(int d = 0;d<12;d++)RX[d] = GN[d];
								RotTSL(LN,0.0,RY,0.0,0,0,0,RX);
								for(int d = 0;d<12;d++)RX[d] = LN[d];
								RotTSL(RTEMP2,-RX2,0.0,0.0,0,0,0,RX);
								for(int d = 0;d<12;d++)RX[d] = RTEMP2[d];
								
					


					}

				}
				else if(m_Vision[i]->m_joint1->m_param.m_type == Slider)
				{
					float ANGLTTEMP = m_Vision[i]->m_joint1->angle;
					float axisxt = m_Vision[i]->m_joint1->m_param.m_axisx;
					float axisyt = m_Vision[i]->m_joint1->m_param.m_axisy;
					float axiszt = m_Vision[i]->m_joint1->m_param.m_axisz;
					float ALP = sqrt(axisxt*axisxt + axisyt*axisyt + axiszt * axiszt);
					RX2 = ANGLTTEMP * axisxt / ALP;
					RY = ANGLTTEMP * axisyt / ALP;
					RZ = ANGLTTEMP * axiszt / ALP;
					RotTSL(RTEMP2,0,0,0,RX2,RY,RZ,RX);
					for(int d = 0;d<12;d++)RX[d] = RTEMP2[d];
					
					

				}
			dot3X3(RTEMP, m_Vision[i]->m_joint1->ROT,RX);
			for(int z=0;z<12;z++)R5[z] = RTEMP[z];
			
		}
		

		const float POSR[3] = {R5[3], R5[7], R5[11]};
		float RTW[12] = {1,0,0,0,0,1,0,0,0,0,1,0};

			if(m_Vision[i]->m_param.m_slz == 0.0 && m_Vision[i]->m_param.m_sly == 0.0)RotTSL(R4,0.0, 1.57, 0.0, 0,0,0,RTW);
			else if(m_Vision[i]->m_param.m_slz == 0.0 && m_Vision[i]->m_param.m_slx == 0.0)RotTSL(R4,1.57, 0.0, 0.0, 0,0,0,RTW);
			else if(m_Vision[i]->m_param.m_slx == 0.0 && m_Vision[i]->m_param.m_sly == 0.0)RotTSL(R4,0.0, 0.0, 0.0, 0,0,0,RTW);
			else if(m_Vision[i]->m_param.m_slx != 0.0){
				float TEMPX = m_Vision[i]->m_param.m_slx;
				float TEMPY = m_Vision[i]->m_param.m_sly;
				float TEMPZ = m_Vision[i]->m_param.m_slz;
				float TEMPXY = sqrt(TEMPZ * TEMPZ + TEMPY * TEMPY);
				float TEMPRZ = atan2(TEMPY, TEMPZ);
				float TEMPRY = atan2(-TEMPX, TEMPXY);

				RotTSL(R4,TEMPRZ, TEMPRY, 0.0, 0,0,0,RTW);
			}
			else if(m_Vision[i]->m_param.m_sly != 0.0)
			{
				float TEMPY = m_Vision[i]->m_param.m_sly;
				float TEMPZ = m_Vision[i]->m_param.m_slz;
				float TEMPRX = atan2(TEMPY, TEMPZ);
				RotTSL(R4,TEMPRX, 0.0, 0.0, 0,0,0,RTW);
			}

			float RKKK[12]={0,0,0,0,0,0,0,0,0,0,0,0};
			for(int z=0;z<12;z++)RKKK[z] = R4[z];

			float RTF[12]={0,0,0,0,0,0,0,0,0,0,0,0};


			dot3X3(RTF, R5, R4);

		for(int z=0;z<12;z++)R5[z] = RTF[z];
		
		

		Return3X3(R3,R5);

		const float R[12] = {R3[0],R3[1],R3[2],R3[3],R3[4],R3[5],R3[6],R3[7],R3[8],R3[9],R3[10],R3[11]};



		if(!MoveFlag && CHECK){
		if(m_Vision[i]->m_param.m_type == Camera){

			
				const float POS[3] = {POSR[0], POSR[1], POSR[2]};
			
			setTransform (POS,R);
			const float sides[3] = {0.02*SScale, 0.02*SScale, 0.02*SScale};
			const float RTE[12] = {1,0,0,0,0,1,0,0,0,0,1,0};
			const float pos1[3] = {0,0,0};
			dsDrawBox(pos1,RTE,sides);
			glPopMatrix();
						if(i == CCNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 1.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			const float pos2[3] = {0,0,0.01*SScale};
			setTransform (POS,R);
			dsDrawCylinder(pos2,RTE,0.01*SScale,0.005*SScale);
			glPopMatrix();
			

		}


		}

		else{


		if(m_Vision[i]->m_param.m_type == Camera){

			

			const float POS[3] = {m_Vision[i]->m_param.m_px, m_Vision[i]->m_param.m_py, m_Vision[i]->m_param.m_pz};
			setTransform (POS,R);
			const float sides[3] = {0.02*SScale, 0.02*SScale, 0.02*SScale};
			const float RTE[12] = {1,0,0,0,0,1,0,0,0,0,1,0};
			const float pos1[3] = {0,0,0};
			dsDrawBox(pos1,RTE,sides);
			glPopMatrix();
						if(i == CCNum){
				color[3] = 1.0;
				color[0] = 2.0;
				color[1] = 2.0;
				color[2] = 2.0;
			}
			else{
				color[3] = 0.8;
				color[0] = 1.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			const float pos2[3] = {0,0,0.01*SScale};
			setTransform (POS,R);
			dsDrawCylinder(pos2,RTE,0.01*SScale,0.005*SScale);
			glPopMatrix();


		}
		
		
		
		}
	}
	}


	for(int i=0;i<m_Joint.size();i++)
	{
		
			float R5[12] = {1,0,0,0,
					0,1,0,0,
					0,0,1,0};
		BodyOrJoint = false;
		if(i == RotNum){
		color[3] = 1.0;
		color[0] = 2.0;
		color[1] = 2.0;
		color[2] = 2.0;
		}
		else{
		color[3] = 1.0;
		color[0] = 0.0;
		color[1] = 0.0;
		color[2] = 0.0;
		}

		{
		if(!MoveFlag && CHECK){
			for(int z=0;z<12;z++)R5[z] = m_Joint[i]->ROT[z];
		}
		float RTW[12] = {1,0,0,0,0,1,0,0,0,0,1,0};

			if(m_Joint[i]->m_param.m_axisz == 0.0 && m_Joint[i]->m_param.m_axisy == 0.0)RotTSL(R4,0.0, -1.57, 0.0, 0,0,0,RTW);
			else if(m_Joint[i]->m_param.m_axisz == 0.0 && m_Joint[i]->m_param.m_axisx == 0.0)RotTSL(R4,-1.57, 0.0, 0.0, 0,0,0,RTW);
			else if(m_Joint[i]->m_param.m_axisx == 0.0 && m_Joint[i]->m_param.m_axisy == 0.0)RotTSL(R4,0.0, 0.0, 0.0, 0,0,0,RTW);
			else if(m_Joint[i]->m_param.m_axisx != 0.0){
				float TEMPX = m_Joint[i]->m_param.m_axisx;
				float TEMPY = m_Joint[i]->m_param.m_axisy;
				float TEMPZ = m_Joint[i]->m_param.m_axisz;
				float TEMPXY = sqrt(TEMPZ * TEMPZ + TEMPY * TEMPY);
				float TEMPRZ = atan2(TEMPY, TEMPZ);
				float TEMPRY = atan2(-TEMPX, TEMPXY);

				RotTSL(R4,TEMPRZ, TEMPRY, 0.0, 0,0,0,RTW);
			}
			else if(m_Joint[i]->m_param.m_axisy != 0.0)
			{
				float TEMPY = m_Joint[i]->m_param.m_axisy;
				float TEMPZ = m_Joint[i]->m_param.m_axisz;
				float TEMPRX = atan2(TEMPY, TEMPZ);
				RotTSL(R4,TEMPRX, 0.0, 0.0, 0,0,0,RTW);
			}

		float RTW3[12];

		dot3X3(RTW3, R5, R4);

		for(int z=0;z<12;z++)R5[z] = RTW3[z];
		
		if(!MoveFlag && CHECK){
			R5[3] = m_Joint[i]->ROT[3];
			R5[7] = m_Joint[i]->ROT[7];
			R5[11] = m_Joint[i]->ROT[11];

		}

		Return3X3(R3,R5);

		const float R[12] = {R3[0],R3[1],R3[2],R3[3],R3[4],R3[5],R3[6],R3[7],R3[8],R3[9],R3[10],R3[11]};
		if(!MoveFlag && CHECK){
		if(m_Joint[i]->m_param.m_type == Fix){
			const float POS[3] = {R5[3], R5[7], R5[11]};
			const float sides[3] = {0.01*JScale, 0.01*JScale, 0.01*JScale};
			dsDrawBox(POS,R,sides);

		}
		else if(m_Joint[i]->m_param.m_type == Hinge){
			
			const float POS[3] = {R5[3], R5[7], R5[11]};
			dsDrawCylinder(POS,R,0.03*JScale,0.001*JScale);
			dsDrawCylinder(POS,R,0.01*JScale,0.005*JScale);

		}
		else if(m_Joint[i]->m_param.m_type == Slider){

			float TEMP[3] = {0.0, 0.0, 0.0}; 
			float TEMPX = m_Joint[i]->m_param.m_axisx;
			float TEMPY = m_Joint[i]->m_param.m_axisy;
			float TEMPZ = m_Joint[i]->m_param.m_axisz;
			float TEMPXYZ = sqrt(TEMPX * TEMPX + TEMPY * TEMPY + TEMPZ * TEMPZ);
			TEMP[0] = 0.005 * TEMPX / TEMPXYZ*JScale;
			TEMP[1] = 0.005 * TEMPY / TEMPXYZ*JScale;
			TEMP[2] = 0.005 * TEMPZ / TEMPXYZ*JScale;
			const float POS[3] = {R5[3]-TEMP[0], R5[7]-TEMP[1], R5[11]-TEMP[2]};
			dsDrawCylinder(POS,R,0.01*JScale,0.01*JScale);
			const float POS2[3] = {R5[3]+TEMP[0], R5[7]+TEMP[1], R5[11]+TEMP[2]};
			dsDrawCylinder(POS2,R,0.01*JScale,0.005*JScale);

		}
		}
		else{
		if(m_Joint[i]->m_param.m_type == Fix){
			const float POS[3] = {m_Joint[i]->m_param.m_px, m_Joint[i]->m_param.m_py, m_Joint[i]->m_param.m_pz};
			const float sides[3] = {0.01*JScale, 0.01*JScale, 0.01*JScale};
			dsDrawBox(POS,R,sides);

		}
		else if(m_Joint[i]->m_param.m_type == Hinge){

			const float POS[3] = {m_Joint[i]->m_param.m_px, m_Joint[i]->m_param.m_py, m_Joint[i]->m_param.m_pz};
			//std::cout << POS[0] << "\t" << POS[1] << "\t" << POS[2] << std::endl;
			//std::cout << JScale << std::endl;
			dsDrawCylinder(POS,R,0.03*JScale,0.001*JScale);
			dsDrawCylinder(POS,R,0.01*JScale,0.005*JScale);

		}
		else if(m_Joint[i]->m_param.m_type == Slider){ 

			float TEMP[3] = {0.0, 0.0, 0.0}; 
			float TEMPX = m_Joint[i]->m_param.m_axisx;
			float TEMPY = m_Joint[i]->m_param.m_axisy;
			float TEMPZ = m_Joint[i]->m_param.m_axisz;
			float TEMPXYZ = sqrt(TEMPX * TEMPX + TEMPY * TEMPY + TEMPZ * TEMPZ);
			TEMP[0] = 0.005 * TEMPX / TEMPXYZ*JScale;
			TEMP[1] = 0.005 * TEMPY / TEMPXYZ*JScale;
			TEMP[2] = 0.005 * TEMPZ / TEMPXYZ*JScale;
			const float POS[3] = {m_Joint[i]->m_param.m_px-TEMP[0], m_Joint[i]->m_param.m_py-TEMP[1], m_Joint[i]->m_param.m_pz-TEMP[2]};
			dsDrawCylinder(POS,R,0.01*JScale,0.01*JScale);
			const float POS2[3] = {m_Joint[i]->m_param.m_px+TEMP[0], m_Joint[i]->m_param.m_py+TEMP[1], m_Joint[i]->m_param.m_pz+TEMP[2]};
			dsDrawCylinder(POS2,R,0.01*JScale,0.005*JScale);

		}
		}
		}
	}



	for(int i=0;i<m_Body.size();i++)
	{

				
				
		
				
			float R5[12] = {1,0,0,0,
					0,1,0,0,
					0,0,1,0};
		BodyOrJoint = true;
		if(i != GeoNum){
		color[3] = BCL;
		color[0] = m_Body[i]->m_param.m_red;
		color[2] = m_Body[i]->m_param.m_blue;
		color[1] = m_Body[i]->m_param.m_green;
		}
		else{
		color[3] = 1.0;
		color[0] = 2.0;
		color[2] = 2.0;
		color[1] = 2.0;
		}
		
		if(!MoveFlag && CHECK){
			for(int z=0;z<12;z++)R5[z] = m_Body[i]->ROT[z];
			float RTW[12] = {1,0,0,0,0,1,0,0,0,0,1,0};

			float RTW3[12];

			RotTSL(RTW3,m_Body[i]->m_param.m_slx, m_Body[i]->m_param.m_sly, m_Body[i]->m_param.m_slz, 0,0,0,RTW);
			float RXX[12];
			for(int z=0;z<12;z++)RXX[z] = RTW3[z];
			
			dot3X3(R4, R5, RXX);

		}
		else RotTSL(R4,m_Body[i]->m_param.m_slx, m_Body[i]->m_param.m_sly, m_Body[i]->m_param.m_slz, 0,0,0,R5);
		for(int z=0;z<12;z++)R5[z] = R4[z];
		if(!MoveFlag && CHECK){
			R5[3] = m_Body[i]->ROT[3];
			R5[7] = m_Body[i]->ROT[7];
			R5[11] = m_Body[i]->ROT[11];

		}
		Return3X3(R3,R5);

		const float R[12] = {R3[0],R3[1],R3[2],R3[3],R3[4],R3[5],R3[6],R3[7],R3[8],R3[9],R3[10],R3[11]};
		if(!MoveFlag && CHECK){
		if(m_Body[i]->m_param.m_type == Body_Box){
			const float POS[3] = {R5[3], R5[7], R5[11]};
			const float sides[3] = {m_Body[i]->m_param.m_length, m_Body[i]->m_param.m_width, m_Body[i]->m_param.m_height};
			dsDrawBox(POS,R,sides);

		}
		else if(m_Body[i]->m_param.m_type == Body_Sphere){

			const float POS[3] = {R5[3], R5[7], R5[11]};
			dsDrawSphere(POS,R,m_Body[i]->m_param.m_rad);
			

		}
		else if(m_Body[i]->m_param.m_type == Body_Cylinder){
			const float POS[3] = {R5[3], R5[7], R5[11]};
			dsDrawCylinder(POS,R,m_Body[i]->m_param.m_length,m_Body[i]->m_param.m_rad);

		}
		else if(m_Body[i]->m_param.m_type == Body_Cone){
			const float POS[3] = {R5[3], R5[7], R5[11]};
			dsDrawCone(POS,R,m_Body[i]->m_param.m_length,m_Body[i]->m_param.m_rad);

		}
		else if(m_Body[i]->m_param.m_type == Body_Polygon){

			const float POS[3] = {R5[3], R5[7], R5[11]};
			if(i != GeoNum)
				DrawPolygon(m_Body[i]->m_param.m_pd,POS,R,false);
			else
				DrawPolygon(m_Body[i]->m_param.m_pd,POS,R,true);

		}
		}
		else{
		if(m_Body[i]->m_param.m_type == Body_Box){
			const float POS[3] = {m_Body[i]->m_param.m_px, m_Body[i]->m_param.m_py, m_Body[i]->m_param.m_pz};
			const float sides[3] = {m_Body[i]->m_param.m_length, m_Body[i]->m_param.m_width, m_Body[i]->m_param.m_height};
			dsDrawBox(POS,R,sides);

		}
		else if(m_Body[i]->m_param.m_type == Body_Sphere){




			const float POS[3] = {m_Body[i]->m_param.m_px, m_Body[i]->m_param.m_py, m_Body[i]->m_param.m_pz};
			dsDrawSphere(POS,R,m_Body[i]->m_param.m_rad);


		}
		else if(m_Body[i]->m_param.m_type == Body_Cylinder){
			const float POS[3] = {m_Body[i]->m_param.m_px, m_Body[i]->m_param.m_py, m_Body[i]->m_param.m_pz};
			dsDrawCylinder(POS,R,m_Body[i]->m_param.m_length,m_Body[i]->m_param.m_rad);

		}
		else if(m_Body[i]->m_param.m_type == Body_Cone){
			const float POS[3] = {m_Body[i]->m_param.m_px, m_Body[i]->m_param.m_py, m_Body[i]->m_param.m_pz};
			dsDrawCone(POS,R,m_Body[i]->m_param.m_length,m_Body[i]->m_param.m_rad);

		}
		else if(m_Body[i]->m_param.m_type == Body_Polygon){
			const float POS[3] = {m_Body[i]->m_param.m_px, m_Body[i]->m_param.m_py, m_Body[i]->m_param.m_pz};
			if(i != GeoNum)
				DrawPolygon(m_Body[i]->m_param.m_pd,POS,R,false);
			else
				DrawPolygon(m_Body[i]->m_param.m_pd,POS,R,true);
			

		}
		
		}
	
	}

	glRotatef( -zRot, 0.0, 0.0, 1.0 );
	glRotatef( -yRot, 0.0, 1.0, 0.0 ); 
	glRotatef( -xRot, 1.0, 0.0, 0.0 );

	glTranslatef(-xWe, -yWe, 0);
    
	glPushMatrix();

	color[3] = 1.0;
	color[0] = 1.0;
	color[1] = 0.0;
	color[2] = 0.0;

	glScaled(scale,scale,scale);
	
	glTranslatef( ArrowPosX, ArrowPosY, 0.0);

	glRotatef( xRot, 1.0, 0.0, 0.0 ); 
    glRotatef( yRot, 0.0, 1.0, 0.0 ); 
    glRotatef( zRot, 0.0, 0.0, 1.0 );

	

	const float POSA[3] = {0.0, -0.0, 0.5};
	dsDrawArrow(POSA, 0, Arrowlength, Arrowradius);

	glPopMatrix();
	
	glPushMatrix();

	color[3] = 1.0;
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 1.0;

	glScaled(scale,scale,scale);

	
	glTranslatef( ArrowPosX, ArrowPosY, 0.0);

	glRotatef( xRot, 1.0, 0.0, 0.0 ); 
    glRotatef( yRot, 0.0, 1.0, 0.0 ); 
    glRotatef( zRot, 0.0, 0.0, 1.0 );

	

	const float POSB[3] = {0.0, -0.0, 0.5};
	dsDrawArrow(POSB, 1, Arrowlength, Arrowradius);

	glPopMatrix();

	glPushMatrix();

	color[3] = 1.0;
	color[0] = 0.0;
	color[1] = 1.0;
	color[2] = 0.0;

	glScaled(scale,scale,scale);


	glTranslatef( ArrowPosX, ArrowPosY, 0.0);

	glRotatef( xRot, 1.0, 0.0, 0.0 ); 
    glRotatef( yRot, 0.0, 1.0, 0.0 ); 
    glRotatef( zRot, 0.0, 0.0, 1.0 );

	

	const float POSC[3] = {0.0, -0.0, 0.5};
	dsDrawArrow(POSC, 2, Arrowlength, Arrowradius);

	glPopMatrix();
	
	

}



void GLBox::clearBody()
{
	m_Body.clear();
}

void GLBox::clearJoint()
{
	m_Joint.clear();
}

void GLBox::clearSensor()
{
	m_Sensor.clear();
}

void GLBox::clearCamera()
{
	m_Vision.clear();
}



void GLBox::setBody(BodyData *bd, int num)
{


	if(num == -1 || num >= m_Body.size())
	{
		m_Body.push_back(bd);
	}
	else
	{
		m_Body[num] = bd;
	}



	MoveFlag = true;





}


void GLBox::setBodyParam(BodyParam *bp, int num)
{


	if (num == -1 || num >= m_Body.size())
	{
		BodyData *bd = new BodyData(*bp);
		m_Body.push_back(bd);
	}
	else
	{
		m_Body[num]->m_param = *bp;
	}



	MoveFlag = true;




}

void GLBox::setSensor(SensorData *sd, int num)
{


	if(num == -1 || num >= m_Sensor.size())
	{
		m_Sensor.push_back(sd);
	}
	else
	{
		m_Sensor[num] = sd;
	}


	MoveFlag = true;
}

void GLBox::setCamera(CameraData *cd, int num)
{


	if(num == -1 || num >= m_Vision.size())
	{
		m_Vision.push_back(cd);
	}
	else
	{
		m_Vision[num] = cd;
	}
	MoveFlag = true;
}

void GLBox::setJoint(JointData *jd, int num)
{

	if(num == -1 || num >= m_Joint.size())
	{
		m_Joint.push_back(jd);
	}
	else
	{
		m_Joint[num] = jd;
	}


	MoveFlag = true;


}




void GLBox::initializeGL()
{
  qglClearColor(Qt::black);
  object = makeObject();
  glShadeModel( GL_FLAT );
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glDisable (GL_TEXTURE_2D);
  glDisable (GL_TEXTURE_GEN_S);
  glDisable (GL_TEXTURE_GEN_T);
  glShadeModel (GL_FLAT);
  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_LESS);
  glEnable (GL_CULL_FACE);
  glCullFace (GL_BACK);
  glFrontFace (GL_CCW);

    static GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
  static GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  static GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  static GLfloat light_shiness[] = { 40.0 };

  glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv (GL_LIGHT0, GL_SHININESS, light_shiness);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);

  glColor3f (1.0, 1.0, 1.0);
}




void GLBox::resizeGL( int w, int h )
{
    glViewport( 0, 0, (GLint)w, (GLint)h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 15.0 );
    glMatrixMode( GL_MODELVIEW );
}




GLuint GLBox::makeObject()
{	
    GLuint list;

    list = glGenLists( 1 );

    glNewList( list, GL_COMPILE );

    qglColor(Qt::white);		

    glLineWidth( 2.0 );

    glBegin( GL_LINE_LOOP );
    glVertex3f(  1.0,  0.5, -0.4 );
    glVertex3f(  1.0, -0.5, -0.4 );
    glVertex3f( -1.0, -0.5, -0.4 );
    glVertex3f( -1.0,  0.5, -0.4 );
    glEnd();

    glBegin( GL_LINE_LOOP );
    glVertex3f(  1.0,  0.5, 0.4 );
    glVertex3f(  1.0, -0.5, 0.4 );
    glVertex3f( -1.0, -0.5, 0.4 );
    glVertex3f( -1.0,  0.5, 0.4 );
    glEnd();

    glBegin( GL_LINES );
    glVertex3f(  1.0,  0.5, -0.4 );   glVertex3f(  1.0,  0.5, 0.4 );
    glVertex3f(  1.0, -0.5, -0.4 );   glVertex3f(  1.0, -0.5, 0.4 );
    glVertex3f( -1.0, -0.5, -0.4 );   glVertex3f( -1.0, -0.5, 0.4 );
    glVertex3f( -1.0,  0.5, -0.4 );   glVertex3f( -1.0,  0.5, 0.4 );
    glEnd();

    glEndList();

    return list;
}




void GLBox::setXRotation( int degrees )
{
    xRot = (double)(degrees % 360);
    updateGL();
}




void GLBox::setYRotation( int degrees )
{
    yRot = (GLfloat)(degrees % 360);
    updateGL();
}




void GLBox::setZRotation( int degrees )
{
    zRot = (GLfloat)(degrees % 360);
    updateGL();
}






void GLBox::mousePressEvent(QMouseEvent *e)
{
    anchor = e->pos();
}







void GLBox::mouseMoveEvent(QMouseEvent *e)
{
    QPoint diff = e->pos() - anchor;
    if (e->buttons() & Qt::LeftButton) {
        xRot += diff.y()/5.0f;
        yRot += diff.x()/5.0f;
		testan += 0.01;

    } else if (e->buttons() & Qt::RightButton) {
		if(BorT == 0)scale += diff.y()/100.0f;
		else{
			xWe += diff.x()/50.0f;
			yWe += diff.y()/50.0f;
		}
    }

    anchor = e->pos();
    updateGL();
}



std::vector<JointData*> GLBox::getJoint(BodyData* bd)
{
	std::vector<JointData*> ans;
	for (int i = 0; i < m_Joint.size(); i++)
	{
		if (m_Joint[i]->m_item1 == bd)
			ans.push_back(m_Joint[i]);
		else if (m_Joint[i]->m_item2 == bd)
			ans.push_back(m_Joint[i]);
	}
	return ans;

}

void GLBox::setBodyPosition(JointData *jd)
{
	
	MoveFlag = false;
	
	float BPX = jd->m_item2->m_param.m_px - jd->m_param.m_px;
	float BPY = jd->m_item2->m_param.m_py - jd->m_param.m_py;
	float BPZ = jd->m_item2->m_param.m_pz - jd->m_param.m_pz;
	
	float RK[12] = { 1, 0, 0, BPX, 0, 1, 0, BPY, 0, 0, 1, BPZ };
	dot3X3(jd->m_item2->ROT, jd->ROT, RK);
	//for (int i = 0; i < 12; i++)std::cout << i << "\t" << jd->ROT[i] << std::endl;
	//std::cout << jd->m_item2->m_param.NUM << std::endl;

	std::vector<JointData *> tmp_jd;
	std::vector<JointData *> jv = getJoint(jd->m_item2);
	for (int i = 0; i < jv.size(); i++)
	{
		if (jv[i]->m_item1 == jd->m_item2)
		{
			tmp_jd.push_back(jv[i]);
		}
	}
	for (std::vector<JointData*>::iterator it = tmp_jd.begin(); it != tmp_jd.end(); ++it)
	{
		calcJointRot((*it));
		(*it)->ROT[3] += (*it)->m_param.m_px - jd->m_param.m_px;
		(*it)->ROT[7] += (*it)->m_param.m_py - jd->m_param.m_py;
		(*it)->ROT[11] += (*it)->m_param.m_pz - jd->m_param.m_pz;
		float TN[12];
		dot3X3(TN, jd->ROT, (*it)->ROT);
		for (int i = 0; i < 12; i++)(*it)->ROT[i] = TN[i];
		setBodyPosition((*it));
	}

}

void GLBox::calcJointRot(JointData *jd)
{
	float RX, RY, RZ;
	if (jd->m_param.m_axisy == 0.0
		&& jd->m_param.m_axisz == 0.0)
	{
		RX = jd->angle;
		RY = 0.0;
		RZ = 0.0;
		
	}
	else if (jd->m_param.m_axisx == 0.0
		&& jd->m_param.m_axisz == 0.0)
	{
		RX = 0.0;
		RY = jd->angle;
		RZ = 0.0;
		
	}
	else if (jd->m_param.m_axisy == 0.0
		&& jd->m_param.m_axisx == 0.0)
	{
		RX = 0.0;
		RY = 0.0;
		RZ = jd->angle;
		
	}
	else if (jd->m_param.m_axisx != 0)
	{
		float TEMPX = jd->m_param.m_axisx;
		float TEMPY = jd->m_param.m_axisy;
		float TEMPZ = jd->m_param.m_axisz;
		float TEMPXY = sqrt(TEMPX*TEMPX + TEMPY*TEMPY);
		RZ = atan2(jd->m_param.m_axisx, jd->m_param.m_axisy);
		RY = atan2(TEMPZ, TEMPXY);
		RX = jd->angle;
		

	}

	else if (jd->m_param.m_axisy != 0)
	{
		RX = atan2(jd->m_param.m_axisy, jd->m_param.m_axisz);
		RY = jd->angle;
		
	}
	
	float RK[12] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 };
	float LN[12], GN[12];

	if (jd->m_param.m_type == Hinge){
		if ((jd->m_param.m_axisy == 0.0
			&& jd->m_param.m_axisz == 0.0)
			|| (jd->m_param.m_axisx == 0.0
			&& jd->m_param.m_axisz == 0.0)
			|| (jd->m_param.m_axisy == 0.0
			&& jd->m_param.m_axisx == 0.0)){
			
			RotTSL(jd->ROT, RX, RY, RZ, 0, 0, 0, RK);

		}
		else if (jd->m_param.m_axisx != 0){
			RotTSL(GN, 0.0, 0.0, -RZ, 0, 0, 0, RK);
			RotTSL(LN, 0.0, RY, 0.0, 0, 0, 0, GN);
			RotTSL(jd->ROT, RX, -RY, RZ, 0, 0, 0, LN);
		}
		else if (jd->m_param.m_axisy != 0)
		{
			RotTSL(GN, RX, 0.0, 0.0, 0, 0, 0, RK);
			RotTSL(LN, 0.0, RY, 0.0, 0, 0, 0, GN);
			RotTSL(jd->ROT, -RX, 0.0, 0.0, 0, 0, 0, LN);
		}



	}
	else if (jd->m_param.m_type == Slider){
		
		RotTSL(jd->ROT, 0, 0, 0, RX, RY, RZ, RK);
	}
	else if (jd->m_param.m_type == Fix){
		for (int d = 0; d<12; d++)jd->ROT[d] = RK[d];
	}







}

void GLBox::moveBody(std::vector<float> ANGLE)
{
	BodyData* n_bd;
	for (std::vector<BodyData*>::iterator it = m_Body.begin(); it != m_Body.end(); ++it)
	{
		if((*it)->m_param.NUM == 0)n_bd = (*it);
		
	}

	for (int i = 0; i < m_Joint.size(); i++)
	{
		m_Joint[i]->angle = 0;
	}
	
	for(int i=0;i<ANGLE.size();i++)
	{
		if(m_Joint.size() > i)m_Joint[i]->angle = ANGLE[i];
		
	}

	n_bd->ROT[0] = 1.0;
	n_bd->ROT[1] = 0.0;
	n_bd->ROT[2] = 0.0;
	n_bd->ROT[3] = n_bd->m_param.m_px;
	n_bd->ROT[4] = 0.0;
	n_bd->ROT[5] = 1.0;
	n_bd->ROT[6] = 0.0;
	n_bd->ROT[7] = n_bd->m_param.m_py;
	n_bd->ROT[8] = 0.0;
	n_bd->ROT[9] = 0.0;
	n_bd->ROT[10] = 1.0;
	n_bd->ROT[11] = n_bd->m_param.m_pz;

	std::vector<JointData *> tmp_jd;
	std::vector<JointData *> jv = getJoint(n_bd);
	for (int i = 0; i < jv.size(); i++)
	{
		if (jv[i]->m_item1 == n_bd)
		{
			tmp_jd.push_back(jv[i]);
		}
	}
	for (std::vector<JointData*>::iterator it = tmp_jd.begin(); it != tmp_jd.end(); ++it)
	{
		calcJointRot((*it));
		(*it)->ROT[3] += (*it)->m_param.m_px;
		(*it)->ROT[7] += (*it)->m_param.m_py;
		(*it)->ROT[11] += (*it)->m_param.m_pz;
		//for (int i = 0; i < 12; i++)std::cout << (*it)->ROT[i] << std::endl;
		setBodyPosition((*it));
	}
	
	
	
	




}

