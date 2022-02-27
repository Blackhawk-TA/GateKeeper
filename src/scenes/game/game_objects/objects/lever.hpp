//
// Created by daniel on 19.12.21.
//

#pragma once
#include "../template/game_object.hpp"

namespace game {
	class Lever : public GameObject {
	public:
		explicit Lever(map::MapSection map_section, Point position, Signature interaction_object, bool working);
		~Lever() override = default;
		bool player_interact() override;
		ObjectType get_type() override;

	private:
		enum State {
			ON = 1,
			OFF = 2,
		};

		State state;

		const uint16_t TILE_ID_ON = 957;
		const uint16_t TILE_ID_OFF = 1021;

		bool working; //Shows if this lever as a function or is just a dummy
		Signature interaction_object; //The GameObjects signature with which the lever interacts with

		void set_state(uint8_t new_state) override;
	};
}
