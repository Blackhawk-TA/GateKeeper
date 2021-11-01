//
// Created by D069765 on 26.10.2021.
//

#include "gate_statue.hpp"
#include "../engine/camera.hpp"
#include "../ui/inventory.hpp"
#include "../items/items.hpp"

GateStatue::GateStatue(map::MapSections map_section, Point position, bool usable) {
	GateStatue::position = position;
	GateStatue::map_section = map_section;
	GateStatue::usable = usable;
	spritesheet_size = get_spritesheet_size(screen.sprites->bounds);

	GateStatue::set_usable(usable);

	//TODO move to parent constructor
	//Generate object signature
	signature = Signature{
		map_section,
		position
	};
}

GateStatue::Signature GateStatue::get_signature() {
	return signature;
}

GateStatue::Save GateStatue::get_save() {
	return Save{
		signature,
		usable
	};
}

void GateStatue::load_save(bool value) {
	set_usable(value);
}

bool GateStatue::check_collision(Point next_position) {
	if (map::get_section() != map_section) {
		return false;
	}

	return position.x <= next_position.x && position.y <= next_position.y &&
	       position.x > next_position.x - STATUE_SIZE.w && position.y > next_position.y - STATUE_SIZE.h;
}

void GateStatue::draw() {
	if (map::get_section() != map_section) {
		return;
	}

	Point camera_position = camera::get_screen_position();
	Point camera_position_world = screen_to_world(camera_position);

	if (sprite_rect_in_screen(position, STATUE_SIZE, camera_position_world)) {
		screen.blit_sprite(
			Rect(
				(tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
				(tile_id / spritesheet_size.h) * TILE_SIZE,
				STATUE_SIZE.w * TILE_SIZE,
				STATUE_SIZE.h * TILE_SIZE
			),
			world_to_screen(position) - camera_position,
			SpriteTransform::NONE
		);
	}
}

bool GateStatue::interact() {
	if (map::get_section() != map_section) {
		return false;
	}

	if (camera::get_player_position() == position + Point(0, STATUE_SIZE.h) && usable) {
		set_usable(false);
		inventory::add_item(listbox_item::create_inventory_item(listbox_item::GATE_PART));
		return true;
	}

	return false;
}

void GateStatue::update_state(Point next_position) {
	if (map::get_section() != map_section) {
		return;
	}

	//Show as active when player stands directly in front of the statue
	if (state == INACTIVE && next_position == position + Point(0, STATUE_SIZE.h)) {
		set_state(ACTIVE);
	} else if (state == ACTIVE) {
		set_state(INACTIVE);
	}
}

void GateStatue::set_state(uint8_t new_state) {
	auto new_state_enum = static_cast<RenderStates>(new_state);

	switch (new_state_enum) {
		case DEPLETED:
			tile_id = TILE_ID_EMPTY;
			break;
		case INACTIVE:
			tile_id = TILE_ID_INACTIVE;
			break;
		case ACTIVE:
			tile_id = TILE_ID_ACTIVE;
			break;
	}

	state = new_state_enum;
}

void GateStatue::set_usable(bool value) {
	usable = value;

	if (value) {
		set_state(INACTIVE);
	} else {
		set_state(DEPLETED);
	}

	update_state(camera::get_player_position());
}
