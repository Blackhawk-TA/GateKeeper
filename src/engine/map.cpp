//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include "assets.hpp"
#include "map.hpp"
#include "flags.hpp"
#include "camera.hpp"

using namespace blit;

map::TMX_16 *tmx;
Point screen_tiles;
map::MapSections current_section;
std::vector<map::Tile> tile_data;

/**
 * Parses the tile map data into optimized tile struct vector
 */
void map::precalculate_tile_data() {
	Point sprite_sheet_size = get_sprite_sheet_size(screen.sprites->bounds);
	bool first_tile = true;
	bool last_tile;
	uint16_t tile_id, x, y, z;
	uint16_t level_size = tmx->width * tmx->height;
	uint16_t previous_tile_id = 0; //Set to 0, so it can never be equal to tile_id on first run. Prevents first tile being count as 2
	uint16_t range = 0;
	uint8_t previous_tile_x = 0;
	uint8_t previous_tile_y = 0;

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
						continue;
					}

					//For first tile, set previous tile to current one
					if (first_tile) {
						previous_tile_id = tile_id;
						first_tile = false;
						continue;
					}

					//Instead of saving each tile count repetitions
					if (tile_id == previous_tile_id) {
						range++;
						continue;
					}
				} else if (tile_id == previous_tile_id) { //Increment range for last tile
					range++;
				}

				//Save first tile in row of equals and its position.
				tile_data.push_back(Tile{
						previous_tile_x,
						previous_tile_y,
						flags::get_flag(previous_tile_id),
						previous_tile_id,
						range,
						static_cast<uint16_t>((previous_tile_id % sprite_sheet_size.x) * TILE_SIZE),
						static_cast<uint16_t>((previous_tile_id / sprite_sheet_size.y) * TILE_SIZE),
				});

				//Reset range information for next tile with a different id
				range = 0;
				previous_tile_x = x;
				previous_tile_y = y;
				previous_tile_id = tile_id;
			}
		}
	}
}

/**
 * Loads new map section into memory and deletes the old one
 * @param map_section The enum describing the map section
 */
void map::load_section(MapSections map_section) {
	//Remove old TileMap from memory to load_section a new one
	if (tmx != nullptr) {
		free(tmx);
	}

	//Remove old TileMap
	tile_data.clear();

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

	if (tmx == nullptr) return;

	screen_tiles = get_screen_tiles();
	current_section = map_section;

	precalculate_tile_data();
}

/**
 * Draws the tile map to the screen if a TileMap is loaded in the memory
 * @param camera_position The position of the camera on the TileMap
 */
void map::draw() {
	Point camera_position = camera::get_screen_position();
	Point camera_position_world = screen_to_world(camera_position);

	if (tmx == nullptr) return; //Prevent rendering when TileMap is not loaded

	uint16_t r, tile_x, tile_y;
	for (auto i = 0u; i < tile_data.size(); i++)  {
		tile_x = tile_data[i].x;

		for (r = 0u; r <= tile_data[i].range; r++) {
			tile_y = (tile_data[i].y + r) & (tmx->height - 1); //Equal to modulo operator but faster, only works with powers of 2

			//Checks if tile is visible on screen
			if (camera_position_world.x <= tile_x && camera_position_world.y <= tile_y &&
			screen_tiles.x + camera_position_world.x - tile_x >= 0 && screen_tiles.y + camera_position_world.y - tile_y >= 0)
			{
				screen.blit_sprite(
						Rect(tile_data[i].sprite_rect_x, tile_data[i].sprite_rect_y, TILE_SIZE, TILE_SIZE),
						Point(tile_x * TILE_SIZE, tile_y * TILE_SIZE) - camera_position,
						SpriteTransform::NONE
				);
			}

			//Increment tile_x for next loop if tile_y hits upper limit
			if (tile_y == tmx->height - 1) {
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
	uint16_t i = tile_data.size();
	uint16_t flag_enum_id = 0;
	uint8_t tile_max_x;
	uint8_t tile_max_y;
	bool found = false;

	while (i > 0 && !found) {
		i--;
		tile_max_x = tile_data[i].x + (tile_data[i].x + tile_data[i].range) / tmx->width;
		tile_max_y = (tile_data[i].y + tile_data[i].range) & (tmx->height -1);

		if (p.x >= tile_data[i].x && p.y >= tile_data[i].y && p.x <= tile_max_x && p.y <= tile_max_y) {
			flag_enum_id = tile_data[i].flag;
			found = true;
		}
	}

	return flag_enum_id;
}

map::MapSections map::get_section() {
	return current_section;
}
