//
// Created by daniel on 25.12.21.
//

#pragma once
#include "../scene_interface.hpp"
#include "../../engine/map.hpp"

class CombatScene : public IScene {
public:
	explicit CombatScene(map::MapSections map_section);
	~CombatScene() override;
	void render(uint32_t time) override;
	void update(uint32_t time) override;
	void inputs() override;

private:
	map::MapSections map_section;

	void load_combat_scene();
};
