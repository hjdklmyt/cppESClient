/*=============================================================================
#     FileName: countQuery.h
#         Desc:  
#       Author: Taihua He
#        Email: hetaihua@ict.ac.cn
#      Version: 0.0.1
#   LastChange: 2013-07-04 15:51:58
#      History:
=============================================================================*/


#ifndef countQuery_H
#define countQuery_H

#include <string>
#include <vector>
#include "../gen-cpp/elasticsearch_types.h"

using namespace ::elasticsearch::thrift;

namespace cppESClient {
    /**
     * CountQuery have to be used as follows:
     * CountQuery query;
     * query.addIndex(indexName); //optional to be called, must be called before addType if need.
     * query.addType( typeName ); //optional to be called, valid under one indexName existed.
     * query.setRequestPara( para ); //optional to be called, must be called after the above statements.
     * query.setQueryData( data ); //optional to be called and no requirement on calling order.
     * conn.execute( query, actionResult );
     */
    class CountQuery: public RestRequest {
        public:
          explicit CountQuery(): uriPrefix("") {
            this->__set_method( Method::GET );
          }
          
          ~CountQuery() throw () {}

          int addIndex( const std::string& );

          int addType( const std::string& );

          void clearIndicesAndTypes() {
              types.clear();
              indices.clear();
              uriPrefix = "";
          }

          void setQueryData( const std::string& data ) {
            this->__set_body( data );
          }

          void setRequestPara( const std::string &);

        private:
            std::vector<std::string> indices;
            std::vector<std::string> types;
            std::string              uriPrefix;
    };
}

#endif
