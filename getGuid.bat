@echo off

set PYTHONBIN=C:\python27\python.exe
set SCRIPT_DIR=%~dp0

if "%1" == "" goto end
for /f %%n in ('%PYTHONBIN% %SCRIPT_DIR%uuid_gen.py') do @set GUID=%%n
echo %1:%GUID%>> %2

:end
@echo on