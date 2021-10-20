//
// Created by D069765 on 20.10.2021.
//

#pragma once
#include "../utils/utils.hpp"
#include "scene_interface.hpp"
#include "../ui/controls/listbox.hpp"

class OptionsScene : public IScene {
public:
	explicit OptionsScene(uint8_t save_id = 0);
	~OptionsScene() override;
	void render(uint32_t time) override;
	void update(uint32_t time) override;
	void inputs() override;

private:
	std::vector<Listbox::Item> option_items;
	uint32_t last_buttons;
	uint32_t changed;
	Listbox *listbox;
};
