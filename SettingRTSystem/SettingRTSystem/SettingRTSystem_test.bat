cd /d %~dp0
python startNamingService.py
start runManager.bat
cd workspace
python ../SettingRTSystem.py -f rtc.conf
pause