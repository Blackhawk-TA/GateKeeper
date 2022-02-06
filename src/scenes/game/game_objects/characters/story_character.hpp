//
// Created by daniel on 05.02.22.
//

#pragma once

#include "template/character.hpp"

namespace game {
	class StoryCharacter : public Character {
	private:
		std::string message;
		std::string alt_message;
		bool default_turn_value;

		void set_state(uint8_t new_state) override;
		void close_textbox() override;
		void trigger_cutscene() override;
		void trigger_back_at_spawn() override;
		bool player_interact() override;

	public:
		explicit StoryCharacter(map::MapSection mapSection, Point position, uint16_t tile_id, MovementDirection direction, bool turn, std::string message, std::string alt_message);
		~StoryCharacter() override = default;
		void update_state(Point next_position) override;
		void update(uint32_t time) override;
	};
}
