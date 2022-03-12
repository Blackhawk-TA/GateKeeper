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

		explicit Player(uint8_t current_save_id);
		void draw();
		void animate();
		void move(MovementDirection direction);
		void heal(uint8_t heal_amount);
		uint8_t get_health() const;
		MovementDirection get_direction();
		void change_direction(MovementDirection direction, bool animate = true);
		void set_cut_scene(bool value);
		bool in_cut_scene() const;
		bool is_dead() const;
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
		bool dead;
		uint16_t sprite_id;
		uint8_t sprite_index;
		uint8_t health;
		uint8_t save_id;
		uint8_t level;
		uint8_t elevation_offset;
		MovementDirection current_direction;
		Point position;
		Size spritesheet_size;

		void take_damage(uint8_t damage_amount);
		bool in_action() const;

		/**
		 * Teleports a player to the given gate and sets the movement direction to facing downwards
		 * @param destination_gate The gate to which the player is teleported
		 * @param current_save_id The id of the current save
		 */
		static void gate_teleport(Stargate *destination_gate, uint8_t current_save_id);
	};
}