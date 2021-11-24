//
// Created by daniel on 24.11.21.
//

#pragma once
#include "template/character.hpp"

class Salesman : public Character {
private:
	const uint16_t TILE_ID = 0;

public:
	explicit Salesman(map::MapSections map_section, Point position);
	~Salesman() override = default;
};
