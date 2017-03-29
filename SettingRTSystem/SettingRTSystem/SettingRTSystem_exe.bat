set PythonDistPath=.\
PATH=%PATH%;%RTM_ROOT%bin\vc14;%RTM_ROOT%omniORB\4.2.1_vc14\bin\x86_win32
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
