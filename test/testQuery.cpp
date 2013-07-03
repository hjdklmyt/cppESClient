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

void testBulkQueries( char *filename, int recordCount ) {
    const int times = 5000;
    fstream infile( filename );
    Connection conn( "10.21.2.160", 9500 );
    ActionResult result;
    MultiQuery query("test","test");
    query.bulk();

    for( int i = 0 ; i < recordCount; ++i ) {
        string body = "";
        char line[ 1024 ];
        char total[ 1024 * 1024 ] = "";
        for( int j = 0 ; j < times && !infile.eof() ; ++j ) {
            infile.getline(line, 1023);
            jsonString1( total, line );
            //body += jsonString( line );
        }

        query.setQueryData( total );

        cout<<"Sending ..." <<endl;
        conn.execute( query, result );
        cout<<"status: "<<result.getResultStatusName()<<endl;
        cout<<"Response: "<<result.getResponse().body<<endl;
    }
    infile.close();
}

void testIndexQueries( char *filename, int recordCount) {
    fstream infile( filename );
    Connection conn( "10.21.2.160", 9500 );
    ActionResult result;
    SingleQuery query("test","test");
    query.indexDoc();

    for( int i = 0 ; i < recordCount && !infile.eof() ; ++i ) {
        string body = "";
        char line[ 1024 ];
        char total[ 1024 * 1024 ] = "";
        infile.getline(line, 1023);
        jsonString1( total, line );

        query.setQueryData( total );
        cout<<"Sending ..." <<endl;
        conn.execute( query, result );
        cout<<"status: "<<result.getResultStatusName()<<endl;
        cout<<"Response: "<<result.getResponse().body<<endl;
        cout<<"OK: "<<result.getFieldValue("ok");
        cout<<"_id: "<<result.getFieldValue("_id");
    }
    //client.execute
    infile.close();
}

int main( int argc, char **argv ) {

    char filename[128];
    int  recordCount = 0;
    parseParameters( argc, argv, filename, recordCount );

    testIndexQueries( filename, recordCount );
    //testBulkQueries( filename, recordCount );
    return 0;
}

