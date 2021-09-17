//
// Created by daniel on 17.09.21.
//

#pragma once
#include "../utils/utils.hpp"

class Stargate {
private:
	enum RenderStates {
		BROKEN = 1,
		INACTIVE = 2,
		ACTIVE = 3
	};

	RenderStates state;
	Point position;
	Point sprite_sheet_size;
	uint16_t tile_id;
	const uint8_t tile_size = 48; //Gate sprite consists of 3x3 16 bit sprites
	const uint16_t animation_id = 939;

public:
	explicit Stargate(Point position, bool broken);
	void draw();
	uint16_t get_tile_id(RenderStates new_state);
};
