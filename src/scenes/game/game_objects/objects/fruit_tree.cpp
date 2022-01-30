//
// Created by daniel on 06.11.21.
//

#include "fruit_tree.hpp"
#include "../../../../engine/camera.hpp"
#include "../../../../utils/game_time.hpp"
#include "../../player.hpp"
#include "../../handlers/sidemenu_handler.hpp"

namespace game {
	FruitTree::FruitTree(map::MapSection map_section, Point position, bool player_usable)
	: GameObject(map_section, position, player_usable, false) {
		size = Size(3, 3);
		tile_id = TILE_ID_TREE;
		value = game_time::get_time() + GROW_TIME_MS; //Value equals grow time
		FruitTree::set_player_usable(player_usable);
	}

	void FruitTree::draw() {
		Point camera_position = camera::get_screen_position();

		//Draw tree
		screen.blit_sprite(
			Rect(
				(tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
				(tile_id / spritesheet_size.h) * TILE_SIZE,
				size.w * TILE_SIZE,
				size.h * TILE_SIZE
			),
			world_to_screen(position) - camera_position,
			SpriteTransform::NONE
		);

		//Draw fruits
		if (player_usable) {
			screen.blit_sprite(
				Rect(
					(TILE_ID_FRUITS & (spritesheet_size.w - 1)) * TILE_SIZE,
					(TILE_ID_FRUITS / spritesheet_size.h) * TILE_SIZE,
					FRUIT_SIZE.w * TILE_SIZE,
					FRUIT_SIZE.h * TILE_SIZE
				),
				world_to_screen(position + FRUIT_OFFSET) - camera_position,
				SpriteTransform::NONE
			);
		}

		//Draw textbox notification
		if (textbox != nullptr) {
			textbox->draw();
		}
	}

	void FruitTree::update(uint32_t time) {
		if (!player_usable && value < game_time::get_time()) {
			player_usable = true;
		}
	}

	bool FruitTree::player_interact() {
		if (player_usable && Player::get_direction() == UP && camera::get_player_position() == position + Point(size.w / 2, size.h)) {
			bool has_inventory_space = sidemenu::add_item(sidemenu::INVENTORY, listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::APPLE));
			if (has_inventory_space) {
				set_player_usable(false);
				value = game_time::get_time() + GROW_TIME_MS;
				textbox = new Textbox("You put an apple in your inventory.");
			} else {
				textbox = new Textbox("You cannot carry any more apples.");
			}
			return true;
		}
		return false;
	}

	GameObject::ObjectType FruitTree::get_type() {
		return FruitTreeType;
	}

	void FruitTree::set_state(uint8_t new_state) {}

	void FruitTree::update_state(Point next_position) {}
}
