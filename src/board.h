#pragma once

#include "tile.h"
#include <vector>
#include "ge211.h"

// Board has invisible rows and cols bordering
// Visible board is 10 x 20
// Top left corner is (1, 1)
static int const board_rows = 22;
static int const board_cols = 12;

class Board {

public:

    // Constructs a board.
    Board();

    std::vector<std::vector<Tile>> board;
    std::vector<Tile> empty_row;

    // Returns dimensions.
    ge211::Dimensions dimensions() const;

    // Gets the tile at a given position.
    Tile& operator[](ge211::Position pos);

    // Gets the vector of tiles of a given row.
    std::vector<Tile>& operator[](int row);

    // Creates empty row which is used by Model::shift_rows.
    void create_empty_row(std::vector<Tile>& vec);

private:

    ge211::Dimensions dims_;

};
