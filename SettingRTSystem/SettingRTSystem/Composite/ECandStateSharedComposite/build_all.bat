cd /d %~dp0
cmake ./ -G "%VC%" -D CMAKE_INSTALL_PREFIX="C:/OpenRTM-aist" ./
cmake --build . --config %BuildType%
