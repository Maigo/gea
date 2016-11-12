#ifndef __GEA_MTH_BINPACK_BIN_PACK_H__
#define __GEA_MTH_BINPACK_BIN_PACK_H__

// std includes
#include <vector>

// gea includes
#include <gea/mth_binpack/algorithm/common_defs.h>
#include <gea/mth_core/base.h>
#include <gea/mth_geometry/rectangle2.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// bin pack: ga (guillotine algorithm)                                       //
// ------------------------------------------------------------------------- //
class bin_pack_ga {
public:
    inline static const size_t bin_pack(const rectangle2 &bin_rect, std::vector<rectangle2> &rects);

    inline bin_pack_ga(const rectangle2& bin_rect);
    const bool bin_pack(rectangle2& rect);

    typedef std::vector<rectangle2> bin_stack;
    inline const bin_stack& stack() const;

private:
    const int find_best_bin(const rectangle2& r);
    void split_bin(const rectangle2& bin, const rectangle2& rect);

    bin_stack m_stack;
};

// ------------------------------------------------------------------------- //

// set default algorithm
typedef bin_pack_ga bin_pack;

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "bin_pack.inl"

#endif // __GEA_MTH_BINPACK_BIN_PACK_H__ //
