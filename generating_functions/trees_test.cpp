#include <iostream>
#include <vector>

using namespace std;
const long long mod = 998244353;

int module(long long val) {
    int res = val % mod;
    while (res < 0)
        res = res + mod;
    return res;
}


int main() {
    long long k, n;
    cin >> k >> n;
    vector<vector<long long>> C(k);
    for (int i = 0; i <= k - 1; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i == 0) {
                C[0].push_back(1);
            } else {
                long long res = 0;
                if (j < C[i - 1].size()) {
                    res += C[i - 1][j];
                    res = module(res);
                }
                if ((j - 1 >= 0) && (j - 1 < C[i - 1].size())) {
                    res += C[i - 1][j - 1];
                    res = module(res);
                }
                C[i].push_back(res);
            }
        }
    }

    vector<long long> p;
    vector<long long> q;
    int j = 0;
    while (j <= k - 2 - j) {
        p.push_back(C[k - 2 - j][j]);
        j++;
    }
    j = 0;
    while (j <= k - 1 - j) {
        q.push_back(C[k - 1 - j][j]);
        j++;
    }

    for (int i = 0; i < p.size(); ++i) {
        if (i % 2 != 0) {
            p[i] = -p[i];
            p[i] = module(p[i]);
        }
    }
    for (int i = 0; i < q.size(); ++i) {
        if (i % 2 != 0) {
            q[i] = -q[i];
            q[i] = module(q[i]);
        }
    }

    vector<long long> ans;
    for (int i = 0; i <= n - 1; ++i) {
        long long res = 0;
        for (j = 1; j < q.size(); ++j) {
            res += (module(-q[j])) * (i - j >= 0 && i - j < ans.size() ? ans[i - j] : 0);
            res = module(res);
        }
        res += (i < p.size() ? p[i] : 0);
        res = module(res);
        ans.push_back(res);
    }
    for (int l = 0; l < ans.size(); ++l) {
        cout << ans[l] << "\n";
    }

    return 0;
}