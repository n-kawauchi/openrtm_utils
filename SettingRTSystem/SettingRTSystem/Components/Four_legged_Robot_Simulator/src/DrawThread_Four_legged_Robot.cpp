#include <fstream>
#include "DrawThread_Four_legged_Robot.h"
#include "searchFile.h"
#include <coil/stringutil.h>

//std::ofstream ofs( "test.txt" );

#ifdef dDOUBLE
#define dsDrawCapsule dsDrawCapsuleD
#define dsDrawBox     dsDrawBoxD
#define dsDrawLine    dsDrawLineD
#define dsDrawTriangle    dsDrawTriangleD
#endif

DrawThread_Four_legged_Robot *obj = NULL;


/**
*@brief シミュレーションの描画をするスレッドのコンストラクタ
*/
DrawThread_Four_legged_Robot::DrawThread_Four_legged_Robot(SimulatorObj_Four_legged_Robot *so)
{
	m_so = so;
	

	setDrawStuff();

	obj = this;
	m_pause = 0;
	RCP_flag = false;
	stop_flag = false;
}

/**
*@brief シミュレーションループ
* @param pause 未使用
*/
void simLoop(int pause)
{
#ifdef WIN32
	Sleep(1000.0 / obj->fps);
#else
	struct timespec ts;
	ts.tv_sec = 1;
	ts.tv_nsec = 0;
	nanosleep(&ts, NULL);
#endif
	if (obj)
	{
		if (!obj->stop_flag)
		{
			obj->m_pause = pause;
			obj->drawRobot();
			obj->resetCameraPosition();
		}
		else
		{
			
			dsStop();
			
		}
	}

	
}



/**
*@brief シミュレーション初期化
*/
void start()
{
  //float xyz[3] = {  .0f,  1.0f, 3.0f};  
  float xyz[3] = {  0.5f,  -0.0f, 0.25f}; 
  float hpr[3] = {180.0f, -10.0f, 0.0f};  
  //float hpr[3] = {0.0f, -90.0f, 90.0f}; 
  //float xyz[3] = {  5.0f,  -5.0f, 3.0f};
  //float hpr[3] = {180.0f, -10.0f, 0.0f};
  dsSetViewpoint(xyz,hpr);                
  dsSetSphereQuality(3);
  dsSetCapsuleQuality(6);


  
  
}

/**
*@brief スレッド実行関数
* @return
*/
int DrawThread_Four_legged_Robot::svc()
{
	int argc = 0;
	char *argv[] = {""};

	dsSimulationLoop(argc, argv, 800, 480, &fn);
	

	

	return 0;
}


/**
*@brief DrawStuff初期化
*/
void DrawThread_Four_legged_Robot::setDrawStuff()
{
	fn.version = DS_VERSION;
  fn.start   = &start;
  fn.step    = &simLoop;
  fn.command = NULL;
  fn.stop = NULL;

  static std::string drawstuff = search_file("drawstuff/textures", "PATH", ";");

  coil::replaceString(drawstuff, "\\", "/");


  if (drawstuff == "")
  {
	  fn.path_to_textures = "drawstuff/textures";
  }
  else
  {
	  fn.path_to_textures = drawstuff.c_str();

  }
}

/**
*@brief 直方体描画
* @param body ボディオブジェクト
*/
void DrawThread_Four_legged_Robot::drawBox(MyLink *body)
{
	const double sides[3] = {body->lx, body->ly, body->lz};
	dsSetColorAlpha(body->red,body->green,body->blue,1.0);
	dsDrawBoxD(dBodyGetPosition(body->body),
						dBodyGetRotation(body->body),sides);
}

/**
*@brief 円柱描画
* @param body ボディオブジェクト
*/
void DrawThread_Four_legged_Robot::drawCylinder(MyLink *body)
{
	dsSetColorAlpha(body->red,body->green,body->blue,1.0);
	dsDrawCylinderD(dBodyGetPosition(body->body),
						dBodyGetRotation(body->body),body->lz,body->lx);
}

/**
*@brief 全ボディ描画
*/
void DrawThread_Four_legged_Robot::drawRobot()
{
	if(m_so->pause)
	{
		m_so->mu.lock();

		for (int i = 0; i < m_so->legs.size(); i++)
		{
			for (int j = 0; j < m_so->legs[i].size(); j++)
			{
				drawBox(&m_so->legs[i][j]);
			}
		}

		
		drawBox(&m_so->body);

		m_so->mu.unlock();
	}
}

/**
*@brief カメラ位置再設定
*/
void DrawThread_Four_legged_Robot::resetCameraPosition()
{ 
	m_so->mu.lock();
	if (RCP_flag)
	{
		float xyz[3] = { 0.5f, -0.0f, 0.25f };
		float hpr[3] = { 180.0f, -10.0f, 0.0f };
		dsSetViewpoint(xyz, hpr);
		dsSetSphereQuality(3);
		dsSetCapsuleQuality(6);


		RCP_flag = false;
		
	}
	m_so->mu.unlock();
}


/**
*@brief カメラ位置再設定フラグを立てる
*/
void DrawThread_Four_legged_Robot::setRCPFlag()
{
	m_so->mu.lock();
	RCP_flag = true;
	m_so->mu.unlock();
}


/**
*@brief 描画を停止する
*/
void DrawThread_Four_legged_Robot::stop()
{
	
	m_so->mu.lock();
	stop_flag = true;
	m_so->mu.unlock();
	
	wait();
	

}