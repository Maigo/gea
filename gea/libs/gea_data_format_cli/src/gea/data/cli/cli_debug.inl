#pragma once

// headder include
#include "cli_debug.h"

#if !defined(GEA_RELEASE)

namespace gea {

// ------------------------------------------------------------------------- //
// debug                                                                     //
// ------------------------------------------------------------------------- //

void debug_print(cli_lexer& lexer, std::ostream& out) {
    cli_lexeme lexeme;
    while (lexer.next(lexeme) != cli_lexer_ret__eof) {
        out << to_string(lexeme.token_type) << " [" << std::string(lexeme.token.begin, lexeme.token.end) << "]" << std::endl;
    }
}

// ------------------------------------------------------------------------- //

} // namespace gea //

#else

namespace gea {

// ------------------------------------------------------------------------- //
// debug                                                                     //
// ------------------------------------------------------------------------- //

void debug_print(cli_lexer& lexer, std::ostream& out) {}

// ------------------------------------------------------------------------- //

} // namespace gea //

#endif // not defined(GEA_RELEASE) //
