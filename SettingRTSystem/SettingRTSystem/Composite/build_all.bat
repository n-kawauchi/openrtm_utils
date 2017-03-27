cd /d %~dp0
set VC="Visual Studio 12 2013"
set BuildType=Release
set EIGEN_DIRECTORIY="C:\eigen-eigen-07105f7124f9"
set ODE_DIRECTORIY="C:\ode-0.13"
set QWT_DIRECTORIY="C:\workspace\Qwt"
set LUABIND_PATH="C:\workspace\luabind-0.9.1"

cmd /c ECandStateSharedComposite\build_all.bat
