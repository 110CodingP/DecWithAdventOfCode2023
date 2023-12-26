#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

std::vector<std::string> maze;
std::vector<std::vector<char>> isOnPath(140, std::vector<char>(140, '.'));

std::pair<int, int> findStart() {
    for (int row = 0; row < maze.size(); row++) {
        for (int col = 0; col < maze[row].size(); col++) {
            if (maze[row][col] == 'S') return { row, col };
        }
    }
}

bool hasLeft() {
    for (int row = 0; row < isOnPath.size(); row++) {
        for (int col = 0; col < isOnPath[row].size(); col++) {
            if (isOnPath[row][col] == '.') return true;
        }
    }
    return false;
}

std::pair<int, int> stepTo(int prevRow, int prevCol, int currRow, int currCol, bool indicateSide) {
    std::pair<int, int> ret;
    int side;
    if (maze[currRow][currCol] == 'L') {
        if (prevRow == currRow - 1 && prevCol == currCol) { // from up
            ret = { currRow, currCol + 1 };
            side = 'R';
        }
        else if (prevRow == currRow && prevCol == currCol + 1) { // from right
            ret = { currRow - 1, currCol };
            side = 'L';
        }
        else std::cout << "ERROR" << std::endl;
        if (indicateSide) {
            if (currCol != 0 && isOnPath[currRow][currCol - 1] != 'X') isOnPath[currRow][currCol - 1] = side;
            if (currRow != isOnPath.size() - 1 && isOnPath[currRow + 1][currCol] != 'X') isOnPath[currRow + 1][currCol] = side;
        }
    }
    else if (maze[currRow][currCol] == 'F') {
        if (prevRow == currRow + 1 && prevCol == currCol) { // from down
            side = 'L';
            ret = { currRow, currCol + 1 };
        }
        else if (prevRow == currRow && prevCol == currCol + 1) { // from right
            side = 'R';
            ret = { currRow + 1, currCol };
        }
        else std::cout << "ERROR" << std::endl;
        if (indicateSide) {
            if (currCol != 0 && isOnPath[currRow][currCol - 1] != 'X') isOnPath[currRow][currCol - 1] = side;
            if (currRow != 0 && isOnPath[currRow - 1][currCol] != 'X') isOnPath[currRow - 1][currCol] = side;
        }
    }
    else if (maze[currRow][currCol] == '7') {
        if (prevRow == currRow + 1 && prevCol == currCol) { // from down
            side = 'R';
            ret = { currRow, currCol - 1 };
        }
        else if (prevRow == currRow && prevCol == currCol - 1) { // from left
            side = 'L';
            ret = { currRow + 1, currCol };
        }
        else std::cout << "ERROR" << std::endl;
        if (indicateSide) {
            if (currCol != isOnPath.size() - 1 && isOnPath[currRow][currCol + 1] != 'X') isOnPath[currRow][currCol + 1] = side;
            if (currRow != 0 && isOnPath[currRow - 1][currCol] != 'X') isOnPath[currRow - 1][currCol] = side;
        }
    }
    else if (maze[currRow][currCol] == 'J') {
        if (prevRow == currRow - 1 && prevCol == currCol) { // from up
            side = 'L';
            ret = { currRow, currCol - 1 };
        }
        else if (prevRow == currRow && prevCol == currCol - 1) { // from left
            side = 'R';
            ret = { currRow - 1, currCol };
        }
        else std::cout << "ERROR" << std::endl;
        if (indicateSide) {
            if (currCol != isOnPath.size() - 1 && isOnPath[currRow][currCol + 1] != 'X') isOnPath[currRow][currCol + 1] = side;
            if (currRow != isOnPath.size() - 1 && isOnPath[currRow + 1][currCol] != 'X') isOnPath[currRow + 1][currCol] = side;
        }
    }
    else if (maze[currRow][currCol] == '|') {
        if (prevRow == currRow - 1 && prevCol == currCol) return { currRow + 1, currCol };
        else if (prevRow == currRow + 1 && prevCol == currCol) return { currRow - 1, currCol };
        else std::cout << "ERROR" << std::endl;
    }
    else if (maze[currRow][currCol] == '-') {
        if (prevRow == currRow && prevCol == currCol - 1) return { currRow, currCol + 1 };
        else if (prevRow == currRow && prevCol == currCol + 1) return { currRow, currCol - 1 };
        else std::cout << "ERROR" << std::endl;
    }
    return ret;
}

void propagate(int row, int col, char c) {
    if (row != 0 && isOnPath[row - 1][col] == '.') isOnPath[row - 1][col] = c; // UP
    if (col != 0 && isOnPath[row][col - 1] == '.') isOnPath[row][col - 1] = c; // LEFT
    if (col != isOnPath.size() - 1 && isOnPath[row][col + 1] == '.') isOnPath[row][col + 1] = c; // RIGHT
    if (row != isOnPath.size() - 1 && isOnPath[row + 1][col] == '.') isOnPath[row + 1][col] = c; // DOWN
}

int main() {
    std::ifstream file("input.in");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }
    std::string line;
    while (std::getline(file, line)) {
        maze.push_back(line);
    }

    std::pair<int, int> start = findStart();
    isOnPath[start.first][start.second] = 'X';
    std::pair<int, int> dir_1_pos = { start.first - 1, start.second };
    isOnPath[dir_1_pos.first][dir_1_pos.second] = 'X';
    std::pair<int, int> prev_1 = start;
    while (dir_1_pos.first != start.first || dir_1_pos.second != start.second) {
        std::pair<int, int> prev_1_tmp = dir_1_pos;
        dir_1_pos = stepTo(prev_1.first, prev_1.second, dir_1_pos.first, dir_1_pos.second, false);
        isOnPath[dir_1_pos.first][dir_1_pos.second] = 'X';
        prev_1 = prev_1_tmp;
    }

    for (int i = 0; i < isOnPath.size(); ++i) {
        for (int j = 0; j < isOnPath[i].size(); ++j) {
            std::cout << isOnPath[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    dir_1_pos = { start.first - 1, start.second };
    prev_1 = start;
    while (dir_1_pos.first != start.first || dir_1_pos.second != start.second) {
        std::pair<int, int> prev_1_tmp = dir_1_pos;
        dir_1_pos = stepTo(prev_1.first, prev_1.second, dir_1_pos.first, dir_1_pos.second, true);
        prev_1 = prev_1_tmp;
    }

    for (int i = 0; i < isOnPath.size(); ++i) {
        for (int j = 0; j < isOnPath[i].size(); ++j) {
            std::cout << isOnPath[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    //while (hasLeft()) {
        //for (int i = 0; i < isOnPath.size(); ++i) {
            //for (int j = 0; j < isOnPath[i].size(); ++j) {
                //if (isOnPath[i][j] == 'L' || isOnPath[i][j] == 'R') propagate(i, j, isOnPath[i][j]);
            //}
        //}
    //}

    //for (int i = 0; i < isOnPath.size(); ++i) {
        //for (int j = 0; j < isOnPath[i].size(); ++j) {
            //std::cout << isOnPath[i][j];
        //}
        //std::cout << std::endl;
    //}

    //int sum = 0;
    //for (int i = 0; i < isOnPath.size(); ++i) {
        //for (int j = 0; j < isOnPath[i].size(); ++j) {
            //if (isOnPath[i][j] == 'R') sum++;
        //}
    //}
    //std::cout << sum << std::endl;
    return 0;
}