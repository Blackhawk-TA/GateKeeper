//
// Created by daniel on 28.02.21.
//

#pragma once

#include <list>
#include "../utils/utils.hpp"

using namespace blit;

namespace map {
	enum MapSection {
		NO_MAP = 0,
		DUNGEON = 1,
		GRASSLAND = 2,
		INTERIOR = 3,
		SNOWLAND = 4,
		DESERT = 5,
		DUNGEON_COMBAT = 6,
		VOLCANO = 7,
		VOLCANO_COMBAT = 8,
		SNOWLAND_COMBAT = 9,
		DESERT_COMBAT = 10,
		GRASSLAND_COMBAT = 11,
		CASTLE = 12,
		CASTLE_COMBAT = 13,
	};

	//Stores information of a tile and how often it appears in repetition
	struct Tile {
		uint8_t x;
		uint8_t y;
		uint8_t flag;
		uint8_t range;
		uint16_t sprite_rect_x;
		uint16_t sprite_rect_y;
	};

	//Stores information of the tree clusters that are rendered
	struct TreeTile {
		uint8_t x;
		uint8_t y;
		uint8_t range;
		uint16_t tile_id;
	};

	struct Tree{
		uint16_t tile_id;
		uint8_t w; //width in pixels
		uint8_t h; //height in pixels
	};

	struct TreePartSizes {
		Tree top;
		Tree center;
		Tree bottom;
	};

	#pragma pack(push,1)
	struct TMX_16 {
		char head[4];
		uint16_t header_length;
		uint16_t flags;
		uint16_t empty_tile;
		uint16_t width;
		uint16_t height;
		uint16_t layers;
		uint16_t data[];
	};
	#pragma pack(pop)

	struct TileMap {
		uint16_t emtpy_tile;
		uint8_t width;
		uint8_t height;
		uint8_t layers;
		std::vector<map::Tile> data;
		std::vector<map::TreeTile> tree_data;
	};

	// A map containing the size of an entire tree. The index is the top left corner tile id of the tree.
	const std::map<uint16_t, Size> tree_map = {
		{2904, Size(48, 48)}, // 3x3 green tree full
		{2907, Size(48, 48)}, // 3x3 fancy green tree full
		{2910, Size(32, 48)}, // 2x3 round green tree full
		{3216, Size(32, 48)}, // 2x3 fir green tree full
	};

	// A map containing the sizes of the individual tree parts indexed by their top left tile id.
	const std::map<uint16_t, TreePartSizes> tree_part_map = {
		{2904, {{2904, 48, 16}, {3096, 48, 32}, {2968, 48, 32}}}, //3x3 green tree
		{2907, {{2907, 48, 16}, {3099, 48, 32}, {2971, 48, 32}}}, //3x3 fancy green tree
		{2910, {{2910, 32, 16}, {3102, 32,32}, {2974, 32, 32}}}, //2x3 fir green tree
		{3216, {{3216, 32, 16}, {3218, 32,32}, {3280, 32, 32}}}, //2x3 round green tree
	};

	/**
	 * Parses the tmx struct into a tile map struct with render optimized tile_data
	 * @param tmx The TMX struct which contains the data directly extracted from the tilemap file
	 * @return The rendering and memory optimized TileMap struct
	 */
	TileMap precalculate_tile_data(TMX_16 *tmx);

	/**
	 * Loads new map section into memory and deletes the old one
	 * @param map_section The enum describing the map section
	 */
	void load_section(MapSection map_section);

	/**
	 * Draws the tile map to the screen if a TileMap is loaded in the memory
	 * @param camera_position The position of the camera on the TileMap
	 */
	void draw();

	/**
	 * Gets the id of a tile at a specific Point on the map.
	 * Always selects the tile on the highest layer if several tiles overlap.
	 * @param p The point at which the tile is located
	 * @return The id of the tile mapped to the sprite sheet
	 */
	uint8_t get_flag(Point &p);

	/**
	 * Get the section of the map that is being rendered
	 * @return The current map section enum
	 */
	MapSection get_section();

	/**
	 * Checks if a point is within an area of the map defined by a min and max point.
	 * It is expected that the map is drawn from top to bottom and then left to right.
	 * @param p The point which shall be checked
	 * @param min_x The position at which the rectangle begins on the x-axis
	 * @param min_y The position at which the rectangle begins on the y-axis
	 * @param max_x The position at which the rectangle ends on the x-axis
	 * @param max_y The position at which the rectangle ends on the y-axis
	 * @return True if the point p is within the rectangle, else false
	 */
	bool point_in_area(Point &p, uint8_t min_x, uint8_t min_y, uint8_t max_x, uint8_t max_y);
}
