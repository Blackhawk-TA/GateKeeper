//
// Created by daniel on 28.02.21.
//

#pragma once
#include "utils.hpp"

using namespace blit;

namespace map {
	enum TileFlags {
		SOLID = 1,
		COUNTER = 2
	};

	enum MapTypes {
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

	void load(MapTypes map_type);
	void draw(Point camera_position);
	uint16_t tile_at(Point &p);
	void set_flags(TileFlags flag, const std::vector<uint16_t> &tiles);
	uint8_t get_flag(Point p);
}
