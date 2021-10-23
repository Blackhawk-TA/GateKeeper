//
// Created by daniel on 21.09.21.
//

#pragma once
#include "../../utils/utils.hpp"

class Box {
public:
	explicit Box(Rect rect);
	void draw() const;
	void set_visibility(bool value);

	static Rect set_bounds(Rect &r);

private:
	const uint16_t sprite_id_top_left = 1679;
	const uint16_t sprite_id_top_center = 1680;
	const uint16_t sprite_id_top_right = 1681;
	const uint16_t sprite_id_center_left = 1743;
	const uint16_t sprite_id_center_center = 1744;
	const uint16_t sprite_id_center_right = 1745;
	const uint16_t sprite_id_bottom_left = 1807;
	const uint16_t sprite_id_bottom_center = 1808;
	const uint16_t sprite_id_bottom_right = 1809;

	Rect rect;
	bool visible;
	Size spritesheet_size;
};
