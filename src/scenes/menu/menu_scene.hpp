//
// Created by daniel on 17.10.21.
//

#pragma once
#include "../../utils/utils.hpp"
#include "../scene_interface.hpp"
#include "../../engine/ui/listbox.hpp"

class MenuScene : public IScene {
public:
	explicit MenuScene();
	~MenuScene() override;
	void render(uint32_t time) override;
	void update(uint32_t time) override;
	void inputs() override;

private:
	std::vector<Listbox::Item> saves;
	uint32_t last_buttons;
	uint32_t changed;
	Listbox *listbox;

	void create_list_entries();
};