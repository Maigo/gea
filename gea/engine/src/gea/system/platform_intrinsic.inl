
namespace gea {
// ------------------------------------------------------------------------- //
// System functions                                                          //
// ------------------------------------------------------------------------- //
inline void i_system_break() {
    __asm {
        int 3   // breakpoint!
    }
}

} // namespace gea //
