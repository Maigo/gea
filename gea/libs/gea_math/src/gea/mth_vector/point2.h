#ifndef __GEA_MTH_VECTOR_POINT2_H__
#define __GEA_MTH_VECTOR_POINT2_H__

// gea includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/vector2.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point2                                                                    //
// ------------------------------------------------------------------------- //
class point2 {
public:
    float x, y;

    // constructors
    inline point2();
    inline point2(const float x, const float y);
    inline explicit point2(skip_initialization);
    inline explicit point2(zero_initialization);
    inline point2(const point2 &o);

    // arithmetic
    inline point2 &operator= (const point2 &o);
    inline const point2 operator+ (const vector2 &v) const;
    inline const point2 operator- (const vector2 &v) const;

    // compound assignment
    inline point2 &operator+= (const vector2 &v);
    inline point2 &operator-= (const vector2 &v);

    // comparative
    inline bool operator== (const point2 &o) const;
    inline bool operator!= (const point2 &o) const;
    inline bool operator<  (const point2 &o) const;
    inline bool operator<= (const point2 &o) const;
    inline bool operator>  (const point2 &o) const;
    inline bool operator>= (const point2 &o) const;

    // member access
    inline       float &operator[] (const int32_t i);
    inline const float &operator[] (const int32_t i) const;

    // linear algebra
    inline const vector2 to(const point2 &o) const;

    // attributes
    inline const bool is_zero() const;

    // static constants
    static const point2 ORIGIN;
};

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //

inline const float distance(const point2 &p0, const point2 &p1);
inline const float distance_sq(const point2 &p0, const point2 &p1);

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const point2 &p0, const point2 &p1, const float e = APPROX_EPSILON);
inline const bool approx_ne(const point2 &p0, const point2 &p1, const float e = APPROX_EPSILON);

// attributes
inline const bool nice(const point2 &p);
inline const bool finite(const point2 &p);

// round
inline const point2 round(const point2 &p);
inline const point2 ceil(const point2 &p);
inline const point2 floor(const point2 &p);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const point2 &p);
#endif

} // namespace mth //
} // namespace gea //

#include "point2.inl"

#endif // __GEA_MTH_VECTOR_POINT2_H__ //
