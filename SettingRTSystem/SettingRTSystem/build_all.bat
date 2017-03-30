cd /d %~dp0

if not DEFINED SettingRTSystemPath set SettingRTSystemPath=%~dp0


if not DEFINED VC_VERSION set VC_VERSION=12
if not DEFINED ARCH set ARCH=x86

if %VC_VERSION%==9 (
	if %ARCH% == x86 (
		set VC=Visual Studio 9 2008
	)
) else if %VC_VERSION%==10 (
	if %ARCH% == x86 (
		set VC=Visual Studio 10 2010
	) else (
		set VC=Visual Studio 10 2010 Win64
	)
) else if %VC_VERSION%==11 (
	if %ARCH% == x86 (
		set VC=Visual Studio 11 2012
	) else (
		set VC=Visual Studio 11 2012 Win64
	)
) else if %VC_VERSION%==12 (
	if %ARCH% == x86 (
		set VC=Visual Studio 12 2013
	) else (
		set VC=Visual Studio 12 2013 Win64
	)
) else if %VC_VERSION%==14 (
	if %ARCH% == x86 (
		set VC=Visual Studio 14 2015
	) else (
		set VC=Visual Studio 14 2015 Win64
	)
) else if %VC_VERSION%==15 (
	if %ARCH% == x86 (
		set VC=Visual Studio 15 2017
	) else (
		set VC=Visual Studio 15 2017 Win64
	)
) else (
	set VC=Visual Studio 12 2013
)

if not DEFINED BuildType set BuildType=Release
if not DEFINED LUABIND_PATH set LUABIND_PATH=C:\workspace\luabind-0.9.1
if not DEFINED EIGEN_DIRECTORIY set EIGEN_DIRECTORIY=C:\workspace\eigen-eigen-07105f7124f9
if not DEFINED ODE_DIRECTORIY set ODE_DIRECTORIY=C:\workspace\ode-0.13
if not DEFINED QWT_DIRECTORIY set QWT_DIRECTORIY=C:\workspace\Qwt
if not DEFINED BOOST_DIRECTORIY set BOOST_DIRECTORIY=C:\workspace\boost_1_49_0
if not DEFINED PACKAGE_DIRECTORIY set PACKAGE_DIRECTORIY=C:\workspace\site-packages



cmd /c Components\build_all.bat
cmd /c ExecutionContext\build_all.bat
cmd /c Composite\build_all.bat
cmd /c Manager\Cpp\build_all.bat
cmd /c rtcdControl\build_all.bat
cmd /c RTCD_IDL\idlcompile.bat
cmd /c rtcdControlPy\idlcompile.bat


