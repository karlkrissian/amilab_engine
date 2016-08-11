#
# Organize the different types for function arguments
# 

import config
import utils
import typesubst
import wrap_class

#------------------------------
class ArgTypeBase:
  def __init__(self):
    self._type=""
    self._name=""
    self._id=0
    self._context=None
    self.demangled=None

  def SetType(self,t):
    self._type=t
  
  def GetType(self):
    return self._type

  def GetRealType(self):
    #print "ArgTypeBase::GetRealType()"
    return self._type
    
  def SetName(self,n):
    self._name=n

  def GetName(self):
    return self._name
  
  def GetAbstract(self):
    return None
    
  def SetDemangled(self,d):
    self.demangled = d

  def GetDemangled(self):
    if self.demangled!=None:
      return self.demangled
    else:
      return self.GetString()

  def SetId(self,_id):
    self._id = _id

  def GetId(self):
    return self._id

  def SetRefTypeId(self,t):
    self._reftypeid=t
  
  def GetRefTypeId(self):
    return self._reftypeid

  def GetFullString(self):
    return self.GetDemangled()

  def GetMainTypeId(self):
    return self._id

  def GetString(self):
    #print "ArgTypeBase::GetString()"
    return self._name
    
  def IsConst(self):
    return False
    
  def SetContext(self,context):
    utils.WarningMessage(" type {0} context {1} ".format(self._name,context) )
    self._context = context
    
  def GetContext(self):
    return self._context


# organize a little bit the information
#------------------------------
class ClassInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self.publicmembers=()
    self._type="Class"
    # additional information for classes to wrap
    self.bases=[]
    self.abstract="0"
    self.incomplete="0"
    self.has_copyconstr=False
    self.fileid=""
    self.public_members=wrap_class.PublicMembers()
  
  def GetString(self):
    if self._context != None:
      if self._context in config.types.keys() and self._context!="_1":
        return "{0}::{1}".format(config.types[self._context].GetString(),self._name)
      else:
        #print "context = ",self._context," not recognized"
        return self._name
    else:
      #print "no context for class ",self._name
      return self._name
  
  def GetAbstract(self):
    return self.abstract=="1"

# organize a little bit the information
#------------------------------
class NamespaceInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="Namespace"
  
  def GetString(self):
    if self._context != None:
      if self._context in config.types.keys() and self._context!="_1":
        return "{0}::{1}".format(config.types[self._context].GetString(),self._name)
      else:
        return self._name
    else:
      return self._name
  

#------------------------------
class ArgumentInfo:
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self.name=""

#------------------------------
class MemberInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="Member"

#------------------------------
class TypedefInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="Typedef"
    
  def GetRealType(self):
    #print "TypedefInfo::GetRealType()"
    if (self._name not in config.available_classes) and (self._reftypeid in config.types.keys()):
      return config.types[self._reftypeid].GetType()
    else:
      return self.GetType()

  def GetString(self):
    # deal with typedef inside a class ...
    if self._context != None:
      if self._context in config.types.keys() and self._context!="_1":
        return "{0}::{1}".format(config.types[self._context].GetString(),self._name)
    if self._reftypeid in config.types.keys():
      #print config.types[self._reftypeid].GetString()
      # if member typedef (or function), keep the typedef name
      #print "*** {0}".format(self._name)
      maintyperef = config.types[self._reftypeid].GetMainTypeId()
      if config.types[maintyperef].GetType()=="MethodType":
        #print "*** returning '{0}'".format(self._name)
        typename=self._name
      else:
        typename=config.types[self._reftypeid].GetString()
    else:
      typename=self._reftypeid
    return typename


  def GetFullString(self):
    if self._reftypeid in config.types.keys():
      #print config.types[self._reftypeid].GetString()
      # if member typedef (or function), keep the typedef name
      maintyperef = config.types[self._reftypeid].GetMainTypeId()
      if config.types[maintyperef].GetType()=="MethodType":
        typename=self._name
      else:
        typename=config.types[self._reftypeid].GetFullString()
    else:
      typename=self._reftypeid
    return typename

  def GetMainTypeId(self):
    if self._reftypeid in config.types.keys():
      maintyperef = config.types[self._reftypeid].GetMainTypeId()
      # Do an exception for MethodType ...
      if config.types[maintyperef].GetType()=="MethodType":
        return self.GetId()
      else:
        return maintyperef
    else:
      return self.GetId()

  def GetDemangled(self):
    if self._reftypeid in config.types.keys():
      maintyperef = config.types[self._reftypeid].GetMainTypeId()
      if config.types[maintyperef].GetType()=="MethodType":
        typename = self._name
      else:
        typename=config.types[self._reftypeid].GetDemangled()
    else:
      typename=self._reftypeid
    return typename


#------------------------------
class StructInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="Struct"
    self.bases=[]
    self.incomplete="0"
    self.fileid=""
    self.abstract='0'
    self.public_members=wrap_class.PublicMembers()

#------------------------------
class EnumerationInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="Enumeration"
    self._values={}

  def SetName(self,n):
    self._name=n
    # register global enums or enums that belong to available types
    if (self._context=="_1") or (self._context in config.types.keys()):
      self.Register()
      
    
  def Register(self):
    utils.WarningMessage("Registering enum type {0} with 'int' substitution".format(self.GetString()))
    typesubst.type_substitute[self.GetString()]='int'

  def GetString(self):
    if self._context != None:
      if self._context in config.types.keys() and self._context!="_1":
        return "{0}::{1}".format(config.types[self._context].GetString(),self._name)
      else:
        return self._name
    else:
      return self._name

  def GetFullString(self):
    return self.GetString()

#------------------------------
class FundamentalTypeInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="FundamentalType"

#------------------------------
class UnionInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="Union"

#------------------------------
class ArrayTypeInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="ArrayType"

  def GetString(self):
    if self._reftypeid in config.types.keys():
      typename=config.types[self._reftypeid].GetString()
    else:
      typename=self._reftypeid
    return typename

#------------------------------
class MethodTypeInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="MethodType"
    self.const="0"
  
  def GetString(self):
    # return "__MethodType__"
    return self._name

  def SetConst(self,v):
    self.const = v

#------------------------------
class CvQualifiedTypeInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="CvQualifiedType"
    self.const="0"

  def SetConst(self,v):
    self.const = v

  def GetFullString(self):
    if self._reftypeid in config.types.keys():
      typename=config.types[self._reftypeid].GetFullString()
    else:
      typename=self._reftypeid
    if self.const=="1":
      return typename+" const"
    else:
      return typename
  
  def GetString(self):
    if self._reftypeid in config.types.keys():
      typename=config.types[self._reftypeid].GetString()
    else:
      typename=self._reftypeid
    return typename

  def GetDemangled(self):
    if self._reftypeid in config.types.keys():
      typename=config.types[self._reftypeid].GetDemangled()
    else:
      typename=self._reftypeid
    return typename

  def GetAbstract(self):
    if self._reftypeid in config.types.keys():
      return config.types[self._reftypeid].GetAbstract()
    return None

  def GetMainTypeId(self):
    if self._reftypeid in config.types.keys():
      return config.types[self._reftypeid].GetMainTypeId()
    else:
      return self.GetId()
      
  def IsConst(self):
    return self.const=="1"

#------------------------------
class ReferenceTypeInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="ReferenceType"
  
  def GetFullString(self):
    if self._reftypeid in config.types.keys():
      typename=config.types[self._reftypeid].GetFullString()
    else:
      typename=self._reftypeid
    return typename+" &"

  def IsConst(self):
    return config.types[self._reftypeid].IsConst()
  
  def GetString(self):
    if self._reftypeid in config.types.keys():
      typename=config.types[self._reftypeid].GetString()
    else:
      typename=self._reftypeid
    return typename

  def GetDemangled(self):
    if self._reftypeid in config.types.keys():
      typename=config.types[self._reftypeid].GetDemangled()
    else:
      typename=self._reftypeid
    return typename

  def GetAbstract(self):
    if self._reftypeid in config.types.keys():
      return config.types[self._reftypeid].GetAbstract()
    return None

  def GetMainTypeId(self):
    if self._reftypeid in config.types.keys():
      return config.types[self._reftypeid].GetMainTypeId()
    else:
      return self.GetId()
#------------------------------
class PointerTypeInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="PointerType"
  
  def GetFullString(self):
    if self._reftypeid in config.types.keys():
      typename=config.types[self._reftypeid].GetFullString()
    else:
      typename=self._reftypeid
    return typename+" *"

  def GetString(self):
    if self._reftypeid in config.types.keys():
      typename=config.types[self._reftypeid].GetString()
    else:
      typename=self._reftypeid
    return typename

  def GetDemangled(self):
    if self._reftypeid in config.types.keys():
      typename=config.types[self._reftypeid].GetDemangled()
    else:
      typename=self._reftypeid
    return typename

  def GetMainTypeId(self):
    if self._reftypeid in config.types.keys():
      return config.types[self._reftypeid].GetMainTypeId()
    else:
      return self.GetId()

#------------------------------
class OperatorFunctionInfo(ArgTypeBase):
  def __init__(self):
    ArgTypeBase.__init__(self) 
    self._type="OperatorFunction"
    # saving the first argument id
    self._first_argument_id = ''
