//
// Created by daniel on 07.11.21.
//

#include "../items.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"
#include "../../scenes/game/game_objects/handler/player_handler.hpp"

Listbox::Item items::create_shop_apple(uint8_t type_id) {
	uint8_t price = 5;
	return Listbox::Item{
		type_id,
		"Apple",
		"Buy 1 apple for " + std::to_string(price) + " gold. Eating them regenerates your health.",
		"You bought 1 apple for " + std::to_string(price) + " gold.",
		"You can't buy this now.",
		false,
		0,
		[price] {
			if (game::player_handler::remove_gold(price)
			&& game::sidemenu::add_item(game::sidemenu::INVENTORY, items::create_inventory_item(items::APPLE))) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
