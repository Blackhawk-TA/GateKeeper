//
// Created by daniel on 17.10.21.
//

#pragma once
#include "utils/utils.hpp"
#include "assets.hpp"
#include "engine/camera.hpp"
#include "engine/map.hpp"
#include "ui/overlay.hpp"
#include "player.hpp"
#include "engine/transition.hpp"
#include "engine/flags.hpp"
#include "handlers/stargate_handler.hpp"
#include "ui/sidemenu.hpp"
#include "ui/inventory.hpp"
#include "items/items.hpp"
#include "utils/savegame.hpp"

class GameScene {
public:
	explicit GameScene();
	~GameScene();
	void render(uint32_t time);
	void update(uint32_t time);

private:
	uint32_t last_buttons;
	uint32_t changed;
	uint32_t ms_start;
	uint32_t ms_end;
	Player *player;
};
