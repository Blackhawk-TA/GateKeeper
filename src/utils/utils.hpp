//
// Created by daniel on 27.02.21.
//

#pragma once
#include "32blit.hpp"

using namespace blit;

constexpr uint8_t TILE_SIZE = 16;
constexpr uint8_t TMP_SAVE_ID = 4;
constexpr uint8_t VERSION_SAVE_ID = 5;
constexpr uint8_t MAX_ITEMS = 32;
constexpr uint8_t MAX_GAME_OBJECTS = 255;
constexpr uint8_t ANIMATION_SPRITE_COUNT = 4;

inline Surface *characters_spritesheet;
inline Surface *attack_spritesheet;
inline Surface *weapons_spritesheet;

bool sprite_rect_in_screen(Point &position, const Size &size, Point camera_position_world);

Point screen_to_world(const Point &p);

Point world_to_screen(const Point &p);
Point world_to_screen(const Vec2 &p);
Point world_to_screen(const float &x, const float &y);

Size get_spritesheet_size(Size bounds);
Point get_screen_tiles();

void load_persistent_spritesheets();
void draw_fps(uint32_t &current_time, uint32_t &ms_end);
