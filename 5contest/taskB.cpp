#include <iostream>
#include <vector>

class HashTable {
 public:
  HashTable(int64_t num);
  ~HashTable() { delete[] table_; }
  int32_t Find(int32_t var_x) const;
  void Insert(int32_t var_x);
  void Delete(int32_t var_x);

 private:
  static const int32_t kBaseFactor = 56;
  static const int32_t kBaseAdd = 4567;
  int64_t BaseSize_;
  int64_t buffer_size_;
  std::vector<int64_t>* table_;
  int64_t GetHash(int64_t var_x) const;
  void Resize();
};

int64_t HashTable::GetHash(int64_t var_x) const {
  return static_cast<int64_t>((kBaseFactor * var_x + kBaseAdd) % BaseSize_);
}

HashTable::HashTable(int64_t num) {
  BaseSize_ = num;
  buffer_size_ = num * 2;
  table_ = new std::vector<int64_t>[BaseSize_];
}
void HashTable::Resize() {
  int32_t old_size = BaseSize_;
  BaseSize_ *= 2;
  std::vector<int64_t>* table_2 = new std::vector<int64_t>[BaseSize_];
  for (int32_t i = 0; i < old_size; i++) {
    table_2[i] = table_[i];
  }
  std::swap(table_2, table_);
  delete[] table_2;
}

void HashTable::Insert(int32_t var_x) {
  if (BaseSize_ + 1 > int(buffer_size_)) {
    Resize();
  }
  int32_t index = GetHash(var_x);
  table_[index].push_back(var_x);
  buffer_size_++;
}

int32_t HashTable::Find(int32_t var_x) const {
  int32_t index = GetHash(var_x);
  int32_t cur_size = table_[index].size();
  int32_t i2 = 0;
  int32_t ans;
  bool flag = false;
  while (i2 < cur_size) {
    if (table_[index][i2] == var_x) {
      ans = i2;
      flag = true;
      break;
    }
    i2 += 1;
  }
  if (!flag) {
    ans = -1;
  }
  return ans;
}

void HashTable::Delete(int32_t var_x) {
  int32_t inner_index = Find(var_x);
  if (inner_index != -1) {
    int32_t index = GetHash(var_x);
    int32_t cur_size = table_[index].size();
    std::swap(table_[index][cur_size - 1], table_[index][inner_index]);
    table_[index].pop_back();
  }
}

int quantity;
std::vector<int64_t> ans;

size_t Solution() {
  int64_t var_x;
  HashTable h_table(quantity);
  int32_t index = 0;
  while (index < quantity) {
    std::cin >> var_x;
    h_table.Insert(var_x);
    index++;
  }
  std::cin >> quantity;
  index = 0;
  while (index < quantity) {
    std::cin >> var_x;
    if (h_table.Find(var_x) != -1) {
      ans.push_back(var_x);
      h_table.Delete(var_x);
    }
    index += 1;
  }
  return ans.size();
}

int main() {
  size_t index_sz;
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> quantity;
  HashTable h_table(quantity);
  size_t size2 = Solution();
  std::cout << size2 << std::endl;
  index_sz = 0;
  while (index_sz < size2) {
    std::cout << ans[index_sz] << " ";
    index_sz += 1;
  }
}
