//
// Created by daniel on 17.10.21.
//

#pragma once
#include "../../utils/utils.hpp"
#include "assets.hpp"
#include "../scene_interface.hpp"
#include "game_objects/player.hpp"

namespace game {
	class Scene : public IScene {
	public:
		explicit Scene(const SceneOptions& options);
		~Scene() override;
		void render(uint32_t time) override;
		void update(uint32_t time) override;
		void inputs() override;

	private:
		uint8_t save_id;
		uint32_t last_buttons;
		uint32_t changed;
	};
}