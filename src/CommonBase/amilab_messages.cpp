
#include "amilab_messages.h"
#include <iostream>


// Simple IO message functions
CommonBase_EXPORT void PrintWarning(const char* mess)
{
  std::cout << mess << std::endl;
}
//
CommonBase_EXPORT void PrintWarning(const ami::format& f)
{
  std::cout << f.GetString() << std::endl;
}
//
CommonBase_EXPORT void PrintError(const char* mess)
{
  std::cerr << mess << std::endl;
}
//
CommonBase_EXPORT void PrintError(const ami::format& f)
{
  std::cerr << f.GetString() << std::endl;
}
