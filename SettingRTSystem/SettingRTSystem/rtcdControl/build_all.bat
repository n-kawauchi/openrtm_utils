cd /d %~dp0
cmake ./ -G %VC% -DLUABIND_PATH=%LUABIND_PATH% -D CMAKE_INSTALL_PREFIX="C:/OpenRTM-aist" ./
cmake --build . --config %BuildType%
