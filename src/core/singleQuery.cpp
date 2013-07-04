/*=============================================================================
#     FileName: singleQuery.cpp
#         Desc:  
#       Author: Taihua He
#        Email: hetaihua@ict.ac.cn
#      Version: 0.0.1
#   LastChange: 2013-06-24 14:33:30
#      History:
=============================================================================*/

#include "singleQuery.h"

namespace cppESClient {
    SingleQuery::SingleQuery( const std::string& index, const std::string& type):
        uriPrefix( "/" + index+ "/" + type) {}
    
    SingleQuery::SingleQuery(): uriPrefix("") {}

    SingleQuery::SingleQuery( const SingleQuery& rhs ): 
        uriPrefix( rhs.uriPrefix ) {}

    SingleQuery& SingleQuery::operator= ( const SingleQuery& rhs ) {
        if( this == &rhs ) return *this;
        uriPrefix = rhs.uriPrefix;
        return *this;
    }

    int SingleQuery::indexDocByID( const std::string& id, const std::string filter ) {
        if( filter == "" ) this->__set_uri( uriPrefix + "/" + id );
        else this->__set_uri( uriPrefix+"/"+id+"?"+filter );
        this->__set_method( Method::PUT );
    }

    int SingleQuery::indexDoc( const std::string filter) {
        if( filter == "" ) this->__set_uri( uriPrefix );
        else this->__set_uri( uriPrefix+"?"+filter );
        this->__set_method( Method::POST );
    }

    int SingleQuery::deleteDocByID( const std::string& id, const std::string filter) {
        if( filter == "" ) this->__set_uri( uriPrefix + "/" + id );
        else this->__set_uri( uriPrefix+"/"+id+"?"+filter );
        this->__set_method( Method::DELETE );
    }

    int SingleQuery::getDocByID( const std::string& id, const std::string filter) {
        if( filter == "" ) this->__set_uri( uriPrefix + "/" + id );
        else this->__set_uri( uriPrefix+"/"+id+"?"+filter );
        this->__set_method( Method::GET );
    }

    int SingleQuery::updateDocByID(const std::string &id, const std::string filter ){
        if( filter == "" ) this->__set_uri( uriPrefix + "/" + id + "/_update" );
        else this->__set_uri( uriPrefix+"/"+id+ "/_update"+"?"+filter );
        this->__set_method( Method::POST );
    }

    int SingleQuery::searchDoc( const std::string filter ) {
        if( filter == "" ) this->__set_uri( uriPrefix + "/_search" );
        else this->__set_uri( uriPrefix+"/_search?"+filter );
        this->__set_method( Method::GET );
    }



}
