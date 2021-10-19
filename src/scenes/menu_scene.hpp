//
// Created by daniel on 17.10.21.
//

#pragma once
#include "../utils/utils.hpp"
#include "../ui/controls/listbox.hpp"
#include "scene_interface.hpp"

class MenuScene : public IScene {
public:
	explicit MenuScene();
	~MenuScene() override;
	void render(uint32_t time) override;
	void update(uint32_t time) override;

	struct MenuData {
		uint8_t save_count;
		bool show_fps;
	};

private:
	const uint8_t MAX_SAVES = 3;
	uint8_t saves_count;
	bool show_fps;
	std::vector<Listbox::Item> saves;
	uint32_t last_buttons;
	uint32_t changed;
	Listbox *listbox;

	void create_list_entries();
	void save_menu_data();
	void load_menu_data();
};
