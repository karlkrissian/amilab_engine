//
// C++ Interface: TypeConversion
//
// Description: 
//  Deal with possible type conversion, speed-up processing
//  and avoid endless loops
//
// Author: Karl Krissian <>, (C) 2016
//
// Copyright: See COPYING file that comes with this distribution
//
//

#pragma once
#ifndef TYPECONVERSION_H
#define TYPECONVERSION_H

#include <unordered_map>
#include <string>
#include <vector>
#include <Variable.hpp>

class TypeConversion
{
public:
    
    template <typename T> void RegisterType();
    
    // register the possibility to convertion type1 to type2, like (type2) type1
    void RegisterConversion( std::string type1, std::string type2);
    
    //
    void DisplayTypes();
    
private:
    
    // use hash table here ...
    std::unordered_map<std::string,int> types;
    
    // need dynamic 2D matrix
    // says if conversion if possible
    std::vector<std::vector<bool>> conversions;
};



//------------------------------------------------------------------------------
template <typename T>
void TypeConversion::RegisterType()
{
    int id = conversions.size();
    types[AMILabType<T>::name_as_string()] = id;
    for(int n=0;n<id;n++)
    {
        conversions[n].push_back(false);
    }
    conversions.push_back(std::vector<bool>(id,false));
    // set true for converting a type to itself, although it should never be used!
    conversions[id][id]=true;

    
    for(  std::vector<std::string>::iterator it = AMILabType<T>::conversion_types.begin();
          it!= AMILabType<T>::conversion_types.end();
          ++it)
    {
        this->RegisterConversion(AMILabType<T>::name_as_string(), *it);
    }
    
    
}


#endif // TYPECONVERSION_H
