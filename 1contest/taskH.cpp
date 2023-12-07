#include <iostream>
#include <vector>

void QuickSort(std::vector<long long>& vec, int left, int right) {
  if (left >= right) {
    return;
  }
  int left_index = left;
  int right_index = right;
  int mid = (left + right) / 2;
  long long pivot = vec[mid];
  while (left_index <= right_index) {
    while (vec[left_index] < pivot) {
      left_index++;
    }
    while (vec[right_index] > pivot) {
      right_index--;
    }
    if (left_index >= right_index) {
      break;
    }
    std::swap(vec[left_index++], vec[right_index--]);
  }
  QuickSort(vec, left, right_index);
  QuickSort(vec, right_index + 1, right);
}

int main() {
  int quantity;
  std::cin >> quantity;
  std::vector<long long> arr(quantity);
  for (int i = 0; i < quantity; ++i) {
    std::cin >> arr[i];
  }
  QuickSort(arr, 0, quantity - 1);
  for (int i = 0; i < quantity; ++i) {
    std::cout << arr[i] << " ";
  }
}
