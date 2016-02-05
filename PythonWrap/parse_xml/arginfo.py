
from xml.sax import saxutils,handler
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

#import parse_class

#-----------------------------------------
# ArgInfo: dealing with method arguments
#
class ArgInfo:
  def __init__(self):
    self.name=""
    self.typeid = 0
    self.returnstring="ClassHelpAndReturn"
    self.quiet="false"
    self.default=None
    self.implement_default=False
    
  # Standard Values
  
  def GetSubstName(self):
    substype = typesubst.type_substitute[self.typename]
    substype_short = typesubst.GetShortName(substype)
    substvar="{0}_{1}".format(self.name,substype_short)
    return substvar

  # Deal with type substitution
  # bool --> use int
  def WrapGetParamValue_subst(self):
    substype = typesubst.type_substitute[self.typename]
    substvar = self.GetSubstName()
    res = "  "
    required="true"
    noconstr="false"
    if self.default!=None and self.implement_default:
      if config.types[self.typeid].GetContext()!=None:
        contextid = config.types[self.typeid].GetContext()
        #if contextid in config.types.keys():
          #defaultval = "{0}::{1}".format(config.types[contextid].GetString(),self.default)
        #else:
        defaultval = self.default
      else:
        defaultval = self.default
      res += typesubst.ConvertValFrom(self.typeid,defaultval,substvar)
      required = "false"
    else:
      res +=   "{0} {1}".format(substype,substvar)
    res += ";\n"
    res +=  "  if (!AMILabType<{0} >::get_val_param({1},_p,_n,stacklevel,{3},{4},{5})) {2};\n".format( \
        substype,substvar,self.returnstring,required,noconstr,self.quiet)
    res +=  "  "+typesubst.ConvertValTo(self.typeid,substvar,self.name)+"\n"
    #{1} {0} = ({1}) ({2}>0.5);\n".format(self.name,typename,substvar)
    return res
        
  def WrapGetParamValue(self,noconstructor_call):
    if self.typename in typesubst.type_substitute.keys():
        return self.WrapGetParamValue_subst()
    else:
      res =  "  {0} {1}".format(self.typename,self.name)
      required="true"
      if self.default!=None and self.implement_default:
        res += " = {0}".format(self.default)
        required="false"
      res += ";\n"
      shared_type = config.IsSharedPtr(self.typename)
      if noconstructor_call:
        noconstr="true"
      else:
        noconstr="false | Get_noconstr()"
      if shared_type==None:
        res += "  if (!AMILabType<{0} >::get_val_param({1},_p,_n,stacklevel,{3},{4},{5})) {2};\n".format(\
          self.typename,self.name,self.returnstring,required,noconstr,self.quiet)
      else:
        ## false parameter value to keep smart pointer deleter
        # previous comment (noconstr was set to false): not clear, applying the same noconstr parameter ...
        res += "  if (!AMILabType<{0} >::get_val_smtptr_param({1},_p,_n,stacklevel,{3},{4},{5})) {2};\n".format(\
          shared_type,self.name,self.returnstring,required,noconstr,self.quiet)
    return res
  
  # Pointers
  def WrapGetParamPointer_subst(self,noconstructor_call):
    if noconstructor_call:
      noconstr='true'
    else:
      noconstr='false | Get_noconstr()'
    substype = typesubst.type_substitute[self.typename]
    substvar = self.GetSubstName()
    res =  "  boost::shared_ptr<{0} > {1};\n".format(substype,substvar)
    res += "  if (!AMILabType<{0} >::get_val_smtptr_param({1},_p,_n,stacklevel,{3},{4})) {2};\n".format(\
      substype,substvar,self.returnstring,noconstr,self.quiet)
    # Try to create pointer from smart pointer if available
    conv_res=typesubst.ConvertSmtPtrToPtr(self.typeid,substvar,self.name)
    if conv_res!="":
      res += "  "+typesubst.ConvertSmtPtrToPtr(self.typeid,substvar,self.name)+"\n"
      #res += "  {1}* {0} = &{0}_val;\n".format(self.name,self.typename)
    else:
      print "Smartpointer to pointer conversion failed for type {0}!".format(self.typename)
      # otherwise convert from value, but could only work for constants???
      res += "  "+typesubst.ConvertValTo(self.typeid,"(*{0})".format(substvar), "{0}_val".format(self.name))+"\n"
      res += "  {1}* {0} = &{0}_val;\n".format(self.name,self.typename)
    return res

  # subtitution for double pointer
  def WrapGetParamDoublePointer_subst(self,noconstructor_call):
    substype = typesubst.type_substitute[self.typename]
    substvar = self.GetSubstName()
    res =  "  boost::shared_ptr<{0} > {1};\n".format(substype,substvar)
    res += "  if (!AMILabType<{0} >::get_val_smtptr_param({1},_p,_n,stacklevel,true,false,{3})) {2};\n".format(\
      substype,substvar,self.returnstring,self.quiet)
    # Try to create pointer from smart pointer if available
    conv_res= typesubst.ConvertSmtPtrToDoublePtr(self.typeid,substvar,self.name)
    if conv_res!="":
      res += "  "+conv_res+"\n"
      #res += "  {1}* {0} = &{0}_val;\n".format(self.name,self.typename)
    else:
      print "Smartpointer to pointer conversion failed for type {0}!".format(self.typename)
      # otherwise convert from value, but could only work for constants???
      res += "  "+typesubst.ConvertValTo(self.typeid,"(*{0})".format(substvar), "{0}_val".format(self.name))+"\n"
      res += "  {1}* {0} = &{0}_val;\n".format(self.name,self.typename)
    return res

  def WrapGetParamDoublePointer(self,noconstructor_call):
    if self.typename in typesubst.type_substitute.keys():
      return self.WrapGetParamDoublePointer_subst()
    else:
      res = "  {0}* local_{1} = NULL;\n".format(self.typename,self.name)
      res += "  {0}** {1}".format(self.typename,self.name)
      if self.default==None or not(self.implement_default):
        addparams=',true'
        res += ";\n"
      else:
        res += " = {0};\n".format(self.default)
        addparams=',false'
      # Check for null pointer 
      res += "  if (CheckNullVar(_p,_n))  {\n"
      res += "    {0}=({1}**)NULL;\n".format(self.name,self.typename)
      res += "    _n++;\n"
      res += "  } else {\n"
      if noconstructor_call:
        addparams+=',true'
      else:
        addparams+=',false | Get_noconstr()'
      res += "    boost::shared_ptr<{0} > {1}_smtptr;\n".format(self.typename,self.name)
      res += "    if (!AMILabType<{0} >::get_val_smtptr_param({1}_smtptr,_p,_n{2},stacklevel,{4})) {3};\n".format(\
          self.typename,self.name,addparams,self.returnstring,self.quiet)
      res += "    local_{0} = {0}_smtptr.get();\n".format(self.name)
      res += "    {0} = &local_{0};\n".format(self.name)
      res += "  }\n"
      # TODO: should check if the resulting pointer has been modified after the function 
      # call to update the smart pointer of the variable
    return res

  def WrapGetParamPointer(self,noconstructor_call):
    if self.typename in typesubst.type_substitute.keys():
      return self.WrapGetParamPointer_subst(noconstructor_call)
    else:
      res = "  {0}* {1}".format(self.typename,self.name)
      if self.default==None or not(self.implement_default):
        addparams=',true'
        res += ";\n"
      else:
        res += " = {0};\n".format(self.default)
        addparams=',false'
      # Check for null pointer 
      res += "  if (CheckNullVar(_p,_n))  {\n"
      res += "    {0}=({1}*)NULL;\n".format(self.name,self.typename)
      res += "    _n++;\n"
      res += "  } else {\n"
      if noconstructor_call:
        addparams+=',true'
      else:
        addparams+=',false | Get_noconstr()'
      res += "    boost::shared_ptr<{0} > {1}_smtptr;\n".format(self.typename,self.name)
      res += "    if (!AMILabType<{0} >::get_val_smtptr_param({1}_smtptr,_p,_n{2},stacklevel,{4})) {3};\n".format(\
          self.typename,self.name,addparams,self.returnstring,self.quiet)
      res += "    {0} = {0}_smtptr.get();\n".format(self.name)
      res += "  }\n"
    return res
  
  # References
  def WrapGetParamRef(self,noconstructor_call):
    fulltype=config.types[self.typeid].GetFullString()
    shared_type = config.IsSharedPtr(self.typename)
    if shared_type==None:
      # more complicate to deal with type substitution here ...
      #if self.typename in typesubst.type_substitute.keys():
        #smtptr_type = typesubst.type_substitute[self.typename]
        #substvar = self.GetSubstName()
      #else:
      smtptr_type = self.typename
    else:
      smtptr_type = shared_type
    res = "  boost::shared_ptr<{0} > {1}_smtptr;\n".format(smtptr_type,self.name)
    ispointer = fulltype.startswith(self.typename+" *") or fulltype.startswith(self.typename+" const *")
    if noconstructor_call:
      noconst=',true'
    else:
      noconst=',false | Get_noconstr()'
    #if self.default==None or not(self.implement_default):
    # no default value
    # special case of BasicVariable::ptr, TODO: hack,  need to be improved
    if (shared_type!=None) and (smtptr_type=="BasicVariable"):
      res += "  {0}_smtptr = _p->GetParam(_n++);\n".format(self.name)
    else:
      res += "  if (!AMILabType<{0} >::get_val_smtptr_param({1}_smtptr,_p,_n,stacklevel,true{2},{4})) {3};\n".format(\
        smtptr_type,self.name,noconst,self.returnstring,self.quiet)
    if ispointer:
      print "------------   getting parameter * & : fulltype = {0} -------".\
          format(fulltype)
      #res += "  {0} {1} = {1}_smtptr.get();\n".format(fulltype,self.name)
      res += "  {0} * {1}_ptr = {1}_smtptr.get();\n".format(self.typename,self.name)
      res += "  {0} {1} = {1}_ptr;\n".format(fulltype,self.name)
    else:
      if shared_type==None:
        res += "  {0} {1} = *{1}_smtptr;\n".format(fulltype,self.name)
      else:
        res += "  {0} {1} = {1}_smtptr;\n".format(fulltype,self.name)
    return res
  
  def WrapGetParam(self,noconstructor_call,returnstring,quiet):
    self.maintypeid = config.types[self.typeid].GetMainTypeId()
    self.typename = config.types[self.maintypeid].GetDemangled()
    #print "WrapGetParam {0}, {1}, '{2}'".format(self.name,config.types[self.typeid].GetType(), config.types[self.typeid].GetFullString())
    self.returnstring=returnstring
    self.quiet=quiet
    if config.types[self.typeid].GetRealType()=="PointerType":
      if config.types[self.typeid].GetFullString().endswith("* *"):
        res =  self.WrapGetParamDoublePointer(noconstructor_call)
        #print "res= ",res
        return res
      else:
        return self.WrapGetParamPointer(noconstructor_call)
    if config.types[self.typeid].GetRealType()=="ReferenceType":
      return self.WrapGetParamRef(noconstructor_call)
    return self.WrapGetParamValue(noconstructor_call)

  # Post-treatment for pointers and references in case of substitution
  def WrapGetParamPost_Pointer_bool(self):
    res =  "  "+typesubst.ConvertValFrom_bool("(*{0})".format(self.name),"*{0}_{1}".format(self.name,"int"))+"\n"
    return res

  def WrapGetParamPost_Pointer_uint(self):
    res =  "  *{0}_{1} = boot::numeric_cast<{1} >(*{0});\n".format(self.name,"long")
    return res

  def WrapGetParamPost_Pointer(self):
    typename=config.types[self.typeid].GetDemangled()
    if typename in typesubst.type_substitute.keys():
      if typename=="bool":
        return self.WrapGetParamPost_Pointer_bool()
      if typename=="unsigned int":
        return self.WrapGetParamPost_Pointer_uint()
    else:
      return ""
  
  def WrapGetParamPost(self):
    if config.types[self.typeid].GetType()=="PointerType":
      return self.WrapGetParamPost_Pointer()
    if config.types[self.typeid].GetType()=="ReferenceType":
      return self.WrapGetParamRef_Ref()
    return ""

