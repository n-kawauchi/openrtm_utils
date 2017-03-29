set SettingRTSystemPath=%~dp0
PATH=%PATH%;%RTM_ROOT%bin\vc14;%RTM_ROOT%omniORB\4.2.1_vc14\bin\x86_win32;%OpenCV_DIR%\x86\v14\bin;
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
