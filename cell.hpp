#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include "widget.hpp"

enum class State { Empty, X, O };

class Cell : public Widget {
    State _state;
    bool _clickable;
public:
    Cell(int x, int y, int sx, int sy);

    void draw() override;
    void handle(genv::event ev) override;

    State get_state() const;
    void set_state(State s);
    void set_clickable(bool enable);
};

#endif // CELL_HPP_INCLUDED
