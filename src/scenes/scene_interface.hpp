//
// Created by D069765 on 18.10.2021.
//

#pragma once
#include <iostream>
#include "../utils/utils.hpp"

class IScene {
public:
	virtual ~IScene() = default;
	virtual void render(uint32_t time) = 0;
	virtual void update(uint32_t time) = 0;
};
