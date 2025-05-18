#ifndef SLIDER_HPP_INCLUDED
#define SLIDER_HPP_INCLUDED

#include "widget.hpp"
#include <functional>
#include "button.hpp"

class Slider : public Widget {
    int _min, _max;
    int _value;
    bool _dragging;
    std::function<void(int)> _on_change;
    Button _minus;
    Button _plus;

public:
    Slider(int x, int y, int sx, int sy, int min, int max, int initial,
           std::function<void(int)> on_change);

    void draw() override;
    void handle(genv::event ev) override;
    int get_value() const;
};

#endif
