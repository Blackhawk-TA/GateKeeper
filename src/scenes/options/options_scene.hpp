//
// Created by D069765 on 20.10.2021.
//

#pragma once
#include "../../utils/utils.hpp"
#include "../scene_interface.hpp"
#include "../../engine/ui/listbox.hpp"

namespace options {
	class Scene : public IScene {
	public:
		explicit Scene(uint8_t save_id = 0);
		~Scene() override;
		void render(uint32_t time) override;
		void update(uint32_t time) override;
		void inputs() override;

	private:
		std::vector<Listbox::Item> option_items;
		uint8_t save_id;
		uint32_t last_buttons;
		uint32_t changed;
		Listbox *listbox;
	};
}
