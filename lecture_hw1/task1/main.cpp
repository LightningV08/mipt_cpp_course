#include <iomanip>
#include <iostream>

struct TemperatureLimits {
  int minimum;
  int maximum;
};

double Average(const int* temperatures, int count) {
  long long sum = 0;
  for (int i = 0; i < count; ++i) {
    sum += temperatures[i];
  }
  return (double)sum / count;
}

TemperatureLimits MinMax(const int* temperatures, int count) {
  TemperatureLimits result{temperatures[0], temperatures[0]};
  for (int i = 1; i < count; ++i) {
    if (temperatures[i] < result.minimum) {
      result.minimum = temperatures[i];
    }
    if (temperatures[i] > result.maximum) {
      result.maximum = temperatures[i];
    }
  }
  return result;
}

int FrostDays(const int* temperatures, int count) {
  int result = 0;
  for (int i = 0; i < count; ++i) {
    if (temperatures[i] < 0) {
      ++result;
    }
  }
  return result;
}

int main() {
  int count = 0;
  if (!(std::cin >> count) || count <= 0) {
    return 0;
  }
  int* temperatures = new int[count];
  for (int i = 0; i < count; ++i) {
    if (!(std::cin >> temperatures[i])) {
      delete[] temperatures;
      return 0;
    }
  }
  const TemperatureLimits limits = MinMax(temperatures, count);
  std::cout << std::fixed << std::setprecision(1)
            << Average(temperatures, count) << '\n';
  std::cout << limits.minimum << ' ' << limits.maximum << '\n';
  std::cout << FrostDays(temperatures, count) << '\n';
  delete[] temperatures;
}
