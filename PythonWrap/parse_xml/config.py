
import wrap_class
import re
import sys
import string
import args

# global dictionary of argument types
types             = dict()
classes           = dict()
typedefs          = dict()
variables         = dict()
enumvalues        = dict()
files             = dict()
operatorfunctions = []


classes_blacklist=[
  'wxHtmlWindowMouseHelper', # pb: no public constructor, destructor: can't be used with boost smart pointers
  'std::_Container_base_aux', # pb: wrapping std::vector with VC++
  'std::_Container_base_aux_alloc_real<std::allocator<std::string> >', # idem
  # TODO: find a solution for this problem ...
  # the classes in Release and Debug mode are not the same, but the configuration is done before
  'std::_Container_base_aux_alloc_real<std::allocator<double> >', # idem
  'std::_Container_base_aux_alloc_real<std::allocator<float> >', # idem
  'std::_Container_base_aux_alloc_real<std::allocator<int> >', # idem

  'std::_Ranit<double, long long, double const*, double const&>', #idem
  'std::_Ranit<float, long long, float const*, float const&>', #idem
  'std::_Ranit<int, long long, int const*, int const&>', #idem
  'std::_Ranit<std::string, long long, std::string const*, std::string const&>', #idem

  'std::_Iterator_with_base<std::bidirectional_iterator_tag, std::string, long long, std::string const*, std::string const&, std::_Iterator_base_aux>', # std::set<std::string>::iterator on windows with gccxml


  'wxTrackable', # problem protected destructor: to fix (wx2.9.3)
  #'wxConfigBase', # problems in 2.9.3 also
  'wxRefCounter', # protected destructor not compatible with smart pointers
 ]

classes_startswith_blacklist=[
  'std::_Iterator_with_base<',            # VC++ gccxml 
  'std::_Container_base_aux_alloc_real<', # idem
  #'boost::iterator_facade<'
  'boost::iterators::detail::iterator_facade_base', # filenames too long
  '__gnu_cxx::new_allocator',
  'std::basic_ios',
  'boost::filesystem',
]

# ignore specific members
members_blacklist=[
  'wxCreateObject',
  'wxCmdLineParser::wxCmdLineParser(wxCmdLineEntryDesc const*, int, wchar_t**)', # idem
  'wxCmdLineParser::wxCmdLineParser(int, wchar_t**)', # idem
  'wxWindowBase::GetToolTipText', # not implemented ...
  'wxStringBase::copy',
  'wxString::FormatV', 
  'wxString::PrintfV', 
  'wxFont::Unshare', 
  'wxStatusBar::SetBorderX', # not implemented ... 
  'wxStatusBar::SetBorderY', # not implemented ...
  'wxMenuBase::New',
  'wxMenuItem::GetFactoryPath',
  'wxMenuItemBase::GetAccelFromString',
  'wxColour::GetPixel', # problem with COLOREF on mac which is unsigned char[6]
  'wxColour::FromRGBColor', # pb with COLORREF
  'wxColour::m_pixel', # idem
  'wxConfigBase::Read(wxString const&, wchar_t const*) const', # version 2.9.3: pb with wxFromString(...)
  'wxConfigBase::Write(wxString const&, unsigned char const*)', # idem
  'wxConfigBase::Write(wxString const&, wchar_t const*)', # idem
  'wxAuiNotebook::InsertPage(unsigned long, wxWindow*, wxString const&, bool, wxBitmap const&)', # wx 2.9.3 ambiguity due to default param values
  'wxAuiNotebook::InsertPage(unsigned long, wxWindow*, wxString const&, bool, int)', # ambiguity 
  'wxCursor::GetHCURSOR',           # linking pb on macros
  'wxDateTime::IsGregorianDate',    # no implemented
  'wxToolBar::OnMouse',             # idem, MacOS linking error
  'wxStatusBarGeneric::SetBorderX', # idem, MacOS linking error
  'wxStatusBarGeneric::SetBorderY', # idem, MacOS linking error
  'wxArrayString::resize',          # no defined
  'wxMenuBar::Create',              # idem
  'wxButtonBase::GetDefaultSize',   # idem, MacOS linking
  'wxIcon::SetOk',                  # idem
  'wxWindow::FindItem',             # idem, MacOS error
  'wxPoint2DDouble::SetPolarCoordinates', # idem
  'wxPoint2DInt::SetPolarCoordinates', # idem
  'wxGenericListCtrl::Update(long)', # linking problem, don't know why ...
  'wxBitmap::GetSelectedInto', # not included in windows in release mode
  'wxBitmap::SetSelectedInto', # not included in windows in release mode
  'wxWindow::HandleQueryDragIcon',  # not include in windows link error
  'wxWindowBase::GetAdjustedMinSize', # probably not implemented in wx 3.0.2
  'wxWindowList::front', # returning reference to pointer
  'wxListCtrl::ConvertToMSWStyle', # linking problem MacOS
  'wxListCtrl::ChangeCurrent',     # idem
  'wxListCtrl::ResetCurrent',      # idem
  'MacCreateUIFont',               #Mac problem
  'MacGetCTFont',                  #idem
  'wxApp::Initialize',               # double pointer pb
  'wxApp::InitialzeVisual',          # not implemented, static function
  'wxApp::InitRichEdit',             # not implemented, static function
  'wxAppBase::Initialize',           # double pointer pb
  'wxAppConsole::Initialize',        # double pointer pb
  'wxAppConsole::OnAssertFailure',   # error in windows, not a member
  'wxAppConsole::OnAssert',          # error in windows, not a member
  'wxButton::GTKMouseEnters',    # not define with wx 2.9.2
  'wxButton::GTKMouseLeaves',    # not define with wx 2.9.2
  'wxButton::GTKPressed',        # not define with wx 2.9.2
  'wxButton::GTKReleased',       # not define with wx 2.9.2
  'wxAppConsoleBase::HandleEvent', # *func ? type not recognized probably
  'InternalTransformDerivative', # VTK: pointer to array ...
  'vtkPolyData::GetPointCells', # reference to pointer as parameter
  'vtkPolyData::GetCellPoints',  # idem
  'vtkSource::GetOutputs',       # double pointer
  'vtkProcessObject::GetInputs', # idem
  'vtkPlot::GetProperty', # seems not implemented
  'vtkPlot::SetProperty', # seems not implemented
  'vtkFixedPointVolumeRayCastMapper::LookupAndCombineIndependentColorsUC', # gives an error: to check
  'vtkFixedPointVolumeRayCastMapper::GetGradientNormal', # double pointer pb
  'vtkCellArray::GetNextCell', # reference to pointer
  'vtkCellArray::GetCell', # reference to pointer
  'Variable<AMIObject>::Value', # problem of undefined method public: static class boost::shared_ptr<class BasicVariable> __cdecl AMILabType<class AMIObject>::CreateVar(class AMIObject const &)
  'Variable<WrapClassMember>::Value', # problem of undefined method public: static class boost::shared_ptr<class BasicVariable> __cdecl AMILabType<class AMIObject>::CreateVar(class AMIObject const &)
]


class_types = ['Class','Struct']

# amilab available_types
available_classes=[]
available_classes_usedname=[]
parsed_classes=[]
wrapped_classes=[]
incomplete_classes=[]
new_needed_classes=[]

# available builtin type
available_types       = [
  'int',
  'float',
  'double',
  'unsigned char',
  'long',
  'long int',
  'unsigned long',
  'unsigned long int',
  'long unsigned int',
  'short',
  'short int',
  'unsigned short',
  'unsigned short int',
  'short unsigned int',
  'std::string',
  'bool',
  'void',
  'AMIFunction'
  ]
available_builtin_classes     = [ ]

# Builtin classes that may also be wrapped, so they need
# to have a special treatment for AMILabType<> type.
builtin_classes = ['AMIObject','WrapClassMember']

# not used
#available_pointertypes= ['int','float','double','unsigned char','long','long int','std::string','bool']

available_operators={ \
  '>'  : '__greaterthan__', \
  '<'  : '__lowerthan__', \
  '>>' : '__rightshift__', \
  '<<' : '__leftshift__', \
  '>=' : '__greaterorequalthan__', \
  '<=' : '__lowerorequalthan__', \
  '!=' : '__notequal__', \
  '==' : '__equal__', \
  '[]' : '__at__', \
  '()' : '__parenthesis__', \
  '='  : '__assign__',\
  '-=' : '__sub_assign__', \
  '+'  : '__add__', \
  '+=' : '__add_assign__', \
  '*'  : '__mult__', \
  '*()': '__indirection__', \
  '*=' : '__mult_assign__', \
  '/'  : '__div__', \
  '%'  : '__mod__', \
  '/=' : '__div_assign__', \
  '-'  : '__substract__', \
  '++' : '__preinc__', \
  '--' : '__predec__', \
  '++(int)':'__postinc__', \
  '--(int)':'__postdec__', \
  }

include_list = []
declare_list = []

#-------------------------------------------------------------
def ClassUsedName(classname):
  res = classname
  res = res.replace('<','_L_')
  res = res.replace('>','_G_')
  res = res.replace(',','_')
  res = res.replace('::','_')
  res = res.replace('*','_ptr')
  res = res.replace('&','_ref')
  res = res.replace('unsigned char', 'UC')
  res = res.replace('unsigned short','US')
  res = res.replace('unsigned int',  'UI')
  res = res.replace('unsigned long', 'UL')
  res = res.replace('short int',     'short')
  res = res.replace(' ','')
  res = res.replace('itk_', '')
  res = res.replace('(', '_')
  res = res.replace(')', '_')
  return res

#-------------------------------------------------------------
def ClassShortName(classname,libnamespace=""):
  res = classname
  # ---- commented: now wrapping std::string as a object 
  # ---- keep std::string as is
  # ---- if classname=="std::string":
  # ---- return res
  if libnamespace!="":
    res = res.replace(libnamespace+"::","")
  res = res.replace('<','_')
  res = res.replace('>','')
  res = res.replace(',','_')
  res = res.replace('::','_')
  res = res.replace('*','_ptr')
  res = res.replace('&','_ref')
  res = res.replace('unsigned char', 'UC')
  res = res.replace('unsigned short','US')
  res = res.replace('unsigned int',  'UI')
  res = res.replace('unsigned long', 'UL')
  res = res.replace('short int',     'short')
  res = res.replace(' ','')
  res = res.replace('itk_', '')
  res = res.replace('(', '_')
  res = res.replace(')', '_')
  return res

#-------------------------------------------------------------
def IsMultipleTemplate(classname):
  res=False
  if( (classname.find('<')>=0) and (classname.find(',')>=0) ):
    res=True
  return res
  
#-------------------------------------------------------------
def ClassTypeDef(classname):
  return ClassShortName(classname)



#------------------------------------------------------------------
#  GetBases
#------------------------------------------------------------------
def GetBases(classname, bases):
  if classname in classes.keys():
    classid = classes[classname]
    current_bases = types[classid].bases
    for (base,virtual) in current_bases:
      basename = types[base].GetString()
      basename1 = basename.replace(',',', ')
      basename1 = basename1.replace(',  ',', ')
      bases.append(basename1)
      GetBases(basename1,bases)

#------------------------------------------------------------------
#  AddInclude
#------------------------------------------------------------------
def AddInclude(f):
  if not(f in include_list):
    # temporary fix for <list>
    if f=='#include "stl_list.h"':
      f= '#include <list>'
    #print "adding include file {0}".format(f)
    include_list.append(f)

#------------------------------------------------------------------
#  AddDeclare
#------------------------------------------------------------------
def AddDeclare(f):
  if not(f in declare_list):
    #print "*********** adding {0} to declare_list".format(f)
    declare_list.append(f)

#------------------------------------------------------------------
#  CreateIncludes
#------------------------------------------------------------------
def CreateIncludes():
  res='';
  external_dll_included = False
  external_dll2_included = False
  for f in include_list:
    #res += '#include "{0}"\n'.format(f)
    res += '{0}\n'.format(f)
  
  for f in declare_list:
    declare_dll=False
    #print "{0} in declare list".format(f)
    if  f in args.val.available_external_classes and \
        args.val.external_dllname!='':
      declare_dll=True
      if not(external_dll_included):
        res += '#include "{0}Configure.h"\n'.format(args.val.external_dllname)
      external_dll_included = True
    # second external library
    declare_dll2=False
    if  f in args.val.available_external_classes2 and \
        args.val.external_dllname2!='':
      declare_dll2=True
      if not(external_dll2_included):
        res += '#include "{}Configure.h"\n'.format(args.val.external_dllname2)
      external_dll2_included = True
    
    # avoid inclusion, just declare the type ...
    res += '#ifndef {0}_declared\n'.format(ClassUsedName(f))
    res += '  #define {0}_declared\n'.format(ClassUsedName(f))
    if f.count(",")>0:
      res += '  typedef {0} {1};\n'.format(f,ClassTypeDef(f))
      if declare_dll:
        res += '  AMI_DECLARE_TYPE_DLL({0}_EXPORT,{1})\n'.format(
          args.val.external_dllname,
          ClassTypeDef(f))
      else:
        res += '  AMI_DECLARE_TYPE({0})\n'.format(ClassTypeDef(f))
    else:
      if f in builtin_classes:
        res += '  AMI_DECLARE_WRAPPED_LIMITED_TYPE({0})\n'.format(f)
      else:
        if declare_dll:
          res += '  AMI_DECLARE_TYPE_DLL({0}_EXPORT,{1})\n'.format(
            args.val.external_dllname,
            f)
        else:
          res += '  AMI_DECLARE_TYPE({0})\n'.format(f)
    res += '#endif\n'
  return res


#------------------------------------------------------------------
#  Check for boost shared pointer type
#------------------------------------------------------------------
def IsSharedPtr(typename):
  res = re.match(r"boost::shared_ptr<(.*)>",typename)
  if res!=None:
    # get rid of spaces with strip ...
    return res.group(1).strip()
  else:
    return None

#------------------------------------------------------------------
# Recursively find all the types within the template expression
#------------------------------------------------------------------
def templatetypes(string, all_types):
    #print "--------------"
    #print " starting templatetypes for", string
    #print ""
    types = []
    types.append("")
    #index
    idx = 0
    template_level=0
    intemplate=False
    template=""
    for char in string:
      #print types, " ", template
      if char == "<":
        template_level += 1
        if template_level == 1:
          template=""
        else:
          template+=char
      elif char == ">":
        template_level -= 1
        if template_level ==0:
          types[idx] += "<" + template + ">"
          templatetypes(template,all_types)
        else:
          template+=char
      else:
        if template_level>0:
          template+=char
        else:
          if char==",":
            types[idx] = types[idx].strip()
            types.append("")
            idx=idx+1
          else:
            types[idx] += char
    types[idx] = types[idx].strip()
    all_types +=  types


#-------------------------------------------
# Language tokens
#-------------------------------------------

improcess_flex_lpp      = sys.path[0]+"/../../src/Language/amiengine_flex.l"

def get_tokens():
    lex_tokens={}
    f = open (improcess_flex_lpp, "r")
    fc = f.read()
    parse_token=re.compile('/\*\{(.+),(.*)\}\*/')
    f.seek(0)
    #
    lines=string.split(fc,'\n')
    #
    for l in lines:
        t=parse_token.search(l)
        if t:
            lex_tokens[t.group(2)]=t.group(1)
            # now split expression and lex token:
    return lex_tokens

ami_tokens = get_tokens()
#print ami_tokens
