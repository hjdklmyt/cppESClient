#include "multiQuery.h"

namespace cppESClient {

    MultiQuery::MultiQuery( const std::string index, const std::string type) {
        if( index != "" ) uriPrefix = "/"+index;
        if( type != "" ) uriPrefix += "/"+type;
    }

    int MultiQuery::multiGet() {
        this->__set_uri( uriPrefix+"/_mget");
    }

    int MultiQuery::multiSearch() {
        this->__set_uri( uriPrefix+"/_msearch");
        this->__set_method( Method::GET );
    }

    int MultiQuery::bulk() {
        this->__set_uri( uriPrefix + "/_bulk");
        this->__set_method( Method::POST );
    }
}
