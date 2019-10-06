#pragma once

// header include
#include "cli_lexer.h"

namespace gea {

// ------------------------------------------------------------------------- //
// common                                                                    //
// ------------------------------------------------------------------------- //

static inline const char* const to_string(const cli_lexer_ret value) {
    switch (value) {
    case cli_lexer_ret__ok:    return "cli_lexer_ret__ok";
    case cli_lexer_ret__eof:   return "cli_lexer_ret__eof";
    case cli_lexer_ret__error: return "cli_lexer_ret__error";
    }
    return "";
}

static inline const char* const to_string(cli_lexeme_type value) {
    switch (value) {
    case cli_lexeme_type__invalid:  return "cli_lexeme_type__invalid";
    case cli_lexeme_type__operator: return "cli_lexeme_type__operator";
    case cli_lexeme_type__string:   return "cli_lexeme_type__string";
    case cli_lexeme_type__number:   return "cli_lexeme_type__number";
    }
    return "";
}

// ------------------------------------------------------------------------- //
// cli_lexer_arg                                                             //
// ------------------------------------------------------------------------- //

inline cli_lexer_arg::cli_lexer_arg() : m_argc(0), m_argv(nullptr), m_caret(0) {}
inline cli_lexer_arg::cli_lexer_arg(const int argc, const char** argv) : m_argc(argc), m_argv(argv), m_caret(0) {}

inline const cli_lexer_ret cli_lexer_arg::skip(const cli_lexeme& lexeme) {
    if ((lexeme.token_type != cli_lexeme_type__invalid) && (m_caret < m_argc) && (m_argv[m_caret] == lexeme.token.begin))
    {
        ++m_caret;
        return cli_lexer_ret__ok;
    }
    return cli_lexer_ret__error;
}

inline void cli_lexer_arg::reset() { m_caret = 0; }

// ------------------------------------------------------------------------- //
// cli_lexer_string                                                          //
// ------------------------------------------------------------------------- //

inline cli_lexer_string::cli_lexer_string() : m_begin(nullptr), m_end(nullptr), m_caret(nullptr) {}
inline cli_lexer_string::cli_lexer_string(const char* const begin, const char* const end) : m_begin(begin), m_caret(begin), m_end(end) {}
inline cli_lexer_string::cli_lexer_string(const char* const input, const size_t size) : cli_lexer_string(input, input + size) {}

inline const cli_lexer_ret cli_lexer_string::skip(const cli_lexeme& lexeme) {
    if ((lexeme.token_type != cli_lexeme_type__invalid) && (m_caret == lexeme.token.begin))
    {
        m_caret = lexeme.token.end;
        return cli_lexer_ret__ok;
    }
    return cli_lexer_ret__error;
}

inline void cli_lexer_string::reset() { m_caret = m_begin; }

// ------------------------------------------------------------------------- //

} // namespace gea //
