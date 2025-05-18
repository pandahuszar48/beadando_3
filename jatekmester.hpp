#ifndef JATEKMESTER_HPP_INCLUDED
#define JATEKMESTER_HPP_INCLUDED

#include "board.hpp"
#include "button.hpp"
#include <vector>

class JatekMester {
    Board* _board;
    Button* _restart_button;
    std::vector<Widget*> _widgets;

    State _current_player;
    bool _game_over;

    const int _width;
    const int _height;

public:
    JatekMester(int tabla_meret, int cella_meret);
    ~JatekMester();

    void futtat();

private:
    void handle_click(int x, int y);
    bool check_win(int row, int col);
    void reset();
};

#endif // JATEKMESTER_HPP_INCLUDED
