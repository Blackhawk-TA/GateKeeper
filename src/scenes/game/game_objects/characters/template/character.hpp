//
// Created by daniel on 25.10.21.
//

#pragma once
#include "../../../../../utils/utils.hpp"
#include "../../../../../engine/map.hpp"
#include "../../../../../engine/ui/textbox.hpp"
#include "../../template/game_object.hpp"
#include "../../../../../utils/types.hpp"
#include "../../../../../utils/movement_direction.hpp"

namespace game {
	class Character : public GameObject {
	public:
		Character(map::MapSection map_section, Point position, bool player_usable, bool inventory_usable, bool turn = false);
		void draw() override;
		void update(uint32_t time) override;
		bool player_interact() override;
		GameObject::ObjectType get_type() override;
		void animate();

	protected:
		static constexpr uint8_t DIRECTION_COUNT = 4;
		static constexpr uint16_t ANIMATION_BASE_DELAY = 2500;
		static constexpr uint16_t ANIMATION_VARIANCE = 2000;

		bool turn;
		bool in_action;
		bool is_moving;
		uint8_t tile_index;
		uint32_t last_turn;
		uint32_t animation_delay;
		Point screen_position;
		std::map<MovementDirection, std::array<uint16_t, ANIMATION_SPRITE_COUNT>> movement_sprites;
		MovementDirection current_direction;
		std::array<uint16_t, ANIMATION_SPRITE_COUNT> animation_sprites;

		/**
		 * Triggers the cut scene which is started when a player stands directly in front of the character
		 */
		virtual void trigger_cut_scene();

		/**
		 * Checks if the player is in sightline of the character
		 * @return True, if the player is in sightline, else false
		 */
		bool player_in_sightline();

		/**
		 * Makes the character walk a straight line to the given point
		 * @param p The point to which the character shall walk to
		 * @return True, if the character is walking, else false
		 */
		bool walk_straight_line(Point &p);

		/**
		 * Makes the character walk to the player and triggers the cut scene once it stands in front of the player
		 */
		void walk_to_player();

		/**
		 * Changes the direction of the character
		 * @param direction The direction to which the character shall look to
		 * @param animate Whether the direction change should be animated with a step (default: true)
		 */
		void change_direction(MovementDirection direction, bool animate = true);

		/**
		 * Makes the player direction change so it faces the character
		 */
		void player_face_character();

	private:
		/**
		 * Checks if a path between two points is walkable by checking the tile flags.
		 * One of the two axis must be equal on start and end, so only straight lines are allowed.
		 * @param start The start position of the path
		 * @param end The end position of the path
		 * @return True, if the path if walkable, else false
		 */
		static bool path_is_walkable(Point start, Point end);

		/**
		 * Checks if a tile at the given position is walkable or not
		 * @param tile_position The position of the tile on the map
		 * @return True, if a character can walk on the tile, else false
		 */
		static bool tile_is_walkable(Point tile_position);
	};
}
