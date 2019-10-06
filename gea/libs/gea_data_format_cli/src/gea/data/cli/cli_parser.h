#pragma once

// std  includes
#include <tuple>
#include <vector>

// gea includes
#include <gea/core/pattern/delegate.h>
#include <gea/core/string/string_util.h>
#include <gea/data/cli/cli_lexer.h>

namespace gea {

// ------------------------------------------------------------------------- //
// cli_command                                                               //
// ------------------------------------------------------------------------- //

class cli_command {
public:
    inline cli_command();
    inline bool set(cli_lexer& lexer);
    inline const bool is_set() const;

private:
    bool m_is_set;
};

// ------------------------------------------------------------------------- //
// cli_option                                                                //
// ------------------------------------------------------------------------- //

template <typename... Ts>
class cli_option {
public:
    inline cli_option();
    inline bool set(cli_lexer& lexer);
    inline const bool is_set() const;

    template <size_t I>
    inline typename std::tuple_element<I, std::tuple<Ts...>>::type get();

private:
    std::tuple<Ts...> m_values;
    bool m_is_set;
};

typedef cli_option<> cli_flag;

// ------------------------------------------------------------------------- //
// cli_parser                                                                //
// ------------------------------------------------------------------------- //

class cli_parser {
public:
    inline cli_parser(cli_lexer& lexer);

    inline void add_command(const char* op, const char* hint, cli_command& command);
    template <typename... Ts>
    inline void add_option(const char* op, const char* hint, cli_option<Ts...>& option);

    const bool parse();

private:
    enum command_type {
        command_type__command,
        command_type__option,
    };
    typedef delegate<bool(cli_lexer&)> callback_t;
    struct command {
        command_type type;
        const char* op;
        const char* hint;
        callback_t callback;
    };
    typedef std::vector<command> commands_t;

    inline void add_command(const char* op, const char* hint, const callback_t callback = nullptr);
    inline void add_option(const char* op, const char* hint, const callback_t callback = nullptr);

    const bool parse_command();
    const bool parse_option();

    cli_lexer& m_lexer;
    commands_t m_commands;
};

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "cli_parser.inl"
