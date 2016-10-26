namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// color                                                                     //
// ------------------------------------------------------------------------- //
// constructors
inline color::color() : data(0xFF000000) {}
inline color::color(const uint32_t data) : data(data) {}
inline color::color(const uint8_t r, const uint8_t g, const uint8_t b) : a(0xFF), r(r), g(g), b(b) {}
inline color::color(const uint8_t a, const uint8_t r, const uint8_t g, const uint8_t b) : a(a), r(r), g(g), b(b) {}
inline color::color(skip_initialization) {}
inline color::color(const color &o) : data(o.data) {}

// arithmetic
inline color &color::operator= (const color &o) { data = o.data; }

// comparative
inline bool color::operator== (const color &o) const { return (data == o.data); }
inline bool color::operator!= (const color &o) const { return (data != o.data); }

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const color &c) {
    return os << "c:[" << c.a << "," << c.r << "," << c.g << "," << c.b << "]";
}
#endif

} // namespace mth //
} // namespace gea //
