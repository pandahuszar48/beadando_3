#ifndef KIVALASZT_HPP_INCLUDED
#define KIVALASZT_HPP_INCLUDED

#include "widget.hpp"
#include <vector>
#include <string>

class Kivalaszto : public Widget {
protected:
    std::vector<std::string> _elemek;
    int _selected;
    int _visible;
public:
    Kivalaszto(int x, int y, int sx, int sy, std::vector<std::string> elemek, int visible = 3);

    void draw() override;
    void handle(genv::event ev) override;
    std::string selected_text() const;
};
#endif // KIVALASZT_HPP_INCLUDED
