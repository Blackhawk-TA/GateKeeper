//
// Created by daniel on 17.09.21.
//

#pragma once
#include "../utils/utils.hpp"
#include "../engine/map.hpp"
#include "../handlers/stargate_handler.hpp"

class Stargate {
private:
	enum RenderStates {
		BROKEN = 1,
		INACTIVE = 2,
		ACTIVATING = 3,
		ACTIVE = 4,
		DEACTIVATING = 5
	};

	const Point GATE_SIZE = Point(3, 3); //Gate sprite consists of 3x3 16 bit sprites
	const uint16_t tile_id_broken = 1763;
	const uint16_t tile_id_inactive = 683;
	const uint16_t tile_id_active = 872;
	const uint16_t ANIMATION_ID = 939;
	const uint8_t ANIMATION_DURATION = 125;
	const Point ANIMATION_SIZE = Point(3, 2);
	const Point RELATIVE_ACTIVATION_POINT = Point(1, 3); //Position at which the gate animation is triggered
	const Point RELATIVE_PRE_ENTRY_POINT = Point(1, 2); //Position right in front of the gate
	const Point RELATIVE_ENTRY_POINT = Point(1, 1); //Position in center of the portal where teleportation triggers

	RenderStates state;
	map::MapSections map_section;
	Point position;
	stargate_handler::Stargates destination;
	Point sprite_sheet_size;
	Point screen_tiles;
	uint32_t activation_start_time;
	uint16_t tile_id;

	void set_state(RenderStates new_state);

public:
	explicit Stargate(map::MapSections map_section, stargate_handler::Stargates position, Point destination, bool broken);
	bool check_collision(Point next_position) const;
	void update_state(Point next_position);
	bool check_enter(Point next_position);
	void draw();
	void update_animation();
	void repair();
	Point get_entry_point();
	stargate_handler::Stargates get_destination();
	map::MapSections get_map_section();
};
