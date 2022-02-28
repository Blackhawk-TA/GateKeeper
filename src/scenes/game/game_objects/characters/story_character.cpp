//
// Created by daniel on 05.02.22.
//

#include "story_character.hpp"
#include "../../../../engine/effects/transition.hpp"
#include "../handler/player_handler.hpp"
#include <utility>

namespace game {
	StoryCharacter::StoryCharacter(map::MapSection mapSection, Point position, uint16_t tile_id, MovementDirection direction, bool turn, std::string message, std::string alt_message)
	: Character(mapSection, position, true, false) {
		StoryCharacter::tile_id = tile_id;
		StoryCharacter::message = std::move(message);
		StoryCharacter::alt_message = std::move(alt_message);
		StoryCharacter::turn = turn;
		StoryCharacter::default_turn_value = turn;
		set_movement_sprites();
		change_direction(direction, false);
	}

	void StoryCharacter::close_textbox() {
		GameObject::close_textbox();

		//Walk back to initial position
		change_direction(invert_direction(current_direction));
		moving_back = true;
	}

	void StoryCharacter::update(uint32_t time) {
		Character::update(time);

		//Trigger character to walk to player
		if (value == 0 && !in_action && !player_handler::in_cut_scene() && !transition::in_process() && player_in_sightline()) {
			turn = false;
			in_action = true;
			moving_to_player = true;
			player_handler::set_cut_scene(true);
		}

		if (moving_to_player) {
			walk_to_player();
		} else if (moving_back) {
			walk_back();
		}
	}

	void StoryCharacter::trigger_cutscene() {
		Character::player_face_character();

		//If the player already interacted with the character use alt_message
		if (value == 0) {
			textbox = new Textbox(message);
		} else {
			textbox = new Textbox(alt_message);
		}
	}

	void StoryCharacter::trigger_back_at_spawn() {
		//Reset turn value
		turn = default_turn_value;

		//Set value which is saved to 1 when player already interacted with the character
		set_value(1);

		//Stop cut scene
		player_handler::set_cut_scene(false);
	}

	bool StoryCharacter::player_interact() {
		if (Character::player_interact()) {
			trigger_cutscene();
			return true;
		}
		return false;
	}
}