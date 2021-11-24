//
// Created by daniel on 06.11.21.
//

#pragma once

#include "../template/game_object.hpp"

class Sign : public GameObject {
public:
	enum SpriteType {
		STONE = 1,
		WOOD = 2,
	};

	explicit Sign(map::MapSections map_section, Point position, Sign::SpriteType sprite_type, std::string text);
	~Sign() override = default;
	bool player_interact() override;
	void update_state(Point next_position) override;
	ObjectType get_type() override;
	void update(uint32_t time) override;

private:
	std::string text;

	void set_sprite(SpriteType sprite_type);
	void set_state(uint8_t new_state) override;
};
