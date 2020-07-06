#pragma once

#include "libs/lua/lua.h"
#include "libs/lua/lauxlib.h"
#include "../lexer/lexer.h"
#include "../luahelpers/luahelpers.h"

void commandIdentifier(lua_State* L, Token** tokens);