//
// Created by daniel on 16.04.22.
//

#include "save_converter.hpp"
#include "../save_types.hpp"
#include "legacy_option_structs.hpp"
#include "legacy_game_structs.hpp"
#include "../options.hpp"

namespace save_converter {
	/**
	 * Updates the options save file by parsing the v0 into the v1 struct.
	 * If no save is found, nothing is updated.
	 * @return The amount of game saves that have to be updated
	 */
	uint8_t update_options_v0_v1() {
		OptionsDataV0 old_version{};

		bool found = read_save(old_version, options::OPTIONS_DATA_SLOT);
		if (found) { //If no save is found, nothing will be updated
			save::OptionsData new_version = {
				old_version.save_count,
				old_version.show_fps,
				old_version.show_time,
				0,
			};

			write_save(new_version, options::OPTIONS_DATA_SLOT);
		}

		return old_version.save_count;
	}

	/**
	 * Updates the game save files by parsing the v0 into the v1 struct.
	 * If no save is found, nothing is updated.
	 * @param save_count The amount of saves that have to be updated
	 */
	void update_game_v0_v1(uint8_t save_count) {
		//Store saves in heap instead of stack due to limit space on PicoSystem
		auto *old_version = new SaveDataV0{};
		auto *new_version = new save::SaveData{};
		uint8_t save_slot;

		for (uint8_t i = 0; i < save_count; i++) {
			save_slot = i + 1;

			bool found = read_save(*old_version, save_slot);
			if (found) { //If no save is found, nothing will be updated
				*new_version = {
					old_version->map_section,
					old_version->camera_position,
					old_version->previous_camera_position,
					old_version->player_data,
					old_version->game_objects,
					old_version->items,
					old_version->passed_time,
				};
				write_save(*new_version, save_slot);
			}
		}

		delete old_version;
		delete new_version;
	}

	void update_save_structs() {
		Versions versions = {};
		uint8_t save_count = 0;

		bool found = read_save(versions, VERSION_SAVE_ID);
		if (!found) {
			versions = {0, 0};
		}

		//Convert options save struct to latest version
		if (versions.options != OPTIONS_SAVE_VERSION) {
			save_count = update_options_v0_v1();
			versions.options = OPTIONS_SAVE_VERSION;
		}

		//Convert game save struct to the latest version
		if (versions.game != GAME_SAVE_VERSION) {
			update_game_v0_v1(save_count);
			versions.game = GAME_SAVE_VERSION;
		}

		write_save(versions, VERSION_SAVE_ID);
	}
}
