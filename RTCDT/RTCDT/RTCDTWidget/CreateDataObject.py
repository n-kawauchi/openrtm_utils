#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
import OpenRTM_aist
import RTC



class CreateDataObject:
    dataTypeList = {
        "RTC.Time":"(0,0)",
        "RTC.TimedState":"(RTC.Time(0,0), 0)",
        "RTC.TimedShort":"(RTC.Time(0,0), 0)",
        "RTC.TimedLong":"(RTC.Time(0,0), 0)",
        "RTC.TimedUShort":"(RTC.Time(0,0), 0)",
        "RTC.TimedULong":"(RTC.Time(0,0), 0)",
        "RTC.TimedFloat":"(RTC.Time(0,0), 0.0)",
        "RTC.TimedDouble":"(RTC.Time(0,0), 0.0)",
        "RTC.TimedChar":"(RTC.Time(0,0), chr(0))",
        "RTC.TimedWChar":'(RTC.Time(0,0), u"00")',
        "RTC.TimedBoolean":"(RTC.Time(0,0), False)",
        "RTC.TimedOctet":"(RTC.Time(0,0), 0)",
        "RTC.TimedString":'(RTC.Time(0,0), "")',
        "RTC.TimedWString":'(RTC.Time(0,0), u"")',
        "RTC.TimedShortSeq":"(RTC.Time(0,0), [])",
        "RTC.TimedLongSeq":"(RTC.Time(0,0), [])",
        "RTC.TimedUShortSeq":"(RTC.Time(0,0), [])",
        "RTC.TimedULongSeq":"(RTC.Time(0,0), [])",
        "RTC.TimedFloatSeq":"(RTC.Time(0,0), [])",
        "RTC.TimedDoubleSeq":"(RTC.Time(0,0), [])",
        "RTC.TimedCharSeq":"(RTC.Time(0,0), [])",
        "RTC.TimedWCharSeq":"(RTC.Time(0,0), [])",
        "RTC.TimedBooleanSeq":"(RTC.Time(0,0), [])",
        "RTC.TimedOctetSeq":'(RTC.Time(0,0), "")',
        "RTC.TimedStringSeq":"(RTC.Time(0,0), [])",
        "RTC.TimedWStringSeq":"(RTC.Time(0,0), [])",
        "RTC.RGBColour":"(0.0,0.0,0.0)",
        "RTC.Point2D":"(0.0,0.0)",
        "RTC.Vector2D":"(0.0,0.0)",
        "RTC.Pose2D":"(RTC.Point2D(0.0,0.0), 0.0)",
        "RTC.Velocity2D":"(0.0,0.0,0.0)",
        "RTC.Acceleration2D":"(0.0,0.0)",
        "RTC.PoseVel2D":"(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Velocity2D(0.0,0.0,0.0))",
        "RTC.Size2D":"(0.0, 0.0)",
        "RTC.Geometry2D":"(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Size2D(0.0, 0.0))",
        "RTC.Covariance2D":"(*([0.0]*6))",
        "RTC.PointCovariance2D":"(0.0,0.0,0.0)",
        "RTC.Carlike":"(0.0,0.0)",
        "RTC.SpeedHeading2D":"(0.0,0.0)",
        "RTC.Point3D":"(0.0,0.0,0.0)",
        "RTC.Vector3D":"(0.0,0.0,0.0)",
        "RTC.Orientation3D":"(0.0,0.0,0.0)",
        "RTC.Pose3D":"(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0))",
        "RTC.Velocity3D":"(*([0.0]*6))",
        "RTC.AngularVelocity3D":"(0.0,0.0,0.0)",
        "RTC.Acceleration3D":"(0.0,0.0,0.0)",
        "RTC.AngularAcceleration3D":"(0.0,0.0,0.0)",
        "RTC.PoseVel3D":"(0.0,0.0,0.0)",
        "RTC.Size3D":"(0.0,0.0,0.0)",
        "RTC.Geometry3D":"(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Velocity3D(*([0.0]*6)))",
        "RTC.Covariance3D":"(*([0.0]*21))",
        "RTC.SpeedHeading3D":"(0.0, RTC.Orientation3D(0.0,0.0,0.0))",
        "RTC.OAP":"(*([RTC.Vector3D(0.0,0.0,0.0)]*3))",
        "RTC.TimedRGBColour":"(RTC.Time(0,0), RTC.RGBColour(0.0,0.0,0.0))",
        "RTC.TimedPoint2D":"(RTC.Time(0,0), RTC.Point2D(0.0,0.0))",
        "RTC.TimedVector2D":"(RTC.Time(0,0), RTC.Vector2D(0.0,0.0))",
        "RTC.TimedPose2D":"(RTC.Time(0,0), RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0))",
        "RTC.TimedVelocity2D":"(RTC.Time(0,0), RTC.Velocity2D(0.0,0.0,0.0))",
        "RTC.TimedAcceleration2D":"(RTC.Time(0,0), RTC.Acceleration2D(0.0,0.0))",
        "RTC.TimedPoseVel2D":"(RTC.Time(0,0), RTC.PoseVel2D(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Velocity2D(0.0,0.0,0.0)))",
        "RTC.TimedSize2D":"(RTC.Time(0,0), RTC.Size2D(0.0, 0.0))",
        "RTC.TimedGeometry2D":"(RTC.Time(0,0), RTC.Geometry2D(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Size2D(0.0, 0.0)))",
        "RTC.TimedCovariance2D":"(RTC.Time(0,0), RTC.Covariance2D(*([0.0]*6)))",
        "RTC.TimedPointCovariance2D":"(RTC.Time(0,0), RTC.PointCovariance2D(0.0,0.0,0.0))",
        "RTC.TimedCarlike":"(RTC.Time(0,0), RTC.Carlike(0.0,0.0))",
        "RTC.TimedSpeedHeading2D":"(RTC.Time(0,0), RTC.SpeedHeading2D(0.0,0.0))",
        "RTC.TimedPoint3D":"(RTC.Time(0,0), RTC.Point3D(0.0,0.0,0.0))",
        "RTC.TimedVector3D":"(RTC.Time(0,0), RTC.Vector3D(0.0,0.0,0.0))",
        "RTC.TimedOrientation3D":"(RTC.Time(0,0), RTC.Orientation3D(0.0,0.0,0.0))",
        "RTC.TimedPose3D":"(RTC.Time(0,0), RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)))",
        "RTC.TimedVelocity3D":"(RTC.Time(0,0), RTC.Velocity3D(*([0.0]*6)))",
        "RTC.TimedAngularVelocity3D":"(RTC.Time(0,0), RTC.AngularVelocity3D(0.0,0.0,0.0))",
        "RTC.TimedAcceleration3D":"(RTC.Time(0,0), RTC.Acceleration3D(0.0,0.0,0.0))",
        "RTC.TimedAngularAcceleration3D":"(RTC.Time(0,0), RTC.AngularAcceleration3D(0.0,0.0,0.0))",
        "RTC.TimedPoseVel3D":"(RTC.Time(0,0), RTC.PoseVel3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Velocity3D(*([0.0]*6))))",
        "RTC.TimedSize3D":"(RTC.Time(0,0), RTC.Size3D(0.0,0.0,0.0))",
        "RTC.TimedGeometry3D":"(RTC.Time(0,0), RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)))",
        "RTC.TimedCovariance3D":"(RTC.Time(0,0), RTC.Covariance3D(*([0.0]*21)))",
        "RTC.TimedSpeedHeading3D":"(RTC.Time(0,0), RTC.SpeedHeading3D(0.0, RTC.Orientation3D(0.0,0.0,0.0)))",
        "RTC.TimedOAP":"(RTC.Time(0,0), RTC.OAP(*([RTC.Vector3D(0.0,0.0,0.0)]*3)))",
        "RTC.Quaternion":"(*([0.0]*4))",
        "RTC.TimedQuaternion":"(RTC.Time(0,0), RTC.Quaternion(*([0.0]*4)))",
        "RTC.ActArrayActuatorPos":"(RTC.Time(0,0), 0, 0.0)",
        "RTC.ActArrayActuatorSpeed":"(RTC.Time(0,0), 0, 0.0)",
        "RTC.ActArrayActuatorCurrent":"(RTC.Time(0,0), 0, 0.0)",
        "RTC.Actuator":"(0.0,0.0,0.0,0.0, RTC.ACTUATOR_STATUS_IDLE)",
        "RTC.ActArrayState":"(RTC.Time(0,0), [])",
        "RTC.ActArrayActuatorGeometry":"(RTC.ACTARRAY_ACTUATORTYPE_LINEAR, 0.0, RTC.Orientation3D(0.0,0.0,0.0), RTC.Vector3D(0.0,0.0,0.0), 0.0, 0.0, 0.0, 0.0, False)",
        "RTC.ActArrayGeometry":"(RTC.TimedGeometry3D(RTC.Time(0,0), RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), [])",
        "RTC.BumperGeometry":"(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0), 0.0)",
        "RTC.BumperArrayGeometry":"(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), [])",
        "RTC.CameraImage":'(RTC.Time(0,0), 0,0,0,"",0.0,"")',
        "RTC.CameraInfo":"(RTC.Vector2D(0.0,0.0), RTC.Point2D(0.0,0.0), 0.0,0.0,0.0,0.0)",
        "RTC.FiducialInfo":"(0, RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0), RTC.Size3D(0.0,0.0,0.0))",
        "RTC.Fiducials":"(RTC.Time(0,0), [])",
        "RTC.FiducialFOV":"(0.0,0.0,0.0)",
        "RTC.GPSTime":"(0,0)",
        "RTC.GPSData":"(RTC.Time(0,0), RTC.GPSTime(0,0), 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0, RTC.GPS_FIX_NONE)",
        "RTC.GripperState":"(RTC.Time(0,0), RTC.GRIPPER_STATE_UNKNOWN)",
        "RTC.INSData":"(RTC.Time(0,0), 0.0,0.0,0.0,0.0, RTC.Velocity3D(*([0.0]*6)), RTC.Orientation3D(0.0,0.0,0.0))",
        "RTC.LimbState":"(RTC.Time(0,0), RTC.OAP(*([RTC.Vector3D(0.0,0.0,0.0)]*3)), RTC.LIMB_STATUS_IDLE)",
        "RTC.Hypothesis2D":"(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Covariance2D(*([0.0]*6)), 0.0)",
        "RTC.Hypotheses2D":"(RTC.Time(0,0), [])",
        "RTC.Hypothesis3D":"(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Covariance3D(*([0.0]*21)), 0.0)",
        "RTC.Hypotheses3D":"(RTC.Time(0,0), [RTC.Hypothesis3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Covariance3D(*([0.0]*21)), 0.0)])",
        "RTC.OGMapConfig":"(0.0,0.0,0,0, RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0))",
        "RTC.OGMapTile":'(0,0,0,0,"")',
        "RTC.PointFeature":"(0.0, RTC.Point2D(0.0,0.0), RTC.PointCovariance2D(0.0,0.0,0.0))",
        "RTC.PoseFeature":"(0.0, RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Covariance2D(*([0.0]*6)))",
        "RTC.LineFeature":"(0.0,0.0,0.0, RTC.PointCovariance2D(0.0,0.0,0.0), RTC.Point2D(0.0,0.0), RTC.Point2D(0.0,0.0), False, False)",
        "RTC.Features":"(RTC.Time(0,0), [],[],[])",
        "RTC.MultiCameraImages":"(RTC.Time(0,0), [])",
        "RTC.MulticameraGeometry":"(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), [RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0))])",
        "RTC.Waypoint2D":"(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), 0.0,0.0, RTC.Time(0,0), RTC.Velocity2D(0.0,0.0,0.0))",
        "RTC.Path2D":"(RTC.Time(0,0), [RTC.Waypoint2D(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), 0.0,0.0, RTC.Time(0,0), RTC.Velocity2D(0.0,0.0,0.0))])",
        "RTC.Waypoint3D":"(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), 0.0,0.0, RTC.Time(0,0), RTC.Velocity3D(*([0.0]*6)))",
        "RTC.Path3D":"(RTC.Time(0,0), [])",
        "RTC.PointCloudPoint":"(RTC.Point3D(0.0,0.0,0.0), RTC.RGBColour(0.0,0.0,0.0))",
        "RTC.PointCloud":"(RTC.Time(0,0), [])",
        "RTC.PanTiltAngles":"(RTC.Time(0,0), 0.0,0.0)",
        "RTC.RangerGeometry":"(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), [])",
        "RTC.RangerConfig":"(*([0.0]*7))",
        "RTC.RangeData":"(RTC.Time(0,0), [], RTC.RangerGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), []), RTC.RangerConfig(*([0.0]*7)))",
        "RTC.IntensityData":"(RTC.Time(0,0), [], RTC.RangerGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), []), RTC.RangerConfig(*([0.0]*7)))",
        "Img.ImageData":'(0,0, Img.CF_UNKNOWN, "")',
        "Img.CameraIntrinsicParameter":"([0.0]*5, [])",
        "Img.CameraImage":'(RTC.Time(0,0), Img.ImageData(0,0, Img.CF_UNKNOWN, ""), Img.CameraIntrinsicParameter([0.0]*5, []), [[0.0]*4]*4)',
        "Img.TimedCameraImage":'(RTC.Time(0,0), Img.CameraImage(RTC.Time(0,0), Img.ImageData(0,0, Img.CF_UNKNOWN, ""), Img.CameraIntrinsicParameter([0.0]*5, []), [[0.0]*4]*4), 0)',
        "Img.MultiCameraImage":"([],0)",
        "Img.TimedMultiCameraImage":"(RTC.Time(0,0), Img.MultiCameraImage([],0), 0)",
        "Img.NamedValue":'("","")',
        "Img.CameraDeviceProfile":'("","",0,"","",Img.CameraIntrinsicParameter([0.0]*5, []),[])'
        }
    @staticmethod
    def create(data_type):
        if data_type == "RTC.Time":
            return RTC.Time(0,0)
        elif data_type == "RTC.TimedState":
            return RTC.TimedState(RTC.Time(0,0), 0)
        elif data_type == "RTC.TimedShort":
            return RTC.TimedShort(RTC.Time(0,0), 0)
        elif data_type == "RTC.TimedLong":
            return RTC.TimedLong(RTC.Time(0,0), 0)
        elif data_type == "RTC.TimedUShort":
            return RTC.TimedUShort(RTC.Time(0,0), 0)
        elif data_type == "RTC.TimedULong":
            return RTC.TimedULong(RTC.Time(0,0), 0)
        elif data_type == "RTC.TimedFloat":
            return RTC.TimedFloat(RTC.Time(0,0), 0.0)
        elif data_type == "RTC.TimedDouble":
            return RTC.TimedDouble(RTC.Time(0,0), 0.0)
        elif data_type == "RTC.TimedChar":
            return RTC.TimedChar(RTC.Time(0,0), chr(0))
        elif data_type == "RTC.TimedWChar":
            return RTC.TimedWChar(RTC.Time(0,0), u"00")
        elif data_type == "RTC.TimedBoolean":
            return RTC.TimedBoolean(RTC.Time(0,0), False)
        elif data_type == "RTC.TimedOctet":
            return RTC.TimedOctet(RTC.Time(0,0), 0)
        elif data_type == "RTC.TimedString":
            return RTC.TimedString(RTC.Time(0,0), "")
        elif data_type == "RTC.TimedWString":
            return RTC.TimedWString(RTC.Time(0,0), u"")
        elif data_type == "RTC.TimedShortSeq":
            return RTC.TimedShortSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.TimedLongSeq":
            return RTC.TimedLongSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.TimedUShortSeq":
            return RTC.TimedUShortSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.TimedULongSeq":
            return RTC.TimedULongSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.TimedFloatSeq":
            return RTC.TimedFloatSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.TimedDoubleSeq":
            return RTC.TimedDoubleSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.TimedCharSeq":
            return RTC.TimedCharSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.TimedWCharSeq":
            return RTC.TimedWCharSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.TimedBooleanSeq":
            return RTC.TimedBooleanSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.TimedOctetSeq":
            return RTC.TimedOctetSeq(RTC.Time(0,0), "")
        elif data_type == "RTC.TimedStringSeq":
            return RTC.TimedStringSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.TimedWStringSeq":
            return RTC.TimedWStringSeq(RTC.Time(0,0), [])
        elif data_type == "RTC.RGBColour":
            return RTC.RGBColour(0.0,0.0,0.0)
        elif data_type == "RTC.Point2D":
            return RTC.Point2D(0.0,0.0)
        elif data_type == "RTC.Vector2D":
            return RTC.Vector2D(0.0,0.0)
        elif data_type == "RTC.Pose2D":
            return RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0)
        elif data_type == "RTC.Velocity2D":
            return RTC.Velocity2D(0.0,0.0,0.0)
        elif data_type == "RTC.Acceleration2D":
            return RTC.Acceleration2D(0.0,0.0)
        elif data_type == "RTC.PoseVel2D":
            return RTC.PoseVel2D(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Velocity2D(0.0,0.0,0.0))
        elif data_type == "RTC.Size2D":
            return RTC.Size2D(0.0, 0.0)
        elif data_type == "RTC.Geometry2D":
            return RTC.Geometry2D(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Size2D(0.0, 0.0))
        elif data_type == "RTC.Covariance2D":
            return RTC.Covariance2D(*([0.0]*6))
        elif data_type == "RTC.PointCovariance2D":
            return RTC.PointCovariance2D(0.0,0.0,0.0)
        elif data_type == "RTC.Carlike":
            return RTC.Carlike(0.0,0.0)
        elif data_type == "RTC.SpeedHeading2D":
            return RTC.SpeedHeading2D(0.0,0.0)
        elif data_type == "RTC.Point3D":
            return RTC.Point3D(0.0,0.0,0.0)
        elif data_type == "RTC.Vector3D":
            return RTC.Vector3D(0.0,0.0,0.0)
        elif data_type == "RTC.Orientation3D":
            return RTC.Orientation3D(0.0,0.0,0.0)
        elif data_type == "RTC.Pose3D":
            return RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0))
        elif data_type == "RTC.Velocity3D":
            return RTC.Velocity3D(*([0.0]*6))
        elif data_type == "RTC.AngularVelocity3D":
            return RTC.AngularVelocity3D(0.0,0.0,0.0)
        elif data_type == "RTC.Acceleration3D":
            return RTC.Acceleration3D(0.0,0.0,0.0)
        elif data_type == "RTC.AngularAcceleration3D":
            return RTC.AngularAcceleration3D(0.0,0.0,0.0)
        elif data_type == "RTC.PoseVel3D":
            return RTC.PoseVel3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Velocity3D(*([0.0]*6)))
        elif data_type == "RTC.Size3D":
            return RTC.Size3D(0.0,0.0,0.0)
        elif data_type == "RTC.Geometry3D":
            return RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0))
        elif data_type == "RTC.Covariance3D":
            return RTC.Covariance3D(*([0.0]*21))
        elif data_type == "RTC.SpeedHeading3D":
            return RTC.SpeedHeading3D(0.0, RTC.Orientation3D(0.0,0.0,0.0))
        elif data_type == "RTC.OAP":
            return RTC.OAP(*([RTC.Vector3D(0.0,0.0,0.0)]*3))
        elif data_type == "RTC.TimedRGBColour":
            return RTC.TimedRGBColour(RTC.Time(0,0), RTC.RGBColour(0.0,0.0,0.0))
        elif data_type == "RTC.TimedPoint2D":
            return RTC.TimedPoint2D(RTC.Time(0,0), RTC.Point2D(0.0,0.0))
        elif data_type == "RTC.TimedVector2D":
            return RTC.TimedVector2D(RTC.Time(0,0), RTC.Vector2D(0.0,0.0))
        elif data_type == "RTC.TimedPose2D":
            return RTC.TimedPose2D(RTC.Time(0,0), RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0))
        elif data_type == "RTC.TimedVelocity2D":
            return RTC.TimedVelocity2D(RTC.Time(0,0), RTC.Velocity2D(0.0,0.0,0.0))
        elif data_type == "RTC.TimedAcceleration2D":
            return RTC.TimedAcceleration2D(RTC.Time(0,0), RTC.Acceleration2D(0.0,0.0))
        elif data_type == "RTC.TimedPoseVel2D":
            return RTC.TimedPoseVel2D(RTC.Time(0,0), RTC.PoseVel2D(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Velocity2D(0.0,0.0,0.0)))
        elif data_type == "RTC.TimedSize2D":
            return RTC.TimedSize2D(RTC.Time(0,0), RTC.Size2D(0.0, 0.0))
        elif data_type == "RTC.TimedGeometry2D":
            return RTC.TimedGeometry2D(RTC.Time(0,0), RTC.Geometry2D(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Size2D(0.0, 0.0)))
        elif data_type == "RTC.TimedCovariance2D":
            return RTC.TimedCovariance2D(RTC.Time(0,0), RTC.Covariance2D(*([0.0]*6)))
        elif data_type == "RTC.TimedPointCovariance2D":
            return RTC.TimedPointCovariance2D(RTC.Time(0,0), RTC.PointCovariance2D(0.0,0.0,0.0))
        elif data_type == "RTC.TimedCarlike":
            return RTC.TimedCarlike(RTC.Time(0,0), RTC.Carlike(0.0,0.0))
        elif data_type == "RTC.TimedSpeedHeading2D":
            return RTC.TimedSpeedHeading2D(RTC.Time(0,0), RTC.SpeedHeading2D(0.0,0.0))
        elif data_type == "RTC.TimedPoint3D":
            return RTC.TimedPoint3D(RTC.Time(0,0), RTC.Point3D(0.0,0.0,0.0))
        elif data_type == "RTC.TimedVector3D":
            return RTC.TimedVector3D(RTC.Time(0,0), RTC.Vector3D(0.0,0.0,0.0))
        elif data_type == "RTC.TimedOrientation3D":
            return RTC.TimedOrientation3D(RTC.Time(0,0), RTC.Orientation3D(0.0,0.0,0.0))
        elif data_type == "RTC.TimedPose3D":
            return RTC.TimedPose3D(RTC.Time(0,0), RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)))
        elif data_type == "RTC.TimedVelocity3D":
            return RTC.TimedVelocity3D(RTC.Time(0,0), RTC.Velocity3D(*([0.0]*6)))
        elif data_type == "RTC.TimedAngularVelocity3D":
            return returnRTC.TimedAngularVelocity3D(RTC.Time(0,0), RTC.AngularVelocity3D(0.0,0.0,0.0))
        elif data_type == "RTC.TimedAcceleration3D":
            return RTC.TimedAcceleration3D(RTC.Time(0,0), RTC.Acceleration3D(0.0,0.0,0.0))
        elif data_type == "RTC.TimedAngularAcceleration3D":
            return RTC.TimedAngularAcceleration3D(RTC.Time(0,0), RTC.AngularAcceleration3D(0.0,0.0,0.0))
        elif data_type == "RTC.TimedPoseVel3D":
            return RTC.TimedPoseVel3D(RTC.Time(0,0), RTC.PoseVel3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Velocity3D(*([0.0]*6))))
        elif data_type == "RTC.TimedSize3D":
            return RTC.TimedSize3D(RTC.Time(0,0), RTC.Size3D(0.0,0.0,0.0))
        elif data_type == "RTC.TimedGeometry3D":
            return RTC.TimedGeometry3D(RTC.Time(0,0), RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)))
        elif data_type == "RTC.TimedCovariance3D":
            return RTC.TimedCovariance3D(RTC.Time(0,0), RTC.Covariance3D(*([0.0]*21)))
        elif data_type == "RTC.TimedSpeedHeading3D":
            return RTC.TimedSpeedHeading3D(RTC.Time(0,0), RTC.SpeedHeading3D(0.0, RTC.Orientation3D(0.0,0.0,0.0)))
        elif data_type == "RTC.TimedOAP":
            return RTC.TimedOAP(RTC.Time(0,0), RTC.OAP(*([RTC.Vector3D(0.0,0.0,0.0)]*3)))
        elif data_type == "RTC.Quaternion":
            return RTC.Quaternion(*([0.0]*4))
        elif data_type == "RTC.TimedQuaternion":
            return RTC.TimedQuaternion(RTC.Time(0,0), RTC.Quaternion(*([0.0]*4)))
        elif data_type == "RTC.ActArrayActuatorPos":
            return RTC.ActArrayActuatorPos(RTC.Time(0,0), 0, 0.0)
        elif data_type == "RTC.ActArrayActuatorSpeed":
            return RTC.ActArrayActuatorSpeed(RTC.Time(0,0), 0, 0.0)
        elif data_type == "RTC.ActArrayActuatorCurrent":
            return RTC.ActArrayActuatorCurrent(RTC.Time(0,0), 0, 0.0)
        elif data_type == "RTC.Actuator":
            return RTC.Actuator(0.0,0.0,0.0,0.0, RTC.ACTUATOR_STATUS_IDLE)
        elif data_type == "RTC.ActArrayState":
            return RTC.ActArrayState(RTC.Time(0,0), [])
        elif data_type == "RTC.ActArrayActuatorGeometry":
            return RTC.ActArrayActuatorGeometry(RTC.ACTARRAY_ACTUATORTYPE_LINEAR, 0.0, RTC.Orientation3D(0.0,0.0,0.0), RTC.Vector3D(0.0,0.0,0.0), 0.0, 0.0, 0.0, 0.0, False)
        elif data_type == "RTC.ActArrayGeometry":
            return RTC.ActArrayGeometry(RTC.TimedGeometry3D(RTC.Time(0,0), RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), []))
        elif data_type == "RTC.BumperGeometry":
            return RTC.BumperGeometry(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0), 0.0)
        elif data_type == "RTC.BumperArrayGeometry":
            return RTC.BumperArrayGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), [])
        elif data_type == "RTC.CameraImage":
            return RTC.CameraImage(RTC.Time(0,0), 0,0,0,"",0.0,"")
        elif data_type == "RTC.CameraInfo":
            return RTC.CameraInfo(RTC.Vector2D(0.0,0.0), RTC.Point2D(0.0,0.0), 0.0,0.0,0.0,0.0)
        elif data_type == "RTC.FiducialInfo":
            return RTC.FiducialInfo(0, RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0), RTC.Size3D(0.0,0.0,0.0))
        elif data_type == "RTC.Fiducials":
            return RTC.Fiducials(RTC.Time(0,0), [])
        elif data_type == "RTC.FiducialFOV":
            return RTC.FiducialFOV(0.0,0.0,0.0)
        elif data_type == "RTC.GPSTime":
            return RTC.GPSTime(0,0)
        elif data_type == "RTC.GPSData":
            return RTC.GPSData(RTC.Time(0,0), RTC.GPSTime(0,0), 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0, RTC.GPS_FIX_NONE)
        elif data_type == "RTC.GripperState":
            return RTC.GripperState(RTC.Time(0,0), RTC.GRIPPER_STATE_UNKNOWN)
        elif data_type == "RTC.INSData":
            return RTC.INSData(RTC.Time(0,0), 0.0,0.0,0.0,0.0, RTC.Velocity3D(*([0.0]*6)), RTC.Orientation3D(0.0,0.0,0.0))
        elif data_type == "RTC.LimbState":
            return RTC.LimbState(RTC.Time(0,0), RTC.OAP(*([RTC.Vector3D(0.0,0.0,0.0)]*3)), RTC.LIMB_STATUS_IDLE)
        elif data_type == "RTC.Hypothesis2D":
            return RTC.Hypothesis2D(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Covariance2D(*([0.0]*6)), 0.0)
        elif data_type == "RTC.Hypotheses2D":
            return RTC.Hypotheses2D(RTC.Time(0,0), [])
        elif data_type == "RTC.Hypothesis3D":
            return RTC.Hypothesis3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Covariance3D(*([0.0]*21)), 0.0)
        elif data_type == "RTC.Hypotheses3D":
            return RTC.Hypotheses3D(RTC.Time(0,0), [RTC.Hypothesis3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Covariance3D(*([0.0]*21)), 0.0)])
        elif data_type == "RTC.OGMapConfig":
            return RTC.OGMapConfig(0.0,0.0,0,0, RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0))
        elif data_type == "RTC.OGMapTile":
            return RTC.OGMapTile(0,0,0,0,"")
        elif data_type == "RTC.PointFeature":
            return RTC.PointFeature(0.0, RTC.Point2D(0.0,0.0), RTC.PointCovariance2D(0.0,0.0,0.0))
        elif data_type == "RTC.PoseFeature":
            return RTC.PoseFeature(0.0, RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), RTC.Covariance2D(*([0.0]*6)))
        elif data_type == "RTC.LineFeature":
            return RTC.LineFeature(0.0,0.0,0.0, RTC.PointCovariance2D(0.0,0.0,0.0), RTC.Point2D(0.0,0.0), RTC.Point2D(0.0,0.0), False, False)
        elif data_type == "RTC.Features":
            return RTC.Features(RTC.Time(0,0), [],[],[])
        elif data_type == "RTC.MultiCameraImages":
            return RTC.MultiCameraImages(RTC.Time(0,0), [])
        elif data_type == "RTC.MulticameraGeometry":
            return RTC.MulticameraGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), [RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0))])
        elif data_type == "RTC.Waypoint2D":
            return RTC.Waypoint2D(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), 0.0,0.0, RTC.Time(0,0), RTC.Velocity2D(0.0,0.0,0.0))
        elif data_type == "RTC.Path2D":
            return RTC.Path2D(RTC.Time(0,0), [RTC.Waypoint2D(RTC.Pose2D(RTC.Point2D(0.0,0.0), 0.0), 0.0,0.0, RTC.Time(0,0), RTC.Velocity2D(0.0,0.0,0.0))])
        elif data_type == "RTC.Waypoint3D":
            return RTC.Waypoint3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), 0.0,0.0, RTC.Time(0,0), RTC.Velocity3D(*([0.0]*6)))
        elif data_type == "RTC.Path3D":
            return RTC.Path3D(RTC.Time(0,0), [])
        elif data_type == "RTC.PointCloudPoint":
            return RTC.PointCloudPoint(RTC.Point3D(0.0,0.0,0.0), RTC.RGBColour(0.0,0.0,0.0))
        elif data_type == "RTC.PointCloud":
            return RTC.PointCloud(RTC.Time(0,0), [])
        elif data_type == "RTC.PanTiltAngles":
            return RTC.PanTiltAngles(RTC.Time(0,0), 0.0,0.0)
        elif data_type == "RTC.RangerGeometry":
            return RTC.RangerGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), [])
        elif data_type == "RTC.RangerConfig":
            return RTC.RangerConfig(*([0.0]*7))
        elif data_type == "RTC.RangeData":
            return RTC.RangeData(RTC.Time(0,0), [], RTC.RangerGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), []), RTC.RangerConfig(*([0.0]*7)))
        elif data_type == "RTC.IntensityData":
            return RTC.IntensityData(RTC.Time(0,0), [], RTC.RangerGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0,0.0,0.0), RTC.Orientation3D(0.0,0.0,0.0)), RTC.Size3D(0.0,0.0,0.0)), []), RTC.RangerConfig(*([0.0]*7)))
        elif data_type == "Img.ImageData":
            return Img.ImageData(0,0, Img.CF_UNKNOWN, "")
        elif data_type == "Img.CameraIntrinsicParameter":
            return Img.CameraIntrinsicParameter([0.0]*5, [])
        elif data_type == "Img.CameraImage":
            return Img.CameraImage(RTC.Time(0,0), Img.ImageData(0,0, Img.CF_UNKNOWN, ""), Img.CameraIntrinsicParameter([0.0]*5, []), [[0.0]*4]*4)
        elif data_type == "Img.TimedCameraImage":
            return Img.TimedCameraImage(RTC.Time(0,0), Img.CameraImage(RTC.Time(0,0), Img.ImageData(0,0, Img.CF_UNKNOWN, ""), Img.CameraIntrinsicParameter([0.0]*5, []), [[0.0]*4]*4), 0)
        elif data_type == "Img.MultiCameraImage":
            return Img.MultiCameraImage([],0)
        elif data_type == "Img.TimedMultiCameraImage":
            return Img.TimedMultiCameraImage(RTC.Time(0,0), Img.MultiCameraImage([],0), 0)
        elif data_type == "Img.NamedValue":
            return Img.NamedValue("","")
        elif data_type == "Img.CameraDeviceProfile":
            return Img.CameraDeviceProfile("","",0,"","",Img.CameraIntrinsicParameter([0.0]*5, []),[])
        else:
            return None
