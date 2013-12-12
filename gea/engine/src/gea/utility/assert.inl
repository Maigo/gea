
namespace gea {

// ------------------------------------------------------------------------- //
// Context                                                                   //
// ------------------------------------------------------------------------- //
inline context::context() : m_line(0), m_file(""), m_func("") {}
inline context::context(uint32_t line, const char* file, const char* func)
    : m_line(line), m_file(file), m_func(func) {}

inline uint32_t    context::line() const { return m_line; }
inline const char* context::file() const { return m_file; }
inline const char* context::func() const { return m_func; }

} // namespace gea //
