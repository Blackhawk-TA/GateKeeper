//
// Created by D069765 on 20.10.2021.
//

#include "options.hpp"
#include "save_types.hpp"

namespace options {
	bool show_fps = false;
	bool show_time = false;
	uint8_t save_count = 0;
	uint8_t active_tmp_save = 0;

	void save() {
		save::OptionsData data = {
			0, //TODO has new version, needs conversion
			save_count,
			show_fps,
			show_time,
			active_tmp_save,
		};

		write_save(data, OPTIONS_DATA_SLOT);
	}

	void load() {
		save::OptionsData data{};

		bool save_found = read_save(data, OPTIONS_DATA_SLOT);

		if (save_found) {
			save_count = data.save_count;
			show_fps = data.show_fps;
			show_time = data.show_time;
			active_tmp_save = data.active_tmp_save;
		} else {
			save_count = 0;
			show_fps = false;
			show_time = false;
			active_tmp_save = 0;
		}
	}
}