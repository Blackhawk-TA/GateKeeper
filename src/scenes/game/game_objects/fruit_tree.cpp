//
// Created by daniel on 06.11.21.
//

#include "fruit_tree.hpp"
#include "../../../engine/camera.hpp"
#include "../../../utils/game_time.hpp"
#include "../../../items/items.hpp"
#include "../ui/inventory.hpp"

FruitTree::FruitTree(map::MapSections map_section, Point position, bool usable) : GameObject(map_section, position, usable) {
	size = Size(3, 3);
	tile_id = TILE_ID_TREE;
	grown_time = game_time::get_time() + GROW_TIME_MS / 2;
	FruitTree::set_usable(usable);
}

void FruitTree::draw() {
	if (map::get_section() != map_section) {
		return;
	}

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
		if (usable) {
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
	if (!usable && grown_time < game_time::get_time()) {
		usable = true;
	}
}

bool FruitTree::interact() {
	if (map::get_section() != map_section) {
		return false;
	}

	if (usable && camera::get_player_position() == position + Point(size.w / 2, size.h)) {
		set_usable(false);
		grown_time = game_time::get_time() + GROW_TIME_MS;
		inventory::add_item(listbox_item::create_inventory_item(listbox_item::INVENTORY_ITEM::APPLE));
		textbox = new Textbox("You put an apple in your inventory.");
		return true;
	}
	return false;
}


void FruitTree::set_usable(bool value) {
	usable = value;
}

GameObject::ObjectType FruitTree::get_type() {
	return FruitTreeType;
}

void FruitTree::set_state(uint8_t new_state) {}
void FruitTree::update_state(Point next_position) {}
