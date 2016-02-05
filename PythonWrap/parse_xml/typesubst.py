
import config

# equivalence of types
type_equivalence={}

# convenient shortname
type_shortname={
  'unsigned char'      : 'uchar',
  'unsigned int'       : 'uint',
  'unsigned long'      : 'luint',
  'long int'           : 'lint',
  'long long int'      : 'llint',
  'long unsigned int'  : 'luint',
  'long long unsigned int'  : 'lluint',
  'std::string'        : 'string',
  'long long int'      : 'llint',
  'short unsigned int' : 'suint',
  'short int'          : 'sint',
  'signed char'        : 'schar',
}

# type substitution
type_substitute={
  'unsigned int'       : 'long',
#  'long int'          : 'long',
#  'long unsigned int'  : 'long',
  'long long unsigned int'  : 'long',
  'char'               : 'std::string',
  'wchar_t'            : 'std::string',
  'long long int'      : 'long',
#  'short unsigned int' : 'int',
#  'short int'          : 'int',
  'signed char'        : 'unsigned char',
  'void'               : 'unsigned char',
}
#'bool':'int',

def GetShortName(typename):
  if typename in type_shortname.keys():
    return type_shortname[typename]
  else:
    return config.ClassShortName(typename)

#
# Operators
#



def RemovePointerConstness(typename,varname):
  if typename.endswith("const *"):
    return "const_cast<{0}>({1})".format(typename[:-7]+"*", varname)
  else:
    return varname

#
# 'bool' type conversions
#
#def ConvertValFrom_bool(boolvar,substvar):
#  typename="bool"
#  substtype = type_substitute[typename]
#  res =  "{2} {0} = (({1}==true)?1:0);".format(substvar,boolvar,substtype)
#  return res
  
#def ConvertValTo_bool(substvar,typevar):
#  typename="bool"
#  res = "{1} {0} = ({1}) ({2}>0.5);".format(typevar,typename,substvar)
#  return res

#
# 'unsigned int' type conversions
#
def ConvertValFrom_uint(typevar,substvar):
  typename="unsigned int"
  substtype = type_substitute[typename]
  config.AddInclude('#include "boost/numeric/conversion/cast.hpp"\n')
  # should check limits
  res = "{1} {0} = boost::numeric_cast<{1} >((unsigned int){2});".format(substvar,substtype,typevar)
  return res

def ConvertValTo_uint(substvar,typevar):
  typename="unsigned int"
  config.AddInclude('#include "boost/numeric/conversion/cast.hpp"\n')
  # should check limits
  res = "{1} {0} = boost::numeric_cast<{1} >({2});".format(typevar,typename,substvar)
  return res

#
# 'long long int' type conversions
#
def ConvertValFrom_llint(typevar,substvar):
  typename="long long int"
  substtype = type_substitute[typename]
  config.AddInclude('#include "boost/numeric/conversion/cast.hpp"\n')
  # should check limits
  res = "{1} {0} = boost::numeric_cast<{1} >((unsigned int){2});".format(substvar,substtype,typevar)
  return res

def ConvertValTo_llint(substvar,typevar):
  typename="long long int"
  config.AddInclude('#include "boost/numeric/conversion/cast.hpp"\n')
  # should check limits
  res = "{1} {0} = boost::numeric_cast<{1} >({2});".format(typevar,typename,substvar)
  return res

#
# 'short unsigned int' type conversions
#
def ConvertValFrom_suint(typevar,substvar):
  typename="short unsigned int"
  substtype = type_substitute[typename]
  config.AddInclude('#include "boost/numeric/conversion/cast.hpp"\n')
  # should check limits
  res = "{1} {0} = boost::numeric_cast<{1} >((unsigned int){2});".format(substvar,substtype,typevar)
  return res

def ConvertValTo_suint(substvar,typevar):
  typename="short unsigned int"
  config.AddInclude('#include "boost/numeric/conversion/cast.hpp"\n')
  # should check limits
  res = "{1} {0} = boost::numeric_cast<{1} >({2});".format(typevar,typename,substvar)
  return res

#
# 'long int' type conversions
#
def ConvertValFrom_lint(typevar,substvar):
  typename="long int"
  substtype = type_substitute[typename]
  res = "{1} {0} = {2};".format(substvar,substtype,typevar)
  return res

def ConvertValTo_lint(substvar,typevar):
  typename="long int"
  res = "{1} {0} = {2};".format(typevar,typename,substvar)
  return res

#
# 'long unsigned int' type conversions
#
def ConvertValFrom_luint(typevar,substvar):
  typename="long unsigned int"
  substtype = type_substitute[typename]
  config.AddInclude('#include "boost/numeric/conversion/cast.hpp"\n')
  # should check limits
  res = "{1} {0} = boost::numeric_cast<{1} >({2});".format(substvar,substtype,typevar)
  return res

def ConvertValTo_luint(substvar,typevar):
  typename="long unsigned int"
  config.AddInclude('#include "boost/numeric/conversion/cast.hpp"\n')
  # should check limits
  res = "{1} {0} = boost::numeric_cast<{1} >({2});".format(typevar,typename,substvar)
  return res

#
# 'char' type conversions
#
def ConvertValFrom_char(typevar,substvar):
  typename="char"
  substtype = type_substitute[typename]
  res = "{1} {0} = std::string(1,{2});".format(substvar,substtype,typevar)
  return res

def ConvertPtrFrom_char(typevar,substvar):
  typename="char"
  substtype = type_substitute[typename]
  res = "{1} {0} = std::string({2});".format(substvar,substtype,typevar)
  return res

def ConvertPtrFrom_void(typevar,substvar):
  typename="void"
  substtype = type_substitute[typename]
  res = "{1}* {0} = ({1}*) {2};".format(substvar,substtype,typevar)
  return res

def ConvertValTo_char(substvar,typevar):
  typename="char"
  res =  "{0} {1} = ' ';\n".format(typename,typevar)
  res += "  if ({0}.size()==1) {1} = {0}[0];".format(substvar,typevar)
  res += "else ClassReturnEmptyVar;"
  return res

def ConvertSmtPtrToPtr_char(typeid,substvar,typevar):
  #print "within ConvertSmtPtrToPtr_char()"
  fulltypename=config.types[typeid].GetFullString()
  if fulltypename=="char *":
    # trick to convert to char *, not const char *, but maybe not valid ...
    res = "{0} {1} = &(*{2})[0];".format(fulltypename,typevar,substvar)
  else:
    res = "{0} {1} = {2}->c_str();".format(fulltypename,typevar,substvar)
  #print "res = {0}".format(res)
  return res
  
def ConvertSmtPtrToDoublePtr_char(typeid,substvar,typevar):
  #print "within ConvertSmtPtrToPtr_char()"
  fulltypename=config.types[typeid].GetFullString()
  # Tricky conversion here, problably not correct ...
  res = "// this conversion is probably not correct but should compile\n"
  res += "char* {0}_pointer = (char*){1}->c_str();\n".format(typevar,substvar)
  res += "{0} {1} = ({0}) &{1}_pointer;".format(fulltypename,typevar,substvar)
  #print "res = {0}".format(res)
  return res

#
# 'wchar_t' type conversions
#
def ConvertValFrom_wchar_t(typevar,substvar):
  typename="wchar_t"
  substtype = type_substitute[typename]
  config.AddInclude('#include "stdlib.h"\n')
  # convert to char
  res =  "{0} {1};\n".format(substtype,substvar)
  indent= "  "
  res += indent+"{\n"
  res += indent+"  wchar_t val = {0};\n".format(typevar)
  res += indent+"  char char_conv;\n"
  res += indent+"  size_t conv_res = wcstombs(&char_conv,&val,1);\n"
  res += indent+"  if (conv_res>0) {0} = std::string(1,char_conv);\n".format(substvar)
  res += indent+"}"
  return res

#
# 'wchar_t' type conversions
#
def ConvertPtrFrom_wchar_t(typevar,substvar):
  typename="wchar_t"
  substtype = type_substitute[typename]
  config.AddInclude('#include "stdlib.h"\n')
  config.AddInclude('#include "wchar.h"\n')
  # convert to char
  res =  "{0} {1};\n".format(substtype,substvar)
  indent= "  "
  res += indent+"{\n"
  res += indent+"  const wchar_t* val = {0};\n".format(typevar)
  res += indent+"  size_t size = wcslen(val);\n".format(typevar)
  res += indent+"  char* char_conv = new char[size+1];\n"
  res += indent+"  size_t conv_res = wcstombs(char_conv,val,size+1);\n"
  res += indent+"  if (conv_res>0) {0} = std::string(char_conv);\n".format(substvar)
  res += indent+"  delete[] char_conv;\n".format(substvar)
  res += indent+"}"
  return res

def ConvertValTo_wchar_t(substvar,typevar):
  typename="wchar_t"
  substtype = type_substitute[typename]
  config.AddInclude('#include "stdlib.h"\n')
  # convert from char
  res =  "{0} {1} = 0;\n".format(typename,typevar)
  res += "  {\n" 
  res += "    if({0}.size()==1) mbstowcs(&{1}, &{0}[0],1); \n".format(substvar,typevar)
  res += "    else ClassReturnEmptyVar;\n"
  res += "  }\n"
  return res

def ConvertSmtPtrToPtr_wchar_t(typeid,substvar,typevar):
  #print "within ConvertSmtPtrToPtr_char()"
  config.AddInclude('#include "stdlib.h"\n')
  fulltypename=config.types[typeid].GetFullString()
  res  = "wchar_t* {0} = new wchar_t[{1}->size()+1];\n".format(typevar,substvar)
  res += "mbstowcs({0},{1}->c_str(),{1}->size()+1);".format(typevar,substvar)
  #print "res = {0}".format(res)
  return res
  

def ConvertSmtPtrToPtr_void(typeid,substvar,typevar):
  #print "within ConvertSmtPtrToPtr_char()"
  fulltypename=config.types[typeid].GetFullString()
  res  = "void* {0} = (void*) {1}.get();\n".format(typevar,substvar)
  return res

def ConvertSmtPtrToDoublePtr_void(typeid,substvar,typevar):
  #print "within ConvertSmtPtrToPtr_char()"
  fulltypename=config.types[typeid].GetFullString()
  res  = "void** {0} = (void**) {1}.get();\n".format(typevar,substvar)
  return res


#
# Generic calls
#
def ConvertValFrom(typeid,typevar,substvar):
  maintypeid = config.types[typeid].GetMainTypeId()
  typename=config.types[maintypeid].GetString()
  substtype = type_substitute[typename]
  shorttypename=GetShortName(typename)
  if shorttypename=="wchar_t":
    return ConvertValFrom_wchar_t(typevar,substvar)
  else:
    try:
      return eval("ConvertValFrom_{0}(typevar,substvar)".format(shorttypename))
    except NameError:
      res = "{1} {0} = ({1}) {2};".format(substvar,substtype,typevar)
      return res


def ConvertPtrFrom(typeid,typevar,substvar):
  maintypeid = config.types[typeid].GetMainTypeId()
  typename=config.types[maintypeid].GetString()
  substtype = type_substitute[typename]
  shorttypename=GetShortName(typename)
  try:
    #print "trying ConvertPtrFrom_{0}(typevar,substvar)".format(shorttypename)
    return eval("ConvertPtrFrom_{0}(typevar,substvar)".format(shorttypename))
  except NameError:
    print "Warning: pointer conversion failed for type {0}".format(typename)
    res =  eval("ConvertValFrom(typeid,'*'+typevar,substvar)")
    return res

def ConvertValTo(typeid,substvar,typevar):
  maintypeid = config.types[typeid].GetMainTypeId()
  typename=config.types[maintypeid].GetString()
  shorttypename=GetShortName(typename)
  try:
    return eval("ConvertValTo_{0}(substvar,typevar)".format(shorttypename))
  except NameError:
    res = "{1} {0} = ({1}) {2};".format(typevar,typename,substvar)
    return res
 
def ConvertSmtPtrToPtr(typeid,substvar,typevar):
  typename=config.types[typeid].GetString()
  fulltypename=config.types[typeid].GetFullString()
  shorttypename=GetShortName(typename)
  try:
    return eval("ConvertSmtPtrToPtr_{0}(typeid,substvar,typevar)".format(shorttypename))
  except NameError:
    res  = "{2} {0} = ({2}) {1}.get();\n".format(typevar,substvar,fulltypename)
    return res
 
def ConvertSmtPtrToDoublePtr(typeid,substvar,typevar):
  typename=config.types[typeid].GetString()
  fulltypename=config.types[typeid].GetFullString()
  shorttypename=GetShortName(typename)
  try:
    return eval("ConvertSmtPtrToDoublePtr_{0}(typeid,substvar,typevar)".format(shorttypename))
  except NameError:
    res  = "{2} {0} = ({2}) {1}.get();\n".format(typevar,substvar,fulltypename)
    return res
