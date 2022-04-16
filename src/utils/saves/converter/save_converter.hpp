//
// Created by daniel on 16.04.22.
//

#pragma once
#include "../../utils.hpp"

namespace save_converter {
	struct Versions {
		uint16_t options;
		uint16_t game;
	};

	//The current save versions. They must be updated when a save struct is changed
	const uint16_t OPTIONS_SAVE_VERSION = 1;
	const uint16_t GAME_SAVE_VERSION = 1;

	/**
	 * Checks if version file exists and uses it to update the options and game structs if necessary.
	 * If no version file is found, version 0 is assumed and it is tried to update to the latest version.
	 */
	void update_save_structs();
}
