# Basic parameters; check that these match your project / environment
cmake_minimum_required(VERSION 3.9)

# Replace "game" with a name for your project (this is used the name of the output)
project(32blit-rpg)

# Add your sources here (adding headers is optional, but helps some CMake generators)
set(PROJECT_SOURCE
        src/building.cpp src/building.hpp
        src/engine/camera.cpp src/engine/camera.hpp
        src/engine/flags.cpp src/engine/flags.hpp
        src/engine/map.cpp src/engine/map.hpp
        src/engine/transition.cpp src/engine/transition.hpp
        src/game_objects/stargate.cpp src/game_objects/stargate.hpp
        src/game.cpp src/game.hpp
        src/handlers/stargate_handler.cpp src/handlers/stargate_handler.hpp
        src/player.cpp src/player.hpp
        src/ui/box.cpp src/ui/box.hpp
        src/ui/sidemenu.cpp src/ui/sidemenu.hpp
        src/ui/textbox.cpp src/ui/textbox.hpp
        src/ui/overlay.cpp src/ui/overlay.hpp
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
