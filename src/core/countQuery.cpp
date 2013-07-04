/*=============================================================================
#     FileName: countQuery.cpp
#         Desc:  
#       Author: Taihua He
#        Email: hetaihua@ict.ac.cn
#      Version: 0.0.1
#   LastChange: 2013-07-04 16:08:03
#      History:
=============================================================================*/

#include "countQuery.h"

namespace cppESClient {
    int CountQuery::addIndex( const std::string& indexName ) {
        if( indices.size() > 0 && types.size() > 0 ) return -1;

        if( indices.size() == 0 ) uriPrefix += "/" + indexName;
        else uriPrefix += "," + indexName;
        this->__set_uri( uriPrefix + "/_count" );
        indices.push_back( indexName );
        return 0;
    }

    int CountQuery::addType( const std::string& typeName ) {
        if( indices.size() != 1 ) return -1;

        if( types.size() == 0 ) uriPrefix += "/" + typeName;
        else uriPrefix += "," + typeName;
        this->__set_uri( uriPrefix + "/_count");
        types.push_back( typeName );
        return 0;
    }

    void CountQuery::setRequestPara( const std::string& para ) {
        this->__set_uri( uriPrefix + "/_count?" + para );
    }
}


