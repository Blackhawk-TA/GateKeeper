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
	Character(map::MapSections map_section, Point position, bool player_usable, bool inventory_usable);
	void draw() override;
	bool player_interact() override;
};
