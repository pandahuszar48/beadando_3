#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "widget.hpp"
#include <functional>

class Button : public Widget {
    std::string _label;
    std::function<void()> _action;

public:
    Button(int x, int y, int sx, int sy, std::string label, std::function<void()> action);
    void draw() override;
    void handle(genv::event ev) override;
};

#endif
