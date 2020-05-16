#include <iostream>
#include <vector>

using namespace std;


int main() {
    int k;
    cin >> k;
    vector<long long> a(k);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    vector<long long> c(k + 1, -1);
    for (int j = 1; j <= k; ++j) {
        cin >> c[j];
    }
    vector<long long> q(k + 1);
    q[0] = 1;
    for (int l = 1; l <= k; ++l) {
        q[l] = -c[l];
    }
    vector<long long> product(k, 0);
    int lastProductIndex = 0;
    for (int l = 0; l <= k - 1; ++l) {
        for (int i = 0; i <= l; ++i) {
            product[l] += (a[i] * q[l - i]);
        }
        if (product[l] != 0) {
            lastProductIndex = l;
        }
    }
    cout << lastProductIndex << "\n";
    for (int m = 0; m <= lastProductIndex; ++m) {
        cout << product[m] << " ";
    }
    cout << "\n" << k << "\n";
    for (int n = 0; n <= k; ++n) {
        cout << q[n] << " ";
    }
    return 0;
}