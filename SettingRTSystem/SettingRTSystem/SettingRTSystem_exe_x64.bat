set PythonDistPath=.\
set ARCH=x64
set VC_VERSION=vc14
set OMNI_VERSION=4.2.1
PATH=%PATH%;%RTM_ROOT%bin\%VC_VERSION%;%RTM_ROOT%omniORB\%OMNI_VERSION%_%VC_VERSION%\bin\x86_win32;%OpenCV_DIR%\%ARCH%\%VC_VERSION%\bin;C:\Python27;C:\Python27\Scripts;
set TOOLEXE=TRUE
set SettingRTSystemPath=%~dp0
python "%SettingRTSystemPath%\startNamingService.py"
set SettingRTSystemWorkspace=%TMP%\SettingRTSystemWorkspace\
IF NOT EXIST "%SettingRTSystemWorkspace%" (
	mkdir "%SettingRTSystemWorkspace%"
) 
cd "%SettingRTSystemWorkspace%"
copy "%SettingRTSystemPath%\workspace\rtc.conf" rtc.conf
start "" "%SettingRTSystemPath%runManager.bat"
"%RTM_ROOT%utils\python_dist\SettingRTSystem.exe" -f rtc.conf
