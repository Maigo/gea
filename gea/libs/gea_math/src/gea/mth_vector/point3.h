#ifndef __GEA_MTH_VECTOR_POINT3_H__
#define __GEA_MTH_VECTOR_POINT3_H__

// stl includes
#include <assert.h>

// mth includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/vector3.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// point3                                                                    //
// ------------------------------------------------------------------------- //
class point3 {
public:
	float x,y,z;

    // constructors
    inline point3();
    inline point3(const float x, const float y, const float z);
    inline explicit point3(skip_initialization);
    inline explicit point3(zero_initialization);
    inline point3(const point3 &o);

    // arithmetic
    inline point3 &operator= (const point3 &o);
    inline const point3 operator+ (const vector3 &v) const;
    inline const point3 operator- (const vector3 &v) const;

    // compound assignment
    inline point3 &operator+= (const vector3 &v);
    inline point3 &operator-= (const vector3 &v);

	// comparative
    inline bool operator== (const point3 &o) const;
    inline bool operator!= (const point3 &o) const;
    inline bool operator<  (const point3 &o) const;
    inline bool operator<= (const point3 &o) const;
    inline bool operator>  (const point3 &o) const;
    inline bool operator>= (const point3 &o) const;

    // member access
    inline       float &operator[] (const int32_t i);
    inline const float &operator[] (const int32_t i) const;

    // linear algebra
    inline const vector3 to(const point3 &o) const;

    // attributes
    inline const bool is_zero() const;

    // static constants
    static const point3 ORIGIN;
};

// ------------------------------------------------------------------------- //
// global functions                                                          //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //
// approximative comparison
inline const bool approx_eq(const point3 &p0, const point3 &p1, const float e = APPROX_EPSILON);
inline const bool approx_ne(const point3 &p0, const point3 &p1, const float e = APPROX_EPSILON);

// attributes
inline const bool nice(const point3 &p);
inline const bool finite(const point3 &p);

// round
inline const point3 round(const point3 &p);
inline const point3 ceil(const point3 &p);
inline const point3 floor(const point3 &p);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const point3 &p);
#endif

} // namespace mth //
} // namespace gea //

#include "point3.inl"

#endif // __GEA_MTH_VECTOR_POINT3_H__ //
