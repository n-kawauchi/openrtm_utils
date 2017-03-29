cd /d %~dp0
set WorkDir=%~dp0

set PowerPointControlpy=PowerPointControlpy
set PowerPointControlpy_Copy=utils\PowerPointControlpy
set Tool_Copy=utils\python_dist
set GLOBAL_Tool_Copy=..\python_dist\utils\python_dist

cd %PowerPointControlpy%

IF EXIST "dist" (
	rmdir /s/q dist
)

python setup.py py2exe



cd %WorkDir%


IF EXIST "%PowerPointControlpy_Copy%" (
	rmdir /s/q %PowerPointControlpy_Copy%
)

IF EXIST "%Tool_Copy%" (
	rmdir /s/q %Tool_Copy%
)



mkdir %PowerPointControlpy_Copy%
mkdir %Tool_Copy%




IF NOT EXIST "%GLOBAL_Tool_Copy%" (
	mkdir %GLOBAL_Tool_Copy%
)


xcopy /y/q %PowerPointControlpy%\PowerPointControlpy.bat %PowerPointControlpy_Copy%\
xcopy /y/q %PowerPointControlpy%\rtc.conf %PowerPointControlpy_Copy%\
xcopy /y/q %PowerPointControlpy%\PowerPointControlpy.conf %PowerPointControlpy_Copy%\


xcopy /y/q %PowerPointControlpy%\dist\PowerPointControlpy.exe %Tool_Copy%\
xcopy /y/q %PowerPointControlpy%\dist\PowerPointControlpy.lib %Tool_Copy%\


xcopy /y/q %PowerPointControlpy%\dist\*.pyd %GLOBAL_Tool_Copy%\
xcopy /y/q %PowerPointControlpy%\dist\*.dll %GLOBAL_Tool_Copy%\


