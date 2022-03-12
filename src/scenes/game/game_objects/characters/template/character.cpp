//
// Created by daniel on 01.11.21.
//
#include "character.hpp"
#include "../../../../../engine/camera.hpp"
#include "../../../../../engine/flags.hpp"
#include "../../handler/player_handler.hpp"
#include "../../handler/game_object_handler.hpp"

namespace game {
	Character::Character(map::MapSection map_section, Point position, bool player_usable, bool inventory_usable, bool turn)
		: GameObject(map_section, position, player_usable, inventory_usable) {
		Character::size = Size(1, 1);
		Character::position = position;
		Character::screen_position = world_to_screen(position);
		Character::spritesheet_size = get_spritesheet_size(characters_spritesheet->bounds);
		Character::tile_index = 0;
		Character::in_action = false;
		Character::moving_to_player = false;
		Character::moving_back = false;
		Character::last_turn = blit::now();
		Character::animation_delay = ANIMATION_BASE_DELAY;
		Character::turn = turn;
		Character::current_direction = NO_DIRECTION;
	}

	void Character::set_movement_sprites() {
		movement_sprites = {
			{UP, {
				static_cast<uint16_t>(tile_id + 48),
				static_cast<uint16_t>(tile_id + 49),
				static_cast<uint16_t>(tile_id + 50),
				static_cast<uint16_t>(tile_id + 51)
			}},
			{DOWN, {
				tile_id,
				static_cast<uint16_t>(tile_id + 1),
				static_cast<uint16_t>(tile_id + 2),
				static_cast<uint16_t>(tile_id + 3)
			}},
			{LEFT, {
				static_cast<uint16_t>(tile_id + 16),
				static_cast<uint16_t>(tile_id + 17),
				static_cast<uint16_t>(tile_id + 18),
				static_cast<uint16_t>(tile_id + 19)
			}},
			{RIGHT, {
				static_cast<uint16_t>(tile_id + 32),
				static_cast<uint16_t>(tile_id + 33),
				static_cast<uint16_t>(tile_id + 34),
				static_cast<uint16_t>(tile_id + 35)
			}},
		};
	}

	void Character::draw() {
		screen.blit(
			characters_spritesheet,
			Rect(
				(tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
				(tile_id / spritesheet_size.h) * TILE_SIZE,
				size.w * TILE_SIZE,
				size.h * TILE_SIZE
			),
			screen_position - camera::get_screen_position(),
			SpriteTransform::NONE
		);

		//Draw textbox notification
		if (textbox != nullptr) {
			textbox->draw();
		}
	}

	bool Character::player_interact() {
		bool interacted = false;

		if (player_usable) {
			if (player_handler::get_direction() == UP && camera::get_player_position() == position + Point(0, size.h)) {
				interacted = true;
				change_direction(DOWN, false);
			} else if (player_handler::get_direction() == DOWN && camera::get_player_position() == position - Point(0, size.h)) {
				interacted = true;
				change_direction(UP, false);
			} else if (player_handler::get_direction() == LEFT && camera::get_player_position() == position + Point(size.w, 0)) {
				interacted = true;
				change_direction(RIGHT, false);
			} else if (player_handler::get_direction() == RIGHT && camera::get_player_position() == position - Point(size.w, 0)) {
				interacted = true;
				change_direction(LEFT, false);
			}
		}

		return interacted;
	}

	void Character::change_direction(MovementDirection direction, bool animate) {
		if (current_direction != direction) {
			animation_sprites = movement_sprites.at(direction);
			current_direction = direction;
			tile_id = animate ? animation_sprites[1] : animation_sprites[0]; //Set sprite manually to avoid timer delay on player turn
		}
	}

	GameObject::ObjectType Character::get_type() {
		return GameObject::CharacterType;
	}

	void Character::animate() {
		if (moving_to_player || moving_back) {
			tile_id = animation_sprites[++tile_index % ANIMATION_SPRITE_COUNT];
		}
	}

	void Character::update(uint32_t time) {
		//Handle random turning of enemy
		if (turn && !is_textbox_open() && time > animation_delay && last_turn < time - animation_delay) {
			uint8_t next_direction = blit::random() % DIRECTION_COUNT + 1;
			change_direction(static_cast<MovementDirection>(next_direction), false);

			last_turn = time;
			animation_delay = ANIMATION_BASE_DELAY + blit::random() % ANIMATION_VARIANCE;
		}
	}

	bool Character::walk_straight_line(Point &p) {
		Point p_world = world_to_screen(p);

		//Can only walk straight lines
		if (screen_position.x != p_world.x && screen_position.y != p_world.y) {
			return false;
		}

		if (current_direction == UP && screen_position.y > p_world.y) {
			screen_position.y -= 1;
			return true;
		} else if (current_direction == DOWN && screen_position.y < p_world.y) {
			screen_position.y += 1;
			return true;
		} else if (current_direction == LEFT && screen_position.x > p_world.x) {
			screen_position.x -= 1;
			return true;
		} else if (current_direction == RIGHT && screen_position.x < p_world.x) {
			screen_position.x += 1;
			return true;
		} else {
			return false;
		}
	}

	void Character::walk_to_player() {
		Point player_position = camera::get_player_position();
		Point target_position;

		//Walk in front of the player instead of into it
		switch (current_direction) {
			case UP:
				target_position = Point(player_position.x, player_position.y + 1);
				break;
			case DOWN:
				target_position = Point(player_position.x, player_position.y - 1);
				break;
			case LEFT:
				target_position = Point(player_position.x + 1, player_position.y);
				break;
			case RIGHT:
				target_position = Point(player_position.x - 1, player_position.y);
				break;
			default:
				return;
		}

		if (!walk_straight_line(target_position)) {
			//Enemy is standing in front of player and starts combat
			moving_to_player = false;
			tile_id = animation_sprites[0];
			trigger_cutscene();
		}
	}

	void Character::walk_back() {
		if (!walk_straight_line(position)) {
			//Character is standing at spawn position
			moving_back = false;
			tile_id = animation_sprites[0];
			trigger_back_at_spawn();
		}
	}

	bool Character::player_in_sightline() {
		if (camera::is_moving()) return false;

		Point player_position = camera::get_player_position();
		return (current_direction == UP && position.x == player_position.x && position.y > player_position.y
		&& calc_player_distance(position.y, player_position.y) < 7 && path_is_walkable(player_position, position))

		|| (current_direction == DOWN && position.x == player_position.x && position.y < player_position.y
		&& calc_player_distance(player_position.y, position.y) < 7 && path_is_walkable(position, player_position))

		|| (current_direction == LEFT && position.y == player_position.y && position.x > player_position.x
		&& calc_player_distance(position.x, player_position.x) < 7 && path_is_walkable(player_position, position))

		|| (current_direction == RIGHT && position.y == player_position.y && position.x < player_position.x
		&& calc_player_distance(position.x, player_position.x) < 7 && path_is_walkable(position, player_position));
	}

	uint8_t Character::calc_player_distance(uint8_t a, uint8_t b) {
		return abs(a - b);
	}

	bool Character::path_is_walkable(Point start, Point end) {
		if (start.x == end.x) {
			for (int i = start.y + 1; i < end.y; i++) {
				if (!tile_is_walkable(Point(start.x, i))) {
					return false;
				}
			}
			return  true;
		} else if (start.y == end.y) {
			for (int i = start.x + 1; i < end.x; i++) {
				if (!tile_is_walkable(Point(i, start.y))) {
					return false;
				}
			}
			return  true;
		}

		return false;
	}

	bool Character::tile_is_walkable(Point tile_position) {
		uint8_t flag = map::get_flag(tile_position);
		return (flag == flags::WALKABLE || flag == flags::ELEVATE_1PX || flag == flags::ELEVATE_2PX || flag == flags::ELEVATE_3PX || flag == flags::NO_FLAG)
			&& !game_objects::tile_occupied(tile_position);
	}

	void Character::player_face_character() {
		switch (current_direction) {
			case NO_DIRECTION:
				break;
			case UP:
				player_handler::change_direction(MovementDirection::DOWN, false);
				break;
			case DOWN:
				player_handler::change_direction(MovementDirection::UP, false);
				break;
			case LEFT:
				player_handler::change_direction(MovementDirection::RIGHT, false);
				break;
			case RIGHT:
				player_handler::change_direction(MovementDirection::LEFT, false);
				break;
		}
	}

	void Character::trigger_cutscene() {}
	void Character::trigger_back_at_spawn() {}
}
