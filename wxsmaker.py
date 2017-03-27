#!/usr/bin/env python
# -*- python -*-
# -*- coding: UTF-8 -*-
#
# @brief wxs file generator
# @date $Date$
# @author Norkai Ando <n-ando@aist.go.jp>
#
# Copyright (C) 2014  Noriaki Ando
#     Intelligent Systems Research Institute,
#     National Institute of
#         Advanced Industrial Science and Technology (AIST), Japan
#     All rights reserved.
#
# $Id$
#
#
# Control File Examples:
# dir.wxsctrl: This file should be located a directory
#
# case 1: This element just set a env variable OMNI_ROOT with PATH_TO_DIR.
#   <Environment Id="OMNI_ROOT" Name="OMNI_ROOT" Action="set"
#                System="yes" Value="PATH_TO_DIR" />
#
# case 2: Value can be an ID of a specific directory
#         To refere DIR_ID in Directory entry, use [DIR_ID].
#         This is WiX's rule
#   <Environment Id="OMNI_ROOT" Name="OMNI_ROOT" Action="set"
#                System="yes" Value="[DIR_ID]" />
# This node will appear...
#   <Directory Id="DIR_ID">
#     <Environment .... Value="[DIR_ID]"
#   </Directiry>
# [DIR_ID] will be replaced with "Directory" with Id "DIR_ID" by WiX
#
# case 3 (recommended): '*' in value automatically relaced upper directory ID.
#   <Directory Id="DIR_ID">
#       <Environment Id="OMNI_ROOT" Name="OMNI_ROOT" Action="set"
#                    System="yes" Value="[%Directory.Id%]" />
#   </Directiry>
# --> %Directory.Id% would be replaced with the nearest parent node
#     attribute variable which has name "Directory" and attribute "Id".
#
#
# <filename>.wxsctrl: This control file's node s will be inserted in
#                     the <filename> node
# case 1:
#   <Shortcut Id="%File.Id%" Directory="ExpMenuFolder" Name="catior.exe"
#             Show="normal" WorkingDirectory="CXXexamples" Icon="RTC.ico"
#             IconIndex="0" Arguments=''>
#     <Icon Id="RTC.ico" SourceFile="Bitmaps\RTC.ico"/>
#   </Shortcut>
# This node will appear...
#   <File Id="OmniBinCatior.exe"
#     <Shortcut Id="OmniBinCatior.exe" ...
#       <Icon ...
#     <Shortcut/>
#   </File>
# ---> %File.Id% will be replaced with the parent "File" node's attribute "Id"
#      %File.Id% = OmniBinCatior.exe
#

import sys
import os

#------------------------------------------------------------
# help()
#------------------------------------------------------------
def help():
    print """
Usage:
  %s [OPTIONS]

Options:
  -h, --help                 print this help message

  -i, --include              include mode. Generated file would be
                             wxs include file.
                             
  -n, --root-dir-no-name     root directory name mode. 
                             If root directory represents the same directory 
                             as the parent, specify this option.

  -o, --output={OUTPUT_FILE] specify output file name

  -t, --target=[TARGET_DIR]  specify a target directory to be searched


Examples:
 generating wxs include file under omniORB
    $ %s -i -output omniORB_inc.wxs -t C:\distribution\omniORB-4.1.5-vc10

""" % (sys.argv[0], sys.argv[0])


def check_targetdir(dirname):
    if not os.path.exists(dirname):
        sys.stderr.write("Error: directory %s does not exists. Aborting"
                         % (dirname))
        sys.exit(-1)
    if not os.path.isdir(dirname):
        sys.stderr.write("Error: %s is not directory. Aborting."
                         % (dirname))
        sys.exit(-1)
    return dirname

def check_dirprefix(dir_prefix):
    if os.path.isabs(dir_prefix):
        sys.stderr.write("Error: Given prefix is absolute path.")
        sys.stderr.write("       -p/--prefix only accept relative path.")
        sys.exit(-1)
    return dir_prefix

def check_idprefix(id_prefix):
    import re
    m = re.match("^[a-zA-Z0-9\_\.]+$", id_prefix)
    # m: None -> NG
    if m == None:
        sys.stderr.write("Invalud ID. ID must be consist of [a-zA-Z0-9_.].")
        sys.exit(-1)
    return id_prefix


def tool_main():
    import getopt
    try:
        options, args = getopt.getopt(sys.argv[1:],
                                      'hind:o:p:t:',
                                      ['help',
                                       'dir-prefix=',
                                       'include',
                                       'output=',
                                       'id-prefix=',
                                       'target=',
                                       'root-dir-no-name'])
    except getopt.GetoptError:
        print 'given options are not correct.'
        sys.exit(-1)
    is_include = False
    dir_prefix = ""
    output_file = "default.wxs"
    target_dir = os.path.dirname(sys.argv[0])
    id_prefix = ""
    is_name = True
    for o, a in options:
        # Help message
        if o == "-h" or o == "--help": help(); sys.exit(0)
        # Spefying include mode
        elif o == "-d" or o == "--dir-prefix":
            dir_prefix = check_dirprefix(a)
            continue
        # Spefying include mode
        elif o == "-i" or o == "--include":
            is_include = True
            continue
        # Specifying output file name
        elif o == "-o" or o == "--output":
            output_file = a
            continue
        # Specifying ID prefix
        elif o == "-p" or o == "--id-prefix":
            id_prefix = check_idprefix(a)
            continue
        # Specifying target directory
        elif o == "-t" or o == "--target":
            target_dir = check_targetdir(a)
            continue
        # Spefying root directory name mode
        elif o == "-n" or o == "--root-dir-no-name":
            is_name = False
            continue

        # Unknown
        else:
            print "Unknown option" # never come here
            sys.exit(-1)

    ftree = CreateFileTree(target_dir, output_file,
                           dir_prefix, id_prefix, is_include,
                           is_name)
    ftree.walk()
    ftree.print_xml()

#============================================================
# @class CreatFileTree
#
# This class create file tree XML for WiX wxs format
# with Directory/Component/File nodes
#============================================================
from xml.dom import *
from xml.dom import minidom
from xml.dom.minidom import Document
from xml.dom.minidom import getDOMImplementation
class CreateFileTree():
    def __init__(self, dirname, output_file, dir_prefix = "", id_prefix = "",
                 is_include = True, is_name = True):
        self.doc = Document()
        self.target_dir = os.path.normpath(dirname)
        self.output_file = output_file
        self.dirlist = {}
        self.is_include = is_include
        self.is_name = is_name
        if dir_prefix:
            self.dir_prefix = os.path.normpath(dir_prefix)
        else:
            self.dir_prefix = None
        self.id_prefix = id_prefix
        self.dirid_suffix = "Dir"
        self.compid_suffix = "Comp"
        self.fileid_suffix = "File"
        self.removeid_suffix = "Remove"
        self.parent_dir_id = ""
        self.is_py_exist = False

        self.id_count = 0

        self.prepare_dom()

    def append_prefix(self):
        if not self.dir_prefix:
            return
        path_list = self.dir_prefix.split(os.path.sep)
        path = ""
        for d in path_list:
            path += os.path.sep + d
            element = self.doc.createElement('Directory')
            element.setAttribute('Id', self.to_id(path, 0) + self.dirid_suffix)
            element.setAttribute('Name', d)
            self.dirlist[d] = element
            self.curr_node.appendChild(element)
            self.curr_node = element

    def prepare_dom(self):
        self.curr_node = self.doc
        if self.is_include:
            element = self.doc.createElement('Include')
            element.setAttribute("xmlns",
                                   "http://schemas.microsoft.com/wix/2006/wi")
            self.curr_node.appendChild(element)
            self.curr_node = element

        # dir prefix
        self.append_prefix()
        # root dir
        element = self.doc.createElement('Directory')
        element.setAttribute('Id',
                             self.to_id(self.target_dir, 0) + self.dirid_suffix)
        if self.is_name:
            element.setAttribute('Name', os.path.basename(self.target_dir))
        self.dirlist[self.target_dir] = element
        self.curr_node.appendChild(element)
        self.curr_node = element

    def set_curr_node(self, dirname):
        if self.dirlist.has_key(dirname):
            self.curr_node = self.dirlist[dirname]
        else:
            sys.stderr.write("Unknown directory name %s. Aborting." % (dirname))
            sys.exit(-1)

########################################################
#  Modified by I.Hara  2014/05/01
#  Original code will make warning, because most IDis could be too long.
#  Therefore, I append the second argument to make short IDs.
#
    def to_id(self, dirname, short_id=1):
        dirname = dirname.replace(os.path.dirname(self.target_dir), "")
        if dirname == "":
            sys.stderr.write("Invalid dirname error. Aborting.")
            sys.stderr.write("  target dir: %s" % (self.target_dir))
            sys.stderr.write("  dirname   : %s" % (dirname))
            sys.exit(-1)

	if short_id :
	    self.id_count += 1
	    res = "%s_%04d_" % (self.id_prefix, self.id_count)
	    return res
        else:
            if dirname[0] == os.path.sep:
                dirname = dirname[1:]
            res = self.id_prefix
            for p in dirname.split(os.path.sep):
                res += p[0].upper() + p[1:].lower()
            res = res.replace('-', '_')
            res = res.replace('+', 'x')
            return res

    def append_directory(self, dirname):
        if self.dirlist.has_key(dirname):
            print "already registered?"
            sys.exit(-1)
        element = self.doc.createElement('Directory')
        id = self.to_id(dirname, 0) + self.dirid_suffix
        if len(id) >= 72:
            id = id[len(id)-72:len(id)]
        element.setAttribute('Id', id)
        element.setAttribute('Name', os.path.basename(dirname))
        self.dirlist[dirname] = element
        self.curr_node.appendChild(element)

    def append_component(self, dirname, names):
        import uuid
        comp = self.doc.createElement('Component')
        id = self.to_id(dirname) + self.compid_suffix
        if len(id) >= 72:
            id = id[len(id)-72:len(id)]
        comp.setAttribute('Id', id)
        comp.setAttribute('Guid', str(uuid.uuid1()).upper())
        self.curr_node.appendChild(comp)
        self.curr_node = comp

    def append_file(self, filepath):
        element = self.doc.createElement('File')
        id = self.to_id(filepath) + self.fileid_suffix
        if len(id) >= 72:
            id = id[len(id)-72:len(id)]
        element.setAttribute('Id', id)
        element.setAttribute('Name', os.path.basename(filepath))
        element.setAttribute('DiskId', '1')
        element.setAttribute('Source', filepath)
        self.curr_node.appendChild(element)
        return element
        
    def append_removefile(self, dirname):
        element = self.doc.createElement('RemoveFile')
        id = self.to_id(dirname) + self.removeid_suffix
        if len(id) >= 72:
            id = id[len(id)-72:len(id)]
        element.setAttribute('Id', id)
        element.setAttribute('Directory', self.parent_dir_id)
        element.setAttribute('Name', '*.pyc')
        element.setAttribute('On', 'both')
        self.curr_node.appendChild(element)
        return element

    def append_files(self, files):
        import re
        for f in files:
            fname = os.path.basename(f)
            if re.match(".*\.wxsctrl", fname): continue
            file_element = self.append_file(f)
            ctrlf = f + ".wxsctrl"
            if files.count(ctrlf) > 0: # ctrl file exist
                doc = minidom.parse(ctrlf)
                ele = doc.documentElement.cloneNode(doc.documentElement)
                file_element.appendChild(ele)
                self.replace_variables(ele)

    def dirs_and_files(self, dirname, names):
        dirs = []
        files = []
        self.is_py_exist = False
        for f in names:
            path = dirname + os.path.sep + f
            if os.path.isfile(path):
                files.append(path)

                # If the extension is py, to set the directory ID to add the RemoveFile element. 
                target_path, target_ext = os.path.splitext(path)
                if target_ext == ".py":
                    self.is_py_exist = True
                    id = self.to_id(dirname, 0) + self.dirid_suffix
                    if len(id) >= 72:
                        id = id[len(id)-72:len(id)]
                    self.parent_dir_id = id

            elif os.path.isdir(path):
                dirs.append(path)
            else:
                print "Unknown file type.", f
                os.sys.exit(-1)
        return dirs, files

    def replace_variables(self, node):
        def get_parent_attr_value(node, name, attr):
            if node.nodeName == name:
                return node.getAttribute(attr)
            else:
                return get_parent_attr_value(node.parentNode, name, attr)
        for k in node.attributes.keys():
            attr_var = node.getAttribute(k)
            attr_substr = attr_var.split('%')
            if len(attr_substr) == 3:
                name_attr = attr_substr[1].split('.')
                var = ""
                if len(name_attr) == 2:
                    var += attr_substr[0]
                    var += get_parent_attr_value(node,
                                                 name_attr[0], name_attr[1])
                    var += attr_substr[2]
                    node.setAttribute(k, var)
                else:
                    sys.stderr.write("Warning: %s cannot be splited into two."
                                     % (attr_substr[1]))

    def insert_direlements(self, files):
        import re
        for f in files:
            fname = os.path.basename(f)
########################################################
#   Modified by I.Hara  2014/05/01
#   Find WXSCTRL file.....
#
#            if fname == "dir.wxsctrl":
            if re.match(".*dir\.wxsctrl", fname):
                doc = minidom.parse(f)
                ele = doc.documentElement.cloneNode(doc.documentElement)
                self.curr_node.appendChild(ele)
                self.replace_variables(ele)

    def visitor(self, arg, dirname, names):
        self.set_curr_node(dirname)
        dirs, files = self.dirs_and_files(dirname, names)
        tmp = self.curr_node
        # component element
        if len(files) != 0:
            self.append_component(dirname, names)
        self.insert_direlements(files)
        # file elements
        self.append_files(files)
        # removefile element (*.pyc)
        if self.is_py_exist:
            self.append_removefile(dirname)
        # directory elements
        self.curr_node = tmp
        for d in dirs:
            self.append_directory(d)

    def print_xml(self):
        fd = open(self.output_file, "w")
        fd.write(self.doc.toprettyxml(indent = "    ", encoding = "utf-8"))
        fd.close()

    def walk(self):
        os.path.walk(self.target_dir, self.visitor, "hoge")

#------------------------------------------------------------
# main function
#------------------------------------------------------------
if __name__ == '__main__':
    tool_main()
# end of script
#============================================================