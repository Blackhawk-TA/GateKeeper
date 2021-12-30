//
// Created by daniel on 30.12.21.
//

#pragma once
#include <array>
#include "utils.hpp"
#include "../engine/map.hpp"

struct CharacterData {
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> movement_sprites{};
	uint8_t health = 100;
	uint8_t level = 1;
	bool sword = false;
	bool magic_powers = false; //TODO implement
};

struct CombatData {
	map::MapSection map_section{};
	CharacterData player;
	CharacterData enemy;
};

struct SceneOptions {
	uint8_t save_id = 0;
	CombatData combat_data = {};
	bool previous_player_position = false;
};

enum StargateAddress {
	GRASSLAND = 0,
	GRASSLAND_ENDGAME = 1,
	WINTER = 2,
	DESERT = 3
};
