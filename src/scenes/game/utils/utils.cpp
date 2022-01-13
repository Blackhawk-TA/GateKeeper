//
// Created by daniel on 28.12.21.
//

#include "utils.hpp"
#include "../handlers/game_objects/game_object_handler.hpp"
#include "../../../utils/saves/savegame.hpp"

namespace game::utils {
	void teleport_player(map::MapSection map_section, Point position, MovementDirection direction, uint8_t save_id) {
		//Load map and set position
		load_section(map_section);
		camera::set_position(position);
		Player::change_direction(direction, false);

		//Auto save game
		savegame::save(save_id);

		//Remove game objects of previous map section
		game_objects::cleanup();

		//Create game objects for next map section
		game_objects::init(map_section, save_id);

		//Load save to apply saved game object values for new map section
		std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects = savegame::load_game_objects(save_id);
		game_objects::load_saves(game_objects);
	}

	std::array<uint16_t, ANIMATION_SPRITE_COUNT> get_attack_sprites(uint16_t tile_id) {
		std::map<uint16_t, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> sprite_map = {
			{64, {48, 51, 54, 57}}, //Player
			{76, {84, 87, 90, 93}}, //Blue Knight
			{72, {0, 1, 2, 3}}, //Spider
			{192, {4, 5, 6, 7}}, //Brown Bear
			{196, {12, 13, 14, 15}}, //Devil
			{200, {16, 17, 18, 19}}, //Red Creature
			{204, {8, 9, 10, 11}} //Ice Bear
		};

		return sprite_map[tile_id];
	}
}
