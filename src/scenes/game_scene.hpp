//
// Created by daniel on 17.10.21.
//

#pragma once
#include "../utils/utils.hpp"
#include "assets.hpp"
#include "../engine/camera.hpp"
#include "../engine/map.hpp"
#include "../ui/overlay.hpp"
#include "../player.hpp"
#include "../engine/transition.hpp"
#include "../engine/flags.hpp"
#include "../handlers/stargate_handler.hpp"
#include "../ui/sidemenu.hpp"
#include "../ui/inventory.hpp"
#include "../items/items.hpp"
#include "../utils/savegame.hpp"
#include "scene_interface.hpp"

class GameScene : public IScene {
public:
	explicit GameScene(uint8_t save_id);
	~GameScene() override;
	void render(uint32_t time) override;
	void update(uint32_t time) override;

private:
	uint8_t save_id;
	uint32_t last_buttons;
	uint32_t changed;
	uint32_t ms_start;
	uint32_t ms_end;
	Player *player;
};
