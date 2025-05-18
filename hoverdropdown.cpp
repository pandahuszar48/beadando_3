#include "hoverdropdown.hpp"
#include "graphics.hpp"

using namespace genv;

HoverDropdown::HoverDropdown(int x, int y, int sx, int sy, std::vector<std::string> elemek, int visible_count)
    : Widget(x, y, sx, sy), _elemek(elemek), _selected(0), _scroll_offset(0), _hover(false), _visible_count(visible_count) {}

void HoverDropdown::draw() {
    int line_h = _size_y;

    gout << move_to(_x, _y)
         << color(220, 220, 220)
         << box(_size_x, line_h)
         << color(0, 0, 0)
         << move_to(_x + 5, _y + line_h / 2 + 5)
         << text(_elemek[_selected]);

    int tx = _x + _size_x - 15;
    int ty = _y + line_h / 2 - 3;
    gout << color(0, 0, 0)
         << move_to(tx, ty)
         << line(10, 0)
         << move_to(tx + 5, ty)
         << line(-5, 6)
         << line(-5, -6);

    if (_hover) {
        for (int i = 0; i < _visible_count; ++i) {
            int idx = _scroll_offset + i;
            if (idx < 0 || idx >= (int)_elemek.size()) continue;

            int y_pos = _y + (i + 1) * line_h;
            gout << move_to(_x, y_pos)
                 << color(idx == _selected ? 200 : 240, 240, 240)
                 << box(_size_x, line_h)
                 << color(0, 0, 0)
                 << move_to(_x + 5, y_pos + line_h / 2 + 5)
                 << text(_elemek[idx]);
        }
    }
}

void HoverDropdown::handle(event ev) {
    if (ev.type == ev_mouse) {
        _hover = is_selected(ev.pos_x, ev.pos_y);
        if (_hover && ev.button == btn_wheelup) {
            if (_scroll_offset > 0) _scroll_offset--;
        }
        if (_hover && ev.button == btn_wheeldown) {
            if (_scroll_offset + _visible_count < (int)_elemek.size()) _scroll_offset++;
        }
        if (_hover && ev.button == btn_left) {
            int line_h = _size_y;
            for (int i = 0; i < _visible_count; ++i) {
                int idx = _scroll_offset + i;
                int y_pos = _y + (i + 1) * line_h;
                if (ev.pos_y >= y_pos && ev.pos_y <= y_pos + line_h && idx < (int)_elemek.size()) {
                    _selected = idx;
                    _hover = false;
                }
            }
        }
    }
}

std::string HoverDropdown::selected_text() const {
    return _elemek[_selected];
}

bool HoverDropdown::is_selected(int mx, int my) {
    int h = _size_y;
    if (mx >= _x && mx <= _x + _size_x &&
        my >= _y && my <= _y + (_hover ? (_visible_count + 1) * h : h)) {
        return true;
    }
    return false;
}
