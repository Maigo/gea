
namespace gea {
namespace utl {

// ------------------------------------------------------------------------- //
// mode_base                                                                 //
// ------------------------------------------------------------------------- //
template <typename T>
inline mode_base<T>::mode_base(mode_t init) : m_modes(init) {}

template <typename T>
inline void mode_base<T>::enable_mode (const mode_t& mode) { m_modes |=  (0x01 << mode); }
template <typename T>
inline void mode_base<T>::disable_mode(const mode_t& mode) { m_modes &= ~(0x01 << mode); }

template <typename T>
inline bool mode_base<T>::is_mode(const mode_t& mode) const { return (m_modes & (0x01 << mode)) != 0; }

// ------------------------------------------------------------------------- //
// state_base                                                                //
// ------------------------------------------------------------------------- //
template <typename T>
inline state_base<T>::state_base(state_t init) : m_state(init) {}

template <typename T>
inline void state_base<T>::set_state(const state_t& state) { m_state = state; }
template <typename T>
inline typename state_base<T>::state_t state_base<T>::get_state() const { return m_state; }

template <typename T>
inline bool state_base<T>::is_state(const state_t& state) const { return m_state == state; }

} // namespace utl //
} // namespace gea //
