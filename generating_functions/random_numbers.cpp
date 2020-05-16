#include <iostream>
#include <vector>

using namespace std;
const int mod = 104857601;

int module(long long val) {
    int res = val % mod;
    while (res < 0)
        res = res + mod;
    return res;
//    return val;
}

void prod(vector<int> &product, vector<int> &a, vector<int> &q) {
    for (int l = 0; l <= product.size() - 1; ++l) {
        product[l] = 0;
        for (int i = 0; i <= l; ++i) {
            product[l] += module((long long) (i < a.size() ? a[i] : 0) *
                                 (long long) (l - i >= 0 && l - i < q.size() ? q[l - i] : 0));
            product[l] = module(product[l]);
        }
    }
}

int main() {
    int k;
    long long n;
    cin >> k >> n;
    n--;
    vector<int> a(2 * k + 1);
    vector<int> c(k);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < k; ++i) {
        cin >> c[i];
    }

    vector<int> q(k + 1);
    vector<int> minus_q(k + 1);
    vector<int> res(2 * k + 1);
    q[0] = 1;
    minus_q[0] = 1;
    for (int j = 0; j < c.size(); ++j) {
        q[j + 1] = -c[j];
        q[j + 1] = module(q[j + 1]);
        minus_q[j + 1] = -c[j] * ((j + 1) % 2 == 0 ? 1 : -1);
        minus_q[j + 1] = module(minus_q[j + 1]);
    }

    while (n >= k) {
        for (int j = k; j < a.size(); ++j) {
            a[j] = 0;
            for (int i = 1; i <= k; ++i) {
                a[j] += module(-(long long) q[i] * (long long) a[j - i]);
                a[j] = module(a[j]);
            }
        }
        prod(res, q, minus_q);
        q[0] = 1;
        minus_q[0] = 1;
        int index = 0;
        for (int i = 1; i < res.size(); ++i) {
            if (i % 2 == 0) {
                ++index;
                q[index] = res[i];
                q[index] = module(q[index]);
                minus_q[index] = res[i] * (index % 2 == 0 ? 1 : -1);
                minus_q[index] = module(minus_q[index]);
            } else {
                if (res[i] != 0)throw "2";
            }
        }
        index = 0;
        for (int i = 0; i < a.size(); ++i) {
            if (i % 2 == n % 2) {
                a[index] = a[i];
                index++;
            }
        }
        n /= 2;
    }
    cout << a[n];

    return 0;
}