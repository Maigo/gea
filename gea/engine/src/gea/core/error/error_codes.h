#ifndef __GEA_ERROR_CODES_H__
#define __GEA_ERROR_CODES_H__

namespace gea {

// ------------------------------------------------------------------------- //
// Error Codes                                                               //
// ------------------------------------------------------------------------- //
typedef int32_t err_code_t;
    
enum ErrorCode {
    // generic
    GEA_OK           = 0,
    GEA_ERROR        = -1,
    // thread
    GEA_THREAD_ERROR = -64
};

} // namespace gea //

#endif // __GEA_ERROR_CODES_H__ //
