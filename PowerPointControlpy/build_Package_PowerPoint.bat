cd /d %~dp0


set PKG_NAME=100
set TARGET_NAME=PowerPointControlpy
set ARCH=x86
set PYTHON_DIR=C:\Python27

set TARGET_DIR=utils

copy ..\getGuid.bat getGuid.bat
copy ..\wxsmaker.py wxsmaker.py
copy ..\build_wix_module.bat build_wix_module.bat
copy ..\getGuid.bat getGuid.bat
copy ..\empty_prg_menu.wxs empty_prg_menu.wxs
copy ..\uuid_gen.py uuid_gen.py
copy ..\msm_template.wxs msm_template.wxs


call getGuid.bat %TARGET_NAME%_%PKG_NAME%_%ARCH%_Msm PowerPointControlpy_guids.txt



wxsmaker.py -i -t %TARGET_DIR% -o %TARGET_NAME%_%PKG_NAME%_files.wxs


set MSM_VER=%TARGET_NAME%_%PKG_NAME%_%ARCH%
set TARGET_VERSION=1.0.0.0
set MSM_GUID=%GUID%

set MSM_FILE_NAME=%MSM_VER%.msm
build_wix_module.bat %MSM_FILE_NAME%

