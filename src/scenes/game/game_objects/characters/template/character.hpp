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
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};

	Character(map::MapSections map_section, Point position, bool player_usable, bool inventory_usable);
	virtual void animate();
	void draw() override;
	bool player_interact() override;
	GameObject::ObjectType get_type() override;

protected:
	static constexpr uint8_t ANIMATION_SPRITE_COUNT = 4;
	static constexpr uint8_t DIRECTION_COUNT = 4;
	static constexpr uint16_t ANIMATION_BASE_DELAY = 2500;
	static constexpr uint16_t ANIMATION_VARIANCE = 2000;

	bool in_action;
	bool is_moving;
	uint8_t tile_index;
	Point screen_position;
	std::map<MovementDirection, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> movement_sprites;
	MovementDirection current_direction;
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites;

	void change_direction(MovementDirection direction, bool animate = true);
};
