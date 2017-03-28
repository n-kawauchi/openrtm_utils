cd /d %~dp0
cmake ./ -G %VC% -DLUABIND_PATH=%LUABIND_PATH% -DBOOST_DIRECTORIY=%BOOST_DIRECTORIY% -D CMAKE_INSTALL_PREFIX="C:/OpenRTM-aist" ./
cmake --build . --config %BuildType%
