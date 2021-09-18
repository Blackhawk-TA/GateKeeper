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
	Point screen_tiles;
	uint16_t tile_id;
	const Point gate_size = Point(3, 3); //Gate sprite consists of 3x3 16 bit sprites
	const uint16_t animation_id = 939;
	const Point animation_size = Point(3, 2);
	uint16_t get_tile_id(RenderStates current_state);

public:
	explicit Stargate(Point position, bool broken);
	void draw();
	void set_state(RenderStates new_state);
};
