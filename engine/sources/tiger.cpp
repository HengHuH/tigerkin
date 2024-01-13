#include "tiger.h"

#include "lua.hpp"
#include <iostream>

int pmain(lua_State* L)
{
    luaL_openlibs(L);

//     // change package.path
//     lua_getglobal(L, "package");
//     lua_getfield(L, -1, "path");
//     const char* pp = lua_tostring(L, -1);
//     lua_pop(L, 1);
//     // std::string root = "D:/workdspace/tigerin/"
//     // std::string npp = std::string(pp) + ";scripts/?.lua";
//     // lua_push

//     // luaL_dostring(L, "(require \"game.lua\").run()");

    //luaL_dostring(L, "print(\"Hello Lua!\"); io.flush()");
    luaL_dofile(L, "D:\\workspace\\tigerkin\\engine\\sources\\game.lua");
        //     // call run()
    return 0;
}



extern "C" {
void run_game(int argc, char **argv) {

    // printf("Hello Tiger!\n");
    // #if TIGER_INONE
    // tiger::PluginInitialization();
    // #endif
    // SetPlugins(nullptr);
    // SetPlugins(&tiger::Plugins::GPluginBuiltKey);

    // const char* app_class = "TigerGame";
    // const char* app_title = "-= Tiger =-";

    // const HICON icon = ::LoadIcon(::GetModuleHandle(nullptr),
    // MAKEINTRESOURCE(IDI_MAIN)); RunTigerGame(app_class, app_title, icon, 0,
    // nullptr); while (1)
    // {

    // }
    // deal with pre args
    // --wait
    // --console

    int status, result;
    // int argc = 1;
    // const char* argv[] = { "tigerkin" };

    // printf("Hello Tiger2!\n");
    lua_State *L = luaL_newstate();
    if (L == nullptr) {
        // l_message(argv[0], "cannot create state: not enough memory");
        lua_writestringerror("%s\n", "cannot create state: not enough memory");
        return;
        // return EXIT_FAILURE;
    }
    lua_pushcfunction(L, &pmain);
    lua_pushinteger(L, argc);
    lua_pushlightuserdata(L, argv);
    status = lua_pcall(L, 2, 1, 0);
    result = lua_toboolean(L, -1);
    lua_close(L);
}
}
