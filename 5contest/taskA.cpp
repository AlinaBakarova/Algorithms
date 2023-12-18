#include <iostream>
#include <vector>

static const int32_t kBaseAdd = 18445;
static const int32_t kBaseFactor = 42;
static const int32_t kSize = 40;

class HashTable {
 public:
  HashTable(int32_t number);
  ~HashTable() { delete[] table_; }
  int32_t Find(int32_t var_x);
  void Insert(int32_t var_x);
  void Delete(int32_t var_x);

 private:
  int32_t BaseSize_;
  std::vector<int32_t>* table_;
  int32_t GetHash(int32_t var_x) const;
};

int32_t HashTable::GetHash(int32_t var_x) const {
  return ((kBaseFactor * var_x + kBaseAdd) % BaseSize_);
}

HashTable::HashTable(int32_t number) {
  BaseSize_ = number + kSize;
  table_ = new std::vector<int32_t>[BaseSize_];
}

void HashTable::Insert(int32_t var_x) {
  if (Find(var_x) == -1) {
    int32_t index = GetHash(var_x);
    table_[index].push_back(var_x);
  }
}

int32_t HashTable::Find(int32_t var_x) {
  int32_t ans = 0;
  int32_t index = GetHash(var_x);
  int32_t current_size = table_[index].size();
  bool flag = false;
  for (int32_t i = 0; i < current_size; i++) {
    if (table_[index][i] == var_x) {
      flag = true;
      ans = i;
      break;
    }
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
    int32_t current_size = table_[index].size();
    int32_t temporary = table_[index][current_size - 1];
    table_[index][current_size - 1] = table_[index][inner_index];
    table_[index][inner_index] = temporary;

    table_[index].pop_back();
  }
}

int32_t number;
std::string request_type;
int32_t item;

int main() {
  std::cin >> number;
  HashTable hash_table(number);
  for (int32_t i = 0; i < number; i++) {
    std::cin >> request_type >> item;
    if (request_type == "-") {
      hash_table.Delete(item);
    }
    if (request_type == "+") {
      hash_table.Insert(item);
    }
    int32_t is_in_table = hash_table.Find(item);
    if ((request_type == "?") && (is_in_table != -1)) {
      std::cout << "YES" << std::endl;
    } else if (request_type == "?") {
      std::cout << "NO" << std::endl;
    }
  }
}
