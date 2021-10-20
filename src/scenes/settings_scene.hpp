//
// Created by D069765 on 20.10.2021.
//

#pragma once
#include "../utils/utils.hpp"
#include "scene_interface.hpp"
#include "../ui/controls/listbox.hpp"

class SettingsScene : public IScene {
public:
	explicit SettingsScene();
	~SettingsScene();
	void render(uint32_t time) override;
	void update(uint32_t time) override;

private:
	std::vector<Listbox::Item> settings_items;
	uint32_t last_buttons;
	uint32_t changed;
	Listbox *listbox;
};
