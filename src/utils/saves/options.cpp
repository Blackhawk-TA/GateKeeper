//
// Created by D069765 on 20.10.2021.
//

#include "options.hpp"
#include "../../ui/overlay.hpp"

bool options::show_fps = false;
uint8_t options::save_count = 0;

void options::save() {
	OptionsData data = {
		save_count,
		show_fps
	};

	write_save(data, OPTIONS_DATA_SLOT);
}

void options::load() {
	OptionsData data{};

	bool save_found = read_save(data, OPTIONS_DATA_SLOT);

	if (save_found) {
		save_count = data.save_count;
		show_fps = data.show_fps;
	}
}
