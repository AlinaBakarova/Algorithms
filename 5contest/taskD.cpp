#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

static const int kNum = 6;

struct Point {
  int64_t x;
  int64_t y;

  Point(int64_t x1, int64_t y1) {
    x = x1;
    y = y1;
  }
};

void Theory1(std::vector<Point>& array, int var_n) {
  int64_t ans = 0;
  int32_t i2 = 0;
  while (i2 < var_n) {
    std::unordered_map<int64_t, int64_t> dist;
    int64_t x1 = array[i2].x;
    int64_t y1 = array[i2].y;
    for (int j = 0; j < var_n; ++j) {
      if (i2 != j) {
        int64_t x2 = array[j].x;
        int64_t y2 = array[j].y;
        int64_t var_d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        ++dist[var_d];
      }
    }
    for (std::pair<int64_t, int64_t> elem : dist) {
      ans += elem.second * (elem.second - 1) / 2;
    }
    i2++;
  }
  std::cout << ans;
}

class PointCompare {
 public:
  bool operator()(Point a1, Point b1) {
    return (std::make_pair(a1.x, a1.y) > std::make_pair(b1.x, b1.y));
  }
};

void Theory2(std::vector<Point>& array, int64_t var_n) {
  int64_t ans = 0;
  std::sort(array.begin(), array.end(), PointCompare());

  Point cur_point = array[0];
  int64_t cur_cnt = 0;
  bool flag = false;
  for (int i = 0; i < var_n; i++) {
    if ((array[i].x != cur_point.x || array[i].y != cur_point.y) &&
        (cur_cnt > 2)) {
      cur_point = array[i];
      ans += (cur_cnt * (cur_cnt - 1) * (cur_cnt - 2) / kNum);
      cur_cnt = 1;
      flag = false;
    } else if ((array[i].x != cur_point.x || array[i].y != cur_point.y)) {
      cur_point = array[i];
      cur_cnt = 1;
      flag = false;
    } else {
      ++cur_cnt;
      flag = true;
    }
  }
  if ((static_cast<int>(flag) + cur_cnt) > 3) {
    ans += (cur_cnt * (cur_cnt - 1) * (cur_cnt - 2) / kNum);
  }
  std::cout << ans;
}

int main() {
  int32_t quantity;
  int32_t theory;
  std::cin >> quantity >> theory;
  std::vector<Point> array;
  int32_t index = 0;
  int64_t x;
  int64_t y;
  while (index < quantity) {
    std::cin >> x >> y;
    Point p1(x, y);
    array.push_back(p1);
    index++;
  }
  if (theory == 1) {
    Theory1(array, quantity);
  } else if (theory == 2) {
    Theory2(array, quantity);
  }
}
