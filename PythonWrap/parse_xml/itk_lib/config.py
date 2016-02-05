# -*- coding: utf-8 -*-


# in VTK, the header file is the same as the classname
def get_include_file(classname,filename):
  incfile = '#include "{0}"'.format(filename)
  #print "including class {0} from file {1}".format(classname,incfile)
  if classname.startswith("itk::DefaultConvertPixelTraits"):
    incfile = '#include "itkMatrix.h"\n'+incfile
  if classname.startswith("std::set"):
    incfile = '#include <set>\n'+incfile
  return incfile
  #return "{0}.h".format(classname)
  
def get_var_filter():
  return "(itk::|vnl_|itkAmi|gdcm::|std::).*"
  
def wrap_public_fields(classname):
  return False

def deleter_includefile():
  return ""

def implement_deleter(classname):
  # no deleter for the moment unless for smart pointers?
  # or only in case of protected deleter?
  return ", smartpointer_nodeleter<{0} >()".format(classname)