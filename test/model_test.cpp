#include "model.h"
#include <catch.h>
#include "tile.h"

using namespace ge211;
using namespace std;

struct Test_access {

    Model & m_;

    vector<vector<Tile>> &board() {
        return m_.board_.board;
    }
    void clear_row(int i) {

        m_.clear_row_(i);
    }
    Piece active_piece() {
        return m_.active_piece;
    }

    bool row_is_full(int i) {
        return m_.row_is_full_(i);
    }

    void piece_move_right(){
        m_.piece_move_right();
    }

    void piece_move_left() {
        m_.piece_move_left();
    }

    void piece_move_down() {
        m_.piece_move_down();
    }
    bool is_game_over() {
        return m_.is_game_over();
    }
    int score() {
        return m_.get_score();
    }
    void launch() {
        m_.launch_piece_();
    }

};

TEST_CASE("Test Accelerate") {

    Model m;
    double v = m.active_piece.velocity;

    m.piece_accelerate_down(2);

    CHECK(m.active_piece.velocity>v);

}

TEST_CASE("Test Clear Row and Game Over") {

    Model m;
    Test_access t{m};

    for( Tile &tl : t.board()[1]) {
        tl.occupied = true;
    }

    CHECK(t.row_is_full(1));
    t.clear_row(1);

    for(int i = 1; i < t.board()[1].size() - 1; ++i) {
        CHECK_FALSE(t.board()[1][i].occupied);
    }

    for( Tile &tl : t.board()[1]) {
        tl.occupied = true;
    }

    CHECK_FALSE(t.is_game_over());

    t.piece_move_down();

    CHECK(t.is_game_over());

}

TEST_CASE("Update Velocity") {

    Model m;
    Test_access t{m};

    double v = t.active_piece().velocity;

    for (Tile &tl : t.board()[4]) {
        tl.occupied = true;
    }

    while (t.active_piece().velocity == v) {
        t.piece_move_down();
    }

    CHECK(t.active_piece().velocity > v);

}

TEST_CASE("Update Score") {

    Model m;
    Test_access t{m};

    int s = t.score();

    for( Tile &tl : t.board()[4]) {
        tl.occupied = true;
    }

    while(t.score() == s) {
        t.piece_move_down();
    }

    CHECK(t.score() > s);

}

TEST_CASE("Piece Move") {

    Model m;
    Test_access t{m};

    Position p = t.active_piece().top_left;

    t.piece_move_right();

    CHECK(t.active_piece().top_left.x > p.x);

    t.piece_move_left();
    t.piece_move_left();

    CHECK(t.active_piece().top_left.x < p.x);


    t.piece_move_down();

    CHECK(t.active_piece().top_left.y > p.y);

    for(int i = 0; i < 20; ++i) {
        t.piece_move_left();
    }

    p = t.active_piece().top_left;

    t.piece_move_left();

    CHECK(t.active_piece().top_left.x == p.x);

    t.piece_move_right();


    //Check that piece relaunches from top once it hits bottom

    for(int i = t.active_piece().top_left.y; i < m.board().size() - 3; ++i) {
        t.piece_move_down();
    }

    p = t.active_piece().top_left;

    CHECK_FALSE(t.active_piece().top_left.y == 0);

    t.piece_move_down();

    CHECK(t.active_piece().top_left.y == 0);
    CHECK(p.y > t.active_piece().top_left.y);

    CHECK_FALSE(p.x == t.active_piece().top_left.x);

}

TEST_CASE("Test Construct Board") {

    Model m;

    for (vector<Tile> vec : m.board()) {
        for (Tile tile : vec) {
            if (tile.pos.x == 0 || tile.pos.x == m.dimensions().width - 1) {
                if (tile.pos.y != 0) {
                    CHECK(tile.occupied);
                }
            }
            else if (tile.pos.y == m.dimensions().height - 1) {
                CHECK(tile.occupied);
            }
            else {
                CHECK_FALSE(tile.occupied);
            }
        }
    }

}

TEST_CASE("Test Rotation") {

    Model m;

    Piece old_piece = m.active_piece;
    m.piece_rotate();

    CHECK(old_piece[{0, 0}].active == m.active_piece[{2, 0}].active);
    CHECK(old_piece[{1, 0}].active == m.active_piece[{2, 1}].active);
    CHECK(old_piece[{2, 0}].active == m.active_piece[{2, 2}].active);
    CHECK(old_piece[{0, 1}].active == m.active_piece[{1, 0}].active);
    CHECK(old_piece[{1, 1}].active == m.active_piece[{1, 1}].active);
    CHECK(old_piece[{2, 1}].active == m.active_piece[{1, 2}].active);
    CHECK(old_piece[{0, 2}].active == m.active_piece[{0, 0}].active);
    CHECK(old_piece[{1, 2}].active == m.active_piece[{0, 1}].active);
    CHECK(old_piece[{2, 2}].active == m.active_piece[{0, 2}].active);

    m.active_piece = old_piece;

    m.active_piece.top_left = {0, 21};
    m.piece_rotate();

    CHECK(old_piece[{0, 0}].active == m.active_piece[{0, 0}].active);
    CHECK(old_piece[{1, 0}].active == m.active_piece[{1, 0}].active);
    CHECK(old_piece[{2, 0}].active == m.active_piece[{2, 0}].active);
    CHECK(old_piece[{0, 1}].active == m.active_piece[{0, 1}].active);
    CHECK(old_piece[{1, 1}].active == m.active_piece[{1, 1}].active);
    CHECK(old_piece[{2, 1}].active == m.active_piece[{2, 1}].active);
    CHECK(old_piece[{0, 2}].active == m.active_piece[{0, 2}].active);
    CHECK(old_piece[{1, 2}].active == m.active_piece[{1, 2}].active);
    CHECK(old_piece[{2, 2}].active == m.active_piece[{2, 2}].active);

}
