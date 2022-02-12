//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include <iostream>
#include "assets.hpp"
#include "map.hpp"
#include "flags.hpp"
#include "camera.hpp"

using namespace blit;

map::TileMap tile_map;
Point screen_tiles;
map::MapSection current_section;
Pen background;

/**
 * Parses the tmx struct into a tile map struct with render optimized tile_data
 * @param tmx The TMX struct which contains the data directly extracted from the tilemap file
 * @return The rendering and memory optimized TileMap struct
 */
map::TileMap map::precalculate_tile_data(map::TMX_16 *tmx) {
	std::vector<map::Tile> tile_data;
	Size spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
	uint16_t tile_range, tile_id, i;
	uint8_t tile_x = 0;
	uint8_t tile_y = 0;
	uint16_t data_length = tmx->data[0]; //First array entry is the array length

	//Skip first layer because it only contains the array length
	for (i = 1u; i < data_length; i += 2) {
		//Extract current tile id from tmx data
		tile_range = tmx->data[i];
		tile_id = tmx->data[i + 1];

		if (tile_id != tmx->empty_tile) {
			//Save first tile in row of equals and its position.
			tile_data.push_back(Tile{
				tile_x,
				tile_y,
				flags::get_flag(tile_id),
				tile_range,
				static_cast<uint16_t>((tile_id % spritesheet_size.w) * TILE_SIZE),
				static_cast<uint16_t>((tile_id / spritesheet_size.h) * TILE_SIZE),
			});
		}

		tile_x = (((tile_y + tile_range + 1) / tmx->height) + tile_x) & (tmx->width - 1);
		tile_y = (tile_y + tile_range + 1) & (tmx->height - 1);
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
void map::load_section(MapSection map_section) { //TODO make sure only map data is in memory when loading new section
	map::TMX_16 *tmx = nullptr;

	//Allocate memory for TileMap and copy it into memory
	switch (map_section) {
		case MapSection::DUNGEON:
			tmx = (TMX_16 *) malloc(asset_dungeon_map_length);
			memcpy(tmx, asset_dungeon_map, asset_dungeon_map_length);
			background = Pen(48, 44, 46);
			break;
		case MapSection::GRASSLAND:
			tmx = (TMX_16 *) malloc(asset_grassland_map_length);
			memcpy(tmx, asset_grassland_map, asset_grassland_map_length);
			background = Pen(113, 170, 52);
			break;
		case MapSection::GRASSLAND_COMBAT:
			tmx = (TMX_16 *) malloc(asset_grassland_combat_map_length);
			memcpy(tmx, asset_grassland_combat_map, asset_grassland_combat_map_length);
			background = Pen(113, 170, 52);
			break;
		case MapSection::INTERIOR:
			tmx = (TMX_16 *) malloc(asset_interior_map_length);
			memcpy(tmx, asset_interior_map, asset_interior_map_length);
			background = Pen(48, 44, 46);
			break;
		case MapSection::SNOWLAND:
			tmx = (TMX_16 *) malloc(asset_snowland_map_length);
			memcpy(tmx, asset_snowland_map, asset_snowland_map_length);
			background = Pen(223, 246, 245);
			break;
		case MapSection::DESERT:
			tmx = (TMX_16 *) malloc(asset_desert_map_length);
			memcpy(tmx, asset_desert_map, asset_desert_map_length);
			background = Pen(244, 204, 161);
			break;
		case MapSection::VOLCANO:
			tmx = (TMX_16 *) malloc(asset_volcano_map_length);
			memcpy(tmx, asset_volcano_map, asset_volcano_map_length);
			background = Pen(244, 180, 27);
			break;
		case MapSection::DUNGEON_COMBAT:
			tmx = (TMX_16 *) malloc(asset_dungeon_combat_map_length);
			memcpy(tmx, asset_dungeon_combat_map, asset_dungeon_combat_map_length);
			background = Pen(60, 89, 86);
			break;
		case MapSection::VOLCANO_COMBAT:
			tmx = (TMX_16 *) malloc(asset_volcano_combat_map_length);
			memcpy(tmx, asset_volcano_combat_map, asset_volcano_combat_map_length);
			background = Pen(244, 180, 27);
			break;
		case MapSection::SNOWLAND_COMBAT:
			tmx = (TMX_16 *) malloc(asset_snowland_combat_map_length);
			memcpy(tmx, asset_snowland_combat_map, asset_snowland_combat_map_length);
			background = Pen(223, 246, 245);
			break;
		case MapSection::DESERT_COMBAT:
			tmx = (TMX_16 *) malloc(asset_desert_combat_map_length);
			memcpy(tmx, asset_desert_combat_map, asset_desert_combat_map_length);
			background = Pen(244, 204, 161);
			break;
		default:
			std::cerr << "Invalid map section" << std::endl;
			exit(1);
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
	screen.pen = background;
	screen.rectangle(Rect(0, 0, screen.bounds.w, screen.bounds.h));

	Point camera_position = camera::get_screen_position();
	Point camera_position_world = screen_to_world(camera_position);

	uint16_t i, r, tile_x, tile_y;
	for (i = 0u; i < tile_map.data.size(); i++) {
		tile_x = tile_map.data[i].x;

		for (r = 0u; r <= tile_map.data[i].range; r++) {
			tile_y = (tile_map.data[i].y + r) & (tile_map.height - 1); //Equal to modulo operator but faster, only works with powers of 2

			//Checks if tile is visible on screen
			if (camera_position_world.x <= tile_x && camera_position_world.y <= tile_y &&
			    screen_tiles.x + camera_position_world.x - tile_x >= 0 &&
			    screen_tiles.y + camera_position_world.y - tile_y >= 0) {
				screen.blit(
					screen.sprites,
					Rect(tile_map.data[i].sprite_rect_x, tile_map.data[i].sprite_rect_y, TILE_SIZE, TILE_SIZE),
					Point(tile_x * TILE_SIZE, tile_y * TILE_SIZE) - camera_position
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
		tile_max_x = tile_map.data[i].x + (tile_map.data[i].y + tile_map.data[i].range) / tile_map.width;
		tile_max_y = (tile_map.data[i].y + tile_map.data[i].range) & (tile_map.height - 1);

		if (point_in_area(p, tile_map.data[i].x, tile_map.data[i].y, tile_max_x, tile_max_y)) {
			flag_enum_id = tile_map.data[i].flag;
			found = true;
		}
	}

	//If tile is not found it is an empty tile and therefore should be walkable
	if (!found) {
		flag_enum_id = flags::WALKABLE;
	}

	return flag_enum_id;
}

map::MapSection map::get_section() {
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

