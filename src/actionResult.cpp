#include "actionResult.h"

namespace cppESClient {

    std::string ActionResult::getResultStatusName() {
        return _Status_VALUES_TO_NAMES.find(response.status)->second; 
    }

    Value&  ActionResult::getFieldValue( const std::string& fieldName ) {
        assert( isloaded );
        return (*this)[fieldName];
    }
}
