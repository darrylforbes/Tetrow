#include "controller.h"

Controller::Controller()
        : model_()
        , view_(model_)
        , counter_(0)
        , max_frames_(20)
{}

void Controller::draw(ge211::Sprite_set& sprites) {
    view_.draw(sprites);
}

ge211::Dimensions Controller::initial_window_dimensions() const {
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const {
    return view_.initial_window_title();
}

void Controller::on_key(ge211::Key key) {
    if (key == ge211::Key::left()) {
        model_.piece_move_left();
    }
    else if (key == ge211::Key::right()){
       model_.piece_move_right();
    }
    else if (key == ge211::Key::down()) {
        model_.piece_accelerate_down(acceleration_buffer);
    }
    else if (key == ge211::Key::up())
        model_.piece_rotate();
}

void Controller::on_key_up(ge211::Key key) {
    if (key == ge211::Key::down()){
        model_.active_piece.velocity = starting_velocity;
    }
}

void Controller::on_key_down(ge211::Key key) {
    if (key == ge211::Key::code(' ') &&
        model_.active_piece.velocity < 1000) {
        model_.piece_accelerate_down(1000);
    }
    else if (key == ge211::Key::code('q')) {
        exit(0);
    }
}

void Controller::on_frame(double) {
    if (!model_.is_game_over()) {
        if (counter_ >= max_frames_) {
            model_.piece_move_down();
            counter_ = 0;
        }
        counter_ += model_.active_piece.velocity;
    }
    else {
        printf("\nGame Over\n");
        printf("Score: %i\n", model_.get_score());
        exit(0);
    }
}
