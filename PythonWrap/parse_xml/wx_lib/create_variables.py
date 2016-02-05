#
# Create macro variables
#

from xml.sax import saxutils,handler
from xml.sax import make_parser
import re
# load command line arguments
import args

#import config



def CreateVariables(outputfile,config):
  found_variables=[]
  for v in config.variables.keys():
    # conditions 1: start with wxEVT, 2: is constant, 3: is a direct supported type
    namecheck = re.match(r"wxEVT[a-zA-Z0-0_]*",v)
    argtype = config.types[config.variables[v]]
    typeok  = argtype.IsConst() and \
      (argtype.GetString() in config.available_types or \
       argtype.GetString() in config.available_classes or \
       argtype.GetString().startswith("wxEventTypeTag"))
    if namecheck:
      #print "Type '{0}' for var {1}, ok={2}".format(argtype.GetString(),v,typeok)
      if typeok:
        #print "Found variable : ", v, " of type : ", argtype.GetString()
        found_variables.append(v)
    
  found_variables.sort()
  # Create the variables context
  outputfile.write("\n")
  outputfile.write( "  #define ADD_{0}_VAR(type,name) \\\n".format(args.val.libname.upper()))
  outputfile.write( "    {\\\n")
  outputfile.write( "      BasicVariable::ptr var = AMILabType<type >::CreateVar(name);\\\n")
  outputfile.write( "      if (var.get()) {\\\n")
  outputfile.write( '        var->Rename(#name);\\\n')
  outputfile.write( '        vars_context->AddVar(var,vars_context);\\\n')
  outputfile.write( "      }\\\n")
  outputfile.write( "    }\\\n")
  outputfile.write("\n")


  # Create an amiobject
  outputfile.write( "\n")
  outputfile.write( "  // Variables context\n")
  outputfile.write( "  AMIObject::ptr obj_vars(new AMIObject);\n")
  outputfile.write( '  obj_vars->SetName("_wx_variables");\n')
  outputfile.write( '  Variables::ptr vars_context = obj_vars->GetContext();\n')
  # add all the values
  outputfile.write( "\n")
  for v in found_variables:
    vartypename=config.types[config.variables[v]].GetString()
    # avoid conversion to int for events ...
    if vartypename.startswith("wxEventTypeTag"):
      outputfile.write( "  ADD_{0}_VAR({1},{2});\n".format(args.val.libname.upper(),\
                        'int', v))
    else:
      outputfile.write( "  ADD_{0}_VAR({1},{2});\n".format(args.val.libname.upper(),\
                        vartypename, v))
  outputfile.write( "\n")
  outputfile.write( "  // Add variables to context, and add to default contexts\n")
  outputfile.write( "  context->AddVar<AMIObject>(obj_vars->GetName().c_str(),obj_vars,context);\n")
  outputfile.write( "  context->AddDefault(vars_context);\n")
  

  outputfile.write("  #undef ADD_{0}_VAR\n".format(args.val.libname.upper()))
