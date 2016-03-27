#ifndef __GEA_APPLICATION_H__
#define __GEA_APPLICATION_H__

// gea includes
#include <gea/core/time_scheme.h>

namespace gea {

// ------------------------------------------------------------------------- //
// application                                                               //
// ------------------------------------------------------------------------- //
class application {
public:
    application() : m_quit(false) {}
    ~application() {}

    // initialize all managers in order
    void init_managers();
    // main loop
    void run();
    // main update
    void update();

private:
    // exit parameters
    bool m_quit;

    time_scheme m_time_scheme;
};

} // namespace gea //

#endif // __GEA_APPLICATION_H__ //
