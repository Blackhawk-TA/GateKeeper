//
// Created by daniel on 24.11.21.
//

#include "villager.hpp"

Villager::Villager(map::MapSections map_section, Point position) : Character(map_section, position, true, false) {
	last_turn = blit::now();
	movement_sprites = {
		{UP, {48, 49, 50, 51}},
		{DOWN, {0, 1, 2, 3}},
		{LEFT, {16, 17, 18, 19}},
		{RIGHT, {32, 33, 34, 35}}
	};

	change_direction(DOWN, false);
}

bool Villager::player_interact() {
	bool interacted = Character::player_interact();

	if (interacted) {
		textbox = new Textbox("Hello");
		return true;
	}

	return false;
}

GameObject::ObjectType Villager::get_type() {
	return GameObject::VillagerType;
}

void Villager::update(uint32_t time) {
	if (!is_textbox_open() && last_turn < time - 2500) {
		uint8_t next_direction = blit::random() % DIRECTION_COUNT + 1;
		change_direction(static_cast<MovementDirection>(next_direction), false);
		last_turn = time;
	}
}

void Villager::set_state(uint8_t new_state) {}
void Villager::update_state(Point next_position) {}
