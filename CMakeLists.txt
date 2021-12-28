# Basic parameters; check that these match your project / environment
cmake_minimum_required(VERSION 3.9)

# Replace "game" with a name for your project (this is used the name of the output)
project(GateKeeper)

# Add your sources here (adding headers is optional, but helps some CMake generators)
set(PROJECT_SOURCE
        src/engine/camera.cpp src/engine/camera.hpp
        src/engine/flags.cpp src/engine/flags.hpp
        src/engine/map.cpp src/engine/map.hpp
        src/engine/effects/transition.cpp src/engine/effects/transition.hpp
        src/game.cpp src/game.hpp
        src/scenes/scene_interface.hpp
        src/scenes/combat/combat_scene.cpp src/scenes/combat/combat_scene.hpp
        src/scenes/game/game_scene.cpp src/scenes/game/game_scene.hpp
        src/scenes/game/utils.cpp src/scenes/game/utils.hpp
        src/scenes/menu/menu_scene.cpp src/scenes/menu/menu_scene.hpp
        src/scenes/options/options_scene.cpp src/scenes/options/options_scene.hpp
        src/scenes/combat/characters/template/character.cpp src/scenes/combat/characters/template/character.hpp
        src/scenes/combat/characters/enemy.cpp src/scenes/combat/characters/enemy.hpp
        src/scenes/combat/characters/player.cpp src/scenes/combat/characters/player.hpp
        src/scenes/combat/ui/combat_menu.cpp src/scenes/combat/ui/combat_menu.hpp
        src/scenes/combat/ui/combat_stats.cpp src/scenes/combat/ui/combat_stats.hpp
        src/scenes/game/handlers/game_objects/extensions/character_handler.cpp src/scenes/game/handlers/game_objects/extensions/character_handler.hpp
        src/scenes/game/handlers/entry_handler.cpp src/scenes/game/handlers/entry_handler.hpp
        src/scenes/game/handlers/game_objects/game_object_handler.cpp src/scenes/game/handlers/game_objects/game_object_handler.hpp
        src/scenes/game/handlers/game_objects/extensions/character_handler.cpp src/scenes/game/handlers/game_objects/extensions/character_handler.hpp
        src/scenes/game/handlers/game_objects/extensions/stargate_handler.cpp src/scenes/game/handlers/game_objects/extensions/stargate_handler.hpp
        src/scenes/game/handlers/game_objects/extensions/dungeon_door_handler.cpp src/scenes/game/handlers/game_objects/extensions/dungeon_door_handler.hpp
        src/items/items.cpp src/items/items.hpp
        src/items/inventory/gate_part.cpp
        src/items/inventory/apple.cpp
        src/items/inventory/carrot.cpp
        src/items/inventory/carrot_seed.cpp
        src/items/sidemenu/sidemenu_back_entry.cpp
        src/items/sidemenu/inventory_entry.cpp
        src/items/sidemenu/save_entry.cpp
        src/items/sidemenu/quit_entry.cpp
        src/items/options/show_fps_entry.cpp
        src/items/options/options_back_entry.cpp
        src/items/menu/load_entry.cpp
        src/items/menu/new_save_entry.cpp
        src/items/generic/options_entry.cpp
        src/scenes/game/game_objects/characters/template/character.cpp src/scenes/game/game_objects/characters/template/character.hpp
        src/scenes/game/game_objects/characters/enemy.cpp src/scenes/game/game_objects/characters/enemy.hpp
        src/scenes/game/game_objects/characters/salesman.cpp src/scenes/game/game_objects/characters/salesman.hpp
        src/scenes/game/game_objects/characters/villager.cpp src/scenes/game/game_objects/characters/villager.hpp
        src/scenes/game/game_objects/objects/carrot_bed.cpp src/scenes/game/game_objects/objects/carrot_bed.hpp
        src/scenes/game/game_objects/objects/dungeon_door.cpp src/scenes/game/game_objects/objects/dungeon_door.hpp
        src/scenes/game/game_objects/objects/fruit_tree.cpp src/scenes/game/game_objects/objects/fruit_tree.hpp
        src/scenes/game/game_objects/objects/lever.cpp src/scenes/game/game_objects/objects/lever.hpp
        src/scenes/game/game_objects/objects/sign.cpp src/scenes/game/game_objects/objects/sign.hpp
        src/scenes/game/game_objects/objects/stargate.cpp src/scenes/game/game_objects/objects/stargate.hpp
        src/scenes/game/game_objects/objects/gate_statue.cpp src/scenes/game/game_objects/objects/gate_statue.hpp
        src/scenes/game/game_objects/template/game_object.cpp src/scenes/game/game_objects/template/game_object.hpp
        src/scenes/game/player.cpp src/scenes/game/player.hpp
        src/engine/ui/box.cpp src/engine/ui/box.hpp
        src/engine/ui/listbox.cpp src/engine/ui/listbox.hpp
        src/scenes/game/ui/inventory.cpp src/scenes/game/ui/inventory.hpp
        src/scenes/game/ui/sidemenu.cpp src/scenes/game/ui/sidemenu.hpp
        src/engine/ui/textbox.cpp src/engine/ui/textbox.hpp
        src/scenes/game/ui/overlay.cpp src/scenes/game/ui/overlay.hpp
        src/utils/saves/savegame.cpp src/utils/saves/savegame.hpp
        src/utils/saves/options.cpp src/utils/saves/options.hpp
        src/utils/utils.cpp src/utils/utils.hpp
        src/utils/game_time.cpp src/utils/game_time.hpp
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
