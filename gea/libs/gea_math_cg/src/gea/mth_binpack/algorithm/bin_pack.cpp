// header include
#include "bin_pack.h"

// gea includes
#include <gea/mth_geometry/algorithm2.h>
#include <gea/utility/assert.h>

namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// bin pack: ga (guillotine algorithm)                                       //
// ------------------------------------------------------------------------- //
// find bin: baf (best area fit)
const size_t find_bin_baf::find_bin(const rectangle2 &rect, const std::vector<rectangle2> &bins) {
    l_assert_msg(!bins.empty(), "invalid parameters!");

    int min_i = -1;
    float min_area = FLT_MAX;

    for (size_t i = 0, e = bins.size(); i < e; ++i) {
        const rectangle2& bin = bins[i];

        const float area = bin.area();
        if ((area < min_area) && contains(bin, rect, ignore_position)) {
            min_area = area;
            min_i = i;
        }
    }

    return min_i;
}

// ------------------------------------------------------------------------- //
// find bin: bssf (best short side fit)
const size_t find_bin_bssf::find_bin(const rectangle2 &rect, const std::vector<rectangle2> &bins) {
    l_assert_msg(!bins.empty(), "invalid parameters!");

    int   min_i = -1;
    float min_short_side = FLT_MAX;

    for (size_t i = 0, e = bins.size(); i < e; ++i) {
        const rectangle2& bin = bins[i];

        const float short_side = min(bin.width - rect.width, bin.height - rect.height);
        if ((short_side < min_short_side) && contains(bin, rect, ignore_position)) {
            min_short_side = short_side;
            min_i = i;
        }
    }

    return min_i;
}

// ------------------------------------------------------------------------- //
// find bin: blsf (best long side fit)
const size_t find_bin_blsf::find_bin(const rectangle2 &rect, const std::vector<rectangle2> &bins) {
    l_assert_msg(!bins.empty(), "invalid parameters!");

    int   min_i = -1;
    float min_long_side = FLT_MAX;

    for (size_t i = 0, e = bins.size(); i < e; ++i) {
        const rectangle2& bin = bins[i];

        const float long_side = max(bin.width - rect.width, bin.height - rect.height);
        if ((long_side < min_long_side) && contains(bin, rect, ignore_position)) {
            min_long_side = long_side;
            min_i = i;
        }
    }

    return min_i;
}

// ------------------------------------------------------------------------- //
// split bin: ga (guillotine algorithm)
const size_t split_bin_ga::split_bin(const rectangle2 &bin, const rectangle2 &rect, std::vector<rectangle2> &out_bins) {
    const float delta_width = bin.width - rect.width;
    const float delta_height = bin.height - rect.height;

    const bool split_width = (approx_gt(delta_width, 0.0f));
    const bool split_height = (approx_gt(delta_height, 0.0f));

    const size_t size = out_bins.size();
    if (split_width && split_height) {
        if (delta_width > delta_height) {
            out_bins.push_back({ bin.x + rect.width, bin.y, bin.width - rect.width, bin.height });
            out_bins.push_back({ bin.x, bin.y + rect.height, rect.width, bin.height - rect.height });
        }
        else {
            out_bins.push_back({ bin.x, bin.y + rect.height, bin.width, bin.height - rect.height });
            out_bins.push_back({ bin.x + rect.width, bin.y, bin.width - rect.width, rect.height });
        }
    }
    else if (split_width) {
        out_bins.push_back({ bin.x + rect.width, bin.y, bin.width - rect.width, bin.height });
    }
    else if (split_height) {
        out_bins.push_back({ bin.x, bin.y + rect.height, bin.width, bin.height - rect.height });
    }

    return (out_bins.size() - size);
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
