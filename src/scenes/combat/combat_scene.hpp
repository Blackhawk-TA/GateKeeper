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
		explicit Scene(map::MapSections map_section);
		~Scene() override;
		void render(uint32_t time) override;
		void update(uint32_t time) override;
		void inputs() override;

	private:
		map::MapSections map_section;
		Enemy *enemy;
		CombatPlayer *player;

		void load_combat_scene();
	};
}