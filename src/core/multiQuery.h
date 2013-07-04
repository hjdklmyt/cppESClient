/*=============================================================================
#     FileName: multiQuery.h
#         Desc:  
#       Author: Taihua He
#        Email: hetaihua@ict.ac.cn
#      Version: 0.0.1
#   LastChange: 2013-06-26 10:56:06
#      History:
=============================================================================*/

#ifndef multiQuery_H
#define multiQuery_H

#include <string>

#include "../gen-cpp/elasticsearch_types.h"
using namespace elasticsearch::thrift;

namespace cppESClient {
    class MultiQuery: public RestRequest {
        public:
            explicit MultiQuery( const std::string index="", const std::string type="" );

            MultiQuery( const MultiQuery& rhs );

            ~MultiQuery() throw() {}

            MultiQuery& operator=( const MultiQuery& rhs);

            void setQueryData( const std::string& data ) {
                this->__set_body(data);
            }

            int multiGet();

            int multiSearch();

            int bulk();

            int bulkUDP();
        private:
            std::string uriPrefix;
    };
}

#endif
