#pragma once

#include "board.h"
#include "piece.h"
#include <vector>
#include "ge211.h"

class Model {

public:

    // Constructs a model.
    explicit Model();

    std::vector<std::vector<Tile>> board() const;
    ge211::Dimensions dimensions() const;

    bool is_game_over();
    int get_score() const;

    // Moves a piece left on left arrow press if it will not colliding.
    void piece_move_left();

    // Moves a piece right on right arrow press if it will not colliding.
    void piece_move_right();

    // Moves a piece down if it will not collide. If it does collide, then
    // the corresponding tiles are set to occupied, and it checks for any
    // further action.
    void piece_move_down();

    // Increases a piece's velocity on down arrow press.
    void piece_accelerate_down(int buffer);

    // Rotates piece.
    void piece_rotate();

    Piece active_piece;

    // Test_access to test private functions.
    friend struct Test_access;

private:

    Board board_;

    int score_;
    bool game_over_;

    // Sets a piece to active and places it on game board.
    void launch_piece_();

    // Returns next position of piece.
    ge211::Position next_(ge211::Dimensions d);

    // Checks for collision between active_piece and an occupied tile.
    bool check_collision_(Position pos);

    // Randomly generates next piece.
    Piece get_next_piece_();

    // Checks if a given row is full.
    bool row_is_full_(int num);

    // Clears the given row and shifts all rows above the given row
    // down one level.
    void clear_row_(int row_num);

};
