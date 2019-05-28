#include "board.h"

Board::Board()
        : dims_({board_cols, board_rows})
        , board()
{
    create_empty_row(empty_row);

    board.reserve(dims_.height);
    for (int row = 0; row < dims_.height; ++row) {
        std::vector<Tile> row_of_tiles;
        row_of_tiles.reserve(dims_.width);
        for (int col = 0; col < dims_.width; ++col) {
            row_of_tiles.emplace_back(Tile(ge211::Position(col, row)));
        }
        board.push_back(row_of_tiles);
    }

    // Set border tiles to occupied
    for (int col = 0; col < dims_.width; ++col) {
        board[dims_.height - 1][col].occupied = true;
        board[dims_.height - 1][col].color = ge211::Color(128, 128, 128);
        board[dims_.height - 1][col].letter = "g";

        board[0][col].color = ge211::Color(255, 0, 0);
        board[0][col].letter = "z";
    }

    for (int row = 1; row < dims_.height; ++row) {
        board[row][0].occupied = true;
        board[row][0].color = ge211::Color(128, 128, 128);
        board[row][0].letter = "g";

        board[row][dims_.width - 1].occupied = true;
        board[row][dims_.width - 1].color = ge211::Color(128, 128, 128);
        board[row][dims_.width - 1].letter = "g";
    }
}

ge211::Dimensions Board::dimensions() const {
    return dims_;
}

Tile& Board::operator[](ge211::Position pos) {
    return board[pos.y][pos.x];
}

std::vector<Tile>& Board::operator[](int row) {
    return board[row];
}

void Board::create_empty_row(std::vector<Tile>& vec) {
    for (int col = 0; col < dims_.width; ++col) {
        vec.push_back(Tile({col, 0}));
    }

    vec[0].occupied = true;
    vec[0].color = ge211::Color(128, 128, 128);
    vec[0].letter = "g";

    vec[dims_.width - 1].occupied = true;
    vec[dims_.width - 1].color = ge211::Color(128, 128, 128);
    vec[dims_.width - 1].letter = "g";
}
