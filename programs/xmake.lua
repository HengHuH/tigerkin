
target("game")
    if is_plat("windows") then
        add_rules("win.sdk.application")
        add_files("win32/game.cpp", "win32/game.rc")
    end

    set_kind("binary")
    add_deps("tigerkin")
    add_syslinks("user32")