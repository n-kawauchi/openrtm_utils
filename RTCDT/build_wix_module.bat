@echo off
@rem ================================================================
@rem Merge Module build common script
@rem
@rem run candle.exe and light.exe
@rem
@rem following file name is fixed.
@rem    msm_template.wxs, empty_prg_menu.wxs
@rem ================================================================

@set WiX_BIN_DIR="%WIX%bin\"

@if not "%1" == ""  @set MSM_FILE_NAME=%1
@if "%MSM_FILE_NAME%" == ""  goto end

@if exist %PKG_NAME%_prg_menu.wxs (set MENU_WXS=%PKG_NAME%_prg_menu.wxs ) ELSE (set MENU_WXS=empty_prg_menu.wxs ) 
@if exist msm_template.wixobj del msm_template.wixobj

if "%ARCH%" == "x86" (
  %WiX_BIN_DIR%candle.exe msm_template.wxs
) else (
  %WiX_BIN_DIR%candle.exe -arch x64 msm_template.wxs
)
%WiX_BIN_DIR%light.exe -o %MSM_FILE_NAME% msm_template.wixobj

:end

@echo on