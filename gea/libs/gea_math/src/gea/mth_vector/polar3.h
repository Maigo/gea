#ifndef __GEA_MTH_VECTOR_POLAR3_H__
#define __GEA_MTH_VECTOR_POLAR3_H__

// stl includes
#include <assert.h>

// mth includes
#include <gea/mth_core/base.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// forward declarations
class vector3;

// ------------------------------------------------------------------------- //
// polar3                                                                     //
// ------------------------------------------------------------------------- //
class polar3 {
public:
    float r, theta, phi;

    // constructors
    inline polar3();
    inline polar3(const float r, const float theta, const float phi);
    inline explicit polar3(skip_initialization);
    inline explicit polar3(zero_initialization);
    inline polar3(const polar3 &o);
    inline explicit polar3(const vector3 &v);

    // arithmetic
    inline polar3 &operator= (const polar3 &o);
	inline const polar3 operator+ (const polar3 &o) const;
    inline const polar3 operator- (const polar3 &o) const;
	inline const polar3 operator* (const float s) const;
	inline const polar3 operator/ (const float s) const;
	
    // compound assignment
    inline polar3 &operator+= (const polar3 &o);
    inline polar3 &operator-= (const polar3 &o);
    inline polar3 &operator*= (const float s);
    inline polar3 &operator/= (const float s);

    // comparative
	inline const bool operator== (const polar3 &o) const;
	inline const bool operator!= (const polar3 &o) const;
	inline const bool operator<  (const polar3 &o) const;
	inline const bool operator<= (const polar3 &o) const;
	inline const bool operator>  (const polar3 &o) const;
	inline const bool operator>= (const polar3 &o) const;

    // conversion
    void from_vector(const vector3 &v);
    void to_vector(vector3 &out_v) const;
};

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &lhs, const polar3 &rhs);
#endif

} // namespace mth //
} // namespace gea //

#include "polar3.inl"

#endif // __GEA_MTH_VECTOR_POLAR3_H__ //
