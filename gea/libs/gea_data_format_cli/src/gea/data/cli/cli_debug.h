#pragma once

// std includes
#include <ostream>

// gea includes
#include <gea/data/cli/cli_lexer.h>

namespace gea {

// ------------------------------------------------------------------------- //
// debug                                                                     //
// ------------------------------------------------------------------------- //

inline void debug_print(cli_lexer& lexer, std::ostream& out);

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "cli_debug.inl"
