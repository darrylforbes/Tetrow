#pragma once

#include "tile.h"
#include <vector>
#include <string>
#include "ge211.h"

using namespace ge211;
using namespace std;

static const int piece_width = 3;
static const int piece_height = 3;
static double starting_velocity = 1;

class Piece {

public:

    // Constructs a piece.
    explicit Piece(string &str);

    vector<vector<Tile>> grid;
    string letter;
    double velocity;
    Position top_left;
    Color color;

    vector<Position> corner_list;
    vector<Position> edge_list;

    // Gets the tile at a given position in relation to the top_left
    // of the piece.
    Tile& operator[](Position pos);

    // Fills the given vector with the piece tiles with positions
    // updated to be in relation to the board.
    void get_tiles(vector<Tile>& tiles, Position next_pos) const;

private:

    // Constructs a grid with a configuration of active tiles and color
    // based on the string that is passed.
    vector<vector<Tile>> make_grid_(string str);

    // Constructs a vector of corner positions in the order of rotation.
    vector<Position> make_corner_list_();

    // Constructs a vector of edge positions in the order of rotation.
    vector<Position> make_edge_list_();

};


