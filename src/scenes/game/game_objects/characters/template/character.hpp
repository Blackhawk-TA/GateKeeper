//
// Created by daniel on 25.10.21.
//

#pragma once
#include "../../../../../utils/utils.hpp"
#include "../../../../../engine/map.hpp"
#include "../../../../../engine/ui/textbox.hpp"
#include "../../template/game_object.hpp"

class Character : public GameObject {
public:
	enum MovementDirection {
		NO_DIRECTION = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};

	Character(map::MapSections map_section, Point position, bool player_usable, bool inventory_usable, bool turn = false);
	void draw() override;
	void update(uint32_t time) override;
	bool player_interact() override;
	GameObject::ObjectType get_type() override;
	void animate();

protected:
	static constexpr uint8_t ANIMATION_SPRITE_COUNT = 4;
	static constexpr uint8_t DIRECTION_COUNT = 4;
	static constexpr uint16_t ANIMATION_BASE_DELAY = 2500;
	static constexpr uint16_t ANIMATION_VARIANCE = 2000;

	bool turn;
	bool in_action;
	bool is_moving;
	uint8_t tile_index;
	uint32_t last_turn;
	uint32_t animation_delay;
	Point screen_position;
	std::map<MovementDirection, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> movement_sprites;
	MovementDirection current_direction;
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites;

	virtual void trigger_cut_scene();
	bool player_in_sightline();
	void walk_to_player();
	void change_direction(MovementDirection direction, bool animate = true);
};
