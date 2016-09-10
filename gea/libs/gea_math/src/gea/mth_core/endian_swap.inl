
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// little <-> big endian conversion                                          //
// ------------------------------------------------------------------------- //

namespace internal {

// internal functions
template <int B> inline void endian_swap_mux_n(void *t);
template <> inline void endian_swap_mux_n<1>(void *t) {}
template <> inline void endian_swap_mux_n<2>(void *t) {
    byte_swap16(*((uint16_t*) t));
}
template <> inline void endian_swap_mux_n<4>(void *t) {
    byte_swap32(*((uint32_t*) t));
}
template <> inline void endian_swap_mux_n<8>(void *t) {
    byte_swap64(*((uint64_t*) t));
}

template <typename T>
inline void endian_swap_mux(T &out_t) {
    endian_swap_mux_n<sizeof(T)>(&out_t);
}

} // namespace internal //

// template definition
template <typename T> inline void endian_swap(T &out_t);

// template specialization of common intrincics
template <> inline void endian_swap<bool>    (bool     &out_t) { internal::endian_swap_mux(out_t); }
template <> inline void endian_swap<int8_t>  (int8_t   &out_t) { internal::endian_swap_mux(out_t); }
template <> inline void endian_swap<uint8_t> (uint8_t  &out_t) { internal::endian_swap_mux(out_t); }
template <> inline void endian_swap<int16_t> (int16_t  &out_t) { internal::endian_swap_mux(out_t); }
template <> inline void endian_swap<uint16_t>(uint16_t &out_t) { internal::endian_swap_mux(out_t); }
template <> inline void endian_swap<int32_t> (int32_t  &out_t) { internal::endian_swap_mux(out_t); }
template <> inline void endian_swap<uint32_t>(uint32_t &out_t) { internal::endian_swap_mux(out_t); }
template <> inline void endian_swap<int64_t> (int64_t  &out_t) { internal::endian_swap_mux(out_t); }
template <> inline void endian_swap<uint64_t>(uint64_t &out_t) { internal::endian_swap_mux(out_t); }

template <> inline void endian_swap<float>   (float    &out_t) { internal::endian_swap_mux(out_t); }
template <> inline void endian_swap<double>  (double   &out_t) { internal::endian_swap_mux(out_t); }

} // namespace mth //
} // namespace gea //
