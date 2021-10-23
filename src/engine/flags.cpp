//
// Created by daniel on 07.09.21.
//

#include "flags.hpp"

std::array<std::vector<uint16_t>, flags::TileFlags::COUNTER> flag_register;

/**
 * Gets the flag of the given tile
 * @param tile_id The id of the tile
 * @return The TileFlags enum id of the found flag
 */
uint8_t flags::get_flag(uint16_t tile_id) {
	uint8_t flag_enum_id = 0;
	uint8_t i = 0;
	uint16_t k;

	while (flag_enum_id == 0 && i < flag_register.size()) {
		k = 0;
		while (flag_enum_id == 0 && k < flag_register[i].size()) {
			if (tile_id == flag_register[i][k]) {
				flag_enum_id = i + 1; //Add 1 because flag index starts at 1
			}
			k++;
		}
		i++;
	}

	return flag_enum_id;
}

void flags::set_flags(TileFlags flag, const std::vector<uint16_t> &tiles) {
	flag_register[flag - 1] = tiles;
}
