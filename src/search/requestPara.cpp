/*=============================================================================
#     FileName: RequestPara.cpp
#         Desc:  
#       Author: Taihua He
#        Email: hetaihua@ict.ac.cn
#      Version: 0.0.1
#   LastChange: 2013-07-03 16:00:15
#      History:
=============================================================================*/

#include "requestPara.h"

#include <algorithm>
#include <sstream>

namespace cppESClient {

const char* nameValues[] = {
"q",
"df",
"analyzer",
"default_operator",
"explain",
"fields",
"sort",
"track_scores",
"timeout",
"from",
"size",
"search_type",
"lowercase_expanded_terms",
"analyze_wildcard",
"unknown"
};

int RequestPara::addParameter( Parameters::Name name, const std::string& str ) {
    if( name >= Parameters::UNKNOWN ) {
        return -1;
    }
    parameters[ static_cast<int>(name) ] = str; 
    return 0;
}

int RequestPara::addParameter( Parameters::Name name, const char * str ) {
    if( name >= Parameters::UNKNOWN ) {
        return -1;
    }
    parameters[ static_cast<int>(name) ] = std::string(str); 
    return 0;
}

int RequestPara::addParameter( Parameters::Name name, int size ) {
    if( name >= Parameters::UNKNOWN ) {
        return -1;
    }
    std::stringstream ss;
    std::string str;
    ss<<size;
    ss>>str;
    parameters[ static_cast<int>(name) ] = str;
    return 0;
}

int RequestPara::delParameter( Parameters::Name name ) {
    if( name >= Parameters::UNKNOWN ) {
        return -1;
    }
    std::map<int, std::string>::iterator iter = parameters.find( static_cast<int>(name) );
    if( iter == parameters.end() ) return -1;
    else {
        parameters.erase( iter );
        return 0;
    }
}

std::string RequestPara::toString() {
    std::string ret = "";

   for( std::map<int, std::string>::iterator iter = parameters.begin();  iter != parameters.end(); ++iter ) {
        ret += getParameterName( static_cast<Parameters::Name>( iter->first ) );
        ret += "=" + iter->second + "&";
   }

   if( ret.size() > 0 ) ret = ret.substr(0, ret.size() - 1);
   return ret;
}

}
