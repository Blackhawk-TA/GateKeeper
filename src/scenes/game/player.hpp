//
// Created by daniel on 21.08.21.
//

#pragma once
#include "../../utils/utils.hpp"
#include "../../engine/camera.hpp"
#include "game_objects/objects/stargate.hpp"
#include "../../game.hpp"
#include "../../utils/movement_direction.hpp"
#include "../../utils/saves/save_types.hpp"

using namespace blit;

//TODO rewrite so it is similar to character
namespace game {
	class Player {
	public:
		explicit Player(save::PlayerData player_data, uint8_t current_save_id);
		void draw();
		void move(MovementDirection direction);
		static bool is_dead();
		static uint8_t get_health();
		static void take_damage(uint8_t damage_amount);
		static void heal(uint8_t heal_amount);
		static MovementDirection get_direction();
		static void change_direction(MovementDirection direction, bool animate = true);
		static void set_cut_scene(bool value);
		static bool in_cut_scene();
		static bool has_weapon(AttackType type);
		static CharacterData get_character_data();
		static save::PlayerData get_save();

	private:
		const std::map<MovementDirection, Point> movements{
			{UP,    Point(0, -1)},
			{DOWN,  Point(0, 1)},
			{LEFT,  Point(-1, 0)},
			{RIGHT, Point(1, 0)},
		};

		static const uint16_t INIT_SPRITE_ID = 64;
		static const std::map<MovementDirection, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> movement_sprites;

		static uint16_t sprite_id;
		static uint8_t sprite_index;
		static std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites;
		static bool cut_scene;
		static MovementDirection current_direction;
		static uint8_t health;
		static uint8_t save_id;
		static uint8_t level;
		static bool dead;
		static bool sword;
		static bool spear;
		static bool arrow;
		static bool dagger;
		static bool magic;

		Timer animation_timer;
		Point position;
		Size spritesheet_size;
		uint8_t elevation_offset;

		static void animate(Timer &timer);
		static void gate_teleport(Stargate *destination_gate, uint8_t current_save_id);
		static bool in_action();
		void stop_animation();
	};
}