#ifndef __GEA_MTH_VISUAL_COLOR_H__
#define __GEA_MTH_VISUAL_COLOR_H__

// mth includes
#include <gea/mth_core/base.h>

#if defined(DEBUG) || defined(PRODUCTION)
    #include <ostream>
#endif

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// color                                                                     //
// ------------------------------------------------------------------------- //
class color {
public:
    union {
        uint32_t data;
        struct { uint8_t a, r, g, b; };
    };

    // constructors
    inline color();
    inline color(const uint32_t data);
    inline color(const uint8_t r, const uint8_t g, const uint8_t b);
    inline color(const uint8_t a, const uint8_t r, const uint8_t g, const uint8_t b);
    inline explicit color(skip_initialization);
    inline color(const color &o);

    // arithmetic
    inline color &operator= (const color &o);

    // comparative
    inline bool operator== (const color &o) const;
    inline bool operator!= (const color &o) const;

    // conversion
    void from_hsl(const float hue, const float saturation, const float lightness);
    void to_hsl(float &out_hue, float &out_saturation, float &out_lightness) const;
};

// ------------------------------------------------------------------------- //
// debug functions                                                           //
// ------------------------------------------------------------------------- //
#if defined(DEBUG) || defined(PRODUCTION)
inline std::ostream &operator<< (std::ostream &os, const color &c);
#endif

} // namespace mth //
} // namespace gea //

#include "color.inl"

#endif // __GEA_MTH_VISUAL_COLOR_H__ //
