cd /d %~dp0
set WorkDir=%~dp0

set RTCDT=RTCDT
set RTCDT_Copy=utils\RTCDT
set Tool_Copy=utils\python_dist
set GLOBAL_Tool_Copy=..\python_dist\utils\python_dist

if not DEFINED PACKAGE_DIRECTORIY set PACKAGE_DIRECTORIY="C:\workspace\site-packages"


cd %RTCDT%

IF EXIST "dist" (
	rmdir /s/q dist
)

xcopy /y/q/e %PACKAGE_DIRECTORIY%\wasanbon\core\plugins\admin\rtcprofile_plugin .\rtcprofile_plugin\
xcopy /y/q/e %PACKAGE_DIRECTORIY%\wasanbon .\wasanbon\


python setup.py py2exe



cd %WorkDir%

IF EXIST "%RTCDT_Copy%" (
	rmdir /s/q %RTCDT_Copy%
)

IF EXIST "%Tool_Copy%" (
	rmdir /s/q %Tool_Copy%
)



mkdir %RTCDT_Copy%
mkdir %Tool_Copy%

IF NOT EXIST "%GLOBAL_Tool_Copy%" (
	mkdir %GLOBAL_Tool_Copy%
)

xcopy /y/q %RTCDT%\RTCDT.bat %RTCDT_Copy%\

xcopy /y/q %RTCDT%\dist\RTCDT.exe %Tool_Copy%\
xcopy /y/q %RTCDT%\dist\RTCDT.lib %Tool_Copy%\


xcopy /y/q %RTCDT%\dist\*.pyd %GLOBAL_Tool_Copy%\
xcopy /y/q %RTCDT%\dist\*.dll %GLOBAL_Tool_Copy%\

