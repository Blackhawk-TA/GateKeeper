//
// Created by D069765 on 20.10.2021.
//

#include "options.hpp"
#include "save_types.hpp"

namespace options {
	bool show_fps = false;
	uint8_t save_count = 0;

	void save() {
		save::OptionsData data = {
			save_count,
			show_fps
		};

		write_save(data, OPTIONS_DATA_SLOT);
	}

	void load() {
		save::OptionsData data{};

		bool save_found = read_save(data, OPTIONS_DATA_SLOT);

		if (save_found) {
			save_count = data.save_count;
			show_fps = data.show_fps;
		} else {
			save_count = 0;
			show_fps = false;
		}
	}
}