from xml.sax import saxutils,handler
from xml.sax import make_parser
from xml.sax.handler import feature_namespaces
import sys
import shutil
import fileinput
#import os
import glob
import re
import os.path
import datetime

# configuration, containing the global variables
import config

# load command line arguments
import args

# type substitution
import typesubst

# type argument information
from argtypes import *

import utils

import findtypesvars
import findfiles
import wx_lib

import arginfo

import parse_function
import wrap_class
import copy

def get_include_file(funcname, filename):
  last = filename.rfind('/')
  incfile=filename[last+1:]
  print "including function {0} from file {1}".format(funcname,incfile)
  return incfile

def WxHelpLink(funcname):
  if funcname in config.available_operators.keys():
    mname=config.available_operators[funcname]
  else:
    mname=funcname
  return "http://docs.wxwidgets.org/stable/wx_{0}.html#{1}".format(funcname.lower(),mname.lower())




def CheckBlackList(mname,demangled):
  if mname in config.members_blacklist:
    utils.WarningMessage("Do not implement member {0}, which is in the blacklist !!!".format(mname))
    return True
  for bname in config.members_blacklist:
    if demangled.startswith(bname+"(") or demangled==bname:
      utils.WarningMessage("Do not implement member {0}, which is in the blacklist !!!".format( demangled))
      return True
  return False


#------------------------------
def AddParameters(parsefunc):
  res='('
  if (len(parsefunc.args)>0):
    res += parsefunc.args[0].name
    for i in range(1,len(parsefunc.args)):
      res += ', {0}'.format(parsefunc.args[i].name)
  res += ')'
  return res


#------------------------------------------------------------------
#  ImplementDuplicatedMethodWrap
#------------------------------------------------------------------
def ImplementDuplicatedMethodWrap( method, nummethods, methods):
  # first: easy display
  #if parsefunc.returntype==None:
  #  print 'void',
  #else:
  wrapclass_name="WrapClass_{0}".format(parse_function.FunctionUsedName(funcname))
  wrapmethod_name = parsefunc.usedname
  res = "\n"
  res += "//---------------------------------------------------\n"
  res += "//  Wrapping of multipled defined method:"
  res += "... "
  res += funcname+'(...)\n'
  res += "//---------------------------------------------------\n"
  # second implementation
  #   Documentation part
  res += "void {0}::\n".format(wrapclass_name)
  res += "    wrap_{0}::SetParametersComments()\n".format(wrapmethod_name) 
  res += "{}\n"
  #   Execution part
  res += "\n"
  res += "//---------------------------------------------------\n"
  res += "BasicVariable::ptr {0}::\n".format(wrapclass_name)
  res += "    wrap_{0}::CallMember( ParamList* _p, int stacklevel)\n".format(wrapmethod_name) 
  res += "{\n"
  res += "  BasicVariable::ptr res;\n"
  for n in range(1,nummethods+1):
    usedname= "{0}_{1}".format(parsefunc.usedname,n)
    utils.WarningMessage(" wrapping of {0}".format(usedname))
    # find corresponding method and check if it is implemented
    pos=0
    # Set False as default ...
    is_implemented=False
    for m in methods:
      #print "method name {0} usedname {1}".format(m.name,m.usedname)
      if m.usedname==usedname:
        #print " found method {0}".format(usedname)
        #print " Is implemented = {0}".format(not methods[pos].missingtypes)
        is_implemented = not methods[pos].missingtypes
        utils.WarningMessage(" Duplicated Method {0} is implemented: {1}".format(usedname,is_implemented))
      pos = pos+1
    if is_implemented:
      if m.static=="1":
        usedname = "static_"+usedname
      if constructor or (m.static=="1"):
        res += "  {0}::wrap_{1} m{2};\n".format(wrapclass_name,usedname,n)
      else:
        res += "  {0}::wrap_{1} m{2}(this->_objectptr);\n".format(wrapclass_name,usedname,n)
      res += "  res = m{0}.CallMember(_p, stacklevel+1);\n".format(n)
      res += "  if (!m{0}.Get_arg_failure()) return res;\n".format(n)
  res += "  ClassHelpAndReturn;\n"
  res += "}\n"
  return res


#------------------------------------------------------------------
#  ImplementCopyMethodWrap
#------------------------------------------------------------------
def ImplementCopyMethodWrap(funcname, method):
  wrapclass_name="WrapClass_{0}".format(parse_function.FunctionUsedName(funcname))
  res = "\n"
  res += "//---------------------------------------------------\n"
  res += "//  Wrapping of 'copy' method for {0}.\n".format(funcname)
  res += "//---------------------------------------------------\n"
  # second implementation
  #   Documentation part
  res += "void {0}::\n".format(wrapclass_name)
  res += "    wrap___copy__::SetParametersComments()\n"
  res += "{\n"
  res += '  return_comments="A copy of the {0} object within a new variable.";\n'.format(funcname)
  res += "}\n"
  #   Execution part
  res += "\n"
  res += "//---------------------------------------------------\n"
  res += "BasicVariable::ptr {0}::\n".format(wrapclass_name)
  res += "    wrap___copy__::CallMember( ParamList* _p, int stacklevel)\n"
  res += "{\n"
  res += "    return AMILabType<{0} >::CreateVar( new {0}(*(this->_objectptr->GetObj())));\n".format(funcname)
  res += "}\n"
  return res



#----------------------------------------------------------------------
#  WrapFunction
#----------------------------------------------------------------------
def WrapFunction(funcname,include_file,inputfile):
  print "WrapFunction({0},{1},{2})\n".format(funcname,include_file,inputfile)
  # Create the handler
  dh = parse_function.FindFunction(funcname)

  parser = make_parser()
  # Tell the parser to use our handler
  parser.setContentHandler(dh)
  # Parse the input
  inputfile.seek(0)
  parser.parse(inputfile)

  #
  if not(dh.found):
    print "... {0} : function not found ...".format(funcname)
  else:
    
    methodcount = len(dh.functions)
    print "methodcount = ",methodcount,"\n"

    functioninfo = copy.deepcopy(dh.functions[0])
    print "---- found {0} functions -----".format(len(dh.functions))
    
    utils.WarningMessage( "{0} id= {1}".format(funcname,functioninfo.methodid))

    # Create Header File
    header_filename=args.val.outputdir+"/wrap_{0}.h".format(parse_function.FunctionUsedName(funcname))
    if parse_function.IsTemplate(funcname):
      #shutil.copyfile(args.val.templatefile_dir+"/wrap_templatefunction.h.in",header_filename)
      shutil.copyfile(args.val.templatefile_dir+"/wrap_function.h.in",header_filename)
    else:
      shutil.copyfile(args.val.templatefile_dir+"/wrap_function.h.in",header_filename)

    #

    # now output the results:
    indent=""
    func_decl=""

    if methodcount>1:
      for m in dh.functions:
        func_decl+=indent+'// Adding different functions\n'
        # step 1:
        pos = 0
        missingtypes = wrap_class.MissingTypes("",m)
        if missingtypes!="":
          func_decl+= "/* The following types are missing: "+missingtypes+"\n"
          m.missingtypes=True
        func_decl+=indent+'ADD_CLASS_FUNCTION('+parse_function.FunctionUsedName(m.usedname)+',"{0}  ({1})")\n'.format(\
              m.GetDescription(""),\
              WxHelpLink(m.usedname))
        if missingtypes!="":
          func_decl += "*/\n"
        pos = pos+1
        func_decl+='\n'
    
    func_decl+=indent+'// Adding main function\n'
    # step 1:
    pos = 0
    missingtypes = wrap_class.MissingTypes("",functioninfo)
    if missingtypes!="":
      func_decl+= "/* The following types are missing: "+missingtypes+"\n"
      functioninfo.missingtypes=True
    func_decl+=indent+'ADD_CLASS_FUNCTION('+parse_function.FunctionUsedName(funcname)+',"{0}  ({1})")\n'.format(\
          functioninfo.GetDescription(""),\
          WxHelpLink(funcname))
    if missingtypes!="":
      func_decl += "*/\n"
    pos = pos+1
    func_decl+='\n'

    #local_include_file = get_include_file(funcname,\
    #  config.files[dh.fileid])
    to_include_file = wrap_class.FindIncludeFile(funcname,functioninfo.fileid)
    if to_include_file!="":
      config.AddInclude(to_include_file)
    
    for line in fileinput.FileInput(header_filename,inplace=1):
      line = line.replace("${FUNCTIONNAME}", parse_function.FunctionUsedName(funcname))
      line = line.replace("${INCLUDEFILES}", "")
      line = line.replace("${WRAP_FUNCTION}",     func_decl)
      print line,
          

    ## Implement CreateVar
    #implement_createvar=''

    # Create Implementation File
    impl_filename=args.val.outputdir+"/wrap_{0}.cpp".format(parse_function.FunctionUsedName(funcname))
    if parse_function.IsTemplate(funcname):
      #shutil.copyfile(args.val.templatefile_dir+"/wrap_functiontemplate.cpp.in",impl_filename)
      shutil.copyfile(args.val.templatefile_dir+"/wrap_function.cpp.in",impl_filename)
    else:
      shutil.copyfile(args.val.templatefile_dir+"/wrap_function.cpp.in",impl_filename)
    
    ## arguments
    impl = ""
    


    ## Methods
    
    if methodcount>1:
     
      # first implement individual methods
      for m in dh.functions:
        missingtypes = wrap_class.MissingTypes("",m,True)
        if missingtypes!="":
          impl += "/* The following types are missing: "+missingtypes+"\n"
        impl += wrap_class.ImplementMethodWrap("",m)
        if missingtypes!="":
          impl += "*/\n"
      
      # the implement duplicated one
      print "*** functioninfo.usedname = ", functioninfo.usedname
      functioninfo.usedname = parse_function.FunctionUsedName(funcname)
      print "*** functioninfo.usedname = ", functioninfo.usedname
      print "ImplementDuplicatedMethodWrap\n"
      impl += wrap_class.ImplementDuplicatedMethodWrap("",functioninfo,methodcount,dh.functions)
    else:
      missingtypes = wrap_class.MissingTypes("",functioninfo,True)
      if missingtypes!="":
        impl += "/* The following types are missing: "+missingtypes+"\n"
      print "ImplementMethodWrap\n"
      impl += wrap_class.ImplementMethodWrap("",functioninfo)
      if missingtypes!="":
        impl += "*/\n"
      
    #print "impl=<{0}>\n".format(impl)
    ## OperatorMethods
    #for m in fm.OperatorMethods:
      #missingtypes = MissingTypes(funcname,m,True)
      #if (missingtypes!="") or (m.usedname=="operator not available"):
        #impl += "/*\n"
      #if missingtypes!="":
        #impl += " * The following types are missing: "+missingtypes+"\n"
      #if m.usedname=="operator not available":
        #impl += " * operator not available \n"
      #methodcount=fm.OperatorMethodNames.count(m.name)
      #if m.duplicated:
        #impl += ImplementDuplicatedMethodWrap(funcname,m,methodcount,fm.OperatorMethods)
      #else:
        #impl += ImplementMethodWrap(funcname,m,False,methodcount)
      #if (missingtypes!="") or (m.usedname=="operator not available"):
        #impl += "*/\n"
        
    ## in place replace TEMPLATE by funcname
    ## in place replace ${ADD_CLASS_METHOD_ALL} by func_decl
    ## in place replace ${ADD_CLASS_METHOD_ALL} by func_decl
    for line in fileinput.FileInput(impl_filename,inplace=1):
      line = line.replace("${FUNCTIONNAME}", parse_function.FunctionUsedName(funcname))
      line = line.replace("${INCLUDES}",   config.CreateIncludes())
      line = line.replace("${IMPLEMENT_WRAP_FUNCTION}",   impl)
      print line,

