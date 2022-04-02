//
// Created by daniel on 02.04.22.
//

#pragma once
#include "../../../utils/game_time.hpp"

namespace game::notification {
	enum Icon {
		NO_ICON = 0,
		SAVE = 1761,
	};

	//TODO use template instead of struct for queue
	struct Notification {
		uint16_t tile_id;
		std::string message;
	};

	/**
	 * Adds an icon to the notification
	 * @param icon The enum of the icon which should be shown. The value of the enum represents the tile id of the icon.
	 */
	void add_to_queue(Icon icon);

	/**
	 * Adds a message to the notification queue
	 * @param message The message that should be shown as notification
	 */
	void add_to_queue(std::string message);

	/**
	 * Draws the current notification to the screen.
	 * Checks if a notification can be displayed and handles the notification queue.
	 */
	void draw();

	/**
	 * Cleanup the notifications when leaving the scene.
	 */
	void cleanup();
}
