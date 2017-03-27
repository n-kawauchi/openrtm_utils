cd /d %~dp0


set PKG_NAME=010
set TARGET_NAME=RTCDT
set ARCH=x86
set PYTHON_DIR=C:\Python27

set TARGET_DIR=RTCDT_Copy


call getGuid.bat %TARGET_NAME%_%PKG_NAME%_%ARCH%_Msm RTCDT_guids.txt



wxsmaker.py -i -t %TARGET_DIR% -o %TARGET_NAME%_%PKG_NAME%_files.wxs


set MSM_VER=%TARGET_NAME%_%PKG_NAME%_%ARCH%
set TARGET_VERSION=0.1.0.0
set MSM_GUID=%GUID%

set MSM_FILE_NAME=%MSM_VER%.msm
build_wix_module.bat %MSM_FILE_NAME%

