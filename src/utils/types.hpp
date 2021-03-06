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

enum StargateAddress {
	GRASSLAND = 0,
	GRASSLAND_ENDGAME = 1,
	WINTER = 2,
	DESERT = 3
};

enum CombatCharacterType {
	NO_TYPE = 0,
	PLAYER = 1,
	BLUE_GUARD = 2,
	SPIDER = 3,
	BROWN_BEAR = 4,
	ICE_BEAR = 5,
	DEVIL = 6,
	RED_CREATURE = 7,
	RED_GUARD = 8,
};

enum GEAR_TYPE {
	GEAR_NONE = 0,
	GEAR_SWORD = 1,
	GEAR_SPEAR = 2,
	GEAR_ARROW = 3,
	GEAR_DAGGER = 4,
	GEAR_MAGIC = 5,
	GEAR_FIRE = 6,
	GEAR_ICE = 7,
	GEAR_SHOCK = 8,
	GEAR_NAVIGATE_BACK = 9,
};

struct CharacterStats {
	float damage_multiplier;
	std::vector<GEAR_TYPE> attacks;
};

//Data from the game scene that is needed for fights in combat scene
struct CharacterData {
	Signature signature{};
	CharacterStats stats;
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> movement_sprites{};
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> attack_sprites{};
	uint8_t health = 100;
	uint8_t max_health = 100;
	uint8_t level = 1;
	CombatCharacterType character_type{};
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
	bool won_fight = false;
	bool respawn = false;
};

//Shows if the gear of a player was stripped after the first player death
enum StoryState {
	START = 1, //The first part of the game were the player starts with default weapons
	FIRST_DEATH = 2, //Symbolises that the players gear must be removed on first death
	FIRST_HOSPITAL_WAKEUP = 3, //The player died the first time and woke up at the hospital
	GATE_PART_SEARCH = 4, //The player is visiting dungeons to get the gate part
	COMPLETED = 5, //The end boss was beaten, the game is finished
};

//Data that is required for load a player from a save
struct PlayerTempData {
	map::MapSection map_section;
	MovementDirection direction;
	Point camera_position;
	Point camera_previous_position;
	uint8_t health;
	StoryState story_state;
	Signature enemy_signature{};
};

struct SceneOptions {
	uint8_t save_id = 0;
	CombatData combat_data = {};
	GameData game_data = {};
};

//The stats of an attack in the combat scene
struct AttackStats {
	uint8_t stamina;
	uint8_t base_damage;
	uint8_t bonus_damage;
};
