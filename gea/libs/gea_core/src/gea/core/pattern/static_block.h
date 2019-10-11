#pragma once

// ------------------------------------------------------------------------- //
// static_block                                                              //
// ------------------------------------------------------------------------- //

#define __gea_static_block_impl2(func_name,var_name) \
    static void func_name(); \
    static int var_name = (func_name(), 0); \
    static void func_name()

#define __gea_static_block_impl1(prefix) \
    __gea_static_block_impl2(gea_concatenate(prefix, _fn), gea_concatenate(prefix, _var))

#define gea_static_block __gea_static_block_impl1(gea_make_unique(__static_block_))

// ------------------------------------------------------------------------- //
