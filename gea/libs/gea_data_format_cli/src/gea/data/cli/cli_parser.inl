#pragma once

// header include
#include "cli_parser.h"

// gea includes
#include <gea/core/string/string_parser.h>
#include <gea/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// common                                                                    //
// ------------------------------------------------------------------------- //

namespace cli_option_ns {

//TODO: refactor!
template <typename T>
inline bool read_tuple_element(cli_lexer& it, T& out_value);
template <>
inline bool read_tuple_element<int>(cli_lexer& it, int& out_value) {
    cli_lexeme lexeme;
    if (it.peek(lexeme) == cli_lexer_ret__ok && lexeme.token_type == cli_lexeme_type__number) {
        out_value = string_parser<int>()(lexeme.token.begin, lexeme.token.end);
        it.skip(lexeme);
        return true;
    }
    return false;
}
template <>
inline bool read_tuple_element<float>(cli_lexer& it, float& out_value) {
    cli_lexeme lexeme;
    if (it.peek(lexeme) == cli_lexer_ret__ok && lexeme.token_type == cli_lexeme_type__number) {
        out_value = string_parser<float>()(lexeme.token.begin, lexeme.token.end);
        it.skip(lexeme);
        return true;
    }
    return false;
}
template <>
inline bool read_tuple_element<sub_string>(cli_lexer& it, sub_string& out_value) {
    cli_lexeme lexeme;
    if (it.peek(lexeme) == cli_lexer_ret__ok /*&& lexeme.token_type == cli_lexeme_type__string*/) {
        out_value = string_parser<sub_string>()(lexeme.token.begin, lexeme.token.end);
        it.skip(lexeme);
        return true;
    }
    return false;
}

template <typename Tuple>
inline bool read_tuple_elements(cli_lexer& it, Tuple& value, std::index_sequence<>) {
    return true;
}

template <typename Tuple, size_t I, size_t... Is>
inline bool read_tuple_elements(cli_lexer& it, Tuple& value, std::index_sequence<I, Is...>) {
    return read_tuple_element(it, std::get<I>(value)) && read_tuple_elements(it, value, std::index_sequence<Is...>{});
}

template <typename ... Ts>
inline bool read_tuple_elements(cli_lexer& it, std::tuple<Ts...>& tuple) {
    return read_tuple_elements(it, tuple, std::make_index_sequence<sizeof...(Ts)>{});
}

} // namespace cli_option_ns //

// ------------------------------------------------------------------------- //
// cli_command                                                               //
// ------------------------------------------------------------------------- //

inline cli_command::cli_command() : m_is_set(false) {}
inline bool cli_command::set(cli_lexer& lexer) { m_is_set = true; return true; }
inline const bool cli_command::is_set() const { return m_is_set; }

// ------------------------------------------------------------------------- //
// cli_option                                                                //
// ------------------------------------------------------------------------- //

template <typename... Ts>
inline cli_option<Ts...>::cli_option() : m_is_set(false) {}
template <typename... Ts>
inline bool cli_option<Ts...>::set(cli_lexer& lexer) {
    m_is_set = true;
    return cli_option_ns::read_tuple_elements<Ts...>(lexer, m_values);
}
template <typename... Ts>
inline const bool cli_option<Ts...>::is_set() const { return m_is_set; }

template <typename ... Ts>
template <size_t I>
inline typename std::tuple_element<I, std::tuple<Ts...>>::type cli_option<Ts...>::get() { return std::get<I>(m_values); }

// ------------------------------------------------------------------------- //
// cli_parser                                                                //
// ------------------------------------------------------------------------- //

inline cli_parser::cli_parser(cli_lexer& lexer) : m_lexer(lexer) {}

inline void cli_parser::add_command(const char* op, const char* hint, cli_command& command) {
    const callback_t callback = callback_t::create<cli_command, & cli_command::set>(&command);
    add_command(op, hint, callback);
}
template <typename... Ts>
inline void cli_parser::add_option(const char* op, const char* hint, cli_option<Ts...>& option) {
    const callback_t callback = callback_t::create<cli_option<Ts...>, & cli_option<Ts...>::set>(&option);
    add_option(op, hint, callback);
}

inline void cli_parser::add_command(const char* op, const char* hint, const callback_t callback) {
    l_assert_msg(!string_util::is_empty(op), "op must be a valid string!");
    const command command = { command_type__command, op, hint, callback };
    m_commands.push_back(command);
}
inline void cli_parser::add_option(const char* op, const char* hint, const callback_t callback) {
    l_assert_msg(!string_util::is_empty(op), "op must be a valid string!");
    const command command = { command_type__option, op, hint, callback };
    m_commands.push_back(command);
}

// ------------------------------------------------------------------------- //

} // namespace gea //
