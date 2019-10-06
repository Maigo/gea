#pragma once

// header include
#include "cli_lexer.h"

// gea includes
#include <gea/core/string/string.h>
#include <gea/core/string/string_util.h>
#include <gea/data/parser/predicates.h>

namespace gea {

// ------------------------------------------------------------------------- //
// cli_lexer_arg                                                             //
// ------------------------------------------------------------------------- //

const cli_lexer_ret cli_lexer_arg::next(cli_lexeme& out_lexeme) {
    using namespace predicate;

    if (m_caret < m_argc) {
        const char* caret = m_argv[m_caret];
        if (is_character_p<'-'>::test(*caret)) {
            out_lexeme = cli_lexeme{ cli_lexeme_type__operator, sub_string{ caret, caret + strlen(caret) } };
        }
        else if (is_num_p::test(*caret)) {
            out_lexeme = cli_lexeme{ cli_lexeme_type__number, sub_string{ caret, caret + strlen(caret) } };
        }
        else {
            out_lexeme = cli_lexeme{ cli_lexeme_type__string, sub_string{ caret, caret + strlen(caret) } };
        }

        ++m_caret;
        return cli_lexer_ret__ok;
    }

    out_lexeme = cli_lexeme{ cli_lexeme_type__invalid, sub_string{ nullptr, nullptr } };
    return cli_lexer_ret__eof;
}
const cli_lexer_ret cli_lexer_arg::peek(cli_lexeme& out_lexeme) {
    using namespace predicate;

    if (m_caret < m_argc) {
        const char* caret = m_argv[m_caret];
        if (is_character_p<'-'>::test(*caret)) {
            out_lexeme = cli_lexeme{ cli_lexeme_type__operator, sub_string{ caret, caret + strlen(caret) } };
        }
        else if (is_num_p::test(*caret)) {
            out_lexeme = cli_lexeme{ cli_lexeme_type__number, sub_string{ caret, caret + strlen(caret) } };
        }
        else {
            out_lexeme = cli_lexeme{ cli_lexeme_type__string, sub_string{ caret, caret + strlen(caret) } };
        }

        return cli_lexer_ret__ok;
    }

    out_lexeme = cli_lexeme{ cli_lexeme_type__invalid, sub_string{ nullptr, nullptr } };
    return cli_lexer_ret__eof;
}

// ------------------------------------------------------------------------- //
// cli_lexer_string                                                          //
// ------------------------------------------------------------------------- //

const cli_lexer_ret cli_lexer_string::next(cli_lexeme& out_lexeme) {
    using namespace predicate;

    // skip spaces
    m_caret = skip_while<is_whitespace_p>::test(m_caret, m_end);

    if (m_caret != m_end) {
        const char* caret = m_caret;
        if (is_character_p<'-'>::test(*caret)) {
            caret = skip_while<is_not_whitespace_p>::test(++caret, m_end);
            out_lexeme = cli_lexeme{ cli_lexeme_type__operator, sub_string{ m_caret, caret }  };
        }
        else if (is_num_p::test(*caret)) {
            caret = skip_while<is_float_p>::test(++caret, m_end);
            out_lexeme = cli_lexeme{ cli_lexeme_type__number, sub_string{ m_caret, caret } };
        }
        else if (is_character_p<'"'>::test(*caret)) {
            caret = skip_while<is_not_character_p<'"'>>::test(++caret, m_end);
            out_lexeme = cli_lexeme{ cli_lexeme_type__string, sub_string{ m_caret, caret } };
        }
        else {
            caret = skip_while<is_not_whitespace_p>::test(caret, m_end);
            out_lexeme = cli_lexeme{ cli_lexeme_type__string, sub_string{ m_caret, caret } };
        }

        m_caret = caret;
        return cli_lexer_ret__ok;
    }

    out_lexeme = cli_lexeme{ cli_lexeme_type__invalid, sub_string{ nullptr, nullptr } };
    return cli_lexer_ret__eof;
}

const cli_lexer_ret cli_lexer_string::peek(cli_lexeme& out_lexeme) {
    using namespace predicate;

    // skip spaces
    const char* caret = skip_while<is_whitespace_p>::test(m_caret, m_end);

    if (caret != m_end) {
        if (is_character_p<'-'>::test(*caret)) {
            caret = skip_while<is_not_whitespace_p>::test(++caret, m_end);
            out_lexeme = cli_lexeme{ cli_lexeme_type__operator, sub_string{ m_caret, caret } };
        }
        else if (is_num_p::test(*caret)) {
            caret = skip_while<is_float_p>::test(++caret, m_end);
            out_lexeme = cli_lexeme{ cli_lexeme_type__number, sub_string{ m_caret, caret } };
        }
        else if (is_character_p<'"'>::test(*caret)) {
            caret = skip_while<is_not_character_p<'"'>>::test(++caret, m_end);
            out_lexeme = cli_lexeme{ cli_lexeme_type__string, sub_string{ m_caret, caret } };
        }
        else {
            caret = skip_while<is_not_whitespace_p>::test(caret, m_end);
            out_lexeme = cli_lexeme{ cli_lexeme_type__string, sub_string{ m_caret, caret } };
        }

        return cli_lexer_ret__ok;
    }

    out_lexeme = cli_lexeme{ cli_lexeme_type__invalid, sub_string{ nullptr, nullptr } };
    return cli_lexer_ret__eof;
}

// ------------------------------------------------------------------------- //

} // namespace gea //
