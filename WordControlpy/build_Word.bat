cd /d %~dp0
set WorkDir=%~dp0

set WordControlpy=WordControlpy
set WordControlpy_Copy=utils\WordControlpy
set Tool_Copy=utils\python_dist
set GLOBAL_Tool_Copy=..\python_dist\utils\python_dist

cd %WordControlpy%

IF EXIST "dist" (
	rmdir /s/q dist
)
cmd /c idlcompile.bat
python setup.py py2exe



cd %WorkDir%

IF EXIST "%WordControlpy_Copy%" (
	rmdir /s/q %WordControlpy_Copy%
)

IF EXIST "%Tool_Copy%" (
	rmdir /s/q %Tool_Copy%
)


mkdir %WordControlpy_Copy%
mkdir %Tool_Copy%




IF NOT EXIST "%GLOBAL_Tool_Copy%" (
	mkdir %GLOBAL_Tool_Copy%
)




xcopy /y/q %WordControlpy%\WordControlpy.bat %WordControlpy_Copy%\
xcopy /y/q %WordControlpy%\rtc.conf %WordControlpy_Copy%\
xcopy /y/q %WordControlpy%\WordControlpy.conf %WordControlpy_Copy%\

xcopy /y/q %WordControlpy%\dist\WordControlpy.exe %Tool_Copy%\
xcopy /y/q %WordControlpy%\dist\WordControlpy.lib %Tool_Copy%\


xcopy /y/q %WordControlpy%\dist\*.pyd %GLOBAL_Tool_Copy%\
xcopy /y/q %WordControlpy%\dist\*.dll %GLOBAL_Tool_Copy%\
