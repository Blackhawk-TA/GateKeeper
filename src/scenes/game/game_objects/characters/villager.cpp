//
// Created by daniel on 24.11.21.
//

#include "villager.hpp"
#include <utility>

Villager::Villager(map::MapSections map_section, Point position, uint16_t tile_id, MovementDirection direction, std::string message) : Character(map_section, position, true, false) {
	Villager::message = std::move(message);
	last_turn = blit::now();
	movement_sprites = {
		{UP,{
			static_cast<uint16_t>(tile_id + 48),
			static_cast<uint16_t>(tile_id + 49),
			static_cast<uint16_t>(tile_id + 50),
			static_cast<uint16_t>(tile_id + 51)
		}},
		{DOWN, {
			tile_id,
			static_cast<uint16_t>(tile_id + 1),
			static_cast<uint16_t>(tile_id + 2),
			static_cast<uint16_t>(tile_id + 3)
		}},
		{LEFT, {
			static_cast<uint16_t>(tile_id + 16),
			static_cast<uint16_t>(tile_id + 17),
			static_cast<uint16_t>(tile_id + 18),
			static_cast<uint16_t>(tile_id + 19)
		}},
		{RIGHT, {
			static_cast<uint16_t>(tile_id + 32),
			static_cast<uint16_t>(tile_id + 33),
			static_cast<uint16_t>(tile_id + 34),
			static_cast<uint16_t>(tile_id + 35)
		}},
	};

	change_direction(direction, false);
}

bool Villager::player_interact() {
	bool interacted = Character::player_interact();

	if (interacted) {
		textbox = new Textbox(message);
		return true;
	}

	return false;
}

GameObject::ObjectType Villager::get_type() {
	return GameObject::VillagerType;
}

void Villager::update(uint32_t time) {
	if (!is_textbox_open() && time > ANIMATION_DELAY && last_turn < time - ANIMATION_DELAY) {
		uint8_t next_direction = blit::random() % DIRECTION_COUNT + 1;
		change_direction(static_cast<MovementDirection>(next_direction), false);
		last_turn = time;
	}
}

//Prevent player from looking away directly after closing textbox
void Villager::close_textbox() {
	GameObject::close_textbox();
	last_turn = blit::now();
}

void Villager::set_state(uint8_t new_state) {}
void Villager::update_state(Point next_position) {}
