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

// find bin: baf (best area fit)
struct find_bin_baf {
    static const size_t find_bin(const rectangle2 &rect, const std::vector<rectangle2> &bins);
};
// find bin: bssf (best short side fit)
struct find_bin_bssf {
    static const size_t find_bin(const rectangle2 &rect, const std::vector<rectangle2> &bins);
};
// find bin: blsf (best long side fit)
struct find_bin_blsf {
    static const size_t find_bin(const rectangle2 &rect, const std::vector<rectangle2> &bins);
};

// split bin: quillotine
struct split_bin_ga {
    static const size_t split_bin(const rectangle2 &bin, const rectangle2 &rect, std::vector<rectangle2> &out_bins);
};

template <typename C0, typename C1>
class bin_pack_ga {
public:
    typedef C0 find_t;
    typedef C1 split_t;

    inline static const size_t bin_pack(const rectangle2 &bin_rect, std::vector<rectangle2> &rects);

    inline bin_pack_ga(const rectangle2& bin_rect);
    inline const bool bin_pack(rectangle2& rect);

    typedef std::vector<rectangle2> bin_stack;
    inline const bin_stack& stack() const;

private:
    bin_stack m_stack;
};

// ------------------------------------------------------------------------- //

// construct algorithms
typedef bin_pack_ga<find_bin_baf,  split_bin_ga> bin_pack_ga_baf;
typedef bin_pack_ga<find_bin_bssf, split_bin_ga> bin_pack_ga_bssf;
typedef bin_pack_ga<find_bin_blsf, split_bin_ga> bin_pack_ga_blsf;

// set default algorithm

typedef bin_pack_ga_baf bin_pack;

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //

#include "bin_pack.inl"

#endif // __GEA_MTH_BINPACK_BIN_PACK_H__ //
