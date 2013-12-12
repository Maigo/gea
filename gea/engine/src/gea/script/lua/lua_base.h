#ifndef __GEA_LUA_BASE_H__
#define __GEA_LUA_BASE_H__

// lua includes (c/c++ safe)
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus //
    #include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
#ifdef __cplusplus
}
#endif // __cplusplus //

// gea includes
#include <gea/engine/utility/assert.h>

namespace gea {

// ------------------------------------------------------------------------- //
// lua_state                                                                 //
// ------------------------------------------------------------------------- //
class lua_state {
public:
    static const uint32_t LUA_IO      = (0x01 << 0);
	static const uint32_t LUA_BASE    = (0x01 << 1);
	static const uint32_t LUA_TABLE   = (0x01 << 2);
	static const uint32_t LUA_STRING  = (0x01 << 3);
	static const uint32_t LUA_MATH    = (0x01 << 4);
	static const uint32_t LUA_LOADLIB = (0x01 << 5);
	static const uint32_t LUA_ALL     =  0x0000001F;

	inline lua_state() : m_loaded_libs(0) { m_lua = lua_open(); }
	inline ~lua_state() { lua_close(m_lua); }

	inline void open_libs(uint32_t libs) {
        l_assert_msg((m_lua != NULL), "");

		if ((~m_loaded_libs & libs) & LUA_BASE)    { luaopen_base(m_lua);    m_loaded_libs |= LUA_BASE; }      // opens the basic library
		if ((~m_loaded_libs & libs) & LUA_TABLE)   { luaopen_table(m_lua);   m_loaded_libs |= LUA_TABLE; }     // opens the table library
//		if ((~m_loaded_libs & libs) & LUA_IO)      { luaopen_io(m_lua);      m_loaded_libs |= LUA_IO; }        // opens the io library
		if ((~m_loaded_libs & libs) & LUA_STRING)  { luaopen_string(m_lua);  m_loaded_libs |= LUA_STRING; }    // opens the string library
		if ((~m_loaded_libs & libs) & LUA_MATH)    { luaopen_math(m_lua);    m_loaded_libs |= LUA_MATH; }      // opens the math library
//		if ((~m_loaded_libs & libs) & LUA_LOADLIB) { luaopen_loadlib(m_lua); m_loaded_libs |= LUA_LOADLIB; }
    }

private:
	lua_State* m_lua;
	uint32_t   m_loaded_libs;
};

} // namespace gea //

#endif // __GEA_LUA_BASE_H__ //
