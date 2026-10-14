#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

constexpr int kRows = 5;
constexpr int kColumns = 10;

bool Fits(int x, int y, int length) {
  return x >= 0 && x < kColumns && y >= 0 && y < kRows && length > 0 &&
         length <= kColumns - x;
}

void Clear(char board[][kColumns]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kColumns; ++x) {
      board[y][x] = ' ';
    }
  }
}

bool Put(char board[][kColumns], int x, int y, char symbol) {
  if (!Fits(x, y, 1)) {
    return false;
  }
  board[y][x] = symbol;
  return true;
}

bool Text(char board[][kColumns], int x, int y, const char* word) {
  const int length = (int)std::strlen(word);
  if (!Fits(x, y, length)) {
    return false;
  }
  for (int i = 0; i < length; ++i) {
    Put(board, x + i, y, word[i]);
  }
  return true;
}

void Print(const char board[][kColumns]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kColumns; ++x) {
      std::cout << board[y][x];
    }
    std::cout << '\n';
  }
}

int main() {
  char board[kRows][kColumns];
  Clear(board);
  char name[16] = {};
  while (std::cin >> std::setw(16) >> name) {
    if (std::strcmp(name, "quit") == 0) {
      break;
    }
    if (std::strcmp(name, "clear") == 0) {
      Clear(board);
    } else if (std::strcmp(name, "print") == 0) {
      Print(board);
    } else if (std::strcmp(name, "put") == 0) {
      int x = 0;
      int y = 0;
      char symbol = ' ';
      if (!(std::cin >> x >> y >> symbol) || !Put(board, x, y, symbol)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(name, "text") == 0) {
      int x = 0;
      int y = 0;
      char word[12] = {};
      if (!(std::cin >> x >> y >> std::setw(12) >> word) ||
          !Text(board, x, y, word)) {
        std::cout << "error\n";
      }
    } else {
      std::cout << "error\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}
