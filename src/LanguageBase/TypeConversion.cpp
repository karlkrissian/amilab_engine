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


#include "TypeConversion.h"
#include <iostream>
#include "Variable.hpp"

//------------------------------------------------------------------------------
void TypeConversion::RegisterConversion( std::string type1, std::string type2)
{
    std::cout << "RegisterConversion " << type1 << " --> " << type2 << std::endl;
    int type1_id = types[type1];
    int type2_id = types[type2];
    conversions[type1_id][type2_id] = true;
}

//------------------------------------------------------------------------------
void TypeConversion::DisplayTypes()
{

    std::cout << "List of available types " << std::endl;
    for(auto it = types.begin(); it != types.end(); ++it)
    {
        std::cout << "'" << it->first << "' --> " << it->second << std::endl;
    }
    
}
