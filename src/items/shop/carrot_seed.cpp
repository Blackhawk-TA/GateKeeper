//
// Created by daniel on 07.11.21.
//

#include "../items.hpp"
#include "../../scenes/game/ui/sidemenu.hpp"
#include "../../scenes/game/game_objects/handler/player_handler.hpp"

Listbox::Item items::create_shop_carrot_seed(uint8_t type_id) {
	uint8_t price = 3;
	return Listbox::Item{
		type_id,
		"Carrot Seed",
		"Buy 6 carrot seeds for " + std::to_string(price) + " gold. You can plant them and harvest the grown carrots later.",
		"You bought 6 carrot seeds for " + std::to_string(price) + " gold.",
		"You can't buy this now.",
		false,
		0,
		[price] {
			if (game::player_handler::remove_gold(price)
			&& game::sidemenu::add_item(game::sidemenu::INVENTORY, items::create_inventory_item(items::CARROT_SEED), 6)) {
				return Listbox::Tooltip::SUCCESS;
			} else {
				return Listbox::Tooltip::FAILURE;
			}
		}
	};
}
