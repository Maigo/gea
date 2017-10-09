#ifndef __GEA_ENDIAN_BASE_H__
#define __GEA_ENDIAN_BASE_H__

namespace gea {

namespace { // hide internal functions

template <int N>
gea_force_inline void endian_swap_intrinsic(void* value);

// use intrinsic byte swaps if supported by target platform
#if defined(INTRINSIC_BYTE_SWAP)
template <> gea_force_inline void endian_swap_intrinsic<1>(void* value) {}
template <> gea_force_inline void endian_swap_intrinsic<2>(void* value) {
    byte_swap16( *((uint16_t*)value) );
}
template <> gea_force_inline void endian_swap_intrinsic<4>(void* value) {
    byte_swap32( *((uint32_t*)value) );
}
template <> gea_force_inline void endian_swap_intrinsic<8>(void* value) {
    byte_swap64( *((uint64_t*)value) );
}
// otherwise use custom bitshift implementation
#else // not INTRINSIC_BYTE_SWAP
template <>
gea_force_inline void endian_swap_intrinsic<1>(void* value) {}
template <>
gea_force_inline void endian_swap_intrinsic<2>(void* value) {
    *((uint16_t*)value) = ( (*((uint16_t*)value) & 0xFF00) >> 8 )
                        | ( (*((uint16_t*)value) & 0x00FF) << 8 );
}
template <>
gea_force_inline void endian_swap_intrinsic<4>(void* value) {
    *((uint32_t*)value) = ( (*((uint32_t*)value) & 0xFF000000) >> 24 )
                        | ( (*((uint32_t*)value) & 0x00FF0000) >>  8 )
                        | ( (*((uint32_t*)value) & 0x0000FF00) <<  8 )
                        | ( (*((uint32_t*)value) & 0x000000FF) << 24 );
}
template <>
gea_force_inline void endian_swap_intrinsic<8>(void* value) {
    *((uint64_t*)value) = ( (*((uint64_t*)value) & 0xFF00000000000000) >> 56 )
                        | ( (*((uint64_t*)value) & 0x00FF000000000000) >> 40 )
                        | ( (*((uint64_t*)value) & 0x0000FF0000000000) >> 24 )
                        | ( (*((uint64_t*)value) & 0x000000FF00000000) >>  8 )
                        | ( (*((uint64_t*)value) & 0x00000000FF000000) <<  8 )
                        | ( (*((uint64_t*)value) & 0x0000000000FF0000) << 24 )
                        | ( (*((uint64_t*)value) & 0x000000000000FF00) << 40 )
                        | ( (*((uint64_t*)value) & 0x00000000000000FF) << 56 );
}
#endif // INTRINSIC_BYTE_SWAP //

} // namespace //

template <typename T>
gea_force_inline void endian_swap(T& value) {
    endian_swap_intrinsic<sizeof(T)>(&value);
}

} // namespace gea //

#endif // __GEA_ENDIAN_BASE_H__ //
