# Basic parameters; check that these match your project / environment
cmake_minimum_required(VERSION 3.9)

# Replace "game" with a name for your project (this is used the name of the output)
project(GateKeeper)

# Add your sources here (adding headers is optional, but helps some CMake generators)
set(PROJECT_SOURCE
        src/engine/camera.cpp src/engine/camera.hpp
        src/engine/flags.cpp src/engine/flags.hpp
        src/engine/map.cpp src/engine/map.hpp
        src/engine/transition.cpp src/engine/transition.hpp
        src/game.cpp src/game.hpp
        src/scenes/scene_interface.hpp
        src/scenes/game_scene.cpp src/scenes/game_scene.hpp
        src/scenes/menu_scene.cpp src/scenes/menu_scene.hpp
        src/scenes/options_scene.cpp src/scenes/options_scene.hpp
        src/handlers/entry_handler.cpp src/handlers/entry_handler.hpp
        src/handlers/game_objects.cpp src/handlers/game_objects.hpp
        src/handlers/stargate_handler.cpp src/handlers/stargate_handler.hpp
        src/items/items.cpp src/items/items.hpp
        src/items/inventory/gate_part.cpp
        src/items/sidemenu/sidemenu_back_entry.cpp
        src/items/sidemenu/inventory_entry.cpp
        src/items/sidemenu/save_entry.cpp
        src/items/sidemenu/quit_entry.cpp
        src/items/options/show_fps_entry.cpp
        src/items/options/options_back_entry.cpp
        src/items/menu/load_entry.cpp
        src/items/menu/new_save_entry.cpp
        src/items/generic/options_entry.cpp
        src/game_objects/stargate.cpp src/game_objects/stargate.hpp
        src/game_objects/gate_statue.cpp src/game_objects/gate_statue.hpp
        src/game_objects/template/game_object.cpp src/game_objects/template/game_object.hpp
        src/player.cpp src/player.hpp
        src/ui/controls/box.cpp src/ui/controls/box.hpp
        src/ui/controls/listbox.cpp src/ui/controls/listbox.hpp
        src/ui/inventory.cpp src/ui/inventory.hpp
        src/ui/sidemenu.cpp src/ui/sidemenu.hpp
        src/ui/controls/textbox.cpp src/ui/controls/textbox.hpp
        src/ui/overlay.cpp src/ui/overlay.hpp
        src/utils/saves/savegame.cpp src/utils/saves/savegame.hpp
        src/utils/saves/options.cpp src/utils/saves/options.hpp
        src/utils/utils.cpp src/utils/utils.hpp
)
# ... and any other files you want in the release here
set(PROJECT_DISTRIBS LICENSE.md README.md)

# Build configuration; approach this with caution!
if(MSVC)
  add_compile_options("/W4" "/wd4244" "/wd4324" "/wd4458" "/wd4100")
else()
  add_compile_options("-Wall" "-Wextra" "-Wdouble-promotion" "-Wno-unused-parameter")
endif()

find_package (32BLIT CONFIG REQUIRED PATHS ../32blit-sdk $ENV{PATH_32BLIT_SDK})

blit_executable (${PROJECT_NAME} ${PROJECT_SOURCE})
blit_assets_yaml (${PROJECT_NAME} assets.yml)
blit_metadata (${PROJECT_NAME} metadata.yml)
add_custom_target (flash DEPENDS ${PROJECT_NAME}.flash)

# setup release packages
install (FILES ${PROJECT_DISTRIBS} DESTINATION .)
set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set (CPACK_GENERATOR "ZIP" "TGZ")
include (CPack)
