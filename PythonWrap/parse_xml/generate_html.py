#
# Generates a HTML file with a list of the classes and methods that the Wrapping
# has been processed.
#
# The main functions are:
#
# - Initialization: Provides the values required for the generation of HTML
#   pages. This function must always be invoked before GenerateHTMLClassesFile
#   and GenerateHTMLClassFile.
#
# - GenerateHTMLClassesFile: Generates a file index.html that contains all the
#   appropriate classes wrapped target. If the classes appear without links it
#   is because the url is not found.
#
# - GenerateHTMLClassFile: Generates a HTML file for each class that contains a
#   list of its methods. If the methods appear without links it is because the
#   url is not found.
#
# These functions are invoked from the files:
#
# - parse_xml2.py: In the section of the generation of ancestors, it creates the
#   corresponding file index.html.
#
#   Note: In this file, makes the following call:
#
#   wrap_class.HTMLInitialization(args.val.generate_html,
#                                 args.val.templatefile_dir,
#                                 args.val.outputhtmldir,
#                                 "index.html",
#                                 args.val.url,
#                                 args.val.libname)
#
#   This function defined in the module wrap_class and internally invokes
#   function Initialization.
#
# - wrap_class.py: This module defines the function HTMLInitialization that
#   invokes the Initialization function to initialize the process. Since this
#   module is invoked the following functions:
#
#   - AddClassMethod: Add the object that represents a method to a list called
#     classmethods.
#
#   - GenerateHTMLStandardMethods: Calls the function GenerateHTMLClassFile in
#     the case of the standard methods of a class. It's a function temporary for
#     debugging and this call should be replaced by the function
#     GenerateHTMLClassFile.
#

#
# Import modules
#
import config
import hashlib
import shutil
import fileinput
import urllib2
import re


class generate_html:

  def __init__(self):
    self.classes=[]          # Classes list
    self.ignoremethods=[]    # List of methods to ignore
    self.classmethods=[]
    self.networking=True     # Determines if exists networking
    self.pathtemplate=""     # Path to HTML template
    self.filename=""         # HTML file name
    self.outputdir=""        # HTML output directory
    self.baseurl=""          # HTML base URL
    self.libname=""          # Library name
    self.createhtml=False    # Flag to generate html.
    self.doctype="doxygen"   # type of C++ documentation to link


  #-------------------------------------------------------------
  def Initialization(self,templatedir,outputdirectory,outputfilename,url,libraryname):
    self.networking=self.CheckURL(url)
    self.pathtemplate=templatedir+"wrap_templatehtmlhelp.html.in"
    self.outputdir=outputdirectory
    self.filename=self.outputdir+"/"+outputfilename
    self.baseurl=url
    self.libname=libraryname
    self.createhtml=True
    self.ResetIgnoreMethodList()
    self.ResetClassMethodList()
    # doxygen link info
    self.doxyclasses_html=None
    self.lastdoxyclassname=None
    self.lastdoxyclasslink=None
    self.lastdoxyclass_html=None

  #-------------------------------------------------------------
  def SetPublicMethods(self,pm):
    self.public_methods = pm

  #-------------------------------------------------------------
  def GenerateHTMLClassesFile(self,classlist):
    if (self.createhtml):
      htmltitle="AMILab-C++ Wrapping Class Reference"
      htmlbody="<h1>AMILab C++ wrapped classes"
      if self.libname!=None:
        htmlbody += " for library {0}".format(self.libname)
      htmlbody+="</h1>\n"
      htmlbody+="<h2>Available Wrapped Classes</h2>"
      #htmlbody+="Here are the wrapped classes with a link to their documentation:<br>"
      list_classes = []
      maxlength=25
      for classname in classlist:
        title="Link to AMILab documentation for {0}".format(classname)
        if len(classname)<maxlength:
          truncatedname=classname
        else:
          truncatedname=classname[:(maxlength-3)]+"..."
        namelink = self.GenerateAnchor(self.GenerateLocalURL(classname), \
                                title, truncatedname)
        list_classes.append(namelink )
      htmlbody+=self.CreateTableNoLink(classlist,list_classes,1,4,0,4)
      #print "Debug:\n"
      #print "pathtemplate: {0}\n".format(pathtemplate)
      #print "filename: {0}\n".format(filename)
      self.GenerateHTMLfile(self.pathtemplate, self.filename, htmltitle, htmlbody)

  #-------------------------------------------------------------
  def CreateTable(self,mlist,border,cellpadding,cellspacing,columns):
    tabletext = "<table align=center  border={0} cellpadding={1} cellspacing={2}>\n".\
                  format(border,cellpadding,cellspacing)
    tableindex=0
    tablecol=0
    tablecols=columns
    namecount=1
    prevname=""
    maxnamelength=20
    for fname in mlist:
      if prevname!=fname:
        # Close previous element
        if namecount>1:
          tabletext += " ({0})\n".format(namecount)
        if tableindex>0:
          tabletext += "</td>\n"
          tablecol = (tablecol+1)%tablecols
          if tablecol==0: tabletext += "</tr>\n"
        #
        namecount=1
        # Start new element
        if tablecol==0:
          tabletext += '<tr valign="top">\n'
        #::StripStart(wcm.GetFunctionName(),oc._GetName()+"::")
        tabletext += '<td > '
        tabletext += '<A href=\"#{0}\" title="Internal link to method {0}">'.format(fname)
        if len(fname)>maxnamelength:
          displayedname=fname[:(maxnamelength-3)]+"..."
        else:
          displayedname=fname
        tabletext +=  "{0}".format(displayedname)
        tabletext += " </A>"
      else:
        namecount=namecount+1
      prevname=fname
      tableindex = tableindex+1
    # Close last element
    if namecount>1:
      tabletext += " ({0})\n".format(namecount)
    tabletext += " </td>\n"
    tablecol = (tablecol+1)%tablecols
    if tablecol==0:  tabletext += "</tr>\n"
    tabletext += "</table>\n"
    return tabletext

  #-------------------------------------------------------------
  def CreateTableNoLink(self,mlist,processedlist,border,cellpadding,cellspacing,columns):
    tabletext = "<table align=center border={0} cellpadding={1} cellspacing={2}>\n".\
                  format(border,cellpadding,cellspacing)
    tablecol=0
    tablecols=columns
    prevchar=''
    mincount=10
    count=mincount+1
    index=0
    for fname in mlist:
      if self.libname!=None:
        newchar = fname.lstrip(self.libname)[0]
      else:
        newchar = fname[0]
      if newchar!=prevchar and count>mincount:
        # Start new element
        if tablecol==0: tabletext += "<tr>\n"
        tabletext += '<td align="center"> '
        tabletext +=  "<b>{0}..</b>".format(newchar)
        # Close previous element
        tabletext += "</td>\n"
        tablecol = (tablecol+1)%tablecols
        if tablecol==0: tabletext += "</tr>\n"
        count=0
      prevchar=newchar
      # Start new element
      if tablecol==0:  tabletext += "<tr>\n"
      tabletext += "<td> "
      tabletext +=  "{0}".format(processedlist[index])
      # Close previous element
      tabletext += "</td>\n"
      tablecol = (tablecol+1)%tablecols
      if tablecol==0:  tabletext += "</tr>\n"
      count=count+1
      index=index+1
    tabletext += "</table>\n"
    return tabletext

  #-------------------------------------------------------------
  def ListMethods(self,mlist,classname):
    text = ""
    text += "<table border=0 cellpadding=1 cellspacing=1>\n"
    text += "<tr><td></td><td >{0}</td><td colspan=2>{1}</td></tr>\n".format(\
            "<b><i>AMILab name;&nbsp;</i></b>",\
            "<b><i>C++ declaration and Doxygen link (grey means not wrapped)</i></b>")
    for m in mlist:
      #print "HTML method "+m.name
      if not m.iswrapped:
        text += '<tr style="color:#666666">'
      else:
        text += '<tr>'
      text += "  <td width=50> </td>\n"
      text += "  <td><A NAME=\"{0}\">".format(m.usedname)
      if m.usedname!=config.ClassUsedName(m.name):
        text+="&nbsp;&nbsp;"
      if m.usedname=="operator not available":
        mtext = "not avail"
      else:
        if m.usedname in config.ami_tokens.values():
          mtext = '_'+m.usedname
        else:
          mtext = m.usedname
      if not m.iswrapped:
        mtext = "/{0}/".format(mtext)
      text += "<em>{0}</em></A>".format(mtext)
      text += "</td>\n"
      #text += "</tr><tr>\n"
      #text += "<td width=50>  </td>" 
      url=self.MethodURL(classname,m)
      if url!="":
        text += '  <td><A title="Link to doxygen documentation"'
        text += 'href="{0}"><id>doc</i></A>&nbsp;</td>\n'.format(url)
      text += "  <td>" #+"<font color=\"#22AA22\">"
      if m.duplicated:
        text += ""
      else:
        text += m.GetHTMLDescription(classname,"")
      #if not m.iswrapped:
        #text += "</font>"
      text += "</td>\n"
      text += "</tr>\n"
    text += "</table>\n"
    return text

  #-------------------------------------------------------------
  def ListFields(self,flist,classname):
    text = ""
    text += "<table border=0 cellpadding=1 cellspacing=1>\n"
    for f in flist:
      text += "<tr>"
      text += "  <td width=50> </td>\n"
      fulltypename=config.types[f.typeid].GetFullString()
      if not f.iswrapped:
        text += '<font color="#666666">'
      text += "  <td>{0}</td>\n".format(fulltypename)
      text += "  <td><A NAME=\"{0}\">{0}<A></td>\n".format(f.name)
      if not f.iswrapped:
        text += "</font>"
      text += "</tr>\n"
    text += "</table>\n"
    return text

  #-------------------------------------------------------------
  def ListEnums(self,elist):
    text = ""
    text += "<table border=0 cellpadding=1 cellspacing=1>\n"
    for e in elist:
      enum_usedname = e.name.replace('.','enum')
      text += "<tr>"
      text += "  <td width=50> </td>\n"
      text += "  <td><A NAME=\"{0}\"><em>{1}</em><A></td>\n".format(\
                  e.name,enum_usedname)
      text += "</tr>\n"
      for ev in e.values.keys():
        text += "<tr><td></td><td></td>"
        text += "  <td><em>{0}</em></td>\n".format(ev)
        text += '  <td><font color="#2222DD">{0}</td></tr>\n'.format(e.values[ev])
    text += "</table>\n"
    return text

  #-------------------------------------------------------------
  def HTMLTitle(self,level,title):
    return '<h{0}><font color="#FF1010">{1}</font></h{0}>\n'.format(level,title)

  #-------------------------------------------------------------
  def GenerateHTMLClassFile(self,classname):
    #print "GenerateHTMLClassFile {0}".format(classname)
    #
    if(self.createhtml):
      self.filename = self.outputdir+"/"+self.GenerateLocalURL(classname)
      htmltitle = "AMILab - Automatic Wrapping from C++ - "+classname
      #
      htmlbody = '<h1 align="center">'+ self.GenerateClassFormat(classname, True)+'</h1>'
      # 1. Constructors
      classid = config.classes[classname]
      dh = config.types[classid]
      if len(dh.bases)>0:
        htmlbody += "<h2>Bases</h2>"
        text = ""
        text += "<table border=0 cellpadding=1 cellspacing=1>\n"
        text += "<tr><td></td><td >{0}</td><td>{1}</td></tr>\n".format(\
                "<b><i>AMILab name;&nbsp;</i></b>",\
                "<b><i>C++ declaration and HTML link (grey means not wrapped)</i></b>")
        for (base,virtual) in dh.bases:
          basename=config.types[base].GetString()
          virtualstring=''
          baseusedname=config.ClassUsedName(basename)
          if virtual=='1':
            virtualstring="virtual"
          if basename not in config.available_classes:
            text += '<tr style="color:#666666">'
          else:
            text += '<tr>'
          text += "  <td width=50> </td>\n"
          text += "  <td><em>{0}</em></td>\n".format(\
                    self.CheckTypeLink(basename,baseusedname))
          text += "  <td>{0}</td>\n".format(basename)
          text += "  <td>{0}</td>\n".format(virtualstring)
          text += "</tr>\n"
          text += "</table>\n"
        htmlbody += text
      
      # create list
      #htmlbody += self.HTMLTitle(2,"List of Methods")
      htmlbody += "<HR>\n"
      if len(self.public_methods.ConstructorNames)>0:
        htmlbody += self.HTMLTitle(3,"Constructors")
        m_list = self.public_methods.ConstructorNames
        m_list.sort()
        htmlbody += self.CreateTable(m_list,1,4,0,6)
      #
      # 2. Static methods
      if len(self.public_methods.StaticMethodNames)>0:
        htmlbody += self.HTMLTitle(3,"Static Methods")
        m_list = self.public_methods.StaticMethodNames
        m_list.sort()
        htmlbody += self.CreateTable(m_list,1,4,0,6)
      # 3. Standard public methods
      if len(self.public_methods.MethodNames)>0:
        htmlbody += self.HTMLTitle(3,"Standard Methods")
        m_list = self.public_methods.MethodNames
        m_list.sort()
        htmlbody += self.CreateTable(m_list,1,4,0,6)
      # 4. Operators
      if len(self.public_methods.OperatorMethodNames)>0:
        htmlbody += self.HTMLTitle(3,"Operators")
        m_list = self.public_methods.OperatorMethodNames
        m_list.sort()
        htmlbody += self.CreateTable(m_list,1,4,0,10)
      # 5. Public Fields
      f_list=[]
      for f in self.public_methods.Fields:
        f_list.append(f.name)
      if len(f_list)>0:
        htmlbody += self.HTMLTitle(3,"Fields")
        htmlbody += self.CreateTable(f_list,1,4,0,6)

      # 6. Public Enumerations
      e_list=[]
      for e in self.public_methods.Enumerations:
        e_list.append(e.name)
      if len(e_list)>0:
        htmlbody += self.HTMLTitle(3,"Enumerations")
        htmlbody += self.CreateTable(e_list,1,4,0,6)

      htmlbody += "<HR>\n"
      #htmlbody += self.HTMLTitle(2,"Detailled List of Methods")
      if len(self.public_methods.Constructors)>0:
        # 1. Constructors
        htmlbody += self.HTMLTitle(3,"Constructors")
        htmlbody += self.ListMethods(self.public_methods.Constructors,classname)
      # 2. Static methods
      if len(self.public_methods.StaticMethods)>0:
        htmlbody += self.HTMLTitle(3,"Static Methods")
        htmlbody += self.ListMethods(self.public_methods.StaticMethods,classname)
      # 3. Standard public methods
      if len(self.public_methods.Methods)>0:
        htmlbody += self.HTMLTitle(3,"Standard Methods")
        htmlbody += self.ListMethods(self.public_methods.Methods,classname)
      # 4. Operators
      if len(self.public_methods.OperatorMethods)>0:
        htmlbody += self.HTMLTitle(3,"Operators")
        htmlbody += self.ListMethods(self.public_methods.OperatorMethods,classname)
      # 5. Public Fields
      if len(f_list)>0:
        htmlbody += self.HTMLTitle(3,"Fields")
        htmlbody += self.ListFields(self.public_methods.Fields,classname)
      # 6. Public Enumerations
      if len(e_list)>0:
        htmlbody += self.HTMLTitle(3,"Enumerations")
        htmlbody += self.ListEnums(self.public_methods.Enumerations)

      htmlbody+=self.GenerateList("Unordered","","begin")

      self.GenerateHTMLfile(self.pathtemplate,\
                            self.filename,\
                            htmltitle,\
                            htmlbody)
      self.ResetClassMethodList()
      self.ResetIgnoreMethodList()

  #
  # Functions for debugging of generate_html module.
  #

  #-------------------------------------------------------------
  def GenerateHTMLStandardMethods(self,classname):
    #
    if(self.createhtml):
      self.GenerateHTMLClassFile(classname)
      self.ResetClassMethodList()
      self.ResetIgnoreMethodList()

  #
  # Internal functions of the generate_html module.
  #

  #-------------------------------------------------------------
  def CheckURL(self,url):
    #
    print "Checking url {0}".format(url)
    res=True
    req = urllib2.Request(url)
    try: urllib2.urlopen(req)
    except urllib2.URLError:
      res=False
    #print "result = {0}".format(res)
    return res

  #-------------------------------------------------------------
  def GenerateHTMLfile(self,htmltemplate,htmlfilename,htmltitle,htmlbody):
    #
    shutil.copyfile(htmltemplate,htmlfilename)
    for line in fileinput.FileInput(htmlfilename,inplace=1):
      line = line.replace("__TITLE__", htmltitle)
      line = line.replace("__BODY__",  htmlbody)
      print line,  


  #-------------------------------------------------------------
  def GenerateAnchor(self,url,title,body):
    res = "<a href=\"{0}\" title=\"{1}\">{2}</a>".format(url,title,body)
    return res

  #-------------------------------------------------------------
  def GenerateLineBreak(self):
    return "<br />"

  #-------------------------------------------------------------
  def GenerateList(self,listtype,options,flag):
    if(listtype=="Unordered"):
      if(flag=="begin"):
        res="<UL "+options+">"
      else:
        res="</UL>"
    else: # Ordered
      if(flag=="begin"):
        res="<OL "+options+">"
      else:
        res="</OL>"
    return res
    
  #-------------------------------------------------------------
  def GenerateListItem(self,item):
    return "<LI> "+item

  #-------------------------------------------------------------
  def GenerateDoxygenFileName(self,classname):
    input = classname
    input = input.replace('_','__')
    input = input.replace(':','_1')
    input = input.replace('/','_2')
    input = input.replace('<','_3')
    input = input.replace('>','_4')  
    input = input.replace('*','_5')
    input = input.replace('&','_6')
    input = input.replace('|','_7')
    input = input.replace('.','_8')
    input = input.replace('!','_9')
    input = input.replace(',','_00')
    input = input.replace(' ','_01')
    input = input.replace('{','_02') 
    input = input.replace('}','_03')
    input = input.replace('?','_04')
    input = input.replace('^','_05')
    input = input.replace('%','_06')
    input = input.replace('(','_07')
    input = input.replace(')','_08')
    input = input.replace('+','_09')
    input = input.replace('=','_0A')
    i=0
    res=""
    while i < len(input):
      if(input[i].isupper()):
        res+="_"+input[i]
      else:
        res+=input[i]
      i=i+1
    res = res.lower()
    return res

  #-------------------------------------------------------------
  def GenerateLocalURL(self,classname):
    cname = classname
    cname = cname.replace('::','_')
    cname = cname.replace('<','_')
    cname = cname.replace('>','_')
    return cname+".html"

  #-------------------------------------------------------------
  def GenerateClassFormat(self, classname, isexternalanchor):
    #
    url=self.baseurl
    #
    if(isexternalanchor):
      if self.libname=="wx":
        #Format for the version 2.8.x
        url+="wx_"+classname.lower()+".html#"+classname.lower()
      else:
        if self.doctype=="doxygen":
          vtklink = self.baseurl+'/classes.html'
          if self.doxyclasses_html==None:
            # Download the HTML file linking to the vtk classes ...
            # we should deal with VTK version here ...
            try:
              f = urllib2.urlopen(vtklink)
              self.doxyclasses_html = f.read()
            except IOError:
              print "Error: Failed to open {0}".format(vtklink)
              self.doxyclasses_html = ""
          if self.lastdoxyclassname==None or self.lastdoxyclassname!=classname:
            # now look for the filename using regular expressions
            m = re.search(r"<a[^>]*\"([^\"\.]*)\.html\"[^>]*>"+classname+"</a>",self.doxyclasses_html)
            if m!=None:
              fileid=m.group(1).strip()
              print "Found VTK file {0} for class {1}".format(fileid,classname)
              classurl= self.baseurl+"/{0}.html".format(fileid)
              self.lastdoxyclasslink=classurl
              # download the class documentation
              try:
                f = urllib2.urlopen(classurl)
                self.lastdoxyclass_html = f.read()
              except IOError:
                print "Error: Failed to open {0}".format(classurl)
                self.lastdoxyclass_html = ""
              #print "lastdoxyclass_html {0}".format(self.lastdoxyclass_html[:100])
            else:
              self.lastdoxyclasslink=None
              self.lastdoxyclass_html=None
              classurl=vtklink
          else:
            classurl=self.lastdoxyclasslink
          url=classurl
          self.lastdoxyclassname=classname
        else:
          url+="class"+self.GenerateDoxygenFileName(classname)+".html"

      if(self.networking):
        if self.CheckURL(url):
          res = self.GenerateAnchor(url, classname, classname)
        else:
          res=classname
      else:
        res = self.GenerateAnchor(url, classname, classname)
    else:
      res = self.GenerateAnchor(self.GenerateLocalURL(classname), \
                                classname, classname)
    return res

  #-------------------------------------------------------------
  def CheckTypeLink(self,typename,content):
    if typename in config.available_classes:
      res=self.GenerateAnchor(self.GenerateLocalURL(typename), \
                              "AMILab documentation link",content)
    else:
      res = content
    return res

  #-------------------------------------------------------------
  def MethodURL(self,classname, method):
    #
    if not self.networking:
      return ""
    methodname=method.name
    signature=method.GetDescription(classname,False)
    url=self.baseurl
    if self.libname=="wx":
      #Format for the version 2.8.x
      methodname=methodname.replace('_','')
      #print "GenerateMethodFormat: methodname={0}\n".format(methodname)
      if methodname=="!":        methodname="operatornot"
      if methodname=="=":        methodname="operatorassign"
      if methodname=="+":        methodname="operatorplus"
      if methodname=="+=":       methodname="plusequal"
      if methodname=="[]":       methodname="operatorbracket"
      if methodname=="()":       methodname="operatorparenth"
      if methodname=="<<":       methodname="operatorout"
      if methodname==">>":       methodname="operatorin"
      # constructors
      if methodname==classname:  methodname="ctor"
      url+="wx_"+classname.lower()+".html#"+classname.lower()+methodname.lower()
    else:
      if self.doctype=="doxygen":
        #print "URL is {0}".format(self.baseurl)
        vtklink = self.baseurl+'/classes.html'
        if self.doxyclasses_html==None:
          # Download the HTML file linking to the vtk classes ...
          # we should deal with VTK version here ...
          try:
            f = urllib2.urlopen(vtklink)
            self.doxyclasses_html = f.read()
          except IOError:
            print "Error: Failed to open {0}".format(vtklink)
            self.doxyclasses_html = ""
        if self.lastdoxyclassname==None or self.lastdoxyclassname!=classname:
          # now look for the filename using regular expressions
          m = re.search(r"<a[^>]*\"([^\"\.]*)\.html\"[^>]*>"+classname+"</a>",self.doxyclasses_html)
          if m!=None:
            fileid=m.group(1).strip()
            print "Found VTK file {0} for class {1}".format(fileid,classname)
            classurl=self.baseurl+"/{0}.html".format(fileid)
            self.lastdoxyclasslink=classurl
            # download the class documentation
            try:
              f = urllib2.urlopen(classurl)
              self.lastdoxyclass_html = f.read()
            except IOError:
              print "Error: Failed to open {0}".format(classurl)
              self.lastdoxyclass_html = ""
            #print "lastdoxyclass_html {0}".format(self.lastdoxyclass_html[:100])
          else:
            self.lastdoxyclasslink=None
            self.lastdoxyclass_html=None
            classurl=vtklink
        else:
          classurl=self.lastdoxyclasslink
        if self.lastdoxyclass_html!=None:
          # now look for the tag
          print "Looking for method '{0}' ".format(method.name)
          rname=method.name
          if method.name=="="  : rname=r"operator\="
          if method.name=="==" : rname=r"operator\=\="
          if method.name=="[]" : rname=r"operator\[\]"
          if method.name=="++" : rname=r"operator\+\+"
          if method.name=="+"  : rname=r"operator\+"
          if method.name=="+=" : rname=r"operator\+\="
          if method.name=="-"  : rname=r"operator\-"
          if method.name=="--" : rname=r"operator\-\-"
          if method.name=="-=" : rname=r"operator\-\="
          if method.name=="*"  : rname=r"operator\*"
          if method.name=="*=" : rname=r"operator\*\="
          if method.name=="/" : rname=r"operator/"
          if method.name=="/=" : rname=r"operator/\="
          if method.name=="%"  : rname=r"operator%"
          if method.name=="%=" : rname=r"operator%\="
          if method.name=="<"  : rname=r"operator&lt;"
          if method.name=="<=" : rname=r"operator&lt;="
          if method.name==">"  : rname=r"operator&gt;"
          if method.name==">=" : rname=r"operator&gt;="
          if method.name=="!=" : rname=r"operator\!\="
          if method.name=="!"  : rname=r"operator\!"
          if method.name=="|"  : rname=r"operator\|"
          if method.name=="&"  : rname=r"operator&amp;"
          if method.name=="&&" : rname=r"operator&amp;&amp;"
          if method.name=="||" : rname=r"operator\|\|"
          #print "rname = {0}".format(rname)
          if method.name=="^"  : rname=r"operator\^"
          m = re.search(r"<a[^>]*\"([^\"\.]*\.html#[^\"]*)\"[^>]*>"+rname+"</a>",\
                        self.lastdoxyclass_html)
          if m!=None:
            url=self.baseurl+"/{0}".format(m.group(1).strip())
          else:
            print "----- Method {0} not found -----".format(method.name)
            url=classurl
        else:
          url=self.baseurl+'/classes.html'
        self.lastdoxyclassname=classname
      else:
        #Doxygen methodname format:
        # type classname::methodnamemethodname(parameters)
        #Example:
        # Input:  bool MyClass::Init(const std::string &InputFileName, const std::string &OutputFileName)
        # Output: bool MyClass::InitInit(const std::string &InputFileName, const std::string &OutputFileName)
        #
        # Version con clase metodos que apunten con wxwidgets2.8.
        #print signature
        posbegin=signature.find("::")+2
        posend=signature.find("(")
        themethodname=signature[posbegin:posend]
        themethodname=signature[:posend]+themethodname+signature[posend:]
        #print "GenerateMethodFormat: themethodname={0}\n".format(themethodname)

        txt=hashlib.md5()
        txt.update(themethodname)
        url+="class"+self.GenerateDoxygenFileName(classname)+".html#a"+txt.hexdigest()
    return url

  #-------------------------------------------------------------
  def GenerateMethodFormat(self,classname, methodname, body, signature):
    #
    url=self.baseurl
    if self.libname=="wx":
      #Format for the version 2.8.x
      methodname=methodname.replace('_','')
      #print "GenerateMethodFormat: methodname={0}\n".format(methodname)
      url+="wx_"+classname.lower()+".html#"+classname.lower()+methodname.lower()
    else:
      #Doxygen methodname format:
      # type classname::methodnamemethodname(parameters)
      #Example:
      # Input:  bool MyClass::Init(const std::string &InputFileName, const std::string &OutputFileName)
      # Output: bool MyClass::InitInit(const std::string &InputFileName, const std::string &OutputFileName)
      #
      # Version con clase metodos que apunten con wxwidgets2.8.
      #print signature
      posbegin=signature.find("::")+2
      posend=signature.find("(")
      themethodname=signature[posbegin:posend]
      themethodname=signature[:posend]+themethodname+signature[posend:]
      #print "GenerateMethodFormat: themethodname={0}\n".format(themethodname)

      txt=hashlib.md5()
      txt.update(themethodname)
      url+="class"+GenerateDoxygenFileName(classname)+".html#a"+txt.hexdigest()

    if(self.networking):
      #if self.CheckURL(url):
      res = self.GenerateAnchor(url, methodname, body)
      #else:
      #  res=methodname
    else:
      res = self.GenerateAnchor(url, methodname, methodname)
    res = res + " " + signature
    return res

  #-------------------------------------------------------------
  def IsClassProcessed(self,classname):
    res=False
    for i in range(0,len(self.classes)):
      if(self.classes[i]==classname):
        res=True
        break
    return res

  #-------------------------------------------------------------
  def ResetIgnoreMethodList(self):
    self.ignoremethods=[]

  #-------------------------------------------------------------
  def ResetClassMethodList(self):
    self.classmethods =[]

  #-------------------------------------------------------------
  def AddClassMethod(self,method):
    if(self.createhtml):
      self.classmethods.append(method)

  #-------------------------------------------------------------
  def IsOverloaded(self,methodname):
    pattern="_([0-9])+"
    if(re.search(pattern,methodname)):
      return True;
    else:
      return False;

  #-------------------------------------------------------------
  def IsIgnored(self,methodname):
    res=False
    for i in range(0,len(self.ignoremethods)):
      if(self.ignoremethods[i]==methodname):
        res=True
        break
    return res

  #-------------------------------------------------------------
  def GetMethodName(self,methodname):
    res=methodname
    pattern="_([0-9])+"
    isLocated=re.search(pattern,methodname)
    if(isLocated):
      pos=methodname.find(isLocated.group(0))
      res=methodname[0:pos]
    return res

obj = generate_html()
