// gtest includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// gea includes
#include <gea/core/string/string_builder.h>
#include <gea/data/cli/cli_lexer.h>

namespace gea {

// ------------------------------------------------------------------------- //
// helper functions                                                          //
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// cli_lexer                                                                 //
// ------------------------------------------------------------------------- //

TEST(gea_data_cli, cli_lexer) {
    //struct data_type {
    //    const char* string;
    //    struct token_t {
    //        const cli_lexer_ret ret;
    //        const cli_lexeme_type type;
    //        const char* token;
    //    } tokens[8];
    //};
    //const data_type data_set[] = {
    //    { "   some_initial_word  -t argument    -s 0  1    -x  ", {
    //        { cli_lexer_ret__ok, cli_lexeme_type__string,  "some_initial_word"},
    //        { cli_lexer_ret__ok, cli_lexeme_type__operator, "-t" },
    //        { cli_lexer_ret__ok, cli_lexeme_type__string,  "argument"},
    //        { cli_lexer_ret__ok, cli_lexeme_type__operator, "-s" },
    //        { cli_lexer_ret__ok, cli_lexeme_type__string,  "0"},
    //        { cli_lexer_ret__ok, cli_lexeme_type__string,  "1"},
    //        { cli_lexer_ret__ok, cli_lexeme_type__operator, "-x" },
    //        { cli_lexer_ret__eof, cli_lexeme_type__invalid, nullptr }
    //    }},
    //    { "packed -x 1 2 -s", {
    //        { cli_lexer_ret__ok, cli_lexeme_type__string,  "packed"},
    //        { cli_lexer_ret__ok, cli_lexeme_type__operator, "-x" },
    //        { cli_lexer_ret__ok, cli_lexeme_type__string,  "1"},
    //        { cli_lexer_ret__ok, cli_lexeme_type__string,  "2"},
    //        { cli_lexer_ret__ok, cli_lexeme_type__operator, "-s" },
    //        { cli_lexer_ret__eof, cli_lexeme_type__operator, "-x" },
    //        { cli_lexer_ret__eof, cli_lexeme_type__invalid, nullptr },
    //        { cli_lexer_ret__eof, cli_lexeme_type__invalid, nullptr },
    //    }},
    //    { "\"string with spaces\"", {
    //        { cli_lexer_ret__ok, cli_lexeme_type__string,  "\"string with spaces\""},
    //        { cli_lexer_ret__eof, cli_lexeme_type__invalid, nullptr },
    //        { cli_lexer_ret__eof, cli_lexeme_type__invalid, nullptr },
    //        { cli_lexer_ret__eof, cli_lexeme_type__invalid, nullptr },
    //        { cli_lexer_ret__eof, cli_lexeme_type__invalid, nullptr },
    //        { cli_lexer_ret__eof, cli_lexeme_type__invalid, nullptr },
    //        { cli_lexer_ret__eof, cli_lexeme_type__invalid, nullptr },
    //        { cli_lexer_ret__eof, cli_lexeme_type__invalid, nullptr },
    //    }}
    //};

    //for (const data_type &data : data_set) {
    //    cli_lexer<parse_skip_whitespace> lexer(data.string, strlen(data.string));
    //    for (const data_type::token_t& token : data.tokens)
    //    {
    //        cli_lexeme lexeme;
    //        const cli_lexer_ret ret = lexer.next(lexeme);
    //        if (ret == cli_lexer_ret__eof)
    //            break;

    //        EXPECT_EQ(token.type, lexeme.token_type);

    //        static_string_builder<> string;
    //        string.append(lexeme.token_begin, lexeme.token_end);
    //        EXPECT_STREQ(token.token, string.data());
    //    }
    //}
    FAIL();
}

// ------------------------------------------------------------------------- //

} // namespace gea //
