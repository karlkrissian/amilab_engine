#
# Parse types and variables
#

from xml.sax import saxutils,handler
import config

import argtypes
import re
import args



#------------------------------
class FindFiles(handler.ContentHandler):
  def __init__(self):
    self.number_of_files=0 # classes that match the current library filter

  def startElement(self, name, attrs):

    # first check for variable
    if name == 'File':
      self.number_of_files = self.number_of_files + 1
      fileid = attrs.get('id', None)
      name   = attrs.get('name', None)
      config.files[fileid]=name
