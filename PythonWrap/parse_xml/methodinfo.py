
import config

#------------------------------
def FormatArgDefault(argdef):
  # to deal with string within default parameter ...
  return argdef.replace('"',"'").replace('\\000','')


#-------------------------------------------------------------------------------
# Gathered method or function information
#
class MethodInfo:
  def __init__(self):
    self.name=""
    self.usedname=""
    self.duplicated=False
    self.args=[]
    self.returntype=None
    self.missingtypes=False
    self.is_copyconstr=False
    self.static="0"
    self.const=False
    self.deprecated=False
    self.demangled=""
    self.converter=False
    self.virtual=False
    # added to deal with standalone functions
    self.methodid = ""
    self.fileid   = ""

  def GetDescription(self,classname,constructor=False):
    res=''
    if constructor:
      res += "Constructor "
    if self.static==1:
      res += "static "
    if self.returntype!=None:
      res += config.types[self.returntype].GetFullString()+" "
    if self.name in config.available_operators.keys():
      res += classname+"::operator "+self.name+'('
    else:
      res += classname+"::"+self.name+'('
    for a in self.args:
      if a.name=='lpszHostname':
        print "type for lpszHostname {0}".format(a.typeid)
        print "type for lpszHostname {0}".format(config.types[a.typeid].GetType())
        print "type for lpszHostname {0}".format(config.types[a.typeid].GetFullString())
      res +=  config.types[a.typeid].GetFullString()+" "+a.name
      if a.default!=None:
        res += " = {0}".format(FormatArgDefault(a.default))
      res += ", "
    if len(self.args)>0:
      res = res[:-2]
    res += ')'
    if self.const:
      res += " const"
    return res

  def GetHTMLDescription(self,classname,url):
    if url!="":
      mname = '<A title="Link to doxygen documentation" href="{0}"><i>Dox</i></A>&nbsp;{1}'.format(url,self.name)
    else:
      mname = self.name
    mname='<b>{0}</b>'.format(mname)
    res=''
    if self.static==1:
      res += "static "
    if self.returntype!=None:
      typestr = config.types[self.returntype].GetFullString()
      typestr = typestr.replace('<','&lt;')
      typestr = typestr.replace('>','&gt;')
      typestr = generate_html.obj.CheckTypeLink(\
                      config.types[self.returntype].GetString(),\
                      typestr)
      res += "<em>{0}</em> ".format(typestr)
    if self.name in config.available_operators.keys():
      res += "operator "+mname+'('
    else:
      res += mname+'('
    paramlist=""
    for a in self.args:
      typestr = config.types[a.typeid].GetFullString()
      typestr = typestr.replace('<','&lt;')
      typestr = typestr.replace('>','&gt;')
      typestr = generate_html.obj.CheckTypeLink(\
                      config.types[a.typeid].GetString(),\
                      typestr)
      paramlist +=  "<em>{0}</em> <font color=\"#22AA22\">{1}</font>".format(typestr,a.name)
      if a.default!=None:
        paramlist += " = {0}".format(FormatArgDefault(a.default))
      paramlist += ", "
    if len(self.args)>0:
      paramlist = paramlist[:-2]
    res += paramlist+')'
    return res

