# -*- coding: windows-1252 -*-

# include everything here: difficult to sort
def get_include_file(classname, filename):
  last = filename.rfind('/wx/')
  incfile=filename[last+1:]
  #print "including class {0} from file {1}".format(classname,filename)
  #return incfile
  # get rid of specific library subdir
  s = incfile
  s = s.replace("/gtk","")
  s = s.replace("/gtk1","")
  s = s.replace("/mac/carbon","")
  s = s.replace("/mac","")
  s = s.replace("/osx","")
  s = s.replace("/carbon","")
  s = s.replace("/core","")
  s = s.replace("/cocoa","")
  s = s.replace("/msw","")
  s = s.replace("/msw/wince","")
  s = s.replace("/univ","")
  s = s.replace("/os2","")
  s = s.replace("/generic","")
  # TODO: check existence of the returned filename
  if s.find("tbar")      !=-1:  s = "wx/toolbar.h"
  if s.find("panelg.h")  !=-1:  s = "wx/panel.h"
  if s.find("paletteg.h")!=-1:  s = "wx/palette.h"
  if s.find("aboutdlgg.h")!=-1: s = "wx/aboutdlg.h"
  if s.find("choicdgg.h")!=-1:  s = "wx/choicdlg.h"
  if s.find("textdlgg.h")!=-1:  s = "wx/textdlg.h"
  if s.find("numdlgg.h")!=-1:   s = "wx/numdlg.h"
  if s.find("stdpaths.h")!=-1:  s = "wx/stdpaths.h"
  # AD-HOC fixes, can be improved ...
  if classname.find("Aui")!=-1: s = "wx/aui/aui.h"
  if classname=="wxDC":         s = "wx/dc.h"
  #if classname=="wxListCtrl":   s = "wx_includes.h"
  #if classname=="wxBitmap":     s = "wx_includes.h"
  #if classname=="wxRegionBase": s = "wx_includes.h"
  #if classname=="wxFontBase":   s = "wx_includes.h"
  #if classname=="wxBrush":      s = "wx_includes.h"
  #if classname=="wxGenericImageList": s = "wx_includes.h"
  #if classname=="wxMouseState": s = "wx_includes.h"
  #if classname=="wxPen":        s = "wx_includes.h"
  if classname=="wxWritableWCharBuffer":   s = "wx/string.h"
  if classname=="wxWritableCharBuffer":   s = "wx/string.h"
  if classname=="wxWCharBuffer":   s = "wx/string.h"
  if classname=="wxCharBuffer":   s = "wx/string.h"
  if classname=="wxStatusBar": s = "wx/statusbr.h"
  #if classname=="wxImageList": s = "wx_includes.h"
  if classname=="wxGDIImage": s = "wx/bitmap.h"
  if classname=="wxGDIImageHandler": s = "wx/bitmap.h"
  if classname=="wxIcon": s = "wx/icon.h"
  if classname=="wxPen": s = "wx/pen.h"
  if classname=="wxSplitterWindow": s = "wx/splitter.h"
  if classname=="wxSplitterWindow": s = "wx/splitter.h"
  if classname=="wxAppConsole": s = "wx/app.h"
  #if classname=="wxTextEntry":       s = "wx_includes.h"
  #if classname=="wxTextEntryBase":   s = "wx_includes.h"
  if classname=="wxSlider":   s = "wx/slider.h"
  #print "including class {0} from file '{1}' will use '{2}'".format(classname,incfile,s)
  s1 = '#include "{0}"'.format(s)
  if s.find("tipdlg.h"):
    s1 = '#include <wx/window.h>\n'+s1
  if s.find("aboutdlg.h"):
    s1 = s1+'\n#include <wx/generic/aboutdlgg.h>'
  #print "s1 = ",s1
  #if classname=="wxScopedCharTypeBuffer<char>":
  #  s1 = '#include <wx/wx.h>\n'+s1
  #if classname=="wxEventTypeTag<wxTimerEvent>":
  #  s1 = '#include <wx/timer.h>\n'+s1
  #if classname=="wxEventTypeTag<wxListEvent>":
  #  s1 = '#include <wx/listctrl.h>\n'+s1
  #if classname=="wxFormatString":
  #  s1 = '#include <wx/string.h>\n'+s1

  # include platform.h to avoid problems
  s1 = '#include <wx/platform.h>\n' + s1

  return s1
 
def get_var_filter():
  # allow std::auto_ptr in filter
  return "(std::auto_ptr<)?wx*"

def wrap_public_fields(classname):
  # only wrap public fields for wxPoint
  return classname=="wxPoint"

def implement_deleter(classname):
  if classname.find('auto_ptr'):
    return ""
  else:
    return ", smartpointer_nodeleter<{0} >()".format(classname)


#
# Create a standard smart pointer code for wxWidgets classes
# if the class inherits from wxWindow, no deleter, otherwise, use standard 
#  C++ delete
#
# classname is the class for which to create a smart pointer
# pointervarname is the name of the pointer variable
# resname is the name of the resulting smart pointer variable
# indent is the string to prepend for indentation
#

# Tentative to automatically create wxWidgets smart pointer with correct deleter failed 
# does not work since all classes cannot be dynamically casted
def CreateSmartPointer(classname,pointervarname,resname,indent,bases):
  #print "CreateSmartPointer \n"
  # need to check if the class inherits from wxWindow
  #classname_typedef = config.ClassTypeDef(classname)
  #print 'CreateSmartPointer({0},...)--'.format(classname),
  res = indent+'boost::shared_ptr<{0} > res;\n'.format(classname)
  bases1 = bases
  bases1.append(classname)
  if ('wxWindow' in bases1) or ('wxMenu' in bases1) or ('wxSizer' in bases1) or\
     ('wxMenuItem' in bases1):
    #print " no deleter"
    res += indent+'  {0} =  '.format(resname)+ \
            'boost::shared_ptr<{0} >({1}, smartpointer_nodeleter<{0} >());\n'.\
              format(classname,pointervarname)
  else:
    #print " use C++ delete"
    res += indent+'  {0} =  boost::shared_ptr<{1} >({2});\n'.\
            format(resname,classname,pointervarname)
  return res
  

