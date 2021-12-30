#pragma once
#include "32blit.hpp"
#include "engine/map.hpp"

enum SceneType {
	MENU = 1,
	GAME = 2,
	OPTIONS = 3,
	COMBAT = 4,
};

struct CharacterData {
	std::array<uint16_t, ANIMATION_SPRITE_COUNT> movement_sprites;
	uint8_t health;
	uint8_t level;
};

struct CombatData {
	map::MapSections map_section;
	CharacterData player;
	CharacterData enemy;
};

void load_previous_scene(uint8_t save_id = 0);
void load_scene(SceneType scene_type, uint8_t save_id = 0, CombatData combat_data = {});
