#pragma once

namespace gea {

// ------------------------------------------------------------------------- //
// member_delegate_base                                                      //
// ------------------------------------------------------------------------- //

template <typename RET, typename... ARGS>
inline member_delegate_base<RET(ARGS...)>::function_data::function_data() : function(nullptr) {}

template <typename RET, typename... ARGS>
inline member_delegate_base<RET(ARGS...)>::function_data::function_data(const function_data& other) : function(other.function) {}

template <typename RET, typename... ARGS>
inline member_delegate_base<RET(ARGS...)>::function_data::function_data(function_t other_function) : function(other_function) {}

template <typename RET, typename... ARGS>
inline void member_delegate_base<RET(ARGS...)>::function_data::assign(const function_data& other) {
    function = other.function;
}

template <typename RET, typename... ARGS>
inline void member_delegate_base<RET(ARGS...)>::function_data::assign(function_t other_function) {
    function = other_function;
}

template <typename RET, typename... ARGS>
inline const bool member_delegate_base<RET(ARGS...)>::function_data::is_empty() const { return (function == nullptr); }

template <typename RET, typename... ARGS>
inline const bool member_delegate_base<RET(ARGS...)>::function_data::operator== (function_data& other) const {
    return (function == other.function);
}

template <typename RET, typename... ARGS>
inline const bool member_delegate_base<RET(ARGS...)>::function_data::operator!= (function_data& other) const {
    return (function != other.function);
}

// ------------------------------------------------------------------------- //
// member_delegate                                                           //
// ------------------------------------------------------------------------- //

template <typename RET, typename... ARGS>
inline member_delegate<RET(ARGS...)>::member_delegate() : m_function_data() {}

template <typename RET, typename... ARGS>
inline member_delegate<RET(ARGS...)>::member_delegate(const member_delegate& other) : m_function_data(other.m_function_data) { }

// assign delegate - member function
template <typename RET, typename... ARGS>
inline member_delegate<RET(ARGS...)>& member_delegate<RET(ARGS...)>::operator= (const member_delegate& other) {
    m_function_data.assign(other.m_function_data);
    return (*this);
}

template <typename RET, typename... ARGS>
inline const bool member_delegate<RET(ARGS...)>::is_empty() const { return m_function_data.is_empty(); }

template <typename RET, typename... ARGS>
inline const bool member_delegate<RET(ARGS...)>::operator== (const member_delegate& other) const { return m_function_data == other.m_function_data; }

template <typename RET, typename... ARGS>
inline const bool member_delegate<RET(ARGS...)>::operator!= (const member_delegate& other) const { return m_function_data != other.m_function_data; }

template <typename RET, typename... ARGS>
RET member_delegate<RET(ARGS...)>::operator() (void* self, ARGS... args) const {
    return (*m_function_data.function)(self, args...);
}

// create delegate - member function
template <typename RET, typename... ARGS>
template <class T, RET(T::*TFunction)(ARGS...)>
static inline member_delegate<RET(ARGS...)> member_delegate<RET(ARGS...)>::create() {
    return member_delegate(member_function_call<T, TFunction>);
}

// create delegate - const member function
template <typename RET, typename... ARGS>
template <class T, RET(T::*TFunction)(ARGS...) const>
static inline member_delegate<RET(ARGS...)> member_delegate<RET(ARGS...)>::create() {
    return member_delegate(const_member_function_call<T, TFunction>);
}

template <typename RET, typename... ARGS>
inline member_delegate<RET(ARGS...)>::member_delegate(function_t function) : m_function_data(function) {}

// call wrapper - member function
template <typename RET, typename... ARGS>
template <class T, RET(T::*TFunction)(ARGS...)>
static RET member_delegate<RET(ARGS...)>::member_function_call(void* self, ARGS... args) {
    T* t = reinterpret_cast<T*>(self);
    return (t->*TFunction)(args...);
}

// call wrapper - const member function
template <typename RET, typename... ARGS>
template <class T, RET(T::*TFunction)(ARGS...) const>
static RET member_delegate<RET(ARGS...)>::const_member_function_call(void* self, ARGS... args) {
    const T* t = reinterpret_cast<T*>(self);
    return (t->*TFunction)(args...);
}

// ------------------------------------------------------------------------- //

} // namespace gea //

#include "member_delegate.inl"
