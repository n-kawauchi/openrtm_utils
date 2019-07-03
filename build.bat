cd /d %~dp0

if not defined VC_VERSION   set VC_VERSION=14
if not defined ARCH         set ARCH=x86
if not defined RTM_VERSION  set RTM_VERSION=1.2.1

if not defined RTM_ROOT     set RTM_ROOT=C:\src\cxx_123b6b9_190603\OpenRTM-aist_x86
if not defined OpenCV_DIR   set OpenCV_DIR=C:\src\OpenCV_x86\OpenCV3.4

if not defined QTPATH           set QTPATH=C:\Qt\5.13.0\msvc2017
if not defined LUABIND_PATH     set LUABIND_PATH=C:\workspace\luabind-0.9.1
if not defined EIGEN_DIRECTORIY	set EIGEN_DIRECTORIY=C:\workspace\eigen-eigen-323c052e1731
if not defined ODE_DIRECTORIY   set ODE_DIRECTORIY=C:\workspace\ode-0.13
if not defined QWT_DIRECTORIY   set QWT_DIRECTORIY=C:\workspace\qwt-6.1.4
if not defined BOOST_DIRECTORIY	set BOOST_DIRECTORIY=C:\workspace\boost_1_70_0
if not defined LUA_DEV          set LUA_DEV=C:\workspace\lua-5.3.5

set PYTHON_DIR=c:\python27
set MERGE_MODULES_DIR=MergeModules
set COIL_ROOT=%RTM_ROOT%\coil
set OpenRTM_DIR=%RTM_ROOT%\cmake
set OMNI_ROOT=%RTM_ROOT%\omniORB
set BuildType=Release
set PACKAGE_DIRECTORIY=C:\workspace\site-packages

set PATH=%PATH:C:\Program Files (x86)\Lua\5.1\clibs=%
set PATH=%PATH:C:\Program Files (x86)\Lua\5.1=%



set PATH=%LUA_DEV%;%QTPATH%\bin;%RTM_ROOT%\bin;%OMNI_ROOT%\bin\x86_win32;%PYTHON_DIR%;%PATH%;


IF EXIST "%MERGE_MODULES_DIR%" (
	rmdir /s/q %MERGE_MODULES_DIR%
)
mkdir %MERGE_MODULES_DIR%

cmd /c ExcelControlpy\build_Excel.bat
cmd /c ExcelControlpy\build_Package_Excel.bat
xcopy /y/q ExcelControlpy\*.msm %MERGE_MODULES_DIR%\

cmd /c PowerPointControlpy\build_PowerPoint.bat
cmd /c PowerPointControlpy\build_Package_PowerPoint.bat
xcopy /y/q PowerPointControlpy\*.msm %MERGE_MODULES_DIR%\

cmd /c WordControlpy\build_Word.bat
cmd /c WordControlpy\build_Package_Word.bat
xcopy /y/q WordControlpy\*.msm %MERGE_MODULES_DIR%\

cmd /c RTCDT\build_RTCDT.bat
cmd /c RTCDT\build_Package_RTCDT.bat
xcopy /y/q RTCDT\*.msm %MERGE_MODULES_DIR%\

cmd /c SettingRTSystem\build_SettingRTSystem.bat
cmd /c SettingRTSystem\build_Package_SettingRTSystem.bat
xcopy /y/q SettingRTSystem\*.msm %MERGE_MODULES_DIR%\

cmd /c python_dist\build_python_dist.bat
cmd /c python_dist\build_Package_python_dist.bat
xcopy /y/q python_dist\*.msm %MERGE_MODULES_DIR%\