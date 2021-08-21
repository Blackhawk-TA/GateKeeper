//
// Created by daniel on 27.02.21.
//

#pragma once
#include "32blit.hpp"

using namespace blit;

//Sprite and map constants
constexpr uint8_t TILE_SIZE = 16;
constexpr uint8_t LAYER_COUNT = 3;
constexpr uint16_t LEVEL_WIDTH = 128;
constexpr uint16_t LEVEL_HEIGHT = 128;
constexpr uint32_t LEVEL_SIZE = LEVEL_WIDTH * LEVEL_HEIGHT;

Vec2 screen_to_world(const Vec2 &p);
Point screen_to_world(const Point &p);

Point world_to_screen(const Point &p);
Point world_to_screen(const float &x, const float &y);

Point get_sprite_sheet_size();
