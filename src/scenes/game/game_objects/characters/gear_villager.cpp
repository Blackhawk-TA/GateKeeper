//
// Created by daniel on 26.02.22.
//

#include "gear_villager.hpp"
#include "../../ui/sidemenu.hpp"

namespace game {
	GearVillager::GearVillager(map::MapSection map_section, Point position, uint16_t tile_id,
		MovementDirection direction, std::string message, std::string alt_message, GEAR_TYPE gear_type)
		: Character(map_section, position, true, false, true) {
		GearVillager::tile_id = tile_id;
		GearVillager::message = std::move(message);
		GearVillager::alt_message = std::move(alt_message);
		GearVillager::gear_type = gear_type;
		set_movement_sprites();
		change_direction(direction, false);
	}

	bool GearVillager::player_interact() {
		if (Character::player_interact()) {
			//If the player already interacted with the character use alt_message
			if (value == 0) {
				//Give character the gear item if he doesn't already have it
				Listbox::Item gear = items::create_gear_item(gear_type);
				if (!sidemenu::has_item(sidemenu::GEAR, gear)) {
					sidemenu::add_item(sidemenu::GEAR, gear);
					textbox = new Textbox(message);
				} else {
					textbox = new Textbox(alt_message);
				}

				//Set value which is saved to 1 when player already interacted with the character
				set_value(1);
			} else {
				textbox = new Textbox(alt_message);
			}
			return true;
		}

		return false;
	}

	//Prevent player from looking away directly after closing textbox
	void GearVillager::close_textbox() {
		GameObject::close_textbox();
		last_turn = blit::now();
	}
}
