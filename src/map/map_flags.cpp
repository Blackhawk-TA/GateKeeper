//
// Created by daniel on 28.08.21.
//

#include "map_flags.hpp"

MapFlags::MapFlags(uint8_t layer_count) {
	MapFlags::layer_count = layer_count;
}

/**
 * Gets the flag of the given sprite on its highest layer, ignoring all underlying flags
 *
 * @param p The point at which the flag is located
 * @return The TileFlags enum id of the found flag
 */
uint8_t MapFlags::get_flag(Point p) {
	uint8_t i = layer_count;
	uint8_t j, k;
	uint8_t flag_enum_id = 0;
	uint16_t tile_id;
	bool flag_found = false;

	while (!flag_found && i > 0) {
		i--;
		j = 0;
		tile_id = map::tile_at(p);

		while (!flag_found && j < flags.size() - 1) {
			j++;
			k = 0;
			while (!flag_found && k < flags[j].size()) {
				if (tile_id == flags[j].at(k)) {
					flag_enum_id = j;
					flag_found = true;
				}
				k++;
			}
		}
	}

	return flag_enum_id;
}

void MapFlags::set_flags(TileFlags flag, const std::vector<uint16_t> &tiles) {
	flags[flag] = tiles;
}
