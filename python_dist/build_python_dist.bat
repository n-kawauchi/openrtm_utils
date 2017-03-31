cd /d %~dp0
set WorkDir=%~dp0

set UTIL_DIR=utils\python_dist
set Licenses_DIR=Licenses

IF NOT EXIST "%UTIL_DIR%" (
	mkdir %UTIL_DIR%
)

xcopy /D/S/R/Y/I/K %Licenses_DIR% %UTIL_DIR%\%Licenses_DIR%



