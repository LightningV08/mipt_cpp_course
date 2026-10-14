#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

bool Deposit(long long& balance) {
  long long amount = 0;
  if (!(std::cin >> amount) || amount <= 0 ||
      balance > std::numeric_limits<long long>::max() - amount) {
    return false;
  }
  balance += amount;
  return true;
}

bool Withdraw(long long& balance) {
  long long amount = 0;
  if (!(std::cin >> amount) || amount <= 0 || amount > balance) {
    return false;
  }
  balance -= amount;
  return true;
}

bool Balance(long long& balance) {
  std::cout << balance << '\n';
  return true;
}

bool Reset(long long& balance) {
  balance = 0;
  return true;
}

bool Inc(long long& balance) {
  if (balance == std::numeric_limits<long long>::max()) {
    return false;
  }
  ++balance;
  return true;
}

using Operation = bool (*)(long long&);

struct Command {
  const char* name;
  Operation operation;
};

int main() {
  long long balance = 0;
  const Command commands[] = {{"deposit", Deposit},
                              {"withdraw", Withdraw},
                              {"balance", Balance},
                              {"reset", Reset},
                              {"inc", Inc}};
  const int command_count = sizeof(commands) / sizeof(commands[0]);
  char name[16] = {};
  while (std::cin >> std::setw(16) >> name) {
    if (std::strcmp(name, "stop") == 0) {
      break;
    }
    int index = 0;
    while (index < command_count &&
           std::strcmp(name, commands[index].name) != 0) {
      ++index;
    }
    if (index == command_count || !commands[index].operation(balance)) {
      std::cout << "error\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}
