#include <iostream>
#include <vector>


using namespace std;

void prod(vector<long long> &product, vector<long long> &a, vector<long long> &q) {
    for (int l = 0; l <= product.size() - 1; ++l) {
        product[l] = 0;
        for (int i = 0; i <= l; ++i) {
            product[l] += (i < a.size() ? a[i] : 0) *
                          (l - i >= 0 && l - i < q.size() ? q[l - i] : 0);
        }
    }
}

void getTempRes(vector<long long int> &tempRes, long long int k) {
    if (k == 0) {
        tempRes[0] = 1;
        return;
    }
    vector<long long> currentBrace(2);
    for (int j = 1; j <= k; ++j) {
        currentBrace[1] = 1;
        currentBrace[0] = j;
        if (j > 1) {
            vector<long long> result(k + 1);
            prod(result, tempRes, currentBrace);
            for (int l = 0; l < tempRes.size(); ++l) {
                tempRes[l] = l < result.size() ? result[l] : 0;
            }

        } else {
            tempRes[1] = 1;
            tempRes[0] = j;
        }

    }


}

long long factorial(long long n) {
    long long res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

long long C(long long k, long long n) {
    long long res = factorial(n);
    res /= factorial(k);
    res /= factorial(n - k);
    return res;
}

long long r_pow(long long pow, long long r) {
    long long res = 1;
    for (int i = 1; i <= pow; ++i) {
        res *= (-r);
    }
    return res;
}

int main() {
    long long r;
    long long k;
    long long d;
    cin >> r >> k;
    vector<long long> b(k + 1);
    for (int i = 0; i <= k; ++i) {
        cin >> b[i];
    }
    vector<long long> a(k + 1);
    d = k;
    while (k >= 0) {
        long long znam = factorial(k);
        a[k] = znam * b[k];
        vector<long long> temp_res(k + 1);
        getTempRes(temp_res, k);
        for (int i = 0; i < temp_res.size(); ++i) {
            temp_res[i] *= b[k];
        }

        for (int j = 0; j < temp_res.size(); ++j) {
            b[j] -= temp_res[j];
        }
        k--;
    }

    long long lastP = -1;
    vector<long long> p(d + 1);
    for (int i = 0; i < p.size(); ++i) {
        p[i] = 0;
        for (int n = 0; n <= d - i; ++n) {
            p[i] += a[n] * C(i, d - n);
        }
        p[i] *= r_pow(i, r);
        if (p[i] != 0)lastP = i;
    }
    cout << lastP << "\n";
    for (int i1 = 0; i1 < p.size(); ++i1) {
        cout << p[i1] << " ";
    }

    vector<long long> q(d + 2);
    q[0] = 1;
    q[1] = -r;
    vector<long long> temp_brace(2);
    temp_brace[0] = 1;
    temp_brace[1] = -r;
    cout << "\n" << d + 1 << "\n";
    for (int l = 1; l < d + 1; ++l) {
        vector<long long> temp_res(d + 2);
        prod(temp_res, q, temp_brace);
        for (int i = 0; i < q.size(); ++i) {
            q[i] = i < temp_res.size() ? temp_res[i] : 0;
        }
    }
    for (int m = 0; m < q.size(); ++m) {
        cout << q[m] << " ";
    }
    return 0;
}

