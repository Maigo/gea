
namespace gea {
namespace math {

// ------------------------------------------------------------------------- //
// Utility Functions                                                         //
// ------------------------------------------------------------------------- //
template <class V, class T>
inline V lerp(const V& v1, const V& v2, T t) {
    return v1*(1-t) + v2*(t);
}

template <typename T>
inline const T& min(const T& a, const T& b) {
	return (b < a) ? b : a;
}

template <typename T>
inline const T& max(const T& a, const T& b) {
	return (b > a) ? b : a;
}

template <typename T>
inline const T& clamp(const T& x, const T& low, const T& high) {
	return max(low, min(high, x));
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
