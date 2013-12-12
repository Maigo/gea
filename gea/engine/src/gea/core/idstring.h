#ifndef __GEA_IDSTRING_H__
#define __GEA_IDSTRING_H__

// gea includes
#include <external/hash/hash.h>

namespace gea {

// ------------------------------------------------------------------------- //
// idstring                                                                  //
// ------------------------------------------------------------------------- //
class idstring {
public:
    inline idstring();
    inline idstring(const void *s, size_t length);
    inline idstring(const idstring &other);

    // assignment
    inline idstring& operator =(const idstring &o);

    // compare
    inline bool operator ==(const idstring& o) const;
    inline bool operator !=(const idstring& o) const;
    inline bool operator  <(const idstring& o) const;
    inline bool operator  >(const idstring& o) const;
    inline bool operator <=(const idstring& o) const;
    inline bool operator >=(const idstring& o) const;

    inline bool empty() const;

private:
    static const uint64_t EMPTY_HASH = 0x1234567890ABCDEF;
    hash64_t m_hash;
};

} // namespace gea //

#include "idstring.inl"

#endif // __GEA_IDSTRING_H__ //
