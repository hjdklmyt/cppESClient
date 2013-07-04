/*=============================================================================
#     FileName: requestPara.h
#         Desc:  
#       Author: Taihua He
#        Email: hetaihua@ict.ac.cn
#      Version: 0.0.1
#   LastChange: 2013-07-03 14:48:50
#      History:
=============================================================================*/


#ifndef requestPara_H
#define requestPara_H

#include <map>
#include <string>

namespace cppESClient {

struct Parameters {
    enum Name {
        Q = 0,
        DF,
        ANALYZER,
        DEFAULT_OPERATOR,
        EXPLAIN,
        FIELDS,
        SORT,
        TRACK_SCORES,
        TIMEOUT,
        FROM,
        SIZE,
        SEARCH_TYPE,
        LOWERCASE_EXPANDED_TERMS,
        ANALYZE_WILDCARD,
        UNKNOWN
    };
};

//extern const map<int, const char *> Parameters_Name_To_Values;

extern const char * nameValues[];

static inline const char* getParameterName( Parameters::Name name ) {
    if( name >= Parameters::UNKNOWN ) return nameValues[ Parameters::UNKNOWN ];
    else return nameValues[ name ];
}

/**
 * This class is used to process the uri request of http://www.elasticsearch.org/guide/reference/api/search/uri-request/
 * People can specify search options explicitly in the uri request string.
 * An uri example is like this:'http://localhost:9200/twitter/tweet/_search?q=user:kimchy'
 */
class RequestPara {
    public:
        explicit RequestPara() {}

        int addParameter( Parameters::Name, const std::string&  );

        int addParameter( Parameters::Name, const char * );

        int addParameter( Parameters::Name, int );

        int delParameter( Parameters::Name ) ;

        std::string toString();

    private:
        std::map<int, std::string> parameters;
};

}


#endif
