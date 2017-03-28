cd /d %~dp0
set WorkDir=%~dp0

set PowerPointControlpy=PowerPointControlpy
set PowerPointControlpy_Copy=PowerPointControlpy_Copy
set Tool_Copy=python_dist
set Tool_Dir_Name=python_dist

cd %PowerPointControlpy%

IF EXIST "dist" (
	rmdir /s/q dist
)
cmd /c idlcompile.bat
python setup.py py2exe



cd %WorkDir%

IF EXIST "%PowerPointControlpy_Copy%" (
	rmdir /s/q %PowerPointControlpy_Copy%
)



mkdir %PowerPointControlpy_Copy%
mkdir %PowerPointControlpy_Copy%\python_dist




IF NOT EXIST "%Tool_Copy%" (
	mkdir %Tool_Copy%
)




xcopy /y/q %PowerPointControlpy%\dist\PowerPointControlpy.exe %PowerPointControlpy_Copy%\python_dist\
xcopy /y/q %PowerPointControlpy%\dist\PowerPointControlpy.lib %PowerPointControlpy_Copy%\python_dist\


xcopy /y/q %PowerPointControlpy%\dist\*.pyd %Tool_Copy%\
xcopy /y/q %PowerPointControlpy%\dist\*.dll %Tool_Copy%\


