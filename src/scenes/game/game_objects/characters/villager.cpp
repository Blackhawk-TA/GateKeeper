//
// Created by daniel on 24.11.21.
//

#include "villager.hpp"

Villager::Villager(map::MapSections map_section, Point position) : Character(map_section, position, true, false) {
	tile_id = TILE_ID;
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
