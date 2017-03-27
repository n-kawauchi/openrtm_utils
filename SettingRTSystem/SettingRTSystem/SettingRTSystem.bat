set SettingRTSystemPath=%~dp0
python "%SettingRTSystemPath%\startNamingService.py"
set SettingRTSystemWorkspace=%TMP%\SettingRTSystemWorkspace\
IF NOT EXIST "%SettingRTSystemWorkspace%" (
	mkdir "%SettingRTSystemWorkspace%"
) 
cd "%SettingRTSystemWorkspace%"
copy "%SettingRTSystemPath%\workspace\rtc.conf" rtc.conf
start "" "%SettingRTSystemPath%runManager.bat"
python "%SettingRTSystemPath%SettingRTSystem.py" -f rtc.conf
