//
// Created by daniel on 28.02.21.
//

#pragma once

#include <list>
#include "../utils/utils.hpp"

using namespace blit;

namespace map {
	enum MapSections {
		DUNGEON = 1,
		GRASSLAND = 2,
		INTERIOR = 3,
		WINTER = 4
	};

	//Stores information of a tile and how often it appears in repetition
	struct Tile {
		uint8_t x;
		uint8_t y;
		uint16_t id;
		uint16_t range;
		uint16_t sprite_rect_x;
		uint16_t sprite_rect_y;
	};

	#pragma pack(push,1)
	struct TMX_16 {
		char head[4];
		uint16_t header_length;
		uint16_t flags;
		uint16_t empty_tile;
		uint16_t width;
		uint16_t height;
		uint16_t layers;
		uint16_t data[];
	};
	#pragma pack(pop)

	void load_section(MapSections map_section);
	void draw(Point camera_position);
	uint16_t tile_at(Point &p);
	MapSections get_section();
	uint8_t get_layer_count();
}
