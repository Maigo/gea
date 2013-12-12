
// stl includes
#include <assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// base                                                                      //
// ------------------------------------------------------------------------- //
// norm functions
inline float norm(const float &f) { return fabs(f); }

// error functions
inline float error_absolute(const float &f, const float &fh) {
    return fabs(f-fh);
}
inline float error_relative(const float &f, const float &fh) {
    assert((f != 0.0f) && "divide by zero!");
    return fabs(1.0f - (fh / f));
}

} // namespace mth //
} // namespace gea //
