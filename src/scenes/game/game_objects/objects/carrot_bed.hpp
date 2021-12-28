//
// Created by daniel on 07.11.21.
//

#pragma once
#include "../template/game_object.hpp"

namespace game {
	class CarrotBed : public GameObject {
	private:
		enum RenderStates {
			HARVESTED = 1,
			PLANTED = 2,
			GROWING = 3,
			GROWN = 4
		};

		const uint16_t TILE_ID_HARVESTED = 1236;
		const uint16_t TILE_ID_PLANTED = 1237;
		const uint16_t TILE_ID_GROWING = 1238;
		const uint16_t TILE_ID_GROWN = 1300;
		const uint16_t GROW_STAGE_1_TIME = 30000;
		const uint16_t GROW_STAGE_2_TIME = 30000;

		RenderStates state;

		void set_state(uint8_t new_state) override;
		void set_player_usable(bool usable) override;
		void set_inventory_usable(bool usable) override;
		bool in_use_range();

	public:
		explicit CarrotBed(map::MapSections map_section, Point position);
		~CarrotBed() override = default;
		void update(uint32_t time) override;
		bool player_interact() override;
		bool inventory_interact(listbox_item::INVENTORY_ITEM item_type) override;
		void update_state(Point next_position) override;
		ObjectType get_type() override;
	};
}
