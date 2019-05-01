#pragma once

// header include
#include "singleton.h"

namespace gea {

// ------------------------------------------------------------------------- //
// singleton                                                                 //
// ------------------------------------------------------------------------- //

template <class T>
inline T& singleton<T>::get() { construct(); return *s_instance; }

template <class T>
inline T* singleton<T>::get_ptr() { construct(); return s_instance; }

template <class T>
inline void singleton<T>::construct() { if (s_instance == nullptr) s_instance = new T(); }
template <class T>
inline void singleton<T>::destruct() { if (s_instance != nullptr) { delete s_instance; s_instance = nullptr; } }

template <class T>
inline bool singleton<T>::exists() { return s_instance != nullptr; }

template <class T>
T* singleton<T>::s_instance = nullptr;

// ------------------------------------------------------------------------- //

} // namespace gea //
