#include <iostream>
#include <vector>

static const int32_t kBaseFactor = 56;
static const int32_t kBaseAdd = 4567;
static const int32_t kMod = 156;

class HashTable {
 public:
  HashTable(int64_t num);
  ~HashTable() { delete[] table_; }
  int32_t Find(int32_t var_x) const;
  void Insert(int32_t var_x);
  void Delete(int32_t var_x);

 private:
  int64_t kBaseSize_;
  std::vector<int64_t>* table_;
  int64_t GetHash(int64_t var_x) const;
};

int64_t HashTable::GetHash(int64_t var_x) const {
  return static_cast<int64_t>((kBaseFactor * var_x + kBaseAdd) % kBaseSize_);
}

HashTable::HashTable(int64_t num) {
  kBaseSize_ = num + (rand() % kMod);
  table_ = new std::vector<int64_t>[kBaseSize_];
}

void HashTable::Insert(int32_t var_x) {
  int32_t index = GetHash(var_x);
  table_[index].push_back(var_x);
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
    int32_t temp = table_[index][cur_size - 1];
    table_[index][cur_size - 1] = table_[index][inner_index];
    table_[index][inner_index] = temp;
    table_[index].pop_back();
  }
}

int quantity;
std::vector<int64_t> ans;
size_t index_sz;

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
