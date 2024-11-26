#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "World.h"

using namespace Life;

World::World(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw "Error compiling!";
    }
    std::string line; //каждая строка
    int line_count = 0;
    while (std::getline(file, line)) {
        if (line_count == 0) { //первая строка - ширина и высота поля
            int width, height;
            std::stringstream ss(line);
            ss >> width >> height;
            _width = width;
            _height = height;

            _array2D = new char* [_height];//выделение памяти под массивж
            _prev_array2D = new char* [_height];
            for (int i = 0; i < _height; ++i) {
                _array2D[i] = new char[_width];
                _prev_array2D[i] = new char[_width];
                for (int j = 0; j < _width; ++j) {
                    _array2D[i][j] = SymbolEmpty; // Инициализируем все ячейки пробелами
                    _prev_array2D[i][j] = SymbolEmpty; // Инициализируем все ячейки пробелами
                }
            }
        }
        else if (line_count == 1) { //вторая строка - имя вселенной
            Name = line;
        }
        else if (line_count == 2) { //третья строка - правило перехода
            std::stringstream ss(line);
            std::string col_to_birth, col_to_survival;
            ss >> col_to_birth >> col_to_survival;
            Rule = "Rule: B" + col_to_birth + "/S" + col_to_survival;

            int digits_S[8];
            int digits_B[8];
            for (char ch : col_to_survival) {
                if (ch >= '0' && ch <= '9') {
                    digits_S[count_S++] = ch - '0';  // Преобразуем символ в цифру и сохраняем в массив
                }
            }
            for (char ch : col_to_birth) {
                if (ch >= '0' && ch <= '9') {
                    digits_B[count_B++] = ch - '0';  // Преобразуем символ в цифру и сохраняем в массив
                }
            }
            for (int i = 0; i < 8; i++) {
                _col_to_birth[i] = digits_B[i];
                _col_to_survival[i] = digits_S[i];
            }
        }
        else if (line_count > 2) { //остальные строки - массив чисел строк
            std::stringstream ss(line);
            int x, y;
            ss >> x >> y;
            _array2D[x][y] = Symbol;
        }
        ++line_count;
    }
    file.close();
}

World::~World() { // Освобождаем память, выделенную для двумерного массива
    for (int i = 0; i < _height; ++i) {
        delete[] _array2D[i];
        delete[] _prev_array2D[i];
    }
    delete[] _array2D;
    delete[] _prev_array2D;
}

int World::col_live_neighbors(int x, int y) const {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0)
                continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < _height && ny >= 0 && ny < _width) {
                if (_prev_array2D[nx][ny] == Symbol) {
                    ++count;
                }
            }
        }
    }
    return count;
}

bool World::is_stable() const { //проверка на стабильность вселенной (поколения не меняются)
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            if (_array2D[i][j] != _prev_array2D[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void World::next_generation() {
    copy_world();
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            int live_neighbors = col_live_neighbors(i, j);
            if (_prev_array2D[i][j] == Symbol) {
                //если не найдёт вернет указатель на конец массива (_col_to_survival + count_S)
                if (std::find(_col_to_survival, _col_to_survival + count_S, live_neighbors) == _col_to_survival + count_S) { //если не находит в массиве цифр для выживания, то умирает
                    _array2D[i][j] = SymbolEmpty;
                }
            }
            else {
                if (std::find(_col_to_birth, _col_to_birth + count_B, live_neighbors) != _col_to_birth + count_B) { //если находит в массиве цифр для рождения, то рождается
                    _array2D[i][j] = Symbol;
                }
            }
        }
    }
    ++generation;
}

void World::copy_world() { //старое поколение становится новым
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            _prev_array2D[i][j] = _array2D[i][j];
        }
    }
}

void World::print_world() const {
    std::cout << Name << std::endl;
    std::cout << Rule << std::endl;
    std::cout << "Current generation: " << generation << std::endl;
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            std::cout << _array2D[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}