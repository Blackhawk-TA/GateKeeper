//
// Created by daniel on 28.12.21.
//

#include "utils.hpp"
#include "handlers/game_objects/game_object_handler.hpp"
#include "../../utils/saves/savegame.hpp"

namespace game::utils {
	void teleport_player(map::MapSections map_section, Point position, Player::MovementDirection direction) {
		//Load map and set position
		load_section(map_section);
		camera::set_position(position);
		Player::change_direction(direction, false);

		//Auto save game
		savegame::save(current_save_id);

		//Remove game objects of previous map section
		game_objects::cleanup();

		//Create game objects for next map section
		game_objects::init(map_section);

		//Load save to apply saved game object values for new map section
		std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects = savegame::load_game_objects(current_save_id);
		game_objects::load_saves(game_objects);
	}
}
