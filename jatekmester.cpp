#include "jatekmester.hpp"
#include "graphics.hpp"
#include <random>

using namespace genv;

JatekMester::JatekMester(int tabla_meret, int cella_meret)
    : _width(tabla_meret * cella_meret),
      _height(tabla_meret * cella_meret),
      _current_player(State::X),
      _game_over(false)
{
    gout.open(_width, _height);

    _board = new Board(tabla_meret, tabla_meret, cella_meret);

    _restart_button = new Button(
        _width  / 2-40, _height/2+40, 150, 40,
        "Uj jatek", [this]() {
            reset();
        });

    _widgets.push_back(_board);
}

JatekMester::~JatekMester() {
    delete _board;
    delete _restart_button;
}

void JatekMester::futtat() {
    event ev;
    int focus = -1;

    while (gin >> ev && ev.keycode != key_escape) {
        if (ev.type == ev_mouse && ev.button == btn_left) {
            focus = -1;
            for (size_t i = 0; i < _widgets.size(); ++i) {
                if (_widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    focus = i;
                }
            }

            if (!_game_over) {
                handle_click(ev.pos_x, ev.pos_y);
            } else if (_restart_button->is_selected(ev.pos_x, ev.pos_y)) {
                _restart_button->handle(ev);
            }
        }

        gout << move_to(0, 0) << color(255, 255, 255) << box(_width, _height);

        for (Widget* w : _widgets) {
            w->draw();
        }

        if (_game_over) {
            std::string message = "Döntetlen!";
            bool found_winner = false;

            for (int i = 0; i < _board->rows() && !found_winner; ++i) {
                for (int j = 0; j < _board->cols() && !found_winner; ++j) {
                    if (check_win(i, j)) {
                        State winner = _board->get_cell(i, j);
                        message = (winner == State::X ? "X nyert!" : "O nyert!");
                        found_winner = true;
                    }
                }
            }



            int tw = gout.twidth(message);
            int tx = (_width - tw) / 2;
            int ty = _board->rows() * (_height - 60) / _board->rows() / 2;
            gout << move_to(tx, ty) << color(0, 0, 0) << text(message);
            _restart_button->draw();
        }

        gout << refresh;
    }
}

void JatekMester::handle_click(int x, int y) {
    int row = y / (_board->rows() > 0 ? _height / (_board->rows() + 1) : 1);
    int col = x / (_board->cols() > 0 ? _width / _board->cols() : 1);

    if (row < _board->rows() && col < _board->cols() && _board->is_cell_empty(row, col)) {
        _board->set_cell(row, col, _current_player);

        if (check_win(row, col)) {
            _game_over = true;
            return;
        }

        if (_board->get_empty_cells().empty()) {
            _game_over = true;
            return;
        }

        _current_player = (_current_player == State::X ? State::O : State::X);
    }
}

bool JatekMester::check_win(int row, int col) {
    const State player = _board->get_cell(row, col);
    if (player == State::Empty) return false;

    const int dirs[4][2] = {{0,1},{1,0},{1,1},{1,-1}};

    for (auto [dx, dy] : dirs) {
        int count = 1;

        for (int i = 1; i < 5; ++i) {
            int r = row + i * dy, c = col + i * dx;
            if (r >= 0 && r < _board->rows() &&
                c >= 0 && c < _board->cols() &&
                _board->get_cell(r, c) == player)
                count++;
            else break;
        }


        for (int i = 1; i < 5; ++i) {
            int r = row - i * dy, c = col - i * dx;
            if (r >= 0 && r < _board->rows() &&
                c >= 0 && c < _board->cols() &&
                _board->get_cell(r, c) == player)
                count++;
            else break;
        }

        if (count >= 5) return true;
    }

    return false;
}




void JatekMester::reset() {
    _board->clear();
    _current_player = State::X;
    _game_over = false;
}
