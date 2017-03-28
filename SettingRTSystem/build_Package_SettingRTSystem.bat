cd /d %~dp0


set PKG_NAME=020
set TARGET_NAME=SettingRTSystem
if not DEFINED ARCH set ARCH=x86
if not DEFINED PYTHON_DIR set PYTHON_DIR=C:\Python27

set TARGET_DIR=SettingRTSystem_Copy


call getGuid.bat %TARGET_NAME%_%PKG_NAME%_%ARCH%_Msm RTCDT_guids.txt



wxsmaker.py -i -t %TARGET_DIR% -o %TARGET_NAME%_%PKG_NAME%_files.wxs


set MSM_VER=%TARGET_NAME%_%PKG_NAME%_%ARCH%
set TARGET_VERSION=0.2.0.0
set MSM_GUID=%GUID%

set MSM_FILE_NAME=%MSM_VER%.msm
build_wix_module.bat %MSM_FILE_NAME%
