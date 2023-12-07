#include <iostream>
#include <string>
#include <vector>

struct Heap {
 private:
  int size_ = 0;
  std::vector<long long> main_heap_;
  int request_number_ = 0;
  std::vector<int> heap_of_request_numbers_;

 public:
  void Insert(long long var_x) {
    if (main_heap_.empty()) {
      main_heap_.push_back(0);
      heap_of_request_numbers_.push_back(0);
    }
    size_++;
    main_heap_.push_back(var_x);
    request_number_++;
    heap_of_request_numbers_.push_back(request_number_);
    SiftUp(size_);
  }

  void ExtractMin() {
    request_number_++;
    std::swap(main_heap_[1], main_heap_[size_]);
    std::swap(heap_of_request_numbers_[1], heap_of_request_numbers_[size_]);
    --size_;
    main_heap_.pop_back();
    heap_of_request_numbers_.pop_back();
    SiftDown(1);
  }

  long long GetMin() {
    request_number_++;
    return main_heap_[1];
  }

  void DecreaseKey(long long var_t, long long delta) {
    for (int i = 0; i <= size_; ++i) {
      if (heap_of_request_numbers_[i] == var_t) {
        int var_v = i;
        main_heap_[var_v] -= delta;
        SiftUp(var_v);
        break;
      }
    }
    request_number_++;
  }

  void SiftUp(int var_v) {
    while (var_v != 1) {
      if (main_heap_[var_v] < main_heap_[var_v / 2]) {
        std::swap(main_heap_[var_v], main_heap_[var_v / 2]);
        std::swap(heap_of_request_numbers_[var_v],
                  heap_of_request_numbers_[var_v / 2]);
        var_v /= 2;
      } else {
        break;
      }
    }
  }

  void SiftDown(int var_v) {
    while (2 * var_v <= size_) {
      int var_u = 2 * var_v;
      if ((2 * var_v + 1 <= size_) &&
          (main_heap_[2 * var_v + 1] < main_heap_[2 * var_v])) {
        var_u = 2 * var_v + 1;
      }
      if (main_heap_[var_u] < main_heap_[var_v]) {
        std::swap(main_heap_[var_u], main_heap_[var_v]);
        std::swap(heap_of_request_numbers_[var_u],
                  heap_of_request_numbers_[var_v]);
        var_v = var_u;
      } else {
        break;
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(0);
  std::cin.tie(0);
  int var_n;
  std::cin >> var_n;
  Heap heap;
  for (int i = 0; i < var_n; ++i) {
    std::string request;
    std::cin >> request;
    if (request == "insert") {
      long long var_x;
      std::cin >> var_x;
      heap.Insert(var_x);
    } else if (request == "decreaseKey") {
      long long var_v;
      long long delta;
      std::cin >> var_v >> delta;
      heap.DecreaseKey(var_v, delta);
    } else if (request == "extractMin") {
      heap.ExtractMin();
    } else {
      long long min_heap = heap.GetMin();
      std::cout << min_heap << '\n';
    }
  }
  return 0;
}
