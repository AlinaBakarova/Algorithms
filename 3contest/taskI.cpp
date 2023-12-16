#include <iostream>
#include <vector>

const int kSize = 1000000;

long long Min3(long long var_x1, long long var_x2, long long var_x3) {
  long long ans = 0;
  if (var_x1 > var_x2) {
    ans = std::min(var_x2, var_x3);
  } else {
    ans = std::min(var_x1, var_x3);
  }
  return ans;
}

long long Min4(long long var_y5, long long var_y6, long long var_y7,
               long long var_y8) {
  long long ans = 0;
  if (var_y5 > var_y6) {
    ans = Min3(var_y8, var_y6, var_y7);
  } else {
    ans = Min3(var_y5, var_y7, var_y8);
  }
  return ans;
}

long long SecondMin(int32_t var_c1, int32_t var_c2, int32_t var_b1,
                    int32_t var_b2) {
  long long mn = Min4(var_c1, var_c2, var_b1, var_b2);
  long long ans = 0;
  if (var_c1 == mn) {
    ans = Min3(var_c2, var_b1, var_b2);
  } else if (var_c2 == mn) {
    ans = Min3(var_c1, var_b1, var_b2);
  } else if (var_b1 == mn) {
    ans = Min3(var_c1, var_c2, var_b2);
  } else {
    ans = Min3(var_c1, var_c2, var_b1);
  }
  return ans;
}
int32_t SecondMin(int32_t h9, int32_t h10, int32_t h11) {
  int32_t mn = Min3(h9, h10, h11);
  int32_t ans = 0;
  if (h9 == mn) {
    ans = std::min(h10, h11);
  } else if (h10 == mn) {
    ans = std::min(h9, h11);
  } else {
    ans = std::min(h9, h10);
  }
  return ans;
}

class SparseTable {
 public:
  void Build(int32_t quantity, int32_t list_a[]);
  int32_t Answer(int32_t left, int32_t right);

 private:
  std::vector<int32_t> deg_;
  std::vector<std::vector<int32_t>> sparse_;
  std::vector<std::vector<int32_t>> sparse2_;
};
void SparseTable::Build(int32_t quantity, int32_t list_a[]) {
  deg_.reserve(quantity + 1);
  deg_[0] = 0;
  deg_[1] = 0;
  for (int32_t i = 2; i <= quantity; i++) {
    deg_[i] = deg_[i - 1];
    if ((i & (i - 1)) == 0) {
      deg_[i]++;
    }
  }
  sparse_.resize(deg_[quantity] + 1, std::vector<int32_t>(quantity + 1, 0));
  sparse2_.resize(deg_[quantity] + 1, std::vector<int32_t>(quantity + 1, 0));
  for (int32_t i = 0; i < quantity; ++i) {
    sparse_[0][i] = list_a[i];
  }
  for (int32_t i = 0; i < quantity; ++i) {
    sparse2_[0][i] = list_a[i];
  }
  for (int32_t k = 0; k < deg_[quantity]; ++k) {
    for (int32_t i = 0; i + (2 << k) <= quantity; ++i) {
      int32_t var_q = (1 << k);
      int32_t var_j = i + var_q;
      sparse_[k + 1][i] = std::min(sparse_[k][i], sparse_[k][var_j]);
    }
  }

  for (int32_t i = 0; i < quantity - 1; ++i) {
    sparse2_[1][i] = std::max(list_a[i], list_a[i + 1]);
  }
  for (int32_t k = 1; k < deg_[quantity]; ++k) {
    for (int32_t i = 0; i < quantity - ((1 << k) - 1); ++i) {
      int32_t var_j = i + (1 << k);
      sparse2_[k + 1][i] = SecondMin(sparse_[k][i], sparse_[k][var_j],
                                     sparse2_[k][i], sparse2_[k][var_j]);
    }
  }
}
int32_t SparseTable::Answer(int32_t left, int32_t right) {
  left--;
  right--;
  int32_t var_k = deg_[right - left + 1];
  int32_t list_f[4];
  list_f[0] = sparse_[var_k][left];
  list_f[1] = sparse_[var_k][right - (1 << var_k) + 1];
  list_f[2] = sparse2_[var_k][left];
  list_f[3] = sparse2_[var_k][right - (1 << var_k) + 1];
  int32_t var_x;
  if (list_f[0] == list_f[1] || list_f[1] == list_f[2]) {
    var_x = SecondMin(list_f[0], list_f[2], list_f[3]);
  } else if (list_f[0] == list_f[2] || list_f[0] == list_f[3]) {
    var_x = SecondMin(list_f[1], list_f[2], list_f[3]);
  } else if (list_f[1] == list_f[3] || list_f[2] == list_f[3]) {
    var_x = SecondMin(list_f[0], list_f[1], list_f[2]);
  } else {
    var_x = SecondMin(list_f[0], list_f[1], list_f[2], list_f[3]);
  }
  return var_x;
}

int main() {
  int32_t sz;
  int32_t quantity_of_d;
  std::cin >> sz >> quantity_of_d;
  int32_t store[kSize];
  for (int32_t i = 0; i < sz; ++i) {
    std::cin >> store[i];
  }
  SparseTable sp;
  sp.Build(sz, store);
  for (int32_t i = 0; i < quantity_of_d; ++i) {
    int32_t left;
    int32_t right;
    std::cin >> left >> right;
    std::cout << sp.Answer(left, right) << std::endl;
  }
  return 0;
}
