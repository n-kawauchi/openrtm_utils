// -*-C++-*-
/*!
 * @file  LeggedRobotSVC_impl.cpp
 * @brief Service implementation code of LeggedRobot.idl
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 */

#include "LeggedRobotSVC_impl.h"

/*
 * Example implementational code for IDL interface OpenHRP::ServerObject
 */
OpenHRP_ServerObjectSVC_impl::OpenHRP_ServerObjectSVC_impl()
{
  // Please add extra constructor code here.
}


OpenHRP_ServerObjectSVC_impl::~OpenHRP_ServerObjectSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
void OpenHRP_ServerObjectSVC_impl::shutdown()
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <void OpenHRP_ServerObjectSVC_impl::shutdown()>"
#endif
}



// End of example implementational code

/*
 * Example implementational code for IDL interface OpenHRP::ShapeSetInfo
 */
OpenHRP_ShapeSetInfoSVC_impl::OpenHRP_ShapeSetInfoSVC_impl()
{
  // Please add extra constructor code here.
}


OpenHRP_ShapeSetInfoSVC_impl::~OpenHRP_ShapeSetInfoSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */


// End of example implementational code

/*
 * Example implementational code for IDL interface OpenHRP::BodyInfo
 */
OpenHRP_BodyInfoSVC_impl::OpenHRP_BodyInfoSVC_impl()
{
  // Please add extra constructor code here.
}


OpenHRP_BodyInfoSVC_impl::~OpenHRP_BodyInfoSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */


// End of example implementational code

/*
 * Example implementational code for IDL interface OpenHRP::SceneInfo
 */
OpenHRP_SceneInfoSVC_impl::OpenHRP_SceneInfoSVC_impl()
{
  // Please add extra constructor code here.
}


OpenHRP_SceneInfoSVC_impl::~OpenHRP_SceneInfoSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */


// End of example implementational code

/*
 * Example implementational code for IDL interface OpenHRP::ModelLoader
 */
OpenHRP_ModelLoaderSVC_impl::OpenHRP_ModelLoaderSVC_impl()
{
  // Please add extra constructor code here.
}


OpenHRP_ModelLoaderSVC_impl::~OpenHRP_ModelLoaderSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
OpenHRP::BodyInfo_ptr OpenHRP_ModelLoaderSVC_impl::getBodyInfo(const char* url)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <OpenHRP::BodyInfo_ptr OpenHRP_ModelLoaderSVC_impl::getBodyInfo(const char* url)>"
#endif
  return 0;
}

OpenHRP::BodyInfo_ptr OpenHRP_ModelLoaderSVC_impl::getBodyInfoEx(const char* url, OpenHRP::ModelLoader::ModelLoadOption option)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <OpenHRP::BodyInfo_ptr OpenHRP_ModelLoaderSVC_impl::getBodyInfoEx(const char* url, OpenHRP::ModelLoader::ModelLoadOption option)>"
#endif
  return 0;
}

OpenHRP::BodyInfo_ptr OpenHRP_ModelLoaderSVC_impl::loadBodyInfo(const char* url)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <OpenHRP::BodyInfo_ptr OpenHRP_ModelLoaderSVC_impl::loadBodyInfo(const char* url)>"
#endif
  return 0;
}

OpenHRP::BodyInfo_ptr OpenHRP_ModelLoaderSVC_impl::loadBodyInfoEx(const char* url, OpenHRP::ModelLoader::ModelLoadOption option)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <OpenHRP::BodyInfo_ptr OpenHRP_ModelLoaderSVC_impl::loadBodyInfoEx(const char* url, OpenHRP::ModelLoader::ModelLoadOption option)>"
#endif
  return 0;
}

OpenHRP::SceneInfo_ptr OpenHRP_ModelLoaderSVC_impl::loadSceneInfo(const char* url)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <OpenHRP::SceneInfo_ptr OpenHRP_ModelLoaderSVC_impl::loadSceneInfo(const char* url)>"
#endif
  return 0;
}

void OpenHRP_ModelLoaderSVC_impl::clearData()
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <void OpenHRP_ModelLoaderSVC_impl::clearData()>"
#endif
}



// End of example implementational code

/*
 * Example implementational code for IDL interface WalkingRobot::LeggedRobotCommonInterface_Robot
 */
WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl::WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl()
{
  // Please add extra constructor code here.
}


WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl::~WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
WalkingRobot::RobotInfo* WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl::getRobotInfo()
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <WalkingRobot::RobotInfo* WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl::getRobotInfo()>"
#endif
  return 0;
}

WalkingRobot::LegList* WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl::getFeedbackPos()
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <WalkingRobot::LegList* WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl::getFeedbackPos()>"
#endif
  return 0;
}



// End of example implementational code



