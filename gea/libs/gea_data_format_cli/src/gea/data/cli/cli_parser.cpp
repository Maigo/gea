// header include
#include "cli_parser.h"

// std includes
#include <algorithm>

// gea includes
#include <gea/core/string/string_util.h>

namespace gea {

// ------------------------------------------------------------------------- //
// cli_parser                                                                //
// ------------------------------------------------------------------------- //

const bool cli_parser::parse() {
    return parse_command();
}

const bool cli_parser::parse_command() {
    cli_lexeme lexeme;
    if (m_lexer.next(lexeme) != cli_lexer_ret__ok || lexeme.token_type != cli_lexeme_type__string) {
        return false;
    }

    const commands_t::const_iterator it = std::find_if(m_commands.begin(), m_commands.end(), [&lexeme](const command& c) {
        return string_util::equals(lexeme.token.begin, lexeme.token.end, c.op);
    });

    while (m_lexer.peek(lexeme) == cli_lexer_ret__ok && lexeme.token_type == cli_lexeme_type__operator) {
        if (!parse_option()) {
            return false;
        }
    }

    if (it != m_commands.end()) {
        const command& command = *it;
        if (!command.callback(m_lexer)) {
            return false;
        }
    }

    // fail if there are still unhandled tokens left
    return (m_lexer.peek(lexeme) == cli_lexer_ret__eof);
}

const bool cli_parser::parse_option() {
    cli_lexeme lexeme;
    if (m_lexer.next(lexeme) != cli_lexer_ret__ok || lexeme.token_type != cli_lexeme_type__operator) {
        return false;
    }

    const commands_t::const_iterator it = std::find_if(m_commands.begin(), m_commands.end(), [&lexeme](const command& c) {
        return string_util::equals(lexeme.token.begin, lexeme.token.end, c.op);
    });

    if (it != m_commands.end()) {
        const command& command = *it;
        if (!command.callback(m_lexer)) {
            return false;
        }
    }

    return true;
}

// ------------------------------------------------------------------------- //

} // namespace gea //
