//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include "assets.hpp"
#include "map.hpp"
#include "flags.hpp"
#include "camera.hpp"

using namespace blit;

map::TileMap tile_map;
Point screen_tiles;
map::MapSections current_section;

/**
 * Parses the tmx struct into a tile map struct with render optimized tile_data
 * @param tmx The TMX struct which contains the data directly extracted from the tilemap file
 * @return The rendering and memory optimized TileMap struct
 */
map::TileMap map::precalculate_tile_data(map::TMX_16 *tmx) {
	std::vector<map::Tile> tile_data;
	Size spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
	bool first_tile = true;
	bool last_tile;
	uint16_t tile_id, x, y, z;
	uint16_t level_size = tmx->width * tmx->height;
	uint16_t previous_tile_id = 0; //Set to 0, so it can never be equal to tile_id on first run. Prevents first tile being count as 2
	uint16_t range = 0;
	uint8_t previous_tile_x = 0;
	uint8_t previous_tile_y = 0;
	bool skipped_empty_tile = false;

	//TODO get rid of triple for loop, maybe by multiplicating them all
	for (z = 0u; z < tmx->layers; z++) {
		for (x = 0u; x < tmx->width; x++) {
			for (y = 0u; y < tmx->height; y++) {
				//Extract current tile id from tmx data
				tile_id = tmx->data[x + y * tmx->width + z * level_size];

				//Support single layer maps
				if (tmx->layers == 1) {
					last_tile = (tmx->width - 1) * (tmx->height - 1) == x * y;
				} else {
					last_tile = (tmx->layers - 1) * (tmx->width - 1) * (tmx->height - 1) == x * y * z;
				}

				//Check if this is not the last tile. If it is the last, skip all steps and save previous
				if (!last_tile) {
					//Do not save empty tiles
					if (tile_id == tmx->empty_tile) {
						skipped_empty_tile = true;
						continue;
					}

					//For first tile, set previous tile to current one
					if (first_tile) {
						previous_tile_id = tile_id;
						first_tile = false;
						continue;
					}

					//Instead of saving each tile count repetitions. Make sure there are no skipped tile in between
					if (tile_id == previous_tile_id && !skipped_empty_tile) {
						range++;
						continue;
					}
				} else if (tile_id == previous_tile_id && !skipped_empty_tile) { //Increment range for last tile
					range++;
				}

				//Save first tile in row of equals and its position.
				tile_data.push_back(Tile{
					previous_tile_x,
					previous_tile_y,
					flags::get_flag(previous_tile_id),
					previous_tile_id,
					range,
					static_cast<uint16_t>((previous_tile_id % spritesheet_size.w) * TILE_SIZE),
					static_cast<uint16_t>((previous_tile_id / spritesheet_size.h) * TILE_SIZE),
				});

				//Reset range information for next tile with a different id
				range = 0;
				previous_tile_x = x;
				previous_tile_y = y;
				previous_tile_id = tile_id;
				skipped_empty_tile = false;
			}
		}
	}

	return map::TileMap{
		tmx->empty_tile,
		static_cast<uint8_t>(tmx->width),
		static_cast<uint8_t>(tmx->height),
		static_cast<uint8_t>(tmx->layers),
		tile_data
	};
}

/**
 * Loads new map section into memory and deletes the old one
 * @param map_section The enum describing the map section
 */
void map::load_section(MapSections map_section) {
	map::TMX_16 *tmx = nullptr;

	//Allocate memory for TileMap and copy it into memory
	switch (map_section) {
		case MapSections::DUNGEON:
			tmx = nullptr;
			break;
		case MapSections::GRASSLAND:
			tmx = (TMX_16 *) malloc(asset_grassland_map_length);
			memcpy(tmx, asset_grassland_map, asset_grassland_map_length);
			break;
		case MapSections::INTERIOR:
			tmx = (TMX_16 *) malloc(asset_interior_map_length);
			memcpy(tmx, asset_interior_map, asset_interior_map_length);
			break;
		case MapSections::SNOWLAND:
			tmx = (TMX_16 *) malloc(asset_snowland_map_length);
			memcpy(tmx, asset_snowland_map, asset_snowland_map_length);
			break;
	}

	if (tmx != nullptr) {
		screen_tiles = get_screen_tiles();
		current_section = map_section;

		tile_map = precalculate_tile_data(tmx);

		//Remove tmx struct from memory because it's only required for the pre-calculations
		free(tmx);
	}
}

/**
 * Draws the tile map to the screen if a TileMap is loaded in the memory
 * @param camera_position The position of the camera on the TileMap
 */
void map::draw() {
	Point camera_position = camera::get_screen_position();
	Point camera_position_world = screen_to_world(camera_position);

	uint16_t i, r, tile_x, tile_y;
	for (i = 0u; i < tile_map.data.size(); i++) {
		tile_x = tile_map.data[i].x;

		for (r = 0u; r <= tile_map.data[i].range; r++) {
			tile_y = (tile_map.data[i].y + r) &
			         (tile_map.height - 1); //Equal to modulo operator but faster, only works with powers of 2

			//Checks if tile is visible on screen
			if (camera_position_world.x <= tile_x && camera_position_world.y <= tile_y &&
			    screen_tiles.x + camera_position_world.x - tile_x >= 0 &&
			    screen_tiles.y + camera_position_world.y - tile_y >= 0) {
				screen.blit_sprite(
					Rect(tile_map.data[i].sprite_rect_x, tile_map.data[i].sprite_rect_y, TILE_SIZE, TILE_SIZE),
					Point(tile_x * TILE_SIZE, tile_y * TILE_SIZE) - camera_position,
					SpriteTransform::NONE
				);
			}

			//Increment tile_x for next loop if tile_y hits upper limit
			if (tile_y == tile_map.height - 1) {
				tile_x++;
			}
		}
	}
}

/**
 * Gets the id of a tile at a specific Point on the map.
 * Always selects the tile on the highest layer if several tiles overlap.
 * @param p The point at which the tile is located
 * @return The id of the tile mapped to the sprite sheet
 */
uint8_t map::get_flag(Point &p) {
	uint16_t i = tile_map.data.size();
	uint8_t flag_enum_id = 0;
	uint8_t tile_max_x;
	uint8_t tile_max_y;
	bool found = false;

	while (i > 0 && !found) {
		i--;
		tile_max_x = tile_map.data[i].x + (tile_map.data[i].x + tile_map.data[i].range) / tile_map.width;
		tile_max_y = (tile_map.data[i].y + tile_map.data[i].range) & (tile_map.height - 1);

		if (point_in_area(p, tile_map.data[i].x, tile_map.data[i].y, tile_max_x, tile_max_y)) {
			flag_enum_id = tile_map.data[i].flag;
			found = true;
		}
	}

	return flag_enum_id;
}

map::MapSections map::get_section() {
	return current_section;
}

/**
 * Checks if a point is within an area of the map defined by a min and max point.
 * It is expected that the map is drawn from top to bottom and then left to right.
 * @param p The point which shall be checked
 * @param min_x The position at which the rectangle begins on the x-axis
 * @param min_y The position at which the rectangle begins on the y-axis
 * @param max_x The position at which the rectangle ends on the x-axis
 * @param max_y The position at which the rectangle ends on the y-axis
 * @return True if the point p is within the rectangle, else false
 */
bool map::point_in_area(Point &p, uint8_t min_x, uint8_t min_y, uint8_t max_x, uint8_t max_y) {
	return (((p.x == min_x && p.y >= min_y) || p.x > min_x) &&
	        ((p.x == max_x && p.y <= max_y) || p.x < max_x));
}

