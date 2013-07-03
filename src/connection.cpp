#include "connection.h"

namespace cppESClient {
    Connection::Connection( const std::string& _address, int _port ):
    address( _address ), port( _port ) {
        init();
    }

    Connection::~Connection() {
        transport->close();
        delete client;
    }

    Connection& Connection::operator=(const Connection &rhs ) {
        if( this == &rhs ) return *this;
        address = rhs.address;
        port = rhs.port;
        init();
        return *this;
    }

    Connection::Connection( const Connection& rhs ):
    address( rhs.getAddress() ), port( rhs.getPort() ) {
        if( this == &rhs ) return;
        init();
    }

    void Connection::init() {
        shared_ptr<TTransport> socket( new TSocket( address, port) );
        transport = shared_ptr<TTransport>( new TBufferedTransport(socket) );
        shared_ptr<TProtocol> protocol( new TBinaryProtocol( transport ));
        client = new RestClient( protocol );
        transport->open();
    }

    Status::type Connection::execute( const RestRequest& request, ActionResult& result ) const {
        client->execute( result.getResponse(), request );
        result.loadJSONFromResponse();
        return result.getResponse().status;
    }

}
