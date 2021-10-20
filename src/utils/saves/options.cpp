//
// Created by D069765 on 20.10.2021.
//

#include "options.hpp"
#include "../../ui/overlay.hpp"

bool options::show_fps = false;
uint8_t options::saves_count = 0;

void options::save() {
	OptionsData data = {
		saves_count,
		show_fps
	};

	write_save(data, OPTIONS_DATA_SLOT);
}

options::OptionsData options::load() {
	OptionsData data{};

	bool save_found = read_save(data, OPTIONS_DATA_SLOT);

	//If not exists, set default values
	if (!save_found) {
		data = {
			0,
			false
		};
	}

	return data;
}
