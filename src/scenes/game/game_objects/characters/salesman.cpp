//
// Created by daniel on 24.11.21.
//

#include "salesman.hpp"

Salesman::Salesman(map::MapSections map_section, Point position) : Character(map_section, position, true, false) {
	tile_id = TILE_ID;
}

void Salesman::update_state(Point next_position) {

}

GameObject::ObjectType Salesman::get_type() {
	return SalesmanType;
}

void Salesman::set_state(uint8_t new_state) {

}

void Salesman::update(uint32_t time) {

}
