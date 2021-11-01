//
// Created by D069765 on 26.10.2021.
//

#pragma once
#include "game_object_interface.hpp"
#include "../engine/map.hpp"

class GateStatue : public IGameObject {
private:
	enum RenderStates {
		DEPLETED = 1,
		INACTIVE = 2,
		ACTIVE = 3
	};

	const Size STATUE_SIZE = Size(1, 3);
	const uint16_t TILE_ID_EMPTY = 2046;
	const uint16_t TILE_ID_INACTIVE = 364;
	const uint16_t TILE_ID_ACTIVE = 2047;

	Signature signature;
	Point position;
	map::MapSections map_section;
	bool usable;
	Size spritesheet_size;
	RenderStates state;
	uint16_t tile_id;

	void set_state(uint8_t new_state) override;
	void set_usable(bool value) override;

public:
	explicit GateStatue(map::MapSections map_section, Point position, bool usable);
	~GateStatue() override = default;
	Signature get_signature() override;
	Save get_save() override;
	void load_save(bool value) override;
	bool check_collision(Point next_position) override;
	void draw() override;
	bool interact() override;
	void update_state(Point next_position) override;
};
