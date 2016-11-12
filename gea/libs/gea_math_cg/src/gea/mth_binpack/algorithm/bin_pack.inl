namespace gea {
namespace mth {

// ------------------------------------------------------------------------- //
// bin pack: ga (guillotine algorithm)                                       //
// ------------------------------------------------------------------------- //

inline const size_t bin_pack_ga::bin_pack(const rectangle2 &bin_rect, std::vector<rectangle2> &rects) {
    bin_pack_ga packer(bin_rect);

    size_t i = 0, e = rects.size();
    while ((i < e) && packer.bin_pack(rects[i])) {
        ++i;
    }

    return i;
}

// ------------------------------------------------------------------------- //

inline bin_pack_ga::bin_pack_ga(const rectangle2& rect) {
    m_stack.push_back(rect);
}

// ------------------------------------------------------------------------- //

inline const bin_pack_ga::bin_stack& bin_pack_ga::stack() const {
    return m_stack;
}

// ------------------------------------------------------------------------- //

} // namespace mth //
} // namespace gea //
