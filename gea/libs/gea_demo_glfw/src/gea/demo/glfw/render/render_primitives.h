#ifndef __GEA_DEMO_RENDER_PRIMITIVES_H__
#define __GEA_DEMO_RENDER_PRIMITIVES_H__

// gea includes
#include <gea/demo/glfw/render/render_types.h>

namespace gea {
namespace ren {

// ------------------------------------------------------------------------- //
// render primitives: square                                                 //
// ------------------------------------------------------------------------- //

void primitive_square(const float size, const color32 color, vertex2_color out_vetices[6]);

} // namespace ren //
} // namespace gea //

#include "render_primitives.inl"

#endif // __GEA_DEMO_RENDER_PRIMITIVES_H__ //
