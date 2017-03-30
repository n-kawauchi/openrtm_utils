set SettingRTSystemPath=%~dp0
set ARCH=x86
set VC_VERSION=vc14
set OMNI_VERSION=4.2.1
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
