//
// Created by daniel on 24.11.21.
//

#include "villager.hpp"

Villager::Villager(map::MapSections map_section, Point position) : Character(map_section, position, true, false) {
	tile_id = TILE_ID;
	movement_sprites = {
		{UP, {48, 49, 50, 51}},
		{DOWN, {0, 1, 2, 3}},
		{LEFT, {16, 17, 18, 19}},
		{RIGHT, {32, 33, 34, 35}}
	};
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

void Villager::update_state(Point next_position) {}
void Villager::update(uint32_t time) {}
void Villager::set_state(uint8_t new_state) {}
