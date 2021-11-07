//
// Created by daniel on 07.11.21.
//

#include "carrot_bed_handler.hpp"
#include "../../../game_objects/template/game_object.hpp"
#include "../../../game_objects/carrot_bed.hpp"
#include "../game_object_handler.hpp"

std::vector<CarrotBed*> carrot_beds;

void carrot_bed_handler::init() {
	std::vector<GameObject*> game_object_collection = game_objects::get_collection();

	for (GameObject* game_object : game_object_collection) {
		if (game_object->get_type() == GameObject::CarrotBedType) {
			carrot_beds.push_back((CarrotBed*)game_object);
		}
	}
}

void carrot_bed_handler::cleanup() {
	//Points don't have to be deleted here since this is done in game_objects cleanup
	carrot_beds.clear();
}

bool carrot_bed_handler::plant() {
	bool planted = false;
	uint8_t i = 0;

	while (!planted && i < carrot_beds.size()) {
		if (carrot_beds[i]->plant()) {
			planted = true;
		}
		i++;
	}

	return planted;
}
