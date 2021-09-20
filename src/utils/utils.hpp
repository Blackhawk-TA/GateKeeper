//
// Created by daniel on 27.02.21.
//

#pragma once
#include "32blit.hpp"

using namespace blit;

//Sprite and map constants. All TileMaps require to have the same size.
constexpr uint8_t TILE_SIZE = 16;

enum StargateAddresses {
	GRASSLAND = 1,
	WINTER = 2
};

bool point_in_rect(Point &p, uint8_t min_x, uint8_t min_y, uint8_t max_x, uint8_t max_y);
bool sprite_rect_in_screen(Point &position, const Size &size, Point &camera_position_world);

Point screen_to_world(const Point &p);

Point world_to_screen(const Point &p);
Point world_to_screen(const float &x, const float &y);

Point get_sprite_sheet_size(Size bounds);
Point get_screen_tiles();
