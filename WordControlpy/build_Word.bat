cd /d %~dp0
set WorkDir=%~dp0

set WordControlpy=WordControlpy
set WordControlpy_Copy=WordControlpy_Copy
set Tool_Copy=python_dist
set Tool_Dir_Name=python_dist

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



mkdir %WordControlpy_Copy%
mkdir %WordControlpy_Copy%\python_dist




IF NOT EXIST "%Tool_Copy%" (
	mkdir %Tool_Copy%
)




xcopy /y/q %WordControlpy%\dist\WordControlpy.exe %WordControlpy_Copy%\python_dist\
xcopy /y/q %WordControlpy%\dist\WordControlpy.lib %WordControlpy_Copy%\python_dist\


xcopy /y/q %WordControlpy%\dist\*.pyd %Tool_Copy%\
xcopy /y/q %WordControlpy%\dist\*.dll %Tool_Copy%\
