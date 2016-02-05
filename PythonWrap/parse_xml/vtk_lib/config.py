# -*- coding: utf-8 -*-


# in VTK, the header file is the same as the classname
def get_include_file(classname,filename):
  last = filename.rfind('/')
  incfile=filename[last+1:]
  incfile = '#include "{0}"'.format(incfile)
  #print "including class {0} from file {1}".format(classname,incfile)
  return incfile
  #return "{0}.h".format(classname)
  
def get_var_filter():
  return "vtk*"
  
def wrap_public_fields(classname):
  return False

def deleter_includefile():
  return '#include "vtk_common.h"'

def implement_deleter(classname):
  # Ad-hoc trying to avoid classes that don't inherit from vtkObjectBase
  if classname.endswith("Info") or \
      classname in ["vtkVariant","vtkTimeStamp","vtkIndent"] or \
      classname.endswith("String"):
    return ", smartpointer_nodeleter<{0} >()".format(classname)
  else:
    return ", vtk_deleter<{0} >()".format(classname)
