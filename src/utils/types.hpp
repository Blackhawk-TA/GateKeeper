//
// Created by daniel on 30.12.21.
//

#pragma once
#include <array>
#include "utils.hpp"
#include "../engine/map.hpp"
#include "movement_direction.hpp"

//Data from the game scene that is needed for fights in combat scene
struct CharacterData {
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> movement_sprites{};
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> attack_sprites{};
	uint8_t health = 100;
	uint8_t level = 1;
	bool sword = false;
	bool magic_powers = false; //TODO implement
};

//Data that is handed over from the game to the combat scene
struct CombatData {
	map::MapSection map_section{};
	CharacterData player;
	CharacterData enemy;
};

//Data that is handed over from the combat to the game scene
struct GameData {
	uint8_t health = 0;
	bool won = false;
};

//The parameters that can be set for loading a save game
struct SaveOptions {
	bool tmp_save = false;
	GameData game_data;
};

//Data that is required for load a player from a save
struct PlayerData {
	map::MapSection map_section;
	MovementDirection direction;
	Point camera_position;
	uint8_t health;
};


struct SceneOptions {
	uint8_t save_id = 0;
	CombatData combat_data = {};
	GameData game_data = {};
	bool tmp_save = false;
};

enum StargateAddress {
	GRASSLAND = 0,
	GRASSLAND_ENDGAME = 1,
	WINTER = 2,
	DESERT = 3
};
