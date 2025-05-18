#ifndef HOVERDROPDOWN_HPP_INCLUDED
#define HOVERDROPDOWN_HPP_INCLUDED

#include "widget.hpp"
#include <vector>
#include <string>

class HoverDropdown : public Widget {
protected:
    std::vector<std::string> _elemek;
    int _selected;
    int _scroll_offset;
    bool _hover;
    int _visible_count;

public:
    HoverDropdown(int x, int y, int sx, int sy, std::vector<std::string> elemek, int visible_count = 5);

    void draw() override;
    void handle(genv::event ev) override;
    std::string selected_text() const;
    bool is_selected(int mx, int my) override;
};

#endif // HOVERDROPDOWN_HPP_INCLUDED
