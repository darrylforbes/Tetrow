#include "model.h"

using namespace ge211;
using namespace std;

Model::Model()
        : board_()
        , score_(0)
        , game_over_(false)
        , active_piece(get_next_piece_())
{}

std::vector<std::vector<Tile>> Model::board() const {
    return board_.board;
}

Dimensions Model::dimensions() const {
    return board_.dimensions();
}

bool Model::is_game_over() {
    for (Tile tile : board_[0]) {
        if (tile.occupied) {
            game_over_ = true;
            return game_over_;
        }
    }
    return game_over_;
}

int Model::get_score() const {
    return score_;
}

void Model::launch_piece_() {
    active_piece = get_next_piece_();
}

Position Model::next_(Dimensions dims) {
    Position pos = active_piece.top_left;
    pos += dims;

    return pos;
}

void Model::piece_move_left() {
    Dimensions dims{-1, 0};
    if (check_collision_(next_(dims))) {
        ;
    }
    else {
        active_piece.top_left = next_(dims);
    }
}

void Model::piece_move_right() {
    Dimensions dims{1, 0};
    if (check_collision_(next_(dims))) {
        ;
    }
    else {
        active_piece.top_left = next_(dims);
    }
}

void Model::piece_move_down() {
    Dimensions dims{0, 1};
    if (check_collision_(next_(dims))) {
        vector<Tile> tiles;
        active_piece.get_tiles(tiles, active_piece.top_left);

        for (Tile tile : tiles) {
            if (tile.active) {
                board_[tile.pos].occupied = true;
                board_[tile.pos].color = tile.color;
                board_[tile.pos].letter = tile.letter;

                if (!is_game_over()) {
                    for (int i = 1; i < board_.board.size() - 1; ++i) {
                        if (row_is_full_(i)) {
                            clear_row_(i);
                            ++score_;
                        }
                    }

                    launch_piece_();
                    active_piece.velocity += (score_ * .1);
                }
            }
        }
    }

    else {
        active_piece.top_left = next_(dims);
    }
}

bool Model::check_collision_(Position pos) {
    vector<Tile> tiles;
    active_piece.get_tiles(tiles, pos);
    for (Tile tile : tiles) {
        if (tile.active && board_[tile.pos].occupied) {
            return true;
        }
    }
    return false;
}

void Model::piece_accelerate_down(int buffer) {
    active_piece.velocity *= buffer;
}

void Model::piece_rotate() {
    vector<vector<Tile>> old_grid = active_piece.grid;
    vector<vector<Tile>> new_grid = active_piece.grid;
    for (vector<Tile> &vec : new_grid) {
        for (Tile &tile : vec) {
            tile.active = false;
        }
    }

    for (int row = 0; row < piece_height; ++row) {
        for (int col = 0; col < piece_width; ++col) {
            Position pos{col, row};
            if (pos.x == 1 && pos.y == 1) {
                new_grid[pos.y][pos.x].active = true;
                ;
            }

            else if ((pos.x + pos.y) % 2 == 0
                     && active_piece.grid[pos.y][pos.x].active) {
                for (int num = 0; num < active_piece.corner_list.size() - 1;
                     ++num) {
                    if (pos == active_piece.corner_list[num]
                        && active_piece.grid[pos.y][pos.x].active) {
                        Position p = active_piece.corner_list[num + 1];
                        new_grid[p.y][p.x].active = true;
                    }
                }
            }

            else if ((pos.x + pos.y) % 2 == 1
                     && active_piece.grid[pos.y][pos.x].active) {
                for (int num = 0; num < active_piece.edge_list.size() - 1;
                     ++num) {
                    if (pos == active_piece.edge_list[num]) {
                        Position p = active_piece.edge_list[num + 1];
                        new_grid[p.y][p.x].active = true;
                    }
                }
            }
        }
    }

    active_piece.grid = new_grid;

    vector<Tile> vec;
    active_piece.get_tiles(vec, active_piece.top_left);
    Position old_top_left = active_piece.top_left;
    for (Tile tile : vec) {
        if(tile.active && board_[tile.pos.y][tile.pos.x].occupied) {
            if (tile.pos.y == board_rows - 2) {
                --active_piece.top_left.y;
                break;
            }
            else if (active_piece.top_left.down_right_by({1, 1}).x
                     > tile.pos.x) {
                ++active_piece.top_left.x;
                break;
            }
            else if (active_piece.top_left.down_right_by({1, 1}).x
                     < tile.pos.x) {
                --active_piece.top_left.x;
                break;
            }
            else if (active_piece.top_left.down_right_by({1, 1}).x
                     == tile.pos.x) {
                --active_piece.top_left.y;
                break;
            }
        }
    }
    if (check_collision_(active_piece.top_left)) {
        active_piece.top_left = old_top_left;
        active_piece.grid = old_grid;
    }
}

Piece Model::get_next_piece_() {
    vector<string> piece_type{"j","l","s","z","t"};
    int rand_num = rand() % 5;

    return Piece(piece_type[rand_num]);
}

bool Model::row_is_full_(int num) {
    for (Tile tile : board_.board[num]) {
        if (!tile.occupied) {
            return false;
        }
    }
    return true;
}

void Model::clear_row_(int row_num) {
    board_.board.erase(board_.board.begin() + row_num);
    board_.board.insert(board_.board.begin() + 1, board_.empty_row);

    for (int num = 1; num <= row_num; ++num) {
        for (Tile& tile : board_.board[num]) {
            ++tile.pos.y;
        }
    }
}
