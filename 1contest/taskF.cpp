#include <iostream>
#include <vector>

const int kConst = 10000007;
const int kC1 = 123;
const int kC2 = 45;
const int kC3 = 10004321;

int quantity, kth;
std::vector<int> array(kConst), num_b(kConst);

int Get() {
  int ans;
  if (quantity == 1) {
    return array[0];
  }
  int prev = quantity / 2;
  int lest = 0;
  int mid = 0;
  int right = 0;

  for (int i = 0; i < quantity; i++) {
    if (array[i] < array[prev]) {
      lest++;
    } else if (array[i] > array[prev]) {
      right++;
    } else {
      mid++;
    }
  }

  if (lest <= kth - 1 && lest + mid >= kth) {
    return array[prev];
  }
  if (lest >= kth) {
    int index_j = 0;
    for (int i = 0; i < quantity; i++) {
      if (array[i] < array[prev]) {
        num_b[index_j++] = array[i];
      }
    }
    swap(array, num_b);
    quantity = lest;
    ans = Get();
  } else {
    int index_j = 0;
    for (int i = 0; i < quantity; i++) {
      if (array[i] > array[prev]) {
        num_b[index_j++] = array[i];
      }
    }
    swap(array, num_b);
    quantity = right;
    kth -= lest + mid;
    ans = Get();
  }
  return ans;
}

int main() {
  std::cin >> quantity >> kth >> array[0] >> array[1];
  for (int i = 2; i < quantity; i++) {
    array[i] = (array[i - 1] * kC1 + array[i - 2] * kC2) % kC3;
  }
  std::cout << Get() << std::endl;
  return 0;
}
