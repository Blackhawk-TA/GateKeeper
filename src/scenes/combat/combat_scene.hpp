//
// Created by daniel on 25.12.21.
//

#pragma once
#include "../scene_interface.hpp"
#include "../../engine/map.hpp"
#include "characters/enemy.hpp"
#include "characters/player.hpp"

namespace combat {
	class Scene : public IScene {
	public:
		explicit Scene(SceneOptions options);
		~Scene() override;
		void render(uint32_t time) override;
		void update(uint32_t time) override;
		void inputs() override;

	private:
		map::MapSection map_section;
		uint32_t last_buttons;
		uint32_t changed;
		Enemy *enemy;
		Player *player;

		void load_combat_scene();
	};
}