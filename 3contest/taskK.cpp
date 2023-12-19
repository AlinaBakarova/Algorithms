#include <bits/stdc++.h>

#include <iostream>

static const int kSize = 1500;

int64_t Solution(int num) {
  std::vector<int> allx;
  std::vector<int> ally;
  std::vector<int> x1(kSize);
  std::vector<int> x2(kSize);
  std::vector<int> rr(kSize);
  std::vector<int> y2(kSize);
  int64_t ans = 0;
  for (int i = 0; i < num; ++i) {
    std::cin >> x1[i] >> rr[i] >> x2[i] >> y2[i];
    ally.push_back(rr[i]);
    ally.push_back(y2[i]);
    allx.push_back(x1[i]);
    allx.push_back(x2[i]);
  }
  sort((ally).begin(), (ally).end());
  sort((allx).begin(), (allx).end());
  allx.resize(unique((allx).begin(), (allx).end()) - allx.begin());
  ally.resize(unique((ally).begin(), (ally).end()) - ally.begin());
  int cntx = allx.size();
  int cnty = ally.size();
  std::vector<std::vector<int>> vec_d(cntx + 1, std::vector<int>(cnty + 1));
  int ind = 0;
  while (ind < num) {
    int i1 = lower_bound((allx).begin(), (allx).end(), x1[ind]) - allx.begin();
    int i2 = lower_bound((allx).begin(), (allx).end(), x2[ind]) - allx.begin();
    int j1 = lower_bound((ally).begin(), (ally).end(), rr[ind]) - ally.begin();
    int j2 = lower_bound((ally).begin(), (ally).end(), y2[ind]) - ally.begin();
    vec_d[i1][j1] += 1;
    vec_d[i1][j2] -= 1;
    vec_d[i2][j1] -= 1;
    vec_d[i2][j2] += 1;
    ++ind;
  }
  for (int i = 0; i <= cntx; ++i) {
    for (int j = 0; j <= cnty; ++j) {
      if (i > 0 && j > 0) {
        vec_d[i][j] += vec_d[i - 1][j];
        vec_d[i][j] -= vec_d[i - 1][j - 1];
      } else if (i > 0) {
        vec_d[i][j] += vec_d[i - 1][j];
      }
      if (j > 0) {
        vec_d[i][j] += vec_d[i][j - 1];
      }
    }
  }
  for (int i = 0; i < cntx; ++i) {
    for (int j = 0; j < cnty; ++j) {
      if (vec_d[i][j] > 0) {
        int64_t dx = allx[i + 1] - allx[i];
        int64_t dy = ally[j + 1] - ally[j];
        ans += dx * dy;
      }
    }
  }
  return ans;
}

int main() {
  int num;
  std::cin >> num;
  std::cout << Solution(num) << std::endl;
}
