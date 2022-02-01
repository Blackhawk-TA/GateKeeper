//
// Created by daniel on 06.01.22.
//

#pragma once

#include "../scene_interface.hpp"
#include "../../utils/types.hpp"
#include "../../engine/ui/textbox.hpp"

namespace gameover {
	class Scene : public IScene {
	public:
		explicit Scene(const SceneOptions& options);
		~Scene() override;
		void render(uint32_t time) override;
		void update(uint32_t time) override;
		void inputs() override;

	private:
		Textbox *textbox;
		uint8_t save_id;
		uint32_t last_buttons;
		uint32_t changed;
	};
}
