//
// Created by daniel on 06.11.21.
//

#include "fruit_tree.hpp"
#include "../../../engine/camera.hpp"
#include "../../../utils/game_time.hpp"
#include "../../../items/items.hpp"
#include "../ui/inventory.hpp"

//TODO save grown time in int32 value, maybe add new
FruitTree::FruitTree(map::MapSections map_section, Point position, bool player_usable) : GameObject(map_section, position, player_usable, false) {
	size = Size(3, 3);
	tile_id = TILE_ID_TREE;
	grown_time = game_time::get_time() + GROW_TIME_MS / 2;
	FruitTree::set_player_usable(player_usable);
}

void FruitTree::draw() {
	Point camera_position = camera::get_screen_position();
	Point camera_position_world = screen_to_world(camera_position);

	if (sprite_rect_in_screen(position, size, camera_position_world)) {
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
	}

	//Draw textbox notification
	if (textbox != nullptr) {
		textbox->draw();
	}
}

void FruitTree::update(uint32_t time) {
	if (!player_usable && grown_time < game_time::get_time()) {
		player_usable = true;
	}
}

bool FruitTree::player_interact() {
	if (player_usable && camera::get_player_position() == position + Point(size.w / 2, size.h)) {
		bool has_inventory_space = inventory::add_item(listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::APPLE));
		if (has_inventory_space) {
			set_player_usable(false);
			grown_time = game_time::get_time() + GROW_TIME_MS;
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
