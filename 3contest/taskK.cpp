#include <bits/stdc++.h>

int main() {
  int num;
  std::cin >> num;
  std::vector<int> allx;
  std::vector<int> ally;
  std::vector<int> x1(num);
  std::vector<int> x2(num);
  std::vector<int> y1(num);
  std::vector<int> y2(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    ally.push_back(y1[i]);
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
  for (int i = 0; i < num; ++i) {
    int i1 = lower_bound((allx).begin(), (allx).end(), x1[i]) - allx.begin();
    int i2 = lower_bound((allx).begin(), (allx).end(), x2[i]) - allx.begin();
    int j1 = lower_bound((ally).begin(), (ally).end(), y1[i]) - ally.begin();
    int j2 = lower_bound((ally).begin(), (ally).end(), y2[i]) - ally.begin();
    vec_d[i1][j1] += 1;
    vec_d[i1][j2] -= 1;
    vec_d[i2][j1] -= 1;
    vec_d[i2][j2] += 1;
  }
  for (int i = 0; i <= cntx; ++i) {
    for (int j = 0; j <= cnty; ++j) {
      if (i > 0) {
        vec_d[i][j] += vec_d[i - 1][j];
        if (j > 0) {
          vec_d[i][j] -= vec_d[i - 1][j - 1];
        }
      }
      if (j > 0) {
        vec_d[i][j] += vec_d[i][j - 1];
      }
    }
  }
  int64_t ans = 0;
  for (int i = 0; i < cntx; ++i) {
    for (int j = 0; j < cnty; ++j) {
      if (vec_d[i][j] > 0) {
        int64_t dx = allx[i + 1] - allx[i];
        int64_t dy = ally[j + 1] - ally[j];
        ans += dx * dy;
      }
    }
  }
  std::cout << ans << std::endl;
}
