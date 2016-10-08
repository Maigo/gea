
namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// linear_transform2                                                         //
// ------------------------------------------------------------------------- //
// constructors
inline linear_transform2::linear_transform2() : m_transform(), m_translation() {}
inline linear_transform2::linear_transform2(skip_initialization) : m_transform(SKIP_INITIALIZATION), m_translation(SKIP_INITIALIZATION) {}
inline linear_transform2::linear_transform2(const matrix2 &transform, const vector2 &translation)
    : m_transform(transform), m_translation(translation) {}

// arithmetic
inline linear_transform2 &linear_transform2::operator= (const linear_transform2 &o) {
    m_transform = o.get_transform();
    m_translation = o.get_translation();
}
inline const vector2 linear_transform2::operator* (const vector2 &v) const {
    return m_transform * v + m_translation;
}
inline const point2  linear_transform2::operator* (const point2  &p) const {
    const mth::point2 result = m_transform * p;
    return result + m_translation;
//    return m_transform * p + m_translation;
}

// member access
inline const matrix2 &linear_transform2::get_transform() const { return m_transform; }
inline const vector2 &linear_transform2::get_translation() const { return m_translation; }

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //
// arithmetic

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const linear_transform2 &lt0, const linear_transform2 &lt1, const float e) {
    return approx_eq(lt0.get_transform(),   lt0.get_transform(),   e) &&
           approx_eq(lt0.get_translation(), lt1.get_translation(), e);
}
inline const bool approx_ne(linear_transform2 &lt0, const linear_transform2 &lt1, const float e) {
    return approx_ne(lt0.get_transform(),   lt0.get_transform(),   e) &&
           approx_ne(lt0.get_translation(), lt1.get_translation(), e);
}
// nice matrix2
inline const bool nice(const linear_transform2 &lt) {
    return nice(lt.get_transform()) &&
           nice(lt.get_translation());
}

// finite matrix2
inline const bool finite(const linear_transform2 &lt) {
    return finite(lt.get_transform()) &&
           finite(lt.get_translation());
}

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const linear_transform2 &lt) {
    return os << "lt:[" << lt.get_transform() << ", " << lt.get_translation() << "]";
}
#endif

} // namespace mth //
} // namespace gea //
