#include "piece.h"

using namespace std;
using namespace ge211;

Piece::Piece(string &str)
        : top_left(4, 0)
        , grid(make_grid_(str))
        , color()
        , letter(str)
        , corner_list(make_corner_list_())
        , edge_list(make_edge_list_())
        , velocity(starting_velocity)
{}

vector<vector<Tile>> Piece::make_grid_(string str) {
    vector<int> row_0;
    vector<int> row_1;
    vector<int> row_2;

    if (str == "j") {
        row_0.insert(row_0.end(), {1, 0, 0});
        row_1.insert(row_1.end(), {1, 1, 1});
        row_2.insert(row_2.end(), {0, 0, 0});
        color = Color(0, 0, 255);
    }

    else if (str == "l") {
        row_0.insert(row_0.end(), {0, 0, 1});
        row_1.insert(row_1.end(), {1, 1, 1});
        row_2.insert(row_2.end(), {0, 0, 0});
        color = Color(255, 128, 0);
    }

    else if (str == "s") {
        row_0.insert(row_0.end(), {0, 1, 1});
        row_1.insert(row_1.end(), {1, 1, 0});
        row_2.insert(row_2.end(), {0, 0, 0});
        color = Color(0, 255, 0);
    }

    else if (str == "z") {
        row_0.insert(row_0.end(), {1, 1, 0});
        row_1.insert(row_1.end(), {0, 1, 1});
        row_2.insert(row_2.end(), {0, 0, 0});
        color = Color(255, 0, 0);
    }

    else if (str == "t") {
        row_0.insert(row_0.end(), {0, 1, 0});
        row_1.insert(row_1.end(), {1, 1, 1});
        row_2.insert(row_2.end(), {0, 0, 0});
        color = Color(128, 0, 255);
    }

    else {
        throw runtime_error("Invalid piece");
    }

    vector<vector<Tile>> vectors(piece_height);

    for (int col = 0; col < piece_width; ++col) {
        Tile tile_0{ge211::Position(col, 0), Color::white()};
        tile_0.letter = letter;
        vectors[0].push_back(tile_0);
        if (row_0[col] == 1) {
            vectors[0][col].active = true;
        }

        Tile tile_1{ge211::Position(col, 1), Color::white()};
        tile_1.letter = letter;
        vectors[1].push_back(tile_1);
        if (row_1[col] == 1) {
            vectors[1][col].active = true;
        }

        Tile tile_2{ge211::Position(col, 2), Color::white()};
        tile_2.letter = letter;
        vectors[2].push_back(tile_2);
        if (row_2[col] == 1) {
            vectors[2][col].active = true;
        }
    }

    return vectors;
}

vector<Position> Piece::make_corner_list_() {
    vector<Position> vec{Position(0, 2), Position(0, 0), Position(2, 0),
                         Position(2, 2), Position(0, 2)};

    return vec;
}

vector<Position> Piece::make_edge_list_() {
    vector<Position> vec{Position(0, 1), Position(1, 0), Position(2, 1),
                         Position(1, 2), Position(0, 1)};

    return vec;
}

Tile& Piece::operator[](Position pos) {
    return grid[pos.y][pos.x];
}

void Piece::get_tiles(vector<Tile>& tiles, Position next_pos) const {
    for (vector<Tile> vec : grid) {
        for (Tile tile : vec) {
            Tile adjusted_tile = tile;
            Position adjusted_pos{tile.pos.x + next_pos.x,
                                  tile.pos.y + next_pos.y};
            adjusted_tile.pos = adjusted_pos;
            adjusted_tile.letter = letter;
            tiles.push_back(adjusted_tile);
        }
    }
}
