/*=============================================================================
#     FileName: testDocumentQuery.cpp
#         Desc:  
#       Author: Taihua He
#        Email: hetaihua@ict.ac.cn
#      Version: 0.0.1
#   LastChange: 2013-06-24 15:10:44
#      History:
=============================================================================*/

#include "../src/connection.h"
#include "../src/actionResult.h"
#include "../src/core/singleQuery.h"
#include "../src/core/multiQuery.h"
#include "../src/search/URIRequest.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cppESClient;

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

void testSearch() {
    Connection conn( "10.21.2.160", 9500 );
    ActionResult result;
    SingleQuery query("test","test");
    URIRequest uriRequest;
    uriRequest.addParameter( Parameters::Q, "fielda:10" );
    uriRequest.addParameter( Parameters::FIELDS, "fielda,fieldb,fieldc,fieldd" );
    uriRequest.addParameter( Parameters::SIZE, 2); 
    cout<<"URIRequest string:"<<uriRequest.toString()<<endl;
    query.searchDoc( uriRequest.toString() );

    cout<<"Query string: "<<query.uri<<endl;

    cout<<"Sending ..." <<endl;
    conn.execute( query, result );
    cout<<"status: "<<result.getResultStatusName()<<endl;
    cout<<"Response: "<<result.getResponse().body<<endl;
    Value hits = result.getFieldValue( "hits" );
    cout<<hits<<endl;
    cout<<"total = "<<hits["total"]<<endl;
}


int main( int argc, char **argv ) {

    char filename[128];
    int  recordCount = 0;
    parseParameters( argc, argv, filename, recordCount );

    testSearch();
    return 0;
}

