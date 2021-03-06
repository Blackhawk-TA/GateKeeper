//
// Created by daniel on 28.12.21.
//

#include "utils.hpp"
#include "../../../utils/saves/savegame.hpp"
#include "../game_objects/handler/save_game_objects.hpp"
#include "../game_objects/handler/player_handler.hpp"

namespace game::utils {
	void teleport_player(map::MapSection map_section, Point position, MovementDirection direction, uint8_t save_id, StoryState story_state) {
		//Load map and set position
		load_section(map_section);
		camera::set_position(position);
		player_handler::change_direction(direction, false);

		//Auto save game
		savegame::save(save_id);

		//Remove game objects of previous map section
		game_objects::cleanup();

		//Create game objects for next map section
		game_objects::init(map_section, save_id, story_state);

		//Load save to apply saved game object values for new map section
		std::array<game::GameObject::Save, MAX_GAME_OBJECTS> game_objects = savegame::load_game_objects(save_id);
		game_objects::load_saves(game_objects, story_state);
	}

	std::array<uint16_t, ANIMATION_SPRITE_COUNT> get_attack_sprites(CombatCharacterType type) {
		std::map<CombatCharacterType, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> sprite_map = {
			{PLAYER,       {0,   3,   6,   9}},
			{BLUE_GUARD,   {72,  75,  78,  81}},
			{SPIDER,       {12,  15,  18,  21}},
			{BROWN_BEAR,   {144, 147, 150, 153}},
			{DEVIL,        {84,  87,  90,  93}},
			{RED_CREATURE, {216, 219, 222, 225}},
			{RED_GUARD,    {228, 231, 234, 237}},
			{ICE_BEAR,     {156, 159, 162, 165}}
		};

		return sprite_map[type];
	}

	uint8_t sequence_index = 0;
	void input_sequence_handler(uint8_t pressed_button) {
		std::array<Button, 10> sequence = {
			Button::DPAD_UP, Button::DPAD_UP, Button::DPAD_DOWN, Button::DPAD_DOWN,
			Button::DPAD_LEFT, Button::DPAD_RIGHT, Button::DPAD_LEFT, Button::DPAD_RIGHT, Button::B, Button::A
		};

		if (pressed_button == sequence[sequence_index] && sequence_index < sequence.size() - 1) {
			sequence_index++;
		} else if (pressed_button == sequence[sequence_index] && sequence_index == sequence.size() - 1) {
			player_handler::add_gold(999);
			player_handler::heal(100);
			sequence_index = 0;
		} else {
			sequence_index = 0;
		}
	}
}
