#ifndef __GEA_DEMO_RENDER_TYPES_H__
#define __GEA_DEMO_RENDER_TYPES_H__

namespace gea {
namespace ren {

// ------------------------------------------------------------------------- //
// render types                                                              //
// ------------------------------------------------------------------------- //

struct gea_alignment(16) vector2{
    float x, y;
};

struct gea_alignment(32) vector3 {
    float x, y, z;
};

typedef uint32_t color32;

struct vertex2 {
    static const int position_offset = 0;
    static const int position_stride = 0;
    vector2 position;
};

struct vertex2_color {
    static const int position_offset = 0;
    static const int position_stride = 4;
    static const int color_offset = 4;
    static const int color_stride = 4;
    vector2 position;
    color32 color;
};

struct vertex3 {
    static const int position_offset = 0;
    static const int position_stride = 0;
    vector3 position;
};

struct vertex3_color {
    static const int position_offset = 0;
    static const int position_stride = 4;
    static const int color_offset = 4;
    static const int color_stride = 4;
    vector3 position;
    color32 color;
};

} // namespace ren //
} // namespace gea //

#endif // __GEA_DEMO_RENDER_TYPES_H__ //
