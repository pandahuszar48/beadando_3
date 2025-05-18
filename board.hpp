#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include "cell.hpp"
#include "widget.hpp"
#include <vector>

class Board : public Widget {
    std::vector<std::vector<Cell>> _cells;
    int _rows, _cols;
    int _cell_size;

public:
    Board(int rows, int cols, int cell_size);

    void draw() override;
    void handle(genv::event) override {}

    void set_cell(int row, int col, State s);
    State get_cell(int row, int col) const;
    bool is_cell_empty(int row, int col) const;
    std::vector<std::pair<int, int>> get_empty_cells() const;

    int rows() const;
    int cols() const;
    void clear();
};

#endif
