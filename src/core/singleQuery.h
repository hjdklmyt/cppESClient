/*=============================================================================
#     FileName: singleQuery.h
#         Desc:  
#       Author: Taihua He
#        Email: hetaihua@ict.ac.cn
#      Version: 0.0.1
#   LastChange: 2013-06-24 14:11:54
#      History:
=============================================================================*/

#ifndef singleQuery_H
#define singleQuery_H

#include <string>

#include "../gen-cpp/elasticsearch_types.h"

using namespace elasticsearch::thrift;

namespace cppESClient {
    class SingleQuery: public RestRequest {
        public:
        explicit SingleQuery( const std::string& indexName, const std::string& typeName );

        explicit SingleQuery();

        SingleQuery( const SingleQuery& );

        ~SingleQuery() throw() {}

        SingleQuery& operator=( const SingleQuery& rhs );

        void setQueryData( const std::string& data ) {
            this->__set_body(data);
        }

        int indexDocByID( const std::string& id, const std::string filter="");

        int indexDoc(const std::string filter="");

        int deleteDocByID( const std::string& id, const std::string filter="");

        int getDocByID( const std::string& id, const std::string filter="");

        int updateDocByID( const std::string& id, const std::string filter="");

        int searchDoc(const std::string filter="");

        private:
        std::string     uriPrefix;
    };
}

#endif
