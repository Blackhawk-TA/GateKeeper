//
// Created by daniel on 30.12.21.
//

#pragma once
#include <array>
#include "utils.hpp"
#include "../engine/map.hpp"

struct CharacterData {
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> movement_sprites;
	uint8_t health;
	uint8_t level;
};

struct CombatData {
	map::MapSection map_section;
	CharacterData player;
	CharacterData enemy;
};

enum StargateAddress {
	GRASSLAND = 0,
	GRASSLAND_ENDGAME = 1,
	WINTER = 2,
	DESERT = 3
};
