#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#include <lauxlib.h>
#include "ybase64.h"

	int lua_ybase64_encode(lua_State *L) ;
int lua_ybase64_decode(lua_State *L) ;

static const luaL_Reg reg[] = {
    {"encode", lua_ybase64_encode},
	{"decode", lua_ybase64_decode},
    NULL, NULL,
  };


int luaopen_ybase64(lua_State * L) {

  luaL_newlib(L, reg);
  lua_pushvalue(L, -1);
  lua_setglobal(L, "ybase64");
  return 1;
}

int lua_ybase64_encode(lua_State *L) {
	size_t len = 0;
	unsigned char * data = NULL;
	data = (unsigned char *)lua_tolstring(L, 1, &len);
	if (len) {
		size_t result_size;
		char * base64 = ybase64_encode_alloc(data, len, &result_size);
		lua_pushstring(L, base64);
		ybase64_free(base64);
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

int lua_ybase64_decode(lua_State *L) {
	size_t len = 0;
	char * base64 = NULL;
	printf("%d\n", len);
	base64 = lua_tolstring(L, 1, &len);
	printf("%d:%s\n", len, base64);
	if (len) {
		size_t result_size;
		void * data = ybase64_decode_alloc(base64, len, &result_size);
		if(data) {
			lua_pushlstring(L, data, result_size);
			ybase64_free(data);
		}
		else {
			lua_pushnil(L);
		}
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

#ifdef __cplusplus
}
#endif
