#pragma once

//TODO: replace
#define static_hash(s,v) (v)

namespace gea {
namespace uni {

enum enc {
    ASCII = static_hash("ASCII", 0x6e26aa30),
    UTF8  = static_hash("UTF8",  0xcf2e6766),
    UTF16 = static_hash("UTF16", 0x3b6cf82f),
    UTF32 = static_hash("UTF32", 0xddbf6236),
    UCS2  = static_hash("UCS2",  0x15255f1b),
    UCS4  = static_hash("UCS4",  0xb40d251f),
};

} // namespace uni //
} // namespace gea //
