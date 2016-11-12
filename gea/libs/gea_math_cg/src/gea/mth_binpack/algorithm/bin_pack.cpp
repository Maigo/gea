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

const bool bin_pack_ga::bin_pack(rectangle2& rect)
{
    // early out
    if (m_stack.empty()) {
        return false;
    }

    const int bin_index = find_best_bin(rect);
    if (bin_index < 0) {
        return false;
    }

    //TODO: refactor pop_remove
    const rectangle2 bin = m_stack[bin_index];
    rect.x = bin.x;
    rect.y = bin.y;

    std::swap(m_stack[bin_index], m_stack.back());
    m_stack.pop_back();

    split_bin(bin, rect);
    return true;
}

// ------------------------------------------------------------------------- //

const int bin_pack_ga::find_best_bin(const rectangle2& rect)
{
    l_assert_msg(!m_stack.empty(), "invalid parameters!");

    int index = -1;
    float min_delta_area = FLT_MAX;

    const float area_rect = rect.area();
    for (int i = 0, e = m_stack.size(); i < e; ++i)
    {
        const rectangle2& bin = m_stack[i];
        if (contains(bin, rect, ignore_position))
        {
            const float delta_area = bin.area() - area_rect;
            if (delta_area < min_delta_area)
            {
                min_delta_area = delta_area;
                index = i;
            }
        }
    }

    return index;
}

// ------------------------------------------------------------------------- //

void bin_pack_ga::split_bin(const rectangle2& bin, const rectangle2& rect) {
    const float delta_width = bin.width - rect.width;
    const float delta_height = bin.height - rect.height;

    const bool split_width = (approx_gt(delta_width, 0.0f));
    const bool split_height = (approx_gt(delta_height, 0.0f));

    if (split_width && split_height) {
        if (delta_width > delta_height) {
            m_stack.push_back({ bin.x + rect.width, bin.y, bin.width - rect.width, bin.height });
            m_stack.push_back({ bin.x, bin.y + rect.height, rect.width, bin.height - rect.height });
        }
        else {
            m_stack.push_back({ bin.x, bin.y + rect.height, bin.width, bin.height - rect.height });
            m_stack.push_back({ bin.x + rect.width, bin.y, bin.width - rect.width, rect.height });
        }
    }
    else if (split_width) {
        m_stack.push_back({ bin.x + rect.width, bin.y, bin.width - rect.width, bin.height });
    }
    else if (split_height) {
        m_stack.push_back({ bin.x, bin.y + rect.height, bin.width, bin.height - rect.height });
    }
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
