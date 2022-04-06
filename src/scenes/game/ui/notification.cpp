//
// Created by daniel on 02.04.22.
//

#include "notification.hpp"
#include <utility>

namespace game::notification {
	const uint16_t DISPLAY_TIME_MS = 2000;
	uint32_t last_notification_time = 0;
	Notification *current_notification = nullptr;
	std::queue<Notification> queue;

	void cleanup() {
		last_notification_time = 0;
		std::queue<Notification>().swap(queue); //Empty queue by swapping it with empty one
		current_notification = nullptr; //Point must not be deleted because it is already done while emptying the queue
	}

	void add_to_queue(Icon icon) {
		queue.push(Notification{
			static_cast<uint16_t>(icon),
			""
		});
	}

	void add_to_queue(std::string message) {
		queue.push({
			NO_ICON,
			std::move(message),
		});
	}

	void draw() {
		//Trigger next notification and end existing
		if (last_notification_time == 0 || game_time::get_time() > last_notification_time + DISPLAY_TIME_MS) {
			if (queue.empty()) {
				current_notification = nullptr;
			} else {
				last_notification_time = game_time::get_time();
				current_notification = &queue.front();
				queue.pop();
			}
		}

		if (current_notification == nullptr) return;

		if (!current_notification->message.empty()) { //Message notification
			screen.pen = Pen(255, 255, 255, 255);
			screen.text(current_notification->message, minimal_font, Rect(1, 13, 10, 10), false, TextAlign::left);
		} else if (current_notification->tile_id != NO_ICON) { //Icon notification
			Size spritesheet_size = get_spritesheet_size(screen.sprites->bounds);
			screen.blit(
				screen.sprites,
				Rect(
					(current_notification->tile_id & (spritesheet_size.w - 1)) * TILE_SIZE,
					(current_notification->tile_id / spritesheet_size.h) * TILE_SIZE,
					TILE_SIZE,
					TILE_SIZE
				),
				Point(1, 13)
			);
		}
	}
}
