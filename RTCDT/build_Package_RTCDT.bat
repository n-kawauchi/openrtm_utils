cd /d %~dp0

if not defined INSTALL_VERSION set INSTALL_VERSION=1.2.0
if not defined TOOL_VERSION set TOOL_VERSION=010
if not defined TARGET_VERSION set TARGET_VERSION=0.1.0.0

if not defined ARCH set ARCH=x86
if not defined PYTHON_DIR set PYTHON_DIR=C:\Python27

set PKG_NAME=RTCDT
set TARGET_NAME=%PKG_NAME%_%TOOL_VERSION%




set TARGET_DIR=utils

copy ..\getGuid.bat getGuid.bat
copy ..\wxsmaker.py wxsmaker.py
copy ..\build_wix_module.bat build_wix_module.bat
copy ..\getGuid.bat getGuid.bat
rem copy ..\empty_prg_menu.wxs empty_prg_menu.wxs
copy ..\uuid_gen.py uuid_gen.py
copy ..\msm_template.wxs msm_template.wxs

xcopy /y/q start-RTCDT.vbs utils\RTCDT\
xcopy /y/q start-RTCDT.vbs.wxsctrl utils\RTCDT\



call getGuid.bat %PKG_NAME%_%TOOL_VERSION%_%ARCH%_Msm %PKG_NAME%_guids.txt



wxsmaker.py -i -t %TARGET_DIR% -p %PKG_NAME% -o %TARGET_NAME%_%PKG_NAME%_files.wxs


set MSM_VER=%PKG_NAME%_%TOOL_VERSION%_%ARCH%

set MSM_GUID=%GUID%

set MSM_FILE_NAME=%MSM_VER%.msm
build_wix_module.bat %MSM_FILE_NAME%
