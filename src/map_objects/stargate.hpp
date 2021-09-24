//
// Created by daniel on 17.09.21.
//

#pragma once
#include "../utils/utils.hpp"
#include "../engine/map.hpp"

class Stargate {
private:
	enum RenderStates {
		BROKEN = 1,
		INACTIVE = 2,
		ACTIVATING = 3,
		ACTIVE = 4,
		DEACTIVATING = 5
	};

	const Size GATE_SIZE = Size(3, 3); //Gate sprite consists of 3x3 16 bit sprites
	const uint16_t tile_id_broken = 1763;
	const uint16_t tile_id_inactive = 683;
	const uint16_t tile_id_active = 872;
	const uint16_t ANIMATION_ID = 939;
	const uint8_t ANIMATION_DURATION = 125;
	const Size ANIMATION_SIZE = Size(3, 2); //Animation consists of 3x2 16 bit sprites
	const Point RELATIVE_ACTIVATION_POINT = Point(1, 3); //Position at which the gate animation is triggered
	const Point RELATIVE_PRE_ENTRY_POINT = Point(1, 2); //Position right in front of the gate
	const Point RELATIVE_ENTRY_POINT = Point(1, 1); //Position in center of the portal where teleportation triggers
	const Point ANIMATION_OFFSET = Point(GATE_SIZE.w - ANIMATION_SIZE.w, GATE_SIZE.h - ANIMATION_SIZE.h);

	RenderStates state;
	map::MapSections map_section;
	Point position;
	StargateAddresses destination;
	Size spritesheet_size;
	uint32_t activation_start_time;
	uint16_t tile_id;
	bool broken;

	void set_state(RenderStates new_state);

public:
	explicit Stargate(map::MapSections map_section, StargateAddresses destination, Point position, bool broken);
	bool check_collision(Point next_position) const;
	void update_state(Point next_position);
	bool check_enter(Point next_position);
	void draw();
	void update_animation();
	bool repair();
	Point get_entry_point();
	StargateAddresses get_destination();
	map::MapSections get_map_section();
};
