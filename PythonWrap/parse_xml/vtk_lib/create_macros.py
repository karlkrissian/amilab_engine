# -*- coding: utf-8 -*-
#
# Create macro variables
#

from xml.sax import saxutils,handler
from xml.sax import make_parser
import re
# load command line arguments
import args

# 1. find the event.h file

#-------------------------------------------------------------
# Find file
#-------------------------------------------------------------
#-------------------------------------------------------------
class FindFile(handler.ContentHandler):
  def __init__(self, filename):
    self.search_filename = filename
    self.found=False
    self.name=""

  def startElement(self, name, attrs):
    if not (name == "File"): return
    name = attrs.get('name', None)
    if name.find(self.search_filename)!=-1:
      self.name=name
      found = True


# 2. register event macros

# 3. add event macros


def CreateHeaderFileMacros(inputfile,outputfile,headerfilename):
  # Create the handler
  dh = FindFile(headerfilename+".h")

  parser = make_parser()
  # Tell the parser to use our handler
  parser.setContentHandler(dh)
  # Parse the input
  inputfile.seek(0)
  parser.parse(inputfile)
  res = ""
  if dh.name != "":
    print "file is: ", dh.name
    headerfile = open(dh.name, 'r')
    found_macros=[]
    for line in headerfile:
      # limited to macros of type #define VTKXXXX 0x9999 for the moment
      findmacro = re.match(r"^\s*#define\s+(VTK[_0-9a-zA-Z]+)\s*((0x[0-9]+)|([0-9]+))\s(//.*)*$",line)
      if (findmacro!=None):
        found_macros.append(findmacro.group(1))
        #print "Found macro : ", findmacro.group(1), " = ", findmacro.group(2)
      
    if len(found_macros)>0:
      # add all the values
      res += "\n"
      res += "  // MACROS from file {0}.h\n".format(headerfilename)
      for m in found_macros:
        res += "  #ifdef {0}\n".format(m)
        res += "    ADD_{0}_MACRO({1});\n".format(args.val.libname.upper(), m)
        res += "  #endif\n"
      res += "\n"
    else:
      res += "  // No macro found in file {0}.h\n".format(headerfilename)
  return res


def CreateMacros(inputfile,outputfile):
  wrapped_macros=""
  wrapped_macros += CreateHeaderFileMacros(inputfile,outputfile,"vtkType")

  if wrapped_macros!="":
    # Create the macros context
    outputfile.write("\n")
    outputfile.write( "  #define ADD_{0}_MACRO(name) \\\n".format(args.val.libname.upper()))
    outputfile.write( "    {\\\n")
    outputfile.write( "      BasicVariable::ptr var = AMILabType<int >::CreateVar(name);\\\n")
    outputfile.write( "      if (var.get()) {\\\n")
    outputfile.write( '        var->Rename(#name);\\\n')
    outputfile.write( '        macros_context->AddVar(var,macros_context);\\\n')
    outputfile.write( "      }\\\n")
    outputfile.write( "    }\\\n")
    outputfile.write("\n")

    # Create an amiobject
    outputfile.write( "\n")
    outputfile.write( "  // Macros context\n")
    outputfile.write( "  AMIObject::ptr obj_macros(new AMIObject);\n")
    outputfile.write( '  obj_macros->SetName("_vtk_macros");\n')
    outputfile.write( '  Variables::ptr macros_context = obj_macros->GetContext();\n')

    outputfile.write( wrapped_macros)
    
    outputfile.write( "  // Add macros to context, and add to default contexts\n")
    outputfile.write( "  context->AddVar<AMIObject>(obj_macros->GetName().c_str(),obj_macros,context);\n")
    outputfile.write( "  context->AddDefault(macros_context);\n")
    
    outputfile.write("  #undef ADD_{0}_MACRO\n".format(args.val.libname.upper()))
