
namespace gea {
namespace math {

// ------------------------------------------------------------------------- //
// Utility Functions                                                         //
// ------------------------------------------------------------------------- //
template <class V, class T>
inline V lerp(const V& v1, const V& v2, T t) {
    return v1*(1-t) + v2*(t);
}

// ------------------------------------------------------------------------- //
// Template functions                                                        //
// ------------------------------------------------------------------------- //
template <class InputIterator, class T>
inline T mean(InputIterator first, InputIterator last, T init) {
    T acc = init, inc = 0;
    for (; first != last; ++inc)
        acc += *first++;
    return (acc / inc);
}

} // namespace math //
} // namespace gea //
