#ifndef __GEA_VMTH_LINEAR_TRANSFORM2_H__
#define __GEA_VMTH_LINEAR_TRANSFORM2_H__

// mth includes
#include <gea/mth_core/base.h>
#include <gea/mth_vector/matrix2.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// linear_transform2                                                         //
// ------------------------------------------------------------------------- //
class linear_transform2 {
public:


private:
    matrix2 m_transform;
    vector2 m_translation;

};

} // namespace mth //
} // namespace gea //

#include "matrix2.inl"

#endif // __GEA_VMTH_MATRIX2_H__ //
