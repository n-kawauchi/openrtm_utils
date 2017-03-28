cd /d %~dp0
if not DEFINED VC set VC="Visual Studio 12 2013"
if not DEFINED BuildType set BuildType=Release
if not DEFINED LUABIND_PATH set LUABIND_PATH="C:\workspace\luabind-0.9.1"
if not DEFINED EIGEN_DIRECTORIY set EIGEN_DIRECTORIY="C:\workspace\eigen-eigen-07105f7124f9"
if not DEFINED ODE_DIRECTORIY set ODE_DIRECTORIY="C:\workspace\ode-0.13"
if not DEFINED QWT_DIRECTORIY set QWT_DIRECTORIY="C:\workspace\Qwt"
if not DEFINED BOOST_DIRECTORIY set BOOST_DIRECTORIY="C:\boost_1_49_0"

cmd /c Components\build_all.bat
cmd /c ExecutionContext\build_all.bat
cmd /c Composite\build_all.bat
cmd /c Manager\Cpp\build_all.bat
cmd /c rtcdControl\build_all.bat
cmd /c RTCD_IDL\idlcompile.bat
cmd /c rtcdControlPy\idlcompile.bat


