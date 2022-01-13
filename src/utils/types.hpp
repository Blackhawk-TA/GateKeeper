//
// Created by daniel on 30.12.21.
//

#pragma once
#include <array>
#include "utils.hpp"
#include "../engine/map.hpp"
#include "movement_direction.hpp"

/**
 * A struct consisting of the map_section and position of a game object to create a unique signature.
 */
struct Signature {
	uint8_t map_section = 0; //The map section on which the game object exists
	uint8_t x = 0; //The x position of the game object
	uint8_t y = 0; //The y position of the game object
};

//Data from the game scene that is needed for fights in combat scene
struct CharacterData {
	Signature signature{};
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
	Signature enemy_signature{};
	uint8_t health = 0;
	bool won = false;
};

//The parameters that can be set for loading a save game
struct SaveOptions {
	bool tmp_save = false;
	GameData game_data;
};

//Data that is required for load a player from a save
struct PlayerTempData {
	map::MapSection map_section;
	MovementDirection direction;
	Point camera_position;
	uint8_t health;
	Signature enemy_signature{};
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

//Attack types for the combat scene
enum AttackType {
	NO_ATTACK = 0,
	MELEE = 1,
	SPEAR = 2,
	ARROW = 3,
	DAGGER = 4,
	FIRE = 5,
	ICE = 6,
	ELECTRIC = 7,
	MAGIC = 8,
};

//The stats of an attack in the combat scene
struct AttackStats {
	uint8_t stamina;
	uint8_t base_damage;
	uint8_t bonus_damage;
};
