//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include <iostream>
#include "assets.hpp"
#include "map.hpp"
#include "flags.hpp"
#include "camera.hpp"
#include "engine/fast_code.hpp"

using namespace blit;

map::TileMap tile_map;
map::MapSection current_section;
Point screen_tiles;
Size spritesheet_size;
Pen background;

map::TileMap map::precalculate_tile_data(map::TMX_16 *tmx) {
	std::vector<map::Tile> tile_data;
	std::vector<map::TreeTile> tree_data;
	uint16_t tile_id, i;
	uint8_t tile_range, tree_repetitions;
	uint8_t tile_x = 0;
	uint8_t tile_y = 0;
	uint16_t data_length = tmx->data[0]; //First array entry is the array length
	bool is_tree_layer = false;

	//Skip first layer because it only contains the array length
	for (i = 1u; i < data_length; i += 2) {
		//Extract current tile id from tmx data
		tile_range = tmx->data[i];
		tile_id = tmx->data[i + 1];

		//Detect tree layer start and end and toggle the is_tree_layer variable.
		if (tile_range == 255 && tile_id == 65355) {
			is_tree_layer ^= true;
			tile_x = 0; //Reset tile positions for next layer
			tile_y = 0;
			continue; //Don't add tree layer markers to tile_data
		}

		if (is_tree_layer) {
			tile_id = tmx->data[i];
			tile_x = tmx->data[i + 1];
			tile_y = tmx->data[i + 2];
			tree_repetitions = tmx->data[i + 3];

			tree_data.push_back(TreeTile{
				tile_x,
				tile_y,
				tree_repetitions,
				tile_id,
			});
			i += 2; //Skip the next 2 loop iterations since tree layers use quadruples instead of tuples
		} else {
			if (tile_id != tmx->empty_tile) {
				//Save first tile in row of equals and its position.
				tile_data.push_back(Tile{
					tile_x,
					tile_y,
					flags::get_flag(tile_id),
					tile_range,
					static_cast<uint16_t>((tile_id % spritesheet_size.w) * TILE_SIZE),
					static_cast<uint16_t>((tile_id / spritesheet_size.h) * TILE_SIZE),
				});
			}

			tile_x = (((tile_y + tile_range + 1) / tmx->height) + tile_x) & (tmx->width - 1);
			tile_y = (tile_y + tile_range + 1) & (tmx->height - 1);
		}
	}

	return map::TileMap{
		tmx->empty_tile,
		static_cast<uint8_t>(tmx->width),
		static_cast<uint8_t>(tmx->height),
		static_cast<uint8_t>(tmx->layers),
		tile_data,
		tree_data
	};
}

void map::load_section(MapSection map_section) { //TODO make sure only map data is in memory when loading new section
	map::TMX_16 *tmx = nullptr;

	//Allocate memory for TileMap and copy it into memory
	switch (map_section) {
		case MapSection::DUNGEON:
			tmx = (TMX_16 *) malloc(asset_dungeon_map_length);
			memcpy(tmx, asset_dungeon_map, asset_dungeon_map_length);
			background = Pen(48, 44, 46);
			break;
		case MapSection::GRASSLAND:
			tmx = (TMX_16 *) malloc(asset_grassland_map_length);
			memcpy(tmx, asset_grassland_map, asset_grassland_map_length);
			background = Pen(113, 170, 52);
			break;
		case MapSection::GRASSLAND_COMBAT:
			tmx = (TMX_16 *) malloc(asset_grassland_combat_map_length);
			memcpy(tmx, asset_grassland_combat_map, asset_grassland_combat_map_length);
			background = Pen(113, 170, 52);
			break;
		case MapSection::INTERIOR:
			tmx = (TMX_16 *) malloc(asset_interior_map_length);
			memcpy(tmx, asset_interior_map, asset_interior_map_length);
			background = Pen(48, 44, 46);
			break;
		case MapSection::SNOWLAND:
			tmx = (TMX_16 *) malloc(asset_snowland_map_length);
			memcpy(tmx, asset_snowland_map, asset_snowland_map_length);
			background = Pen(223, 246, 245);
			break;
		case MapSection::DESERT:
			tmx = (TMX_16 *) malloc(asset_desert_map_length);
			memcpy(tmx, asset_desert_map, asset_desert_map_length);
			background = Pen(244, 204, 161);
			break;
		case MapSection::VOLCANO:
			tmx = (TMX_16 *) malloc(asset_volcano_map_length);
			memcpy(tmx, asset_volcano_map, asset_volcano_map_length);
			background = Pen(244, 180, 27);
			break;
		case MapSection::DUNGEON_COMBAT:
			tmx = (TMX_16 *) malloc(asset_dungeon_combat_map_length);
			memcpy(tmx, asset_dungeon_combat_map, asset_dungeon_combat_map_length);
			background = Pen(60, 89, 86);
			break;
		case MapSection::VOLCANO_COMBAT:
			tmx = (TMX_16 *) malloc(asset_volcano_combat_map_length);
			memcpy(tmx, asset_volcano_combat_map, asset_volcano_combat_map_length);
			background = Pen(244, 180, 27);
			break;
		case MapSection::SNOWLAND_COMBAT:
			tmx = (TMX_16 *) malloc(asset_snowland_combat_map_length);
			memcpy(tmx, asset_snowland_combat_map, asset_snowland_combat_map_length);
			background = Pen(223, 246, 245);
			break;
		case MapSection::DESERT_COMBAT:
			tmx = (TMX_16 *) malloc(asset_desert_combat_map_length);
			memcpy(tmx, asset_desert_combat_map, asset_desert_combat_map_length);
			background = Pen(244, 204, 161);
			break;
		case MapSection::CASTLE:
			tmx = (TMX_16 *) malloc(asset_castle_map_length);
			memcpy(tmx, asset_castle_map, asset_castle_map_length);
			background = Pen(48, 44, 46);
			break;
		case MapSection::CASTLE_COMBAT:
			tmx = (TMX_16 *) malloc(asset_castle_combat_map_length);
			memcpy(tmx, asset_castle_combat_map, asset_castle_combat_map_length);
			background = Pen(48, 44, 46);
			break;
		case MapSection::TOWER:
			tmx = (TMX_16 *) malloc(asset_tower_map_length);
			memcpy(tmx, asset_tower_map, asset_tower_map_length);
			background = Pen(48, 44, 46);
			break;
		case MapSection::TOWER_COMBAT:
			tmx = (TMX_16 *) malloc(asset_tower_combat_map_length);
			memcpy(tmx, asset_tower_combat_map, asset_tower_combat_map_length);
			background = Pen(48, 44, 46);
			break;
		case MapSection::WATER_DUNGEON:
			tmx = (TMX_16 *) malloc(asset_water_dungeon_map_length);
			memcpy(tmx, asset_water_dungeon_map, asset_water_dungeon_map_length);
			background = Pen(0, 0, 0);
			break;
		case MapSection::WATER_DUNGEON_COMBAT:
			tmx = (TMX_16 *) malloc(asset_water_dungeon_combat_map_length);
			memcpy(tmx, asset_water_dungeon_combat_map, asset_water_dungeon_combat_map_length);
			background = Pen(0, 0, 0);
			break;
		default:
			std::cerr << "Invalid map section" << std::endl;
			exit(1);
	}

	if (tmx != nullptr) {
		screen_tiles = get_screen_tiles();
		spritesheet_size = get_spritesheet_size(screen.sprites->bounds);

		current_section = map_section;

		tile_map = precalculate_tile_data(tmx);

		//Remove tmx struct from memory because it's only required for the pre-calculations
		free(tmx);
	}
}

void map::draw() {
	screen.pen = background;
	screen.rectangle(Rect(0, 0, screen.bounds.w, screen.bounds.h));

	Point camera_position = camera::get_screen_position();

	blit_fast_code(draw_tiles(camera_position));
	draw_trees(camera_position);
}

void map::draw_tiles(Point camera_position) {
	uint16_t i, r, tile_x, tile_y;
	Point camera_position_world = screen_to_world(camera_position);

	for (i = 0u; i < tile_map.data.size(); i++) {
		tile_x = tile_map.data[i].x;

		for (r = 0u; r <= tile_map.data[i].range; r++) {
			tile_y = (tile_map.data[i].y + r) & (tile_map.height - 1); //Equal to modulo operator but faster, only works with powers of 2

			//Checks if tile is visible on screen
			if (camera_position_world.x <= tile_x && camera_position_world.y <= tile_y
			    && screen_tiles.x + camera_position_world.x - tile_x >= 0
			    && screen_tiles.y + camera_position_world.y - tile_y >= 0) {
				screen.blit(
					screen.sprites,
					Rect(tile_map.data[i].sprite_rect_x, tile_map.data[i].sprite_rect_y, TILE_SIZE, TILE_SIZE),
					Point(tile_x * TILE_SIZE, tile_y * TILE_SIZE) - camera_position
				);
			}

			//Increment tile_x for next loop if tile_y hits upper limit
			if (tile_y == tile_map.height - 1) {
				tile_x++;
			}
		}
	}

}

void map::draw_trees(Point camera_position) {
	Point sprite_rect_pos;
	Rect tree_rect; //Contains the position on the map and the size of the tree
	Size tree_size;
	TreePartSizes tree_part_sizes = {};
	uint16_t i, h_offset, tree_x_px, tree_y_px;
	uint8_t r;

	for (i = 0u; i < tile_map.tree_data.size(); i++) {
		tree_x_px = tile_map.tree_data[i].x * TILE_SIZE; //The x position of the tree top in px
		tree_y_px = tile_map.tree_data[i].y * TILE_SIZE; //The y position of the tree top in px

		//Render entire tree because there are no repetitions
		if (tile_map.tree_data[i].range == 0) {
			tree_size = tree_map.at(tile_map.tree_data[i].tile_id);
			tree_rect = Rect(tree_x_px, tree_y_px, tree_size.w, tree_size.h);

			//Don't render tree when it is out of view
			if (!rect_in_view(tree_rect, camera_position)) continue;

			sprite_rect_pos = get_sprite_rect_pos(tile_map.tree_data[i].tile_id);
			screen.blit(
				screen.sprites,
				Rect(sprite_rect_pos.x, sprite_rect_pos.y, tree_rect.w, tree_rect.h),
				Point(tree_x_px, tree_y_px) - camera_position
			);
			continue;
		}

		//Get the sizes of the individual tree parts
		tree_part_sizes = tree_part_map.at(tile_map.tree_data[i].tile_id);
		tree_rect = Rect(tree_x_px, tree_y_px, tree_part_sizes.top.w, tree_part_sizes.top.h);

		//Render tree top
		if (rect_in_view(tree_rect, camera_position)) {
			sprite_rect_pos = get_sprite_rect_pos(tree_part_sizes.top.tile_id);
			screen.blit(
				screen.sprites,
				Rect(sprite_rect_pos.x, sprite_rect_pos.y, tree_rect.w, tree_rect.h),
				Point(tree_x_px, tree_y_px) - camera_position
			);
		}
		h_offset = tree_part_sizes.top.h;

		//Render tree center repetitions
		sprite_rect_pos = get_sprite_rect_pos(tree_part_sizes.center.tile_id);

		for (r = 0u; r < tile_map.tree_data[i].range; r++) {
			tree_rect = Rect(tree_x_px, tree_y_px + h_offset, tree_part_sizes.center.w, tree_part_sizes.center.h);
			if (rect_in_view(tree_rect, camera_position)) {
				screen.blit(
					screen.sprites,
					Rect(sprite_rect_pos.x, sprite_rect_pos.y, tree_rect.w, tree_rect.h),
					Point(tree_x_px, tree_y_px + h_offset) - camera_position
				);
			}
			h_offset += tree_part_sizes.center.h;
		}

		//Render tree bottom
		tree_rect = Rect(tree_x_px, tree_y_px + h_offset, tree_part_sizes.bottom.w, tree_part_sizes.bottom.h);
		if (rect_in_view(tree_rect, camera_position)) {
			sprite_rect_pos = get_sprite_rect_pos(tree_part_sizes.bottom.tile_id);
			screen.blit(
				screen.sprites,
				Rect(sprite_rect_pos.x, sprite_rect_pos.y, tree_rect.w, tree_rect.h),
				Point(tree_x_px, tree_y_px + h_offset) - camera_position
			);
		}
	}
}

uint8_t map::get_flag(Point &p) {
	uint16_t i, tree_x_px, tree_y_px, tree_cluster_h;
	uint8_t flag_enum_id = 0;
	uint8_t tile_max_x, tile_max_y, r;
	Size tree_cluster_size;
	Rect tree_cluster;
	TreePartSizes tree_part_sizes = {};
	bool found = false;

	//Get flag of tree tile. Executed before tile flag check because the tree layer is always the highest layer
	i = tile_map.tree_data.size();
	while (i > 0 && !found) {
		i--;
		tree_x_px = tile_map.tree_data[i].x * TILE_SIZE; //The x position of the tree top in px
		tree_y_px = tile_map.tree_data[i].y * TILE_SIZE; //The y position of the tree top in px

		if (tile_map.tree_data[i].range == 0) { //Collision for single tree
			tree_cluster_size = tree_map.at(tile_map.tree_data[i].tile_id);
		} else { //Collision for tree clusters
			tree_part_sizes = tree_part_map.at(tile_map.tree_data[i].tile_id);

			//Add cluster top, only height is required since tree cluster width is always 1 tree
			tree_cluster_h = tree_part_sizes.top.h;

			//Add cluster repetitions
			for (r = 0u; r < tile_map.tree_data[i].range; r++) {
				tree_cluster_h += tree_part_sizes.center.h;
			}

			//Add cluster bottom
			tree_cluster_h += tree_part_sizes.bottom.h;

			tree_cluster_size = Size(tree_part_sizes.top.w, tree_cluster_h);
		}

		tree_cluster = Rect(tree_x_px, tree_y_px, tree_cluster_size.w, tree_cluster_size.h);
		if (tree_cluster.contains(p * TILE_SIZE)) {
			flag_enum_id = flags::TileFlags::TREE;
			found = true;
		}
	}

	//Get flag of a tile
	i = tile_map.data.size();
	while (i > 0 && !found) {
		i--;
		tile_max_x = tile_map.data[i].x + (tile_map.data[i].y + tile_map.data[i].range) / tile_map.width;
		tile_max_y = (tile_map.data[i].y + tile_map.data[i].range) & (tile_map.height - 1);

		if (point_in_area(p, tile_map.data[i].x, tile_map.data[i].y, tile_max_x, tile_max_y)) {
			flag_enum_id = tile_map.data[i].flag;
			found = true;
		}
	}

	//If tile is not found it is an empty tile and therefore should be walkable
	if (!found) {
		flag_enum_id = flags::WALKABLE;
	}

	return flag_enum_id;
}

map::MapSection map::get_section() {
	return current_section;
}

bool map::point_in_area(Point &p, uint8_t min_x, uint8_t min_y, uint8_t max_x, uint8_t max_y) {
	return ((p.x == min_x && p.y >= min_y) || p.x > min_x) &&
	       ((p.x == max_x && p.y <= max_y) || p.x < max_x);
}

Point map::get_sprite_rect_pos(uint16_t tile_id) {
	return Point(
		static_cast<uint16_t>((tile_id % spritesheet_size.w) * TILE_SIZE),
		static_cast<uint16_t>((tile_id / spritesheet_size.h) * TILE_SIZE)
	);
}

bool map::rect_in_view(Rect rect, Point camera_position) {
	Rect view = Rect(camera_position.x, camera_position.y, screen.bounds.w, screen.bounds.h);
	return view.intersects(rect);
}
