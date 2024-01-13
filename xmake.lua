
set_project("tigerkin")
set_version("2024.1")
set_xmakever("2.7.3")
add_moduledirs("$(projectdir)/xmake")
set_languages("cxx20")

-- allowed build mode: debug, inhouse, release
set_allowedmodes("debug", "inhouse", "release")
set_defaultmode("inhouse")
if is_mode("debug") then
    add_defines("DEBUG")
    -- 启用调试符号
    set_symbols("debug")
    -- 禁用优化
    set_optimize("none")
elseif is_mode("inhouse") then
    add_defines("_INHOUSE")
    -- 启用调试符号
    set_symbols("debug")
elseif is_mode("release") then
    add_defines("_FINAL", "NDEBUG")
    -- 隐藏符号
    set_symbols("hidden")
    -- strip所有符号
    set_strip("all")
    set_optimize("fastest")
end

if is_plat("windows") then
    add_defines("NOMINMAX","UNICODE") -- windows
end

option("inone")
    set_default(false)
    add_defines("TIGER_INONE")

-- all target deps option inone
target()
    add_options("inone")

-- if all in one build with static library.
if has_config("inone") then
    set_kind("static")
else
    set_kind("shared")
end

includes("programs")
includes("engine")
includes("external")