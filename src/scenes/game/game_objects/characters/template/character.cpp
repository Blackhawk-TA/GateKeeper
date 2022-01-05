//
// Created by daniel on 01.11.21.
//
#include "character.hpp"
#include "../../../../../engine/camera.hpp"
#include "../../../player.hpp"

namespace game {
	Character::Character(map::MapSection map_section, Point position, bool player_usable, bool inventory_usable, bool turn)
		: GameObject(map_section, position, player_usable, inventory_usable) {
		Character::size = Size(1, 1);
		Character::position = position;
		Character::screen_position = world_to_screen(position);
		Character::spritesheet_size = get_spritesheet_size(characters_spritesheet->bounds);
		Character::tile_index = 0;
		Character::in_action = false;
		Character::is_moving = false;
		Character::last_turn = blit::now();
		Character::animation_delay = ANIMATION_BASE_DELAY;
		Character::turn = turn;
		Character::current_direction = NO_DIRECTION;
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
			if (Player::get_direction() == UP && camera::get_player_position() == position + Point(0, size.h)) {
				interacted = true;
				change_direction(DOWN, false);
			} else if (Player::get_direction() == DOWN && camera::get_player_position() == position - Point(0, size.h)) {
				interacted = true;
				change_direction(UP, false);
			} else if (Player::get_direction() == LEFT && camera::get_player_position() == position + Point(size.w, 0)) {
				interacted = true;
				change_direction(RIGHT, false);
			} else if (Player::get_direction() == RIGHT && camera::get_player_position() == position - Point(size.w, 0)) {
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
		if (is_moving) {
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
		//Can only walk straight lines
		if (position.x != p.x && position.y != p.y) {
			return false;
		}

		if (current_direction == UP && position.y > p.y) {
			screen_position.y -= 1;
			return true;
		} else if (current_direction == DOWN && position.y + 1 < p.y) {
			screen_position.y += 1;
			return true;
		} else if (current_direction == LEFT && position.x > p.x) {
			screen_position.x -= 1;
			return true;
		} else if (current_direction == RIGHT && position.x + 1 < p.x) {
			screen_position.x += 1;
			return true;
		} else {
			return false;
		}
	}

	void Character::walk_to_player() {
		Point player_position = camera::get_player_position();

		if (!walk_straight_line(player_position)) {
			//Enemy is standing in front of player and starts combat
			is_moving = false;
			tile_id = animation_sprites[0];
			trigger_cut_scene();
		}

		position = screen_to_world(screen_position);
	}

	bool Character::player_in_sightline() {
		Point player_position = camera::get_player_position();
		return (current_direction == UP && position.x == player_position.x && position.y > player_position.y)
			|| (current_direction == DOWN && position.x == player_position.x && position.y < player_position.y)
			|| (current_direction == LEFT && position.y == player_position.y && position.x > player_position.x)
			|| (current_direction == RIGHT && position.y == player_position.y && position.x < player_position.x);
	}

	void Character::player_face_character() {
		switch (current_direction) {
			case NO_DIRECTION:
				break;
			case UP:
				Player::change_direction(MovementDirection::DOWN, false);
				break;
			case DOWN:
				Player::change_direction(MovementDirection::UP, false);
				break;
			case LEFT:
				Player::change_direction(MovementDirection::RIGHT, false);
				break;
			case RIGHT:
				Player::change_direction(MovementDirection::LEFT, false);
				break;
		}
	}

	void Character::trigger_cut_scene() {}
}
