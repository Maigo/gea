#pragma once

// gea includes
#include <gea/core/string/string.h>

namespace gea {

// ------------------------------------------------------------------------- //
// common                                                                    //
// ------------------------------------------------------------------------- //

enum cli_lexer_ret {
    cli_lexer_ret__ok,
    cli_lexer_ret__eof,

    cli_lexer_ret__error,
};
static inline const char* const to_string(const cli_lexer_ret value);

enum cli_lexeme_type {
    cli_lexeme_type__invalid,
    cli_lexeme_type__operator,
    cli_lexeme_type__string,
    cli_lexeme_type__number,
};
static inline const char* const to_string(cli_lexeme_type value);

struct cli_lexeme {
    cli_lexeme_type token_type;
    sub_string token;
};

// ------------------------------------------------------------------------- //
// cli_lexer                                                                 //
// ------------------------------------------------------------------------- //

class cli_lexer {
public:
    virtual ~cli_lexer() = default;

    virtual const cli_lexer_ret next(cli_lexeme& out_lexeme) = 0;
    virtual const cli_lexer_ret peek(cli_lexeme& out_lexeme) = 0;
    virtual const cli_lexer_ret skip(const cli_lexeme& lexeme) = 0;
    virtual void reset() = 0;
};

// ------------------------------------------------------------------------- //
// cli_lexer_arg                                                             //
// ------------------------------------------------------------------------- //
class cli_lexer_arg : public cli_lexer {
public:
    virtual ~cli_lexer_arg() = default;

    inline cli_lexer_arg();
    inline cli_lexer_arg(const int argc, const char** argv);

    virtual const cli_lexer_ret next(cli_lexeme& out_lexeme);
    virtual const cli_lexer_ret peek(cli_lexeme& out_lexeme);
    inline virtual const cli_lexer_ret skip(const cli_lexeme& lexeme);
    inline virtual void reset();

private:
    const int m_argc;
    const char** m_argv;

    int m_caret;
};

// ------------------------------------------------------------------------- //
// cli_lexer_string                                                          //
// ------------------------------------------------------------------------- //

class cli_lexer_string : public cli_lexer {
public:
    virtual ~cli_lexer_string() = default;

    inline cli_lexer_string();
    inline cli_lexer_string(const char* const begin, const char* const end);
    inline cli_lexer_string(const char* const input, const size_t size);

    virtual const cli_lexer_ret next(cli_lexeme& out_lexeme) override;
    virtual const cli_lexer_ret peek(cli_lexeme& out_lexeme) override;
    inline virtual const cli_lexer_ret skip(const cli_lexeme& lexeme) override;
    inline virtual void reset() override;

private:
    const char* const m_begin;
    const char* const m_end;

    const char* m_caret;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "cli_lexer.inl"
