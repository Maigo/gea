#ifndef __GEA_VMTH_POINT3_H__
#define __GEA_VMTH_POINT3_H__

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
    inline point3(float x, float y, float z);
    inline explicit point3(skip_initialization);
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
    inline       float &operator[] (int32_t i);
    inline const float &operator[] (int32_t i) const;

    // attributes
    inline bool is_zero() const;

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
inline bool approx_eq(const point3 &p0, const point3 &p1, float e = APPROX_EPSILON);
inline bool approx_ne(const point3 &p0, const point3 &p1, float e = APPROX_EPSILON);
// nice point3
inline bool nice(const point3 &p);
// finite point3
inline bool finite(const point3 &p);

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator <<(std::ostream &os, const point3 &p);
#endif

} // namespace mth //
} // namespace gea //

#include "point3.inl"

#endif // __GEA_VMTH_POINT3_H__ //
