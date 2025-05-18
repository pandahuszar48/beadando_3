#include "button.hpp"
#include "graphics.hpp"

using namespace genv;

Button::Button(int x, int y, int sx, int sy, std::string label, std::function<void()> action)
    : Widget(x, y, sx, sy), _label(label), _action(action) {}

void Button::draw() {
    gout << move_to(_x, _y) << color(200, 200, 200) << box(_size_x, _size_y);
    gout << move_to(_x + 5, _y + _size_y / 2) << color(0, 0, 0) << text(_label);
}

void Button::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y)) {
        _action();
    }
}
