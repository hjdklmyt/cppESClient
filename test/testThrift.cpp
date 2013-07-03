#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "../src/gen-cpp/elasticsearch_types.h"
#include "../src/gen-cpp/elasticsearch_constants.h"
#include "../src/gen-cpp/Rest.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;;
using namespace elasticsearch::thrift;

using namespace boost;


void parseParameters( int argc, char **argv, char *filename, int &count ) {
    char ch;
    const char *filter = "f:n:";
    while( (ch=getopt(argc, argv, filter ) ) != -1 ) {
        switch( ch ) {
            case 'f':
                strcpy( filename, optarg );
                break;
            case 'n':
                count = atoi( optarg );
                break;
            default:
                cout<<"Wrong parameter: "<<ch<<endl;
        }
    }
}
inline string jsonString( char *line ) {
    char *ptr = strtok( line, ", ");
    string sb = "";
    { 
        sb.append("{ \"");
        sb.append( "index" );
        sb.append("\" : { ");

        bool putComma = false;

        sb.append("\"_index\" : \"");
        sb.append( "test" );
        sb.append("\"");

        putComma = true;

        if (putComma) sb.append(", ");
        sb.append("\"_type\" : \"");
        sb.append( "test");
        sb.append("\"");
        sb.append("}}\n");
    }

    sb.append("{ ");
    for( int i = 0 ; ptr; ptr = strtok( NULL, ", ") , ++i ) {
        if( i ) sb.append( "," );
        char tmp = 'a' + i;
        string field = "field";
        field.append( 1, tmp );
        sb.append( "\"" );
        sb.append( field );
        sb.append( "\" : " );
        sb.append( ptr );
    }
    sb.append( "}\n" );
    return sb;
}


inline string jsonString1( char *total, char *line ) {
    char *ptr = strtok( line, ", ");
    char sb[1024*64]="";
    { 
        strcat(sb,"{ \"");
        strcat(sb, "index" );
        strcat(sb,"\" : { ");

        bool putComma = false;

        strcat(sb,"\"_index\" : \"");
        strcat(sb, "test" );
        strcat(sb,"\"");

        putComma = true;

        if (putComma) strcat(sb,", ");
        strcat(sb,"\"_type\" : \"");
        strcat(sb, "test");
        strcat(sb,"\"");
        strcat(sb,"}}\n");
    }

    strcat(sb,"{ ");
    for( int i = 0 ; ptr; ptr = strtok( NULL, ", ") , ++i ) {
        if( i ) strcat(sb, "," );
        char tmp = 'a' + i;
        string field = "field";
        field.append( 1, tmp );
        strcat(sb, "\"" );
        strcat(sb, field.c_str() );
        strcat(sb, "\" : " );
        strcat(sb, ptr );
    }
    strcat(sb, "}\n" );
    strcat( total, sb);
    return "";
}

int main( int argc, char **argv ) {

    char filename[128];
    int  recordCount = 0;
    parseParameters( argc, argv, filename, recordCount );

    shared_ptr<TTransport> socket( new TSocket("10.21.2.160", 9500 ) );
    shared_ptr<TTransport> transport( new TBufferedTransport(socket));
    shared_ptr<TProtocol>  protocol( new TBinaryProtocol(transport));

    RestClient client( protocol );
    RestRequest request;
    request.__set_method( Method::POST );
    //request.__set_uri( "http://10.21.2.160:9200" );
    request.__set_uri( "/test/test/_bulk" );
    //request.__set_uri( "/test" );
    RestResponse response;

    const int times = 100;
    fstream infile( filename );

    try {
        transport->open();

        for( int i = 0 ; i < times; ++i ) {
            string body = "";
            char line[ 1024 ];
            char total[ 1024 * 1024 ] = "";
            for( int j = 0 ; j < recordCount && !infile.eof() ; ++j ) {
                infile.getline(line, 1023);
                jsonString1( total, line );
                //body += jsonString( line );
            }
            //cout<<body<<endl;
            request.__set_body( total );
            //request.__set_body(body);

            cout<<"Sending ..." <<endl;

            client.execute( response, request );

            cout<<"status: "<<response.status<<endl;
            //cout<<response.body<<endl;
        }
        //client.execute
        transport->close();
        infile.close();
    } catch( ... ) {
    
    }
    return 0;
}

