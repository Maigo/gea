namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// bin pack: ga (guillotine algorithm)                                       //
// ------------------------------------------------------------------------- //

template <typename C0, typename C1>
inline const size_t bin_pack_ga<C0, C1>::bin_pack(const rectangle2 &bin_rect, std::vector<rectangle2> &rects) {
    bin_pack_ga packer(bin_rect);

    size_t i = 0, e = rects.size();
    while ((i < e) && packer.bin_pack(rects[i])) {
        ++i;
    }

    return i;
}

// ------------------------------------------------------------------------- //

template <typename C0, typename C1>
inline const bool bin_pack_ga<C0, C1>::bin_pack(rectangle2& rect)
{
    // early out
    if (m_stack.empty()) {
        return false;
    }

    const int bin_index = find_t::find_bin(rect, m_stack);
    if (bin_index < 0) {
        return false;
    }

    //TODO: refactor pop_remove
    const rectangle2 bin = m_stack[bin_index];
    rect.x = bin.x;
    rect.y = bin.y;

    std::swap(m_stack[bin_index], m_stack.back());
    m_stack.pop_back();

    split_t::split_bin(bin, rect, m_stack);
    return true;
}

// ------------------------------------------------------------------------- //

template <typename C0, typename C1>
inline bin_pack_ga<C0, C1>::bin_pack_ga(const rectangle2& rect) {
    m_stack.push_back(rect);
}

// ------------------------------------------------------------------------- //

template <typename C0, typename C1>
inline const typename bin_pack_ga<C0, C1>::bin_stack& bin_pack_ga<C0, C1>::stack() const {
    return m_stack;
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
