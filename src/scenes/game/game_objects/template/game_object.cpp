//
// Created by daniel on 01.11.21.
//
#include "game_object.hpp"
#include "../../../../engine/camera.hpp"
#include "../handler/player_handler.hpp"

namespace game {
	GameObject::GameObject(map::MapSection map_section, Point position, bool player_usable, bool inventory_usable, bool draw_under_player) {
		GameObject::position = position;
		GameObject::map_section = map_section;
		GameObject::player_usable = player_usable;
		GameObject::inventory_usable = inventory_usable;
		GameObject::draw_under_player = draw_under_player;
		GameObject::spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
		GameObject::textbox = nullptr;
		GameObject::active = true;
		GameObject::value = 0;
		GameObject::tile_id = 0;

		//Generate object signature
		signature = Signature{
			static_cast<uint8_t>(map_section),
			static_cast<uint8_t>(position.x),
			static_cast<uint8_t>(position.y),
		};
	}

	GameObject::~GameObject() {
		if (textbox != nullptr) {
			delete textbox;
			textbox = nullptr;
		}
	}

	void GameObject::draw() {
		screen.blit(
			screen.sprites,
			Rect(
				(tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
				(tile_id / spritesheet_size.h) * TILE_SIZE,
				size.w * TILE_SIZE,
				size.h * TILE_SIZE
			),
			world_to_screen(position) - camera::get_screen_position()
		);
	}

	void GameObject::draw_textbox() {
		if (textbox != nullptr) {
			textbox->draw();
		}
	}

	bool GameObject::is_textbox_open() {
		return textbox != nullptr;
	}

	bool GameObject::next_textbox() {
		return textbox->next();
	}

	void GameObject::close_textbox() {
		delete textbox;
		textbox = nullptr;
	}

	bool GameObject::check_collision(Point next_position) {
		return position.x <= next_position.x && position.y <= next_position.y &&
		       position.x > next_position.x - size.w && position.y > next_position.y - size.h;
	}

	Signature GameObject::get_signature() {
		return signature;
	}

	GameObject::Save GameObject::get_save() {
		return Save{
			signature,
			Data{
				player_usable,
				inventory_usable,
				active,
				value,
			}
		};
	}

	void GameObject::load_save(Data data) {
		set_player_usable(data.player_usable);
		set_inventory_usable(data.inventory_usable);
		set_value(data.value);
		set_active(data.is_active);
	}

	void GameObject::set_player_usable(bool usable) {
		player_usable = usable;
	}

	void GameObject::set_inventory_usable(bool usable) {
		inventory_usable = usable;
	}

	void GameObject::set_value(uint32_t new_value) {
		value = new_value;
	}

	void GameObject::set_active(bool active_value) {
		active = active_value;
	}

	bool GameObject::player_interact() {
		return false;
	}

	bool GameObject::inventory_interact(items::INVENTORY_ITEM item_type) {
		return false;
	}

	bool GameObject::is_rendered() {
		return active && map::get_section() == map_section
		       && sprite_rect_in_screen(position, size, camera::get_world_position());
	}

	bool GameObject::is_drawn_under_player() const {
		return draw_under_player;
	}

	bool GameObject::in_range(uint8_t distance) {
		return (player_handler::get_direction() == UP && camera::get_player_position() == position + Point(0, size.h + distance))
			|| (player_handler::get_direction() == DOWN && camera::get_player_position() == position - Point(0, size.h + distance))
			|| (player_handler::get_direction() == RIGHT && camera::get_player_position() == position - Point(size.w + distance, 0))
			|| (player_handler::get_direction() == LEFT && camera::get_player_position() == position + Point(size.w + distance, 0));
	}


	bool GameObject::player_in_front(uint8_t distance) {
		return player_handler::get_direction() == UP && camera::get_player_position() == position + Point(0, size.h + distance);
	}

	bool GameObject::is_active() const {
		return active;
	}

	void GameObject::update_state(Point next_position) {}

	void GameObject::update(uint32_t time) {}

	void GameObject::set_state(uint8_t new_state) {}
}
