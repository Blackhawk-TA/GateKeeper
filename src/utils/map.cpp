//
// Created by daniel on 28.02.21.
//

#include "assets.hpp"
#include "map.hpp"

using namespace blit;

namespace map {
	constexpr uint8_t layer_count = 3;

	std::array<std::vector<uint8_t>, TileFlags::COUNTER> flags;
	std::array<std::array<uint16_t, LEVEL_SIZE>, layer_count> layer_data;
	TMX *tmx;

	void create() {
		tmx = (TMX *) asset_map;
		uint16_t x, y, tile_index;

		if (tmx->width > LEVEL_WIDTH) return;
		if (tmx->height > LEVEL_HEIGHT) return;

		for (auto i = 0u; i < tmx->layers; i++) {
			for (x = 0u; x < tmx->width; x++) {
				for (y = 0u; y < tmx->height; y++) {
					tile_index = y * tmx->width + x;
					layer_data[i][tile_index] = tmx->data[tile_index + i * LEVEL_SIZE];
				}
			}
		}
	}

	void draw(Vec2 &offset) {
		uint16_t tile, x, y;

		for (auto & layer : layer_data) {
			for (x = 0; x < tmx->height ; x++) {
				for (y = 0; y < tmx->width; y++) {
					//Checks if tile is visible in screen
					if (SCREEN_TILES.x + offset.x - x >= 0 && x <= SCREEN_TILES.x + offset.x
					&& SCREEN_TILES.y + offset.y - y >= 0 && y <= SCREEN_TILES.y + offset.y)
					{
						tile = layer[y * tmx->width + x];
						if (tile != tmx->empty_tile) { //Do not draw empty tiles
							screen.blit_sprite(
								Rect((tile % SPRITE_SHEET_SIZE.x) * TILE_SIZE, (tile / SPRITE_SHEET_SIZE.y) * TILE_SIZE, TILE_SIZE, TILE_SIZE),
								world_to_screen(x - offset.x, y - offset.y),
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
		uint8_t i = layer_count;
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
		uint8_t i = layer_count;
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

	void set_flags(TileFlags flag, const std::vector<uint8_t> &tiles) {
		flags[flag] = tiles;
	}
}
