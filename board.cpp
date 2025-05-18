#include "board.hpp"
#include "graphics.hpp"

using namespace genv;

Board::Board(int rows, int cols, int cell_size)
    : Widget(0, 0, cols * cell_size, rows * cell_size),
      _rows(rows), _cols(cols), _cell_size(cell_size)
{
    for (int i = 0; i < rows; ++i) {
        std::vector<Cell> row;
        for (int j = 0; j < cols; ++j) {
            row.emplace_back(j * cell_size, i * cell_size, cell_size, cell_size);
        }
        _cells.push_back(row);
    }
}

void Board::draw() {
    for (auto& row : _cells) {
        for (auto& cell : row) {
            cell.draw();
        }
    }
}

void Board::set_cell(int row, int col, State s) {
    _cells[row][col].set_state(s);
}

State Board::get_cell(int row, int col) const {
    return _cells[row][col].get_state();
}

bool Board::is_cell_empty(int row, int col) const {
    return get_cell(row, col) == State::Empty;
}

std::vector<std::pair<int, int>> Board::get_empty_cells() const {
    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _cols; ++j)
            if (_cells[i][j].get_state() == State::Empty)
                result.emplace_back(i, j);
    return result;
}

int Board::rows() const { return _rows; }
int Board::cols() const { return _cols; }

void Board::clear() {
    for (auto& row : _cells)
        for (auto& cell : row)
            cell.set_state(State::Empty);
}
