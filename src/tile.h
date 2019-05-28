#pragma once

#include <string>
#include "ge211.h"

static const int tile_size = 30;

class Tile {

public:

    // Constructs a tile with a given position and color.
    Tile(ge211::Position pos, ge211::Color c);

    // Constructs a tile with a given position and color of black.
    Tile(ge211::Position pos);

    ge211::Position pos;
    ge211::Color color;
    std::string letter;
    bool occupied;
    bool active;

    // Copies member values from a given tile.
    Tile& operator=(Tile tile);

private:

    bool width_;
    bool height_;

};

