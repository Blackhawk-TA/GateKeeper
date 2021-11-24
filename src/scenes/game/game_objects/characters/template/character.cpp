//
// Created by daniel on 01.11.21.
//
#include "character.hpp"

Character::Character(map::MapSections map_section, Point position, bool player_usable, bool inventory_usable)
	: GameObject(map_section, position, player_usable, inventory_usable) {
	size = Size(1, 1);
}
