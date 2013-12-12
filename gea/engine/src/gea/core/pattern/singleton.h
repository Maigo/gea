#ifndef __GEA_SINGLETON_H__
#define __GEA_SINGLETON_H__

namespace gea {

// ------------------------------------------------------------------------- //
// singleton                                                                 //
// ------------------------------------------------------------------------- //
template <class T>
class singleton {
public:
    inline static T& get();
    inline static T* get_ptr();

    inline static void construct();
    inline static void destruct();

    inline static bool exists();

private:
    static T* s_instance;
};

} // namespace gea //

#include "singleton.inl"

#endif // __GEA_SINGLETON_H__ //
