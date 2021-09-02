//
// Created by daniel on 02.09.21.
//

#pragma once
#include "utils/utils.hpp"

using namespace blit;

/**
 * Connects the building with their interior by linking the coordinates on the specific tile maps.
 */
namespace interior_connector {
	Point teleport(uint8_t building_id, Point position);
}
