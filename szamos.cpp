#include "szamos.hpp"
#include "graphics.hpp"

using namespace genv;

Szamos::Szamos(int x, int y, int sx, int sy,  int initial)
    : Widget(x, y, sx, sy),  _value(initial){}

void Szamos::draw() {
    gout << move_to(_x, _y) << color(255, 255, 255) << box(_size_x, _size_y);
    gout << move_to(_x + 10, _y + _size_y / 2)
         << color(0, 0, 0) << text(std::to_string(_value));
}
void Szamos::novel() {

        _value++;

}

void Szamos::csokkent() {

        _value--;

}

int Szamos::value() const {
    return _value;
}
void Szamos::handle(genv::event ev) {
    if (ev.type == ev_key) {
        if (ev.keycode == key_up) {
            novel();  // +1
        } else if (ev.keycode == key_down) {
            csokkent();  // -1
        } else if (ev.keycode == key_pgup) {
            for (int i = 0; i < 10; ++i) {
                novel();
            }
        } else if (ev.keycode == key_pgdn) {
            for (int i = 0; i < 10; ++i) {
                csokkent();
            }
        }
    }
}
