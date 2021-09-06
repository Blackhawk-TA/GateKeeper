//
// Created by daniel on 28.02.21.
//

#pragma once
#include "utils/utils.hpp"

using namespace blit;

namespace map {
	const uint8_t DUNGEON_LAYER_COUNT = 0;
	const uint8_t EXTERIOR_LAYER_COUNT = 3;
	const uint8_t INTERIOR_LAYER_COUNT = 3;
	const uint8_t WINTER_LAYER_COUNT = 2;

	enum MapSections {
		DUNGEON = 1,
		EXTERIOR = 2,
		INTERIOR = 3,
		WINTER = 4
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
