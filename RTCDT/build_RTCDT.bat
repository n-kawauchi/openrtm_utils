cd /d %~dp0
set WorkDir=%~dp0

set RTCDT=RTCDT
set RTCDT_Copy=RTCDT_Copy
set Tool_Copy=python_dist
set Tool_Dir_Name=python_dist

cd %RTCDT%

IF EXIST "dist" (
	rmdir /s/q dist
)
python setup.py py2exe

xcopy /y/q C:\Python27\Lib\site-packages\numpy\core\numpy-atlas.dll .

cd %WorkDir%

IF EXIST "%RTCDT_Copy%" (
	rmdir /s/q %RTCDT_Copy%
)



mkdir %RTCDT_Copy%
mkdir %RTCDT_Copy%\python_dist

IF NOT EXIST "%Tool_Copy%" (
	mkdir %Tool_Copy%
)


xcopy /y/q %RTCDT%\dist\RTCDT.exe %RTCDT_Copy%\python_dist\
xcopy /y/q %RTCDT%\dist\RTCDT.lib %RTCDT_Copy%\python_dist\


xcopy /y/q %RTCDT%\dist\*.pyd %Tool_Copy%\
xcopy /y/q %RTCDT%\dist\*.dll %Tool_Copy%\

