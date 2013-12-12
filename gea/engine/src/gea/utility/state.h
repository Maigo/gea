#ifndef __GEA_STATE_H__
#define __GEA_STATE_H__

namespace gea {
namespace utl {

// ------------------------------------------------------------------------- //
// mode_base                                                                 //
// ------------------------------------------------------------------------- //
//TODO: extend through templates to include arbitrary number of modes!
//      optimized for <= 8
template <typename T>
class mode_base {
public:
    typedef T mode_t;
    static const mode_t EMPTY = mode_t();

    // constructor
    inline explicit mode_base(mode_t init = EMPTY);
    // mutator functions
    inline void  enable_mode(const mode_t &mode);
    inline void disable_mode(const mode_t &mode);
    // conditional functions
    inline bool is_mode(const mode_t &mode) const;

private:
    mode_t m_modes;
};

// ------------------------------------------------------------------------- //
// state_base                                                                //
// ------------------------------------------------------------------------- //
template <typename T>
class state_base {
public:
    typedef T state_t;
    static const state_t ZERO = state_t();

    // constructor
    inline explicit state_base(state_t init = ZERO);
    // mutator functions
    inline void set_state(const state_t &state);
    inline state_t get_state() const;
    // conditional functions
    inline bool is_state(const state_t &state) const;

private:
    state_t m_state;
};

} // namespace utl //
} // namespace gea //

#include "state.inl"

#endif // __GEA_STATE_H__ //
