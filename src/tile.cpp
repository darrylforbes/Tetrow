#include "tile.h"

using namespace ge211;

Tile::Tile(Position pos, Color c)
        : pos(pos)
        , color(c)
        , letter(" ")
        , height_(tile_size)
        , width_(tile_size)
        , occupied(false)
        , active(false)
{}

Tile::Tile(Position pos)
        : Tile(pos, Color::white())
{}

Tile& Tile::operator=(Tile tile) {
    pos = tile.pos;
    color = tile.color;
    letter = tile.letter;
    occupied = tile.occupied;
    active = tile.active;

    return *this;
}
