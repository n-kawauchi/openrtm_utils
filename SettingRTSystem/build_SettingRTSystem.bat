cd /d %~dp0
set WorkDir=%~dp0

set SettingRTSystem=SettingRTSystem
set SettingRTSystem_Copy=SettingRTSystem_Copy
set Tool_Copy=python_dist
set Tool_Dir_Name=python_dist

cd %SettingRTSystem%

cmd /c build_all.bat

IF EXIST "dist" (
	rmdir /s/q dist
)

python setup.py py2exe



cd rtcConfSet

IF EXIST "dist" (
 	rmdir /s/q dist
)

 python setup.py py2exe

cd ..


cd %WorkDir%

IF EXIST "%SettingRTSystem_Copy%" (
 	rmdir /s/q %SettingRTSystem_Copy%
)

mkdir %SettingRTSystem_Copy%
mkdir %SettingRTSystem_Copy%\python_dist

IF NOT EXIST "%Tool_Copy%" (
	mkdir %Tool_Copy%
)


xcopy /y/q %SettingRTSystem%\SettingRTSystem_exe.bat %SettingRTSystem_Copy%
xcopy /y/q %SettingRTSystem%\runManager.bat %SettingRTSystem_Copy%
xcopy /y/q %SettingRTSystem%\rtcConfSet_exe.bat %SettingRTSystem_Copy%
xcopy /y/q %SettingRTSystem%\startNamingService.py %SettingRTSystem_Copy%


xcopy /y/q %SettingRTSystem%\Composite\ECandStateSharedComposite\src\Release\ECandStateSharedCompositeComp.exe %SettingRTSystem_Copy%\Composite\ECandStateSharedComposite\Release\
xcopy /y/q %SettingRTSystem%\Composite\ECandStateSharedCompositePy\ECandStateSharedComposite.py %SettingRTSystem_Copy%\Composite\ECandStateSharedCompositePy\ECandStateSharedCompositePy\

xcopy /y/q %SettingRTSystem%\ExecutionContext\MultipleOrderedEC-C++\release\MultipleOrderedEC.dll %SettingRTSystem_Copy%\ExecutionContext\MultipleOrderedEC-C++\release\
xcopy /y/q %SettingRTSystem%\ExecutionContext\MultipleOrderedEC-C++\release\loadLua.lua %SettingRTSystem_Copy%\ExecutionContext\MultipleOrderedEC-C++\release\
xcopy /y/q %SettingRTSystem%\ExecutionContext\MultipleOrderedEC-C++\release\CompList.lua %SettingRTSystem_Copy%\ExecutionContext\MultipleOrderedEC-C++\release\
xcopy /y/q %SettingRTSystem%\ExecutionContext\MultipleOrderedEC-C++\release\rtc.conf %SettingRTSystem_Copy%\ExecutionContext\MultipleOrderedEC-C++\release\
xcopy /y/q %SettingRTSystem%\ExecutionContext\MultipleOrderedEC-Python\* %SettingRTSystem_Copy%\MultipleOrderedEC-Python\
xcopy /y/q %SettingRTSystem%\ExecutionContext\MultipleOrderedEC-Python\images\arrow.png %SettingRTSystem_Copy%\ExecutionContext\MultipleOrderedEC-Python\images\
xcopy /y/q %SettingRTSystem%\ExecutionContext\MultipleOrderedEC-Python\MultipleOrderedEC_Lib\*.py %SettingRTSystem_Copy%\ExecutionContext\MultipleOrderedEC-Python\MultipleOrderedEC_Lib\


xcopy /y/q %SettingRTSystem%\Manager\Cpp\rtcd_p\Release\rtcd_p.exe %SettingRTSystem_Copy%\Manager\Cpp\rtcd_p\Release\
xcopy /y/q %SettingRTSystem%\Manager\Python\* %SettingRTSystem_Copy%\Manager\Python\


xcopy /y/q %SettingRTSystem%\dist\SettingRTSystem.exe %SettingRTSystem_Copy%\python_dist\
xcopy /y/q %SettingRTSystem%\dist\SettingRTSystem.lib %SettingRTSystem_Copy%\python_dist\

xcopy /y/q %SettingRTSystem%\dist\*.pyd %Tool_Copy%\
xcopy /y/q %SettingRTSystem%\dist\*.dll %Tool_Copy%\


xcopy /y/q %SettingRTSystem%\rtcConfSet\dist\rtcConfSet.exe %SettingRTSystem_Copy%\python_dist\
xcopy /y/q %SettingRTSystem%\rtcConfSet\dist\rtcConfSet.lib %SettingRTSystem_Copy%\python_dist\

xcopy /y/q %SettingRTSystem%\rtcConfSet\dist\*.pyd %Tool_Copy%\
xcopy /y/q %SettingRTSystem%\rtcConfSet\dist\*.dll %Tool_Copy%\


xcopy /y/q %SettingRTSystem%\rtcdControl\src\Release\rtcdControlComp.exe %SettingRTSystem_Copy%\rtcdControl\src\Release\

xcopy /y/q %SettingRTSystem%\rtcdControlPy\rtcdControlPy.py %SettingRTSystem_Copy%\rtcdControlPy\
xcopy /y/q %SettingRTSystem%\rtcdControlPy\LoadRTCs.py %SettingRTSystem_Copy%\rtcdControlPy\
xcopy /y/q %SettingRTSystem%\rtcdControlPy\rtcControl_idl.py %SettingRTSystem_Copy%\rtcdControlPy\
xcopy /y/q %SettingRTSystem%\rtcdControlPy\rtcControl\* %SettingRTSystem_Copy%\rtcdControlPy\rtcControl\
xcopy /y/q %SettingRTSystem%\rtcdControlPy\rtcControl__POA\* %SettingRTSystem_Copy%\rtcdControlPy\rtcControl__POA\



xcopy /y/q %SettingRTSystem%\workspace\rtc.conf %SettingRTSystem_Copy%\workspace\



python CopyComponent.py

