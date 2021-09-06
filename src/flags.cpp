//
// Created by daniel on 07.09.21.
//

#include "flags.hpp"
#include "map.hpp"

std::array<std::vector<uint16_t>, flags::TileFlags::COUNTER> flag_register;

/**
 * Gets the flag of the given sprite on its highest layer, ignoring all underlying flags
 * @param p The point at which the flag is located
 * @return The TileFlags enum id of the found flag
 */
uint8_t flags::get_flag(Point p) {
	uint8_t i = map::get_layer_count();
	uint8_t j, k;
	uint8_t flag_enum_id = 0;
	uint16_t tile_id;
	bool flag_found = false;

	while (!flag_found && i > 0) {
		i--;
		j = 0;
		tile_id = map::tile_at(p);

		while (!flag_found && j < flag_register.size() - 1) {
			k = 0;
			while (!flag_found && k < flag_register[j].size()) {
				if (tile_id == flag_register[j].at(k)) {
					flag_enum_id = j + 1; //Add 1 because flag index starts at 1
					flag_found = true;
				}
				k++;
			}
			j++;
		}
	}

	return flag_enum_id;
}

void flags::set_flag(TileFlags flag, const std::vector<uint16_t> &tiles) {
	flag_register[flag - 1] = tiles;
}
