#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

const int kHeapsize = 4000;
const long long kMod = (1 << 30);
long long heap[kHeapsize];
int var_sz = 0;

void SiftUp(int index_i) {
  while (index_i > 1 && heap[index_i / 2] > heap[index_i]) {
    std::swap(heap[index_i / 2], heap[index_i]);
    index_i /= 2;
  }
}

void SiftDown(int index_i) {
  while (index_i <= var_sz) {
    int var_m = index_i;
    int minl = heap[index_i];
    if (index_i * 2 <= var_sz && heap[index_i * 2] < heap[index_i]) {
      var_m = index_i * 2;
      minl = heap[index_i * 2];
    }
    if (index_i * 2 + 1 <= var_sz && heap[index_i * 2 + 1] < minl) {
      var_m = index_i * 2 + 1;
    }
    if (index_i == var_m) {
      break;
    }
    std::swap(heap[index_i], heap[var_m]);
    index_i = var_m;
  }
}

void Add(int var_x) {
  var_sz++;
  heap[var_sz] = var_x;
  SiftUp(var_sz);
}

int GetMin() {
  int ans = heap[1];
  std::swap(heap[1], heap[var_sz]);
  var_sz--;
  SiftDown(1);
  return ans;
}

int main() {
  int quantity;
  int var_k;
  std::cin >> quantity >> var_k;
  long long var_a0;
  long long var_x;
  long long var_y;
  std::cin >> var_a0 >> var_x >> var_y;
  long long prev = var_a0;
  int var_t;
  for (int i = 0; i < quantity; i++) {
    long long val = (1LL * prev * var_x + var_y) % kMod;
    prev = val;
    Add(-val);
    if (var_sz > var_k) {
      var_t = GetMin();
    }
  }
  std::vector<int> ans;
  for (int i = var_k; i >= 1; i--) {
    ans.push_back(heap[i] * (-1));
  }
  sort(ans.begin(), ans.end());
  int size_1 = 0;
  if (var_t != 0) {
    size_1 = ans.size();
  }
  if (size_1 == 0) {
    size_1 = ans.size();
  }
  for (int i = 0; i < size_1; i++) {
    std::cout << ans[i] << " ";
  }
  return 0;
}
