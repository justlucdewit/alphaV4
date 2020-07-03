#pragma once
#include "../../libs/lua/lua.h"
#include "../../libs/lua/lauxlib.h"

#include "../lexer/lexer.h"

void assertCommand(Token);
void interpreter(lua_State *L, Token* tokens);