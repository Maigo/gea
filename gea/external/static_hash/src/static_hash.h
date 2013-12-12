#ifndef __GEA_STATIC_HASH_H__
#define __GEA_STATIC_HASH_H__

//#include <external\hash\hash.h>

namespace gea {

#if defined(_debug) || defined(_production)
    //TODO: runtime check?
    #define static_hash(s,v) (v)
#else
    #define static_hash(s,v) (v)
#endif

} // namespace gea //

#endif // __STATIC_HASH_H__ //
