//
// Created by daniel on 26.12.21.
//

#include "character.hpp"
#include "../../../../engine/camera.hpp"

namespace combat {
	Character::Character(CharacterData character_data, Point position, Point attack_position) {
		Character::position = position;
		Character::attack_position = attack_position;

		animation_sprites = character_data.movement_sprites;
		health = character_data.health;
		tile_id = animation_sprites.at(0);
		tile_index = 0;
		screen_position = world_to_screen(position);
		spritesheet_size = get_spritesheet_size(player_sprites->bounds);
		attacking = false;
		moving = false;
	}

	void Character::draw() {
		screen.blit(
			player_sprites,
			Rect(
				(tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
				(tile_id / spritesheet_size.h) * TILE_SIZE,
				SIZE.w * TILE_SIZE,
				SIZE.h * TILE_SIZE
			),
			screen_position - camera::get_screen_position(),
			SpriteTransform::NONE
		);
	}

	void Character::update(uint32_t time) {
	}

	void Character::walk_to_attack_position() {
		if (direction == LEFT && position.x >= attack_position.x) {
			screen_position.x -= 1;
		} else if (direction == RIGHT && position.x <= attack_position.x) {
			screen_position.x += 1;
		}

		position = screen_to_world(screen_position);
	}

	void Character::animate(Timer &timer) {
		if (moving) {
			tile_id = animation_sprites[++tile_index % ANIMATION_SPRITE_COUNT];
		}
	}

	void Character::set_attacking(bool value) {
		attacking = value;
	}

	uint8_t Character::get_health() const {
		return health;
	}

	void Character::take_damage(uint8_t amount) {
		if (health - amount > 0) {
			health -= amount;
		} else {
			health = 0;
			dead = true;
		}
	}
}