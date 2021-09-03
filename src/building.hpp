//
// Created by daniel on 02.09.21.
//

#pragma once
#include "utils/utils.hpp"

using namespace blit;

/**
 * Connects the buildings with their interior by linking the coordinates on the specific tile maps.
 */
namespace building {
	struct Door {
		Point exterior;
		Point interior;
	};

	constexpr Door connections[] = {
			Door{Point(19, 15), Point(15, 13)}
	};
}
