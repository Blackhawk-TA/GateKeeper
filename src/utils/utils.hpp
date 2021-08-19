//
// Created by daniel on 27.02.21.
//

#pragma once
#include "32blit.hpp"

using namespace blit;

constexpr uint8_t TILE_SIZE = 16;
constexpr uint16_t LEVEL_WIDTH = 128;
constexpr uint16_t LEVEL_HEIGHT = 128;
constexpr uint32_t LEVEL_SIZE = LEVEL_WIDTH * LEVEL_HEIGHT;
constexpr Point SCREEN_TILES = Point(19, 14); //TODO adjust

Vec2 screen_to_world(const Vec2 &p);

Point world_to_screen(const Point &p);
Point world_to_screen(const int &x, const int &y);
