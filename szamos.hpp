#ifndef SZAMOS_HPP_INCLUDED
#define SZAMOS_HPP_INCLUDED

#include "widget.hpp"
#include <string>

class Szamos : public Widget {
    int _value;
    int _min, _max;
public:
    Szamos(int x, int y, int sx, int sy,  int initial = 0);
    void draw() override;
    void handle(genv::event ev) override;

    void novel();
    void csokkent();
    int value() const;
};


#endif
