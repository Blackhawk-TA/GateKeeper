//
// Created by daniel on 17.10.21.
//

#pragma once
#include "utils/utils.hpp"
#include "ui/controls/listbox.hpp"

class MenuScene {
public:
	explicit MenuScene();
	~MenuScene();
	void render(uint32_t time);
	void update(uint32_t time);

private:
	uint32_t last_buttons;
	uint32_t changed;
	uint8_t save_id;
	Listbox *listbox;
	Textbox *textbox;
};
