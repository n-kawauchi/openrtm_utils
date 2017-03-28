// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file MoveServiceSkel.h 
 * @brief MoveService server skeleton header wrapper code
 * @date Fri Mar 24 17:17:10 2017 
 *
 */

#ifndef _MOVESERVICESKEL_H
#define _MOVESERVICESKEL_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "MoveServiceC.h"
#  include "MoveServiceS.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "MoveService.hh"
#elif defined ORB_IS_MICO
#  include "MoveService.h"
#elif defined ORB_IS_ORBIT2
#  include "/MoveService-cpp-stubs.h"
#  include "/MoveService-cpp-skels.h"
#elif defined ORB_IS_RTORB
#  include "MoveService.h"
#else
#  error "NO ORB defined"
#endif

#endif // _MOVESERVICESKEL_H
