
classes_includes = {
  "std::set<std::string, std::less<std::string>, std::allocator<std::string> >"   : "set",
  "std::ostream"                                                                  : "iostream",
  "std::istream"                                                                  : "iostream",
  "std::basic_ios<char, std::char_traits<char> >"                                 : "iostream",
  # need to improve this part to allow writting here std::stringstream ...
  "std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >"  : "sstream",
  "std::complex<float>"   : "complex",
  "boost::basic_format<char, std::char_traits<char>, std::allocator<char> >"       : "boost/format.hpp", 
    "std::basic_istream" : "istream",
    "std::basic_ostream" : "ostream",
    "std::char_traits" : "string",
    "std::allocator" : "memory",
    "std::set" : "set",
    "new_allocator" : "memory",
    "boost::filesystem" : "boost/filesystem.hpp"
  }
  
