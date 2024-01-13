local lua_version = "5.4.4"

local lua_root = "lua-" .. lua_version

target("luacore")
    add_files(lua_root .. "/src/*.c|lua.c|luac.c")
    add_includedirs(lua_root .. "/src", {public=true})

    if not has_config('inone') then
        add_defines("LUA_BUILD_AS_DLL", {public=false})
    end
