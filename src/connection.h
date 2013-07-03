/*=============================================================================
#     FileName: connection.h
#         Desc:  
#       Author: Taihua He
#        Email: hetaihua@ict.ac.cn
#      Version: 0.0.1
#   LastChange: 2013-06-21 14:36:44
#      History:
=============================================================================*/

#ifndef connection_H
#define connection_H

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "gen-cpp/elasticsearch_types.h"
#include "gen-cpp/elasticsearch_constants.h"
#include "gen-cpp/Rest.h"
#include "actionResult.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;;
using namespace elasticsearch::thrift;

using namespace boost;


namespace cppESClient {
    class Connection {
        public:
        explicit Connection( const std::string & address, int port );
        ~Connection();

        Connection( const Connection & );

        Connection& operator=( const Connection &);
       
        Status::type execute( const RestRequest&, ActionResult &) const;

        const std::string& getAddress() const {
            return address;
        }

        int getPort() const {
            return port;
        }

        private:
        RestClient * client;
        shared_ptr<TTransport> transport;
        std::string address;
        int port;
        void init() ; 
    }; 
}

#endif

