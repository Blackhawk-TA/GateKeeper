//
// Created by daniel on 21.08.21.
//

#pragma once
#include "../../../utils/utils.hpp"
#include "../../../engine/camera.hpp"
#include "objects/stargate.hpp"
#include "../../../game.hpp"
#include "../../../utils/movement_direction.hpp"
#include "../../../utils/saves/save_types.hpp"

using namespace blit;

namespace game {
	class Player {
	public:
		static const uint8_t MAX_HEALTH = 100;
		static const uint8_t MAX_LEVEL = 25;
		static const uint16_t MAX_GOLD = 999;

		explicit Player(uint8_t current_save_id);
		void draw();
		void animate();
		void move(MovementDirection direction);
		void heal(uint8_t heal_amount);
		uint8_t get_health() const;
		uint8_t get_level() const;
		uint32_t get_xp() const;

		/**
		 * Gets the amount of XP required for the next level without considering the current XP amount
		 * @return The XP amount required for the next level
		 */
		uint32_t get_next_level_max_xp() const;
		void add_xp(uint32_t amount);
		uint16_t get_gold() const;
		void add_gold(uint16_t amount);
		bool remove_gold(uint16_t amount);
		MovementDirection get_direction();
		void change_direction(MovementDirection direction, bool animate = true);
		void set_cut_scene(bool value);
		bool in_cut_scene() const;
		CharacterData get_character_data();
		save::PlayerData get_save();
		void load_save(save::PlayerData save_data);

	private:
		const std::map<MovementDirection, Point> movements{
			{UP,    Point(0, -1)},
			{DOWN,  Point(0, 1)},
			{LEFT,  Point(-1, 0)},
			{RIGHT, Point(1, 0)},
		};
		const std::map<MovementDirection, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> movement_sprites = {
			{UP,    {112, 113, 114, 115}},
			{DOWN,  {16,   17,  18,  19}},
			{LEFT,  {48,   49,  50,  51}},
			{RIGHT, {80,   81,  82,  83}}
		};
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites{};

		bool is_animating;
		bool cut_scene;
		uint16_t sprite_id;
		uint16_t gold;
		uint8_t sprite_index;
		uint8_t health;
		uint8_t save_id;
		uint8_t level;
		uint32_t xp;
		uint8_t elevation_offset;
		MovementDirection current_direction;
		StoryState story_state;
		Point position;
		Size spritesheet_size;

		void take_damage(uint8_t damage_amount);
		bool in_action() const;

		/**
		 * Calculates the total amount of xp needed to achieve the given level when the player has no XP yet
		 * @param target_level The level of which the total xp amount is needed
		 * @return The amount of xp needed to achieve the given level
		 */
		static uint32_t calc_total_level_xp(uint8_t target_level);

		/**
		 * Teleports a player to the given gate and sets the movement direction to facing downwards
		 * @param destination_gate The gate to which the player is teleported
		 * @param current_save_id The id of the current save
		 */
		void gate_teleport(Stargate *destination_gate, uint8_t current_save_id);
	};
}