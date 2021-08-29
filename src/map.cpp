//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include "assets.hpp"
#include "map.hpp"

using namespace blit;

namespace map {
	std::array<std::vector<uint16_t>, TileFlags::COUNTER> flags;
	std::vector<std::array<uint16_t, LEVEL_SIZE>> layer_data;
	TMX_16* tmx;
	Point screen_tiles;
	Point sprite_sheet_size;
	uint8_t current_layer_count;

	/**
	 * Loads new map section into memory and deletes the old one
	 *
	 * @param map_section The enum describing the map section
	 */
	void load_section(MapSections map_section) {
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
				memcpy(tmx, asset_exterior_map, asset_exterior_map_length);

				current_layer_count = EXTERIOR_LAYER_COUNT;
				break;
			case MapSections::INTERIOR:
				tmx = nullptr;
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

		for (auto i = 0u; i < tmx->layers; i++) {
			layer_data.push_back({}); // Create new empty layer to fill it later on

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
	 *
	 * @param camera_position The position of the camera on the TileMap
	 */
	void draw(Point camera_position) {
		uint16_t tile, x, y;
		Point camera_position_world = screen_to_world(camera_position);

		if (tmx == nullptr) return; //Prevent rendering when TileMap is not loaded

		for (auto & layer : layer_data) {
			for (x = 0; x < tmx->height ; x++) {
				for (y = 0; y < tmx->width; y++) {
					//Checks if tile is visible on screen
					if (screen_tiles.x + camera_position_world.x - x >= 0 && camera_position_world.x <= x
					&& screen_tiles.y + camera_position_world.y - y >= 0 && camera_position_world.y <= y)
					{
						tile = layer[y * tmx->width + x];
						if (tile != tmx->empty_tile) { //Do not draw empty tiles
							screen.blit_sprite(
								Rect((tile % sprite_sheet_size.x) * TILE_SIZE, (tile / sprite_sheet_size.y) * TILE_SIZE, TILE_SIZE, TILE_SIZE),
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
	 *
	 * @param p The point at which the tile is located
	 * @return The id of the tile mapped to the sprite sheet
	 */
	uint16_t tile_at(Point &p) {
		uint8_t i = current_layer_count;
		uint16_t tile = 0;

		while (i >= 0 && tile == 0) {
			i--;
			tile = layer_data[i][p.y * tmx->width + p.x];
		}

		return tile;
	}

	/**
	 * Gets the flag of the given sprite on its highest layer, ignoring all underlying flags
	 *
	 * @param p The point at which the flag is located
	 * @return The TileFlags enum id of the found flag
	 */
	uint8_t get_flag(Point p) {
		uint8_t i = current_layer_count;
		uint8_t j, k;
		uint8_t flag_enum_id = 0;
		uint16_t tile_id;
		bool flag_found = false;

		while (!flag_found && i > 0) {
			i--;
			j = 0;
			tile_id = map::tile_at(p);

			while (!flag_found && j < flags.size() - 1) {
				k = 0;
				while (!flag_found && k < flags[j].size()) {
					if (tile_id == flags[j].at(k)) {
						flag_enum_id = j + 1; //Add 1 because flag index starts at 1
						flag_found = true;
					}
					k++;
				}
				j++;
			}
		}

		return flag_enum_id;
	}

	void set_flags(TileFlags flag, const std::vector<uint16_t> &tiles) {
		flags[flag - 1] = tiles;
	}
}