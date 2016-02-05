
#include "AmiMessage.h"
#include <iostream>


//-----------------------------------------
int AmiMessage::Error(const char* message)
{
    if (ErrorFunction!=NULL) {
      return (*ErrorFunction)(message);
    } else {
      std::cerr << "AmiMessage (TODO deal with message) : " << message << std::endl;
      return 0;
    }
}

//-----------------------------------------
int  AmiMessage::Error(const std::string& st) 
{ 
    return this->Error((char*)st.c_str()); 
}

//-----------------------------------------
void AmiMessage::SetErrorFunction(int (*ErrFunc)(const char*))
{
    ErrorFunction = ErrFunc;
}


//-----------------------------------------
void AmiMessage::IncCommand(const std::string& cmd)
{
    if (IncCommandFunction!=NULL) {
      (*IncCommandFunction)(cmd);
    } else {
      std::cout << "AmiMessage (TODO add to console) : "<< cmd << std::endl;
    }
}

//-----------------------------------------
void AmiMessage::SetIncCommandFunction(void (*IncCmdFunc)(const std::string&))
{
  IncCommandFunction = IncCmdFunc;
}
