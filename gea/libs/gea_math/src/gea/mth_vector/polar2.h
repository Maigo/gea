#ifndef __GEA_VMTH_POLAR2_H__
#define __GEA_VMTH_POLAR2_H__

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
class vector2;

// ------------------------------------------------------------------------- //
// polar2                                                                     //
// ------------------------------------------------------------------------- //
class polar2 {
public:
    float r, theta;

    // constructors
    inline polar2();
    inline polar2(float r, float theta);
    inline explicit polar2(skip_initialization);
    inline polar2(const polar2 &o);
    inline explicit polar2(const vector2 &v);

    // arithmetic
    inline polar2 &operator= (const polar2 &o);
	inline const polar2 operator+ (const polar2 &o) const;
    inline const polar2 operator- (const polar2 &o) const;
	inline const polar2 operator* (float s) const;
	inline const polar2 operator/ (float s) const;
	
    // compound assignment
    inline polar2 &operator+= (const polar2 &o);
    inline polar2 &operator-= (const polar2 &o);
    inline polar2 &operator*= (float s);
    inline polar2 &operator/= (float s);

    // comparative
	inline bool operator== (const polar2 &o) const;
	inline bool operator!= (const polar2 &o) const;
	inline bool operator<  (const polar2 &o) const;
	inline bool operator<= (const polar2 &o) const;
	inline bool operator>  (const polar2 &o) const;
	inline bool operator>= (const polar2 &o) const;

    // conversion
    void from_vector(const vector2 &v);
    void to_vector(vector2 &v) const;
};

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator <<(std::ostream &lhs, const polar2 &rhs);
#endif

} // namespace mth //
} // namespace gea //

#include "polar2.inl"

#endif // __GEA_VMTH_POLAR2_H__ //
