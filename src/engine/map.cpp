//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include <iostream>
#include "assets.hpp"
#include "map.hpp"

using namespace blit;

std::vector<std::array<uint16_t, LEVEL_SIZE>> layer_data;
map::TMX_16 *tmx;
Point screen_tiles;
Point sprite_sheet_size;
uint8_t current_layer_count;
map::MapSections current_section;
std::vector<map::Tile> tile_data;

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
		case MapSections::EXTERIOR:
			tmx = (TMX_16 *) malloc(asset_exterior_map_length);
			//TODO handle error case if no mem available
			memcpy(tmx, asset_exterior_map, asset_exterior_map_length);
			break;
		case MapSections::INTERIOR:
			tmx = (TMX_16 *) malloc(asset_interior_map_length);
			memcpy(tmx, asset_interior_map, asset_interior_map_length);
			break;
		case MapSections::WINTER:
			tmx = (TMX_16 *) malloc(asset_winter_map_length);
			memcpy(tmx, asset_winter_map, asset_winter_map_length);
			break;
	}

	if (tmx == nullptr) return;

	screen_tiles = get_screen_tiles();
	sprite_sheet_size = get_sprite_sheet_size(screen.sprites->bounds);
	current_section = map_section;
	current_layer_count = tmx->layers;
//	level_size = tmx->width * tmx->height;

	//TODO move to own function and class with Tile and SpriteData structs
	bool first_tile = true;
	bool last_tile;
	uint16_t tile_id;
	uint16_t previous_tile_id = 0; //Set to 0, so it can never be equal to tile_id on first run. Prevents first tile being count as 2
	uint16_t range = 0;
	uint16_t x, y, z;
	uint8_t previous_tile_x = 0;
	uint8_t previous_tile_y = 0;

	//TODO get rid of triple for loop, maybe by multiplicating them all
	for (z = 0u; z < tmx->layers; z++) {
		for (x = 0u; x < tmx->width; x++) {
			for (y = 0u; y < tmx->height; y++) {
				//Extract current tile id from tmx data
				//TODO umbauen so dass es nicht von oben nach unten sondern von rechts nach links liest.
				tile_id = tmx->data[y * tmx->width + x + z * LEVEL_SIZE];

				last_tile = (tmx->layers - 1) * (tmx->width - 1) * (tmx->height - 1) == x * y * z;

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
				}

				//Save first tile in row of equals and its position.
				tile_data.push_back(Tile{
					previous_tile_x,
					previous_tile_y,
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
 * Draws the tile map to the screen if a TileMap is loaded in the memory
 * @param camera_position The position of the camera on the TileMap
 */
void map::draw(Point camera_position) {
//	uint16_t tile, x, y;
	Point camera_position_world = screen_to_world(camera_position);

	if (tmx == nullptr) return; //Prevent rendering when TileMap is not loaded

	//TODO optimize by removing loops: Maybe use layer_data instead of loop for x & y or recursion or calc x and y from layer data
	//TODO in best case this becomes a single for loop
	//TODO optimizations here require flag handler rework
	/*
	for (auto &layer: layer_data) {
		for (x = 0; x < tmx->height; x++) {
			for (y = 0; y < tmx->width; y++) {
				//Checks if tile is visible on screen
				if (screen_tiles.x + camera_position_world.x - x >= 0 && camera_position_world.x <= x &&
					screen_tiles.y + camera_position_world.y - y >= 0 && camera_position_world.y <= y)
				{
					tile = layer[y * tmx->width + x];
					if (tile != tmx->empty_tile) { //Do not draw empty tiles
						screen.blit_sprite(
								Rect((tile % sprite_sheet_size.x) * TILE_SIZE, (tile / sprite_sheet_size.y) * TILE_SIZE,
								     TILE_SIZE, TILE_SIZE),
								world_to_screen(x, y) - camera_position,
								SpriteTransform::NONE
						);
					}
				}
			}
		}
	}*/

	uint16_t i, tile_x, tile_y;
	for (Tile &tile : tile_data) {
		if (tile.range > 0) {
			for (i = 0u; i < tile.range; i++) {
				tile_x = (tile.x + i) % tmx->width; //TODO should render from top to button before doing left to right
				tile_y = (tile.y + i) / tmx->width;

				//Checks if tile is visible on screen
				if (screen_tiles.x + camera_position_world.x - tile_x >= 0 && camera_position_world.x <= tile_x &&
				    screen_tiles.y + camera_position_world.y - tile_y >= 0 && camera_position_world.y <= tile_y) {
					screen.blit_sprite(
							Rect(tile.sprite_rect_x, tile.sprite_rect_y, TILE_SIZE, TILE_SIZE),
							Point(tile_x * TILE_SIZE, tile_y * TILE_SIZE) - camera_position,
							SpriteTransform::NONE
					);
				}
			}
		} else {
			//Checks if tile is visible on screen
			if (screen_tiles.x + camera_position_world.x - tile_x >= 0 && camera_position_world.x <= tile_x &&
			    screen_tiles.y + camera_position_world.y - tile_x >= 0 && camera_position_world.y <= tile_y) {
				screen.blit_sprite(
						Rect(tile.sprite_rect_x, tile.sprite_rect_y, TILE_SIZE, TILE_SIZE),
						Point(tile.x * TILE_SIZE, tile.y * TILE_SIZE) - camera_position,
						SpriteTransform::NONE
				);
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
uint16_t map::tile_at(Point &p) {
	uint8_t i = current_layer_count;
	uint16_t tile = 0;

	while (i > 0 && tile == 0) {
		i--;
		tile = layer_data[i][p.y * tmx->width + p.x];
	}

	return tile;
}

map::MapSections map::get_section() {
	return current_section;
}

uint8_t map::get_layer_count() {
	return current_layer_count;
}
