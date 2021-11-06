//
// Created by daniel on 17.10.21.
//

#pragma once
#include "../../utils/utils.hpp"
#include "assets.hpp"
#include "../scene_interface.hpp"
#include "characters/player.hpp"

class GameScene : public IScene {
public:
	explicit GameScene(uint8_t save_id);
	~GameScene() override;
	void render(uint32_t time) override;
	void update(uint32_t time) override;
	void inputs() override;

private:
	uint8_t save_id;
	uint32_t last_buttons;
	uint32_t changed;
	Player *player;
};