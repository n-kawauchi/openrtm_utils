cd /d %~dp0
set WorkDir=%~dp0

set ExcelControlpy=ExcelControlpy
set ExcelControlpy_Copy=utils\ExcelControlpy
set Tool_Copy=utils\python_dist
set GLOBAL_Tool_Copy=..\python_dist\utils\python_dist


cd %ExcelControlpy%

IF EXIST "dist" (
	rmdir /s/q dist
)
python setup.py py2exe



cd %WorkDir%

IF EXIST "%ExcelControlpy_Copy%" (
	rmdir /s/q %ExcelControlpy_Copy%
)


IF EXIST "%Tool_Copy%" (
	rmdir /s/q %Tool_Copy%
)


mkdir %ExcelControlpy_Copy%
mkdir %Tool_Copy%




IF NOT EXIST "%GLOBAL_Tool_Copy%" (
	mkdir %GLOBAL_Tool_Copy%
)



xcopy /y/q %ExcelControlpy%\ExcelControlpy.bat %ExcelControlpy_Copy%\
xcopy /y/q %ExcelControlpy%\rtc.conf %ExcelControlpy_Copy%\
xcopy /y/q %ExcelControlpy%\ExcelControlpy0.conf %ExcelControlpy_Copy%\


xcopy /y/q %ExcelControlpy%\dist\ExcelControlpy.exe %Tool_Copy%\
xcopy /y/q %ExcelControlpy%\dist\ExcelControlpy.lib %Tool_Copy%\


xcopy /y/q %ExcelControlpy%\dist\*.pyd %GLOBAL_Tool_Copy%\
xcopy /y/q %ExcelControlpy%\dist\*.dll %GLOBAL_Tool_Copy%\

