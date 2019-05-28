#pragma once

#include "model.h"
#include "tile.h"
#include <string>
#include "ge211.h"

class View {

public:

    explicit View(Model const &model);

    // Draws sprites to screen.
    void draw(ge211::Sprite_set& set);

    // Returns window dimensions.
    ge211::Dimensions initial_window_dimensions() const;

    // Returns window title.
    std::string initial_window_title() const;

    // Converts a board position to a screen position.
    ge211::Position board_to_screen(ge211::Position pos);

private:

    Model const& model_;
    ge211::Rectangle_sprite const background_;
    ge211::Rectangle_sprite const blue_square_;
    ge211::Rectangle_sprite const orange_square_;
    ge211::Rectangle_sprite const green_square_;
    ge211::Rectangle_sprite const red_square_;
    ge211::Rectangle_sprite const purple_square_;
    ge211::Rectangle_sprite const gray_square_;
    ge211::Rectangle_sprite const black_square_;
};
