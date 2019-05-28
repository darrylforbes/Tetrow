#pragma once

#include "model.h"
#include "view.h"
#include "ge211.h"

static const int acceleration_buffer = 10;

class Controller
        : public ge211::Abstract_game
{

public:

    // Constructs a controller.
    explicit Controller();

    // Input handlers.
    void on_key(ge211::Key key) override;
    void on_key_up(ge211::Key key) override;
    void on_key_down(ge211::Key key) override;

    // Main game loop.
    void on_frame(double) override;

protected:

    // Draws sprites to screen.
    void draw(ge211::Sprite_set&) override;

    // Returns window dimensions.
    ge211::Dimensions initial_window_dimensions() const override;

    // Returns window title
    std::string initial_window_title() const override;

private:
    Model model_;
    View view_;
    int counter_;
    int max_frames_;

};
