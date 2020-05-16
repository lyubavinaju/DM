#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const long long mod = 998244353;

long long module(long long val) {
    long long res = val % mod;
    if (res < 0)
        res = res + mod;
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    int size = max(m, n);
    vector<long long> p(size + size + 1, 0);
    vector<long long> q(size + size + 1, 0);
    for (int i = 0; i <= n; ++i) {
        cin >> p[i];
    }
    for (int j = 0; j <= m; ++j) {
        cin >> q[j];
    }

    vector<long long> summa(size + 1);
    int lastSumIndex = 0;
    for (int k = 0; k <= size; ++k) {
        summa[k] = (p[k] + q[k]) % mod;
        summa[k] %= mod;
        if (summa[k] != 0) {
            lastSumIndex = k;
        }
    }
    vector<long long> product(size + size + 1, 0);
    int lastProductIndex = 0;
    for (int l = 0; l <= size + size; ++l) {
        for (int i = 0; i <= l; ++i) {
            product[l] += (p[i] * q[l - i]) % mod;
            product[l] %= mod;
        }
        if (product[l] != 0) {
            lastProductIndex = l;
        }
    }


    vector<long long> a(1000);
    for (int i = 0; i < a.size(); ++i) {
        a[i] = 0;
        if (i < p.size()) {
            a[i] = p[i];
        }

        for (int k = 0; k <= i - 1; ++k) {
            if (i - k < q.size()) {
                a[i] -= module(a[k] * q[i - k]);
                a[i] = module(a[i]);
            }
        }
    }


    cout << lastSumIndex << "\n";
    for (int i = 0; i <= lastSumIndex; ++i) {
        cout << summa[i] << " ";
    }
    cout << "\n" << lastProductIndex << "\n";
    for (int i = 0; i <= lastProductIndex; ++i) {
        cout << product[i] << " ";
    }
    cout << "\n";
    for (long long i : a) {
        cout << i << " ";
    }

    return 0;
}