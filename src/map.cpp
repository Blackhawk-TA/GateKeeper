//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include "assets.hpp"
#include "map.hpp"

using namespace blit;

std::vector<std::array<uint16_t, LEVEL_SIZE>> layer_data;
map::TMX_16 *tmx;
Point screen_tiles;
Point sprite_sheet_size;
uint8_t current_layer_count;
map::MapSections current_section;

/**
 * Loads new map section into memory and deletes the old one
 * @param map_section The enum describing the map section
 */
void map::load_section(MapSections map_section) {
	// Remove old TileMap from memory to load_section a new one
	if (tmx != nullptr) {
		free(tmx);
	}

	// Remove old TileMap from layer_data
	layer_data.clear();

	switch (map_section) {
		case MapSections::DUNGEON:
			tmx = nullptr;

			current_layer_count = DUNGEON_LAYER_COUNT;
			break;
		case MapSections::EXTERIOR:
			// Allocate memory for TileMap and copy it into memory
			tmx = (TMX_16 *) malloc(asset_exterior_map_length);
			//TODO handle error case if no mem available
			memcpy(tmx, asset_exterior_map, asset_exterior_map_length);

			current_layer_count = EXTERIOR_LAYER_COUNT;
			break;
		case MapSections::INTERIOR:
			tmx = (TMX_16 *) malloc(asset_interior_map_length);
			memcpy(tmx, asset_interior_map, asset_interior_map_length);

			current_layer_count = INTERIOR_LAYER_COUNT;
			break;
		case MapSections::WINTER:
			// Allocate memory for TileMap and copy it into memory
			tmx = (TMX_16 *) malloc(asset_winter_map_length);
			memcpy(tmx, asset_winter_map, asset_winter_map_length);

			current_layer_count = WINTER_LAYER_COUNT;
			break;
	}

	if (tmx == nullptr) return;
	if (tmx->width > LEVEL_WIDTH) return;
	if (tmx->height > LEVEL_HEIGHT) return;

	uint16_t x, y, tile_index;
	screen_tiles = get_screen_tiles();
	sprite_sheet_size = get_sprite_sheet_size(screen.sprites->bounds);
	current_section = map_section;

	//TODO optimize by removing loops, currently useless because layer_data is not needed
	// maybe save all data for all layers in a one dimensional array
	for (auto i = 0u; i < current_layer_count; i++) {
		layer_data.push_back({}); // Create new empty layer to fill it later on

		//TODO can use directly loop till x < width * height
		// can be made obsolete when using tmx->data directly in draw
		for (x = 0u; x < tmx->width; x++) {
			for (y = 0u; y < tmx->height; y++) {
				tile_index = y * tmx->width + x;
				layer_data.at(i)[tile_index] = tmx->data[tile_index + i * LEVEL_SIZE];
			}
		}
	}
}

/**
 * Draws the tile map to the screen if a TileMap is loaded in the memory
 * @param camera_position The position of the camera on the TileMap
 */
void map::draw(Point camera_position) {
	uint16_t tile, x, y;
	Point camera_position_world = screen_to_world(camera_position);

	if (tmx == nullptr) return; //Prevent rendering when TileMap is not loaded

	//TODO optimize by removing loops: Maybe use layer_data instead of loop for x & y or recursion or calc x and y from layer data
	//TODO in best case this becomes a single for loop
	//TODO optimizations here require flag handler rework
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
