#include "kivalaszt.hpp"
#include "graphics.hpp"

using namespace genv;

Kivalaszto::Kivalaszto(int x, int y, int sx, int sy, std::vector<std::string> elemek, int visible)
    : Widget(x, y, sx, sy), _elemek(elemek), _selected(0), _visible(visible) {}

void Kivalaszto::draw() {
    for (int i = 0; i < _visible && i < _elemek.size(); ++i) {
        int ypos = _y + i * (_size_y / _visible);
        if (i == _selected) {
            gout << color(100, 100, 255);
        } else {
            gout << color(200, 200, 200);
        }
        gout << move_to(_x, ypos)
             << box(_size_x, _size_y / _visible)
             << color(0, 0, 0)
             << move_to(_x + 5, ypos + (_size_y / _visible) / 2 + 5)
             << text(_elemek[i]);
    }
}

void Kivalaszto::handle(event ev) {
    if (ev.type == ev_key) {
        if (ev.keycode == key_down && _selected < _elemek.size() - 1) {
            _selected++;
        } else if (ev.keycode == key_up && _selected > 0) {
            _selected--;
        }
    } else if (ev.type == ev_mouse && ev.button == btn_left) {
        for (int i = 0; i < _visible; ++i) {
            int ypos = _y + i * (_size_y / _visible);
            if (ev.pos_y >= ypos && ev.pos_y < ypos + (_size_y / _visible)) {
                _selected = i;
            }
        }
    }
}

std::string Kivalaszto::selected_text() const {
    return _elemek[_selected];
}
