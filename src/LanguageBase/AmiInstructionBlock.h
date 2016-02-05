//
// C++ Interface: AmiInstructionBlock
//
// Description: 
//
//
// Author: Karl Krissian <krissian@dis.ulpgc.es>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef _AmiInstructionBlock_h_
#define _AmiInstructionBlock_h_

#include <string>
#include <boost/shared_ptr.hpp>
#include "DefineClass.hpp"

#include "LanguageBaseConfigure.h"
class LanguageBase_EXPORT AmiInstructionBlock 
{
  DEFINE_CLASS(AmiInstructionBlock)

private:
  int     startingline;
  std::string  body;
public:
  int  GetStartingLine() { return startingline; }
  void SetStartingLine(int sl) 
  {  startingline = sl; }
  std::string & GetBody()  { return body; }
};


#endif //  _AmiInstructionBlock_h_