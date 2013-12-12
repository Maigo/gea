
namespace gea {

// ------------------------------------------------------------------------- //
// idstring                                                                  //
// ------------------------------------------------------------------------- //
inline idstring::idstring() : m_hash(EMPTY_HASH) {}
inline idstring::idstring(const void *s, size_t length) {
    m_hash = g_hash.h64(s, length);
}

inline idstring::idstring(const idstring &o) : m_hash(o.m_hash) {}

// assignment
inline idstring& idstring::operator =(const idstring &o) {
    m_hash = o.m_hash;
    return (*this);
}

// compare
inline bool idstring::operator ==(const idstring &o) const { return m_hash == o.m_hash; }
inline bool idstring::operator !=(const idstring &o) const { return m_hash != o.m_hash; }
inline bool idstring::operator  <(const idstring &o) const { return m_hash  < o.m_hash; }
inline bool idstring::operator  >(const idstring &o) const { return m_hash  > o.m_hash; }
inline bool idstring::operator <=(const idstring &o) const { return m_hash <= o.m_hash; }
inline bool idstring::operator >=(const idstring &o) const { return m_hash >= o.m_hash; }

inline bool idstring::empty() const { return m_hash == EMPTY_HASH; }

} // namespace gea //
