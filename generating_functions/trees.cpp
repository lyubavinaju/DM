#include <vector>
#include <iostream>

using namespace std;
const long long mod = 1000000000 + 7;

int main() {
    int k, m;
    cin >> k >> m;
    vector<long long> c(k);
    for (int i = 0; i < k; ++i) {
        cin >> c[i];
    }

    vector<long long> d(m + 1);
    vector<long long> children(m + 1);
    d[0] = 1;
    children[0] = 1;
    for (int w = 1; w <= m; ++w) {
        d[w] = 0;
        children[w] = 0;
        for (int num = 0; num < k; ++num) {
            if (w - c[num] >= 0) {
                d[w] += children[w - c[num]];
                d[w] %= mod;
            }
        }

        for (int i = 0; i <= w; ++i) {
            children[w] += (d[i] * d[w - i]) % mod;
            children[w] %= mod;
        }


    }
    for (int j = 1; j <= m; ++j) {
        cout << d[j] << " ";
    }
    return 0;
}