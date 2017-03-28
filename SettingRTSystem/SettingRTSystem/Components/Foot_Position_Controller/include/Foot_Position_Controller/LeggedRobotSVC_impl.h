// -*-C++-*-
/*!
 * @file  LeggedRobotSVC_impl.h
 * @brief Service implementation header of LeggedRobot.idl
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 */

#include "BasicDataTypeSkel.h"
#include "ExtendedDataTypesSkel.h"
#include "ModelLoaderSkel.h"
#include "OpenHRPCommonSkel.h"

#include "LeggedRobotSkel.h"

#ifndef LEGGEDROBOTSVC_IMPL_H
#define LEGGEDROBOTSVC_IMPL_H
 
/*!
 * @class ServerObjectSVC_impl
 * Example class implementing IDL interface OpenHRP::ServerObject
 */
class OpenHRP_ServerObjectSVC_impl
 : public virtual POA_OpenHRP::ServerObject,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~ServerObjectSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
	 OpenHRP_ServerObjectSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~OpenHRP_ServerObjectSVC_impl();

   // attributes and operations
   void shutdown();

};

/*!
 * @class ShapeSetInfoSVC_impl
 * Example class implementing IDL interface OpenHRP::ShapeSetInfo
 */
class OpenHRP_ShapeSetInfoSVC_impl
 : public virtual POA_OpenHRP::ShapeSetInfo,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~ShapeSetInfoSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
	 OpenHRP_ShapeSetInfoSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~OpenHRP_ShapeSetInfoSVC_impl();

   // attributes and operations

};

/*!
 * @class BodyInfoSVC_impl
 * Example class implementing IDL interface OpenHRP::BodyInfo
 */
class OpenHRP_BodyInfoSVC_impl
 : public virtual POA_OpenHRP::BodyInfo,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~BodyInfoSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
	 OpenHRP_BodyInfoSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~OpenHRP_BodyInfoSVC_impl();

   // attributes and operations

};

/*!
 * @class SceneInfoSVC_impl
 * Example class implementing IDL interface OpenHRP::SceneInfo
 */
class OpenHRP_SceneInfoSVC_impl
 : public virtual POA_OpenHRP::SceneInfo,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~SceneInfoSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
	 OpenHRP_SceneInfoSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~OpenHRP_SceneInfoSVC_impl();

   // attributes and operations

};

/*!
 * @class ModelLoaderSVC_impl
 * Example class implementing IDL interface OpenHRP::ModelLoader
 */
class OpenHRP_ModelLoaderSVC_impl
 : public virtual POA_OpenHRP::ModelLoader,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~ModelLoaderSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
	 OpenHRP_ModelLoaderSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~OpenHRP_ModelLoaderSVC_impl();

   // attributes and operations
   OpenHRP::BodyInfo_ptr getBodyInfo(const char* url);
   OpenHRP::BodyInfo_ptr getBodyInfoEx(const char* url, OpenHRP::ModelLoader::ModelLoadOption option);
   OpenHRP::BodyInfo_ptr loadBodyInfo(const char* url);
   OpenHRP::BodyInfo_ptr loadBodyInfoEx(const char* url, OpenHRP::ModelLoader::ModelLoadOption option);
   OpenHRP::SceneInfo_ptr loadSceneInfo(const char* url);
   void clearData();

};

/*!
 * @class LeggedRobotCommonInterface_ServoSVC_impl
 * Example class implementing IDL interface RTC::LeggedRobotCommonInterface_Servo
 */
class WalkingRobot_LeggedRobotCommonInterface_ServoSVC_impl
	: public virtual POA_WalkingRobot::LeggedRobotCommonInterface_Servo,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~LeggedRobotCommonInterface_ServoSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
	 WalkingRobot_LeggedRobotCommonInterface_ServoSVC_impl();
  /*!
   * @brief destructor
   */
	 virtual ~WalkingRobot_LeggedRobotCommonInterface_ServoSVC_impl();

   // attributes and operations
	 ::CORBA::Boolean setSoftLimitJoint(const WalkingRobot::JointPos& pos);
	 WalkingRobot::JointPos* getSoftLimitjoint();
   ::CORBA::Boolean servoOFF();
   ::CORBA::Boolean servoON();

};

/*!
 * @class LeggedRobotCommonInterface_RobotSVC_impl
 * Example class implementing IDL interface RTC::LeggedRobotCommonInterface_Robot
 */
class WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl
	: public virtual POA_WalkingRobot::LeggedRobotCommonInterface_Robot,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~LeggedRobotCommonInterface_RobotSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
	 WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl();
  /*!
   * @brief destructor
   */
	 virtual ~WalkingRobot_LeggedRobotCommonInterface_RobotSVC_impl();

   // attributes and operations
   WalkingRobot::RobotInfo* getRobotInfo();
   WalkingRobot::LegList* getFeedbackPos();

};



#endif // LEGGEDROBOTSVC_IMPL_H


