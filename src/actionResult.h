/*=============================================================================
#     FileName: actionResult.h
#         Desc:  
#       Author: Taihua He
#        Email: hetaihua@ict.ac.cn
#      Version: 0.0.1
#   LastChange: 2013-06-24 10:29:57
#      History:
=============================================================================*/

#ifndef actionResult_H
#define actionResult_H

//#include "../src/gen-cpp/Rest.h"
#include "gen-cpp/elasticsearch_types.h"
#include "thirdparty/JsonBox.h"

#include <string>

using namespace ::apache::thrift;
using namespace elasticsearch::thrift;
using namespace JsonBox;

namespace cppESClient {

class ActionResult: public Value{
    private:
       bool isloaded;
       RestResponse response;
    public:

        explicit ActionResult(): isloaded(false) {}

        RestResponse&   getResponse() {
            return response;
        }

        void    loadJSONFromResponse() {
            isloaded = true;
            this->loadFromString( response.body );
        }

        std::string     getResultStatusName();

        Value&          getFieldValue( const std::string & );
};

}
#endif


