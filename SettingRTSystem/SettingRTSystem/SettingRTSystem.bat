set SettingRTSystemPath=%~dp0
set ARCH=x86
set VC_VERSION=vc14
set OMNI_VERSION=4.2.1
PATH=%PATH%;%RTM_ROOT%bin\%VC_VERSION%;%RTM_ROOT%omniORB\%OMNI_VERSION%_%VC_VERSION%\bin\x86_win32;%OpenCV_DIR%\%ARCH%\%VC_VERSION%\bin;C:\Python27;C:\Python27\Scripts;
set TOOLEXE=FALSE
python "%SettingRTSystemPath%\startNamingService.py"
set SettingRTSystemWorkspace=%TMP%\SettingRTSystemWorkspace\
IF NOT EXIST "%SettingRTSystemWorkspace%" (
	mkdir "%SettingRTSystemWorkspace%"
) 
cd "%SettingRTSystemWorkspace%"
copy "%SettingRTSystemPath%\workspace\rtc.conf" rtc.conf
start "" "%SettingRTSystemPath%runManager.bat"
python "%SettingRTSystemPath%SettingRTSystem.py" -f rtc.conf
