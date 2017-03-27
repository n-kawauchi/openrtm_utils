#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file CopyComponent.py
#   @brief コンポーネントコピー自動化ツール

import os
import glob
import shutil
#import re

def main():
    setting_dir = os.environ["SettingRTSystem"]
    install_dir = os.environ["SettingRTSystem_Copy"]
    components = "Components"

    install_comp_dir = os.path.join(install_dir, components)
    if os.path.exists(install_comp_dir):
        shutil.rmtree(install_comp_dir)
    os.makedirs(install_comp_dir)
    
    files = glob.glob(os.path.join(setting_dir, components, "*"))
    for file in files:
        if os.path.isdir(file):
            xml_file = os.path.join(file, "RTC.xml")
            rtc_dir = os.path.join(install_comp_dir, os.path.basename(file))
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
                    if ext == ".exe":
                        if comp_name.find("Comp") >= 1 or comp_name.find("comp") >= 1:
                            shutil.copyfile(comp_file_path, os.path.join(rtc_dir, comp_file))
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
