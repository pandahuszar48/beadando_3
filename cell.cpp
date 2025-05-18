#include "cell.hpp"
#include "graphics.hpp"

using namespace genv;

Cell::Cell(int x, int y, int sx, int sy)
    : Widget(x, y, sx, sy), _state(State::Empty), _clickable(true) {}

void Cell::draw() {
    gout << move_to(_x, _y) << color(220, 220, 220)
         << box(_size_x, _size_y)
         << color(0, 0, 0) << move_to(_x, _y)
         << box(1, _size_y) << box(_size_x, 1);  // cella kerete

    if (_state == State::X) {
        gout << move_to(_x + 5, _y + _size_y / 2 + 5)
             << color(0, 0, 255) << text("X");
    } else if (_state == State::O) {
        gout << move_to(_x + 5, _y + _size_y / 2 + 5)
             << color(255, 0, 0) << text("O");
    }
}

void Cell::handle(event ev) {
    if (_clickable && ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y)) {
        // Az állapot beállítását külső osztály (Board) végzi majd!
        // Itt csak kattinthatóságot jelezzük vissza.
    }
}

State Cell::get_state() const {
    return _state;
}

void Cell::set_state(State s) {
    _state = s;
}

void Cell::set_clickable(bool enable) {
    _clickable = enable;
}
