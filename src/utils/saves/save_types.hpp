//
// Created by daniel on 09.01.22.
//

#pragma once
#include "../utils.hpp"
#include "../movement_direction.hpp"
#include "../../scenes/game/game_objects/template/game_object.hpp"
#include "../types.hpp"

/*
 * Important: If any of those structs is changed the save version in savegame.hpp must be updated.
 *            The old save struct has to be ported to the new format
 */
//TODO move all save structs to this file
namespace save {
	constexpr uint8_t MAX_INVENTORIES = 2;

	struct PlayerData {
		uint8_t health;
		uint8_t level;
		uint32_t xp;
		uint32_t gained_xp;
		uint16_t gold;
		MovementDirection direction;
		StoryState story_state;
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
		std::array<std::array<Item, MAX_ITEMS>, MAX_INVENTORIES> items;
		uint32_t passed_time;
	};

	struct OptionsData {
		uint8_t save_count;
		bool show_fps;
		bool show_time;
	};
}