#include "view.h"

using namespace ge211;

View::View(Model const &model)
    : model_(model)
    , background_(initial_window_dimensions(), Color::black())
    , blue_square_({tile_size, tile_size}, Color(0, 0, 255))
    , orange_square_({tile_size, tile_size}, Color(255, 128, 0))
    , green_square_({tile_size, tile_size}, Color(0, 255, 0))
    , red_square_({tile_size, tile_size}, Color(255, 0, 0))
    , purple_square_({tile_size, tile_size}, Color(128, 0, 255))
    , gray_square_({tile_size, tile_size}, Color(128, 128, 128))
    , black_square_({tile_size, tile_size}, Color::black())
{}

void View::draw(Sprite_set& set) {
    set.add_sprite(background_, {0, 0}, 0);

    for (vector<Tile> vec : model_.board()) {
        for (Tile tile : vec) {
            Position pix = board_to_screen(tile.pos);
            std::string str = tile.letter;
            if (str == "j") set.add_sprite(blue_square_, pix, 1);
            else if (str == "l") set.add_sprite(orange_square_, pix, 1);
            else if (str == "s") set.add_sprite(green_square_, pix, 1);
            else if (str == "z") set.add_sprite(red_square_, pix, 1);
            else if (str == "t") set.add_sprite(purple_square_, pix, 1);
            else if (str == "g") set.add_sprite(gray_square_, pix, 1);
            else if (str == " ") set.add_sprite(black_square_, pix, 1);
        }
    }

    Position piece_pos = model_.active_piece.top_left;
    vector<Tile> tiles;
    model_.active_piece.get_tiles(tiles, piece_pos);
    for (Tile tile : tiles) {
        Position pix = board_to_screen(tile.pos);
        if (tile.active) {
            std::string str = model_.active_piece.letter;
            if (str == "j") set.add_sprite(blue_square_, pix, 2);
            else if (str == "l") set.add_sprite(orange_square_, pix, 2);
            else if (str == "s") set.add_sprite(green_square_, pix, 2);
            else if (str == "z") set.add_sprite(red_square_, pix, 2);
            else if (str == "t") set.add_sprite(purple_square_, pix, 2);
            else if (str == "g") set.add_sprite(gray_square_, pix, 1);
            else if (str == " ") set.add_sprite(black_square_, pix, 2);
        }
    }
}

Dimensions View::initial_window_dimensions() const {
    return tile_size * model_.dimensions();
}

std::string View::initial_window_title() const {
    return "Tetrow";
}

Position View::board_to_screen(Position pos) {
    pos.x *= tile_size;
    pos.y *= tile_size;

    return pos;
}
