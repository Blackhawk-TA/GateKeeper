//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include <stdexcept>
#include <iostream>
#include "assets.hpp"
#include "map.hpp"

using namespace blit;

namespace map {
	std::array<std::vector<uint16_t>, TileFlags::COUNTER> flags;
	std::array<std::array<uint16_t, LEVEL_SIZE>, LAYER_COUNT> layer_data;
//	std::unique_ptr<TMX_16> tmx;
	TMX_16* tmx = new TMX_16;
	Point screen_tiles;
	Point sprite_sheet_size;

	void load(MapTypes map_type) {
		//TODO delete tmx, sprites and layer_data, flags
		delete screen.sprites;
//		tmx.reset();
		if (tmx != nullptr) {
//			free(tmx);
//			delete &tmx;
		}


		//TODO dont delete flag array, rather store it in class for each map type
		for (auto &flag : flags) {
			std::destroy(flag.begin(), flag.end());
		}

		switch (map_type) {
			case MapTypes::DUNGEON:
				tmx = nullptr;
				break;
			case MapTypes::EXTERIOR:
				screen.sprites = Surface::load(asset_exterior);
//				tmx = (TMX_16 *) malloc(asset_exterior_map_length);
//				if (tmx == nullptr) return;
//				memset(tmx, 0, asset_exterior_map_length);
				tmx = (TMX_16 *) asset_exterior_map;

//				tmx = std::unique_ptr<TMX_16>((TMX_16*) asset_exterior_map);
				break;
			case MapTypes::INTERIOR:
				tmx = nullptr;
				break;
			case MapTypes::WINTER:
				screen.sprites = Surface::load(asset_winter);
				tmx = (TMX_16 *) malloc(asset_winter_map_length);
//				if (tmx == nullptr) return;
				memset(tmx, 0, asset_winter_map_length);
				tmx = (TMX_16 *) asset_winter_map;

//				tmx = std::unique_ptr<TMX_16>((TMX_16*) asset_winter_map);
				break;
		}

		if (tmx == nullptr) return;
		if (tmx->width > LEVEL_WIDTH) return;
		if (tmx->height > LEVEL_HEIGHT) return;

		uint16_t x, y, tile_index;
		screen_tiles = get_screen_tiles();
		sprite_sheet_size = get_sprite_sheet_size();

		for (auto i = 0u; i < tmx->layers; i++) {
			for (x = 0u; x < tmx->width; x++) {
				for (y = 0u; y < tmx->height; y++) {
					tile_index = y * tmx->width + x;
					layer_data[i][tile_index] = tmx->data[tile_index + i * LEVEL_SIZE];
				}
			}
		}
	}

	void draw(Point camera_position) {
		uint16_t tile, x, y;
		Point camera_position_world = screen_to_world(camera_position);

		if (tmx == nullptr) return; //Prevent rendering while switching map

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

	///////////////////////////////////////////////////////////////////////////
	//
	// Gets the id of a tile at a specific Point on the map.
	// Always selects the tile on the highest layer if several tiles overlap.
	//
	uint16_t tile_at(Point &p) {
		uint8_t i = LAYER_COUNT;
		uint16_t tile = 0;

		while (i >= 0 && tile == 0) {
			tile = layer_data[i][p.y * tmx->width + p.x];
			i--;
		}

		return tile;
	}

	///////////////////////////////////////////////////////////////////////////
	//
	// Gets the flag of the given sprite on its highest layer, ignoring all underlying flags
	//
	uint8_t get_flag(Point p) {
		uint8_t i = LAYER_COUNT;
		uint8_t j, k;
		uint8_t flag_enum_id = 0;
		uint16_t tile_id;
		bool flag_found = false;

		while (!flag_found && i > 0) {
			i--;
			j = 0;
			tile_id = tile_at(p);

			while (!flag_found && j < flags.size() - 1) {
				j++;
				k = 0;
				while (!flag_found && k < flags[j].size()) {
					if (tile_id == flags[j].at(k)) {
						flag_enum_id = j;
						flag_found = true;
					}
					k++;
				}
			}
		}

		return flag_enum_id;
	}

	void set_flags(TileFlags flag, const std::vector<uint16_t> &tiles) {
		flags[flag] = tiles;
	}
}
