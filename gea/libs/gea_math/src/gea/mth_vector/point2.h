#ifndef __GEA_VMTH_POINT2_H__
#define __GEA_VMTH_POINT2_H__

// stl includes
#include <assert.h>

// mth includes
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
    float x,y;

    // constructors
    inline point2();
    inline point2(float x, float y);
    inline explicit point2(skip_initialization);
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
    inline       float &operator[] (int32_t i);
    inline const float &operator[] (int32_t i) const;

    // linear algebra
    inline const vector2 to(const point2 &o) const;

    // attributes
    inline bool is_zero() const;

    // static constants
    static const point2 ORIGIN;
};

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline bool approx_eq(const point2 &p0, const point2 &p1, float e = APPROX_EPSILON);
inline bool approx_ne(const point2 &p0, const point2 &p1, float e = APPROX_EPSILON);
// nice point2
inline bool nice(const point2 &p);
// finite point2
inline bool finite(const point2 &p);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator <<(std::ostream &os, const point2 &p);
#endif

} // namespace mth //
} // namespace gea //

#include "point2.inl"

#endif // __GEA_VMTH_POINT2_H__ //
