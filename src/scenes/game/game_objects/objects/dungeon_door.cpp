//
// Created by daniel on 19.12.21.
//

#include "dungeon_door.hpp"
#include "../../../../engine/camera.hpp"
#include "../player.hpp"

namespace game {
	DungeonDoor::DungeonDoor(map::MapSection map_section, Point position) : GameObject(map_section, position, true, false, false) {
		tile_id = TILE_ID_CLOSED;
		size = Size(2, 2);
		DungeonDoor::set_state(CLOSED);
	}

	bool DungeonDoor::player_interact() {
		if (GameObject::player_usable && state == CLOSED && Player::get_direction() == MovementDirection::UP
		&& (camera::get_player_position() == position + Point(0, size.h) || camera::get_player_position() == position + Point(size.w - 1, size.h))) {
			textbox = new Textbox("The door is closed.");
			return true;
		}

		return false;
	}

	GameObject::ObjectType DungeonDoor::get_type() {
		return GameObject::DungeonDoorType;
	}

	void DungeonDoor::set_state(uint8_t new_state) {
		auto new_state_enum = static_cast<State>(new_state);

		switch (new_state_enum) {
			case OPEN:
				tile_id = TILE_ID_OPEN;
				break;
			case CLOSED:
				tile_id = TILE_ID_CLOSED;
				break;
		}

		state = new_state_enum;
	}

	bool DungeonDoor::check_collision(Point next_position) {
		if (state == OPEN) {
			return false;
		} else {
			return GameObject::check_collision(next_position);
		}
	}

	bool DungeonDoor::open() {
		if (state == CLOSED) {
			set_state(OPEN);
			return true;
		}

		return false;
	}
}
