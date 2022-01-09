//
// Created by daniel on 09.01.22.
//

#pragma once
#include "../utils.hpp"
#include "../movement_direction.hpp"
#include "../../scenes/game/game_objects/template/game_object.hpp"

/*
 * Important: If any of those structs is changed the save version in savegame.hpp must be updated.
 *            The old save struct has to be ported to the new format
 */
//TODO move all save structs to this file
namespace save {
	struct PlayerData {
		uint8_t health = 100;
		uint8_t level = 1;
		MovementDirection direction = DOWN;
		bool sword = true;
		bool spear = true;
		bool arrow = true;
		bool dagger = false;
		bool magic = false;
	};

	struct Item {
		uint8_t type;
		uint8_t amount;
	};

	struct SaveData {
		uint8_t version;
		map::MapSection map_section;
		Point camera_position;
		Point previous_camera_position;
		PlayerData player_data;
		std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects; //TODO this causes save warning
		std::array<Item, MAX_ITEMS> items;
		uint32_t passed_time;
	};
}