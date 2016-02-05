
from xml.sax import saxutils,handler
import utils
import re

import config
# load command line arguments
import args
# type substitution
import typesubst
import arginfo

import methodinfo
from methodinfo import *

#-------------------------------------------------------------
def FunctionUsedName(funcname):
  res = funcname
  res = res.replace('<','_L_')
  res = res.replace('>','_G_')
  res = res.replace(',','_')
  res = res.replace('::','_')
  #res = res.replace('(','')
  #res = res.replace(')','')
  # get rid of function parameters
  m=re.search('([^(]+)\s*(\(.*\))?',res)
  res = m.group(1)
  return res

#------------------------------
def FormatArgDefault(argdef):
  # to deal with string within default parameter ...
  return argdef.replace('"',"'").replace('\\000','')


def IsTemplate(classname):
  return re.match(r"(.*)<(.*)>",classname)!=None


#-------------------------------------------------------------
class FindFunction(handler.ContentHandler):
  def __init__(self, funcname):
    self.search_funcname = funcname
    #
    self.functions = []
    self.current_function = None
    #
    self.found        = False
    self.infunc       = False
    #
    #self.name         = funcname
    #self.usedname     = FunctionUsedName(funcname)
    #self.duplicated   = False
    #self.args         = []
    ## returntype
    #self.missingtypes = False
    ## is_copyconstr
    #self.static       = "0"
    #self.const        = False
    ## deprecated
    ## demangled
    #self.converter    = False
    ##virtual
    ##
    #self.funcid       = ""
    #self.fileid       = ""

  #---------------------------------------------
  def CheckEnumDefault(self, default):
    #print "default for {0}".format(default)
    if default in config.enumvalues.keys():
      typeid = config.enumvalues[default]
      if typeid in config.types.keys():
        #print "replacing {0} by {1}::{0} ".format(default,config.types[typeid].GetString())
        return "{1}::{0}".format(default,config.types[typeid].GetString())
    return default
  
  #---------------------------------------------
  def GetDescription(self):
    res=''
    if self.returntype!=None:
      res += config.types[self.returntype].GetFullString()+" "
    if self.name in config.available_operators.keys():
      res += funcname+"::operator "+self.name+'('
    else:
      res += self.name+'('
    for a in self.args:
      res +=  config.types[a.typeid].GetFullString()+" "+a.name
      if a.default!=None:
        res += " = {0}".format(FormatArgDefault(a.default))
      res += ", "
    if len(self.args)>0:
      res = res[:-2]
    res += ')'
    return res

  #---------------------------------------------
  def CheckArgument(self, name, attrs):
    # process arguments
    if name=='Argument':
      typeid=attrs.get('type',None)
      argname=attrs.get('name',None)
      default=attrs.get('default',None)
      if argname==None:
        argname='param{0}'.format(len(self.method.args))
      if typeid in config.types.keys():
        typename=config.types[typeid].GetFullString(),
      else:
        typename=typeid,
      utils.WarningMessage("\t\t {0} \t\t {1}".format(typename,argname))
      # append argument to list
      arg=arginfo.ArgInfo()
      arg.name=argname
      arg.typeid=typeid
      if default != None:
        arg.default=self.CheckEnumDefault(default)
      else:
        arg.default=None
      self.current_function.args.append(arg)
      return True
    else:
      utils.WarningMessage( "Non-argument in method: {0}\n".format(name))

#---------------------------------------------
  def startElement(self, name, attrs):
    # Parse function arguments
    if self.infunc==1:
      return self.CheckArgument(name,attrs)
      
    if (name != "Function"): return

    funcname = attrs.get('name', None)
    demangled=attrs.get('demangled',None)
    if (funcname != self.search_funcname):
      if demangled==None: 
        return
      else:
        if  (self.search_funcname != demangled) and \
            (not (self.search_funcname+"(" in demangled)):
          return
    print "found name = {0}, demangled = {1}".format(funcname,demangled)
    self.found=True
    self.infunc=True
    self.current_function = MethodInfo()
    self.current_function.name = self.search_funcname
    self.current_function.usedname = FunctionUsedName(self.search_funcname)
    func_id = attrs.get('id',None)

    self.current_function.methodid = func_id
    
    self.current_function.fileid = attrs.get('file', None)
    utils.WarningMessage( "{0}  found, id = {1}".format(funcname,func_id))
    self.current_function.returntype=attrs.get('returns',None)

  def endElement(self, name):
    if (self.infunc==True) and (name == "Function"):
      self.infunc=False
      if len(self.functions)==1:
        self.functions[0].usedname += "_1"
      if len(self.functions)>0:
        self.current_function.usedname += "_{0}".format(len(self.functions)+1)
      self.functions.append(self.current_function)

