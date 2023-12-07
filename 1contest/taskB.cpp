#include <math.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

static const int kPrecision = 100;
static const int kPrecision2 = 10;

int main() {
  int num;
  std::cin >> num;
  std::vector<double> list(num);
  double temp;
  for (int i = 0; i < num; ++i) {
    std::cin >> temp;
    list[i] = round(temp * kPrecision) / kPrecision;
  }
  std::vector<long double> results(num + 1);
  results[0] = std::log(1);
  results[1] = std::log(list[0]);
  for (int i = 2; i <= num; ++i) {
    results[i] = results[i - 1] + std::log(list[i - 1]);
  }
  int quu;
  std::cin >> quu;
  for (int i = 0; i < quu; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    double ans;
    ans = exp((results[right + 1] - results[left]) *
              (1 / (double)(right - left + 1)));
    std::cout << std::setprecision(kPrecision2) << std::fixed << ans << "\n";
  }
  return 0;
}
