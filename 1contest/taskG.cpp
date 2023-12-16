#include <iostream>
#include <vector>

const int kC1 = 255;
const int kC2 = 8;
const int kZero = 0;

int GetByte(int index, unsigned long long number) {
  return kC1 & (number >> (kC2 * index));
}

void RadixSort(std::vector<unsigned long long>& array, int& amount) {
  for (int i = kZero; i != kC2; i++) {
    std::vector<unsigned long long> auxiliary_array(amount, kZero);
    for (int i = kZero; i < amount; i++) {
      auxiliary_array[i] = array[i];
    }
    std::vector<int> auxiliary_amount(kC1 + 2, kZero);

    int index_j = kZero;
    while (index_j != amount) {
      auxiliary_amount[GetByte(i, auxiliary_array[index_j]) + 1]++;
      index_j++;
    }
    index_j = 1;
    while (index_j != kC1 + 2) {
      auxiliary_amount[index_j] += auxiliary_amount[index_j - 1];
      index_j++;
    }
    index_j = kZero;
    while (index_j != amount) {
      array[auxiliary_amount[GetByte(i, auxiliary_array[index_j])]] =
          auxiliary_array[index_j];
      auxiliary_amount[GetByte(i, auxiliary_array[index_j])]++;
      index_j++;
    }
  }
}

int main() {
  int amount;
  std::cin >> amount;
  std::vector<unsigned long long> array(amount, kZero);
  for (int i = kZero; i != amount; i++) {
    std::cin >> array[i];
  }
  RadixSort(array, amount);
  for (int i = kZero; i < amount; i++) {
    std::cout << array[i] << "\n";
  }
  return 0;
}
