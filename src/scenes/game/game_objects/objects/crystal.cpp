//
// Created by daniel on 20.02.22.
//

#include "crystal.hpp"
#include "../../../../engine/camera.hpp"
#include "../../ui/sidemenu.hpp"

namespace game {
	Crystal::Crystal(map::MapSection map_section, Point position, CrystalType type) : GameObject(map_section, position, true, false) {
		Crystal::type = type;
		size = Size(1, 2);
		tile_id = 555;

		switch (type) {
			case PURPLE:
				tile_id_crystal = 44;
				break;
			case YELLOW:
				tile_id_crystal = 45;
				break;
			case BLUE:
				tile_id_crystal = 46;
				break;
			case RED:
				tile_id_crystal = 47;
				break;
		}
	}

	void Crystal::draw() {
		GameObject::draw();
		if (!player_usable) return;

		screen.blit(
			screen.sprites,
			Rect(
				(tile_id_crystal & (spritesheet_size.w - 1)) * TILE_SIZE,
				(tile_id_crystal / spritesheet_size.h) * TILE_SIZE,
				TILE_SIZE,
				TILE_SIZE
			),
			world_to_screen(position) - camera::get_screen_position()
		);
	}

	bool Crystal::player_interact() {
		if (player_usable && player_in_front()) {
			set_player_usable(false);
			textbox = new Textbox("You picked up crystal and put it to your gear.");

			switch (type) {
				case PURPLE:
					sidemenu::add_item(sidemenu::GEAR, items::create_gear_item(GEAR_MAGIC));
					break;
				case YELLOW:
					sidemenu::add_item(sidemenu::GEAR, items::create_gear_item(GEAR_SHOCK));
					break;
				case BLUE:
					sidemenu::add_item(sidemenu::GEAR, items::create_gear_item(GEAR_ICE));
					break;
				case RED:
					sidemenu::add_item(sidemenu::GEAR, items::create_gear_item(GEAR_FIRE));
					break;
			}

			return true;
		}
		return  false;
	}


	GameObject::ObjectType Crystal::get_type() {
		return GameObject::CrystalType;
	}

	void Crystal::update_state(Point next_position) {}
	void Crystal::update(uint32_t time) {}
	void Crystal::set_state(uint8_t new_state) {}
}
