#include "slider.hpp"
#include "graphics.hpp"

using namespace genv;

Slider::Slider(int x, int y, int sx, int sy, int min, int max, int initial,std::function<void(int)> on_change)
    : Widget(x, y, sx, sy),_min(min), _max(max), _value(initial), _dragging(false), _on_change(on_change),
      _minus(x - 25, y, 20, sy, "-", [this](){
          if (_value > _min) {
              _value--;
              _on_change(_value);
          }
      }),
      _plus(x + sx + 5, y, 20, sy, "+", [this](){
          if (_value < _max) {
              _value++;
              _on_change(_value);
          }
      }) {}
void Slider::draw() {
    int knob_width = 10;
    float ratio = float(_value - _min) / (_max - _min);
    int knob_x = _x + ratio * (_size_x - knob_width);

    gout << move_to(_x, _y + _size_y / 2 - 2)
         << color(180, 180, 180) << box(_size_x, 4);

    gout << move_to(knob_x, _y)
         << color(100, 100, 255) << box(knob_width, _size_y);
    _minus.draw();
    _plus.draw();
}

void Slider::handle(genv::event ev) {
    _minus.handle(ev);
    _plus.handle(ev);

    int knob_width = 10;

    if (ev.type == ev_mouse) {
        int knob_x = _x + (_value - _min) * (_size_x - knob_width) / (_max - _min);

        if (ev.button == btn_left &&
            ev.pos_x >= knob_x && ev.pos_x <= knob_x + knob_width &&
            ev.pos_y >= _y && ev.pos_y <= _y + _size_y) {
            _dragging = true;
        }

        if (ev.button == -btn_left) {
            _dragging = false;
        }

        if (_dragging && ev.pos_x >= _x && ev.pos_x <= _x + _size_x) {
            int relative = ev.pos_x - _x;
            int new_value = _min + (relative * (_max - _min)) / (_size_x - knob_width);
            if (new_value != _value) {
                _value = new_value;
                _on_change(_value);
            }
        }
    }

    // 🎯 Nyílbillentyűk kezelése
    if (ev.type == ev_key) {
        if (ev.keycode == key_left && _value > _min) {
            _value--;
            _on_change(_value);
        } else if (ev.keycode == key_right && _value < _max) {
            _value++;
            _on_change(_value);
        }
    }
}



int Slider::get_value() const {
    return _value;
}
