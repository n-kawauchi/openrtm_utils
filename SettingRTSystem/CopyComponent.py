#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file CopyComponent.py
#   @brief コンポーネントコピー自動化ツール

import os
import glob
import shutil
#import re



if "ARCH" in os.environ:
	arch = os.environ["ARCH"]
else:
	arch = "x86"


if "VC_VERSION" in os.environ:
	vc_version = os.environ["VC_VERSION"]
else:
	vc_version = "vc14"


if "OMNI_VERSION" in os.environ:
	omni_version = os.environ["OMNI_VERSION"]
else:
	omni_version = "4.2.1"


openrtmDllPath = "%RTM_ROOT%bin\\"+vc_version
omniORBDllPath = "%RTM_ROOT%omniORB\\"+omni_version+"_"+vc_version+"\\bin\\x86_win32"
openCVDllPath = "%OpenCV_DIR%\\"+arch+"\\"+vc_version+"\\bin"
globalDllPath = "%RTM_ROOT%utils\\SettingRTSystem\\DLL"


def main():
    setting_dir = os.environ["SettingRTSystem"]
    install_dir = os.environ["SettingRTSystem_Copy"]
    components = "Components"
    componentsStart = "ComponentsStart"

    install_comp_dir = os.path.join(install_dir, components)
    shortcut_comp_dir = os.path.join(install_dir, componentsStart)
    if os.path.exists(install_comp_dir):
        shutil.rmtree(install_comp_dir)
    os.makedirs(install_comp_dir)
    
    if os.path.exists(shortcut_comp_dir):
        shutil.rmtree(shortcut_comp_dir)
    os.makedirs(shortcut_comp_dir)
    
    files = glob.glob(os.path.join(setting_dir, components, "*"))
    for file in files:
        if os.path.isdir(file):
            xml_file = os.path.join(file, "RTC.xml")
            file_basename = os.path.basename(file)
            rtc_dir = os.path.join(install_comp_dir, file_basename)
            if not os.path.exists(rtc_dir):
                os.mkdir(rtc_dir)
            if os.path.exists(xml_file):
                shutil.copyfile(xml_file,  os.path.join(rtc_dir, "RTC.xml"))
            conf_files = glob.glob(os.path.join(file, "*.conf"))
            for conf_file in conf_files:
                shutil.copyfile(conf_file, os.path.join(rtc_dir, os.path.basename(conf_file)))
            for comp_root, comp_dirs, comp_files in os.walk(file):
                for comp_file in comp_files:
                    comp_name, ext = os.path.splitext(comp_file)
                    comp_file_path = os.path.join(comp_root, comp_file)
                    script_name = os.path.join(shortcut_comp_dir, comp_name)
                    pathsetcmd = "set PATH=" + openrtmDllPath+";"+omniORBDllPath+";"+openCVDllPath+";"+globalDllPath+ + ";"+"%PATH%"+";C:\\Python27;C:\\Python27\\Scripts"+ ";\n"
                    globalpath = "%RTM_ROOT%utils\\SettingRTSystem\\Components\\" + file_basename
                    if ext == ".exe":
                        if comp_name.find("Comp") >= 1 or comp_name.find("comp") >= 1:
                            shutil.copyfile(comp_file_path, os.path.join(rtc_dir, comp_file))
                            with open(script_name, "w"):
                                f.write("cd /d %~dp0\n")
                                f.write(pathsetcmd)
                                f.write(globalpath + "\\" + comp_name)
                                
                    elif ext == ".dll":
                        shutil.copyfile(comp_file_path, os.path.join(rtc_dir, comp_file))
                    elif ext == ".py":
                        if comp_name == "__init__":
                            mod_path = os.path.relpath(comp_root, file)
                            mod_install_dir = os.path.join(rtc_dir, mod_path)
                            if not os.path.exists(mod_install_dir):
                                os.makedirs(mod_install_dir)
                            shutil.copyfile(comp_file_path, os.path.join(mod_install_dir, comp_file))
                            
                        else:
                            shutil.copyfile(comp_file_path, os.path.join(rtc_dir, comp_file))
                    #print os.path.join(comp_root, comp_file)
                #
                
    
    
if __name__ == "__main__":
    main()
