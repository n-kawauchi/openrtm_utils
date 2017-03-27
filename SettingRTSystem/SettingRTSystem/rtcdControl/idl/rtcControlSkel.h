// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file rtcControlSkel.h 
 * @brief rtcControl server skeleton header wrapper code
 * @date Mon Mar 27 16:37:07 2017 
 *
 */

#ifndef _RTCCONTROLSKEL_H
#define _RTCCONTROLSKEL_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "rtcControlC.h"
#  include "rtcControlS.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "rtcControl.hh"
#elif defined ORB_IS_MICO
#  include "rtcControl.h"
#elif defined ORB_IS_ORBIT2
#  include "/rtcControl-cpp-stubs.h"
#  include "/rtcControl-cpp-skels.h"
#elif defined ORB_IS_RTORB
#  include "rtcControl.h"
#else
#  error "NO ORB defined"
#endif

#endif // _RTCCONTROLSKEL_H
