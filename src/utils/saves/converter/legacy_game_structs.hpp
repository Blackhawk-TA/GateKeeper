//
// Created by daniel on 16.04.22.
//

#pragma once
#include "../../utils.hpp"
#include "../../../engine/map.hpp"
#include "../../../scenes/game/game_objects/template/game_object.hpp"
#include "../save_types.hpp"

namespace save_converter {
	struct SaveDataV0 {
		uint8_t version;
		map::MapSection map_section;
		Point camera_position;
		Point previous_camera_position;
		save::PlayerData player_data;
		std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects; //TODO this causes save warning
		std::array<std::array<save::Item, MAX_ITEMS>, save::MAX_INVENTORIES> items;
		uint32_t passed_time;
	};
}
