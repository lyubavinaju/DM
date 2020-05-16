#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;
const long long mod = 998244353;

long long module(long long val) {
    long long res = val % mod;
    while (res < 0)
        res = res + mod;
    return res;
}

void prod(vector<long long> &product, vector<long long> &a, vector<long long> &q) {
    for (int l = 0; l <= product.size() - 1; ++l) {
        product[l] = 0;
        for (int i = 0; i <= l; ++i) {
            product[l] += module(a[i] * q[l - i]);
            product[l] = module(product[l]);
        }
    }
}

void summa(vector<long long> &s, vector<long long> &p, vector<long long> &q) {
    for (int k = 0; k <= s.size() - 1; ++k) {
        s[k] = module(p[k] + q[k]);
        s[k] = module(s[k]);
    }
}

long long factorial(long long n) {
    long long res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
        res = module(res);
    }
    return module(res);
}

long long modular_pow(long long base, long long n) {
    long long c = 1;
    for (int i = 1; i <= n; i++) {
        c = module(c * base);
        c = module(c);
    }
    return c;
}

long long gcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}


long long getReversed(long long a) {
    long long x, y;
    long long g = gcd(a, mod, x, y);
    if (g != 1 && mod % g == 0 && g <= 0 && a < 0)
//        throw "no solution";
//    else {
        x = (x % mod + mod) % mod;
    return x;
//    }
}

long long getSqRootCoefficient(long long n) {
    if (n == 0)return 1;
    long long a = factorial(2 * n);
    a = module(a);

    long long b = module((1 - 2 * n) * (n % 2 == 0 ? 1 : -1));
    b *= module(factorial(n) * factorial(n));
    b = module(b);
    b *= modular_pow(4, n);
    b = module(b);
    b = getReversed(module(b));
    return module(a * b);
}

long long getECoefficient(long long n) {
    if (n == 0)return 1;
    long long a = 1;
    long long b = factorial(n);
    b = getReversed(module(b));
    return module(a * b);

}

long long getLnCoefficient(long long n) {
    if (n == 0)return 0;
    long long b = n * (n % 2 == 0 ? -1 : 1);
    b = getReversed(module(b));
    return module(b);

}


void multiply(long long coefficient, vector<long long> &vec, vector<long long> &source) {
    for (int i = 0; i < vec.size(); ++i) {
        vec[i] = source[i];
        vec[i] *= module(coefficient);
        vec[i] = module(vec[i]);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> p(max(n, m) + 1, 0);
    for (int i = 0; i <= n; ++i) {
        cin >> p[i];
    }
    vector<vector<long long>> x;
    for (int j = 0; j < m; ++j) {
        x.push_back(vector<long long>(m));
    }
    for (int l = 0; l < m; ++l) {
        if (x.size() > 1) x[1][l] = p[l];
        x[0][l] = 0;
    }
    x[0][0] = 1;

    for (int j = 2; j < m; ++j) {
        prod(x[j], x[j - 1], p);
    }

    vector<vector<long long>> sqRoot;
    for (int j = 0; j < m; ++j) {
        sqRoot.push_back(vector<long long>(m));
    }
    vector<vector<long long >> e;
    for (int j = 0; j < m; ++j) {
        e.push_back(vector<long long>(m));
    }
    vector<vector<long long >> ln;
    for (int j = 0; j < m; ++j) {
        ln.push_back(vector<long long>(m));
    }
    for (int j = 0; j < m; ++j) {
        multiply(getSqRootCoefficient(j), sqRoot[j], x[j]);
        multiply(getECoefficient(j), e[j], x[j]);
        multiply(getLnCoefficient(j), ln[j], x[j]);
    }

    for (int j = 1; j < m; ++j) {
        summa(sqRoot[j], sqRoot[j], sqRoot[j - 1]);
        summa(e[j], e[j], e[j - 1]);
        summa(ln[j], ln[j], ln[j - 1]);
    }

    for (int k = 0; k < sqRoot[m - 1].size(); ++k) {
        cout << sqRoot[m - 1][k] << " ";
    }
    cout << "\n";
    for (int k = 0; k < e[m - 1].size(); ++k) {
        cout << e[m - 1][k] << " ";
    }
    cout << "\n";
    for (int k = 0; k < ln[m - 1].size(); ++k) {
        cout << ln[m - 1][k] << " ";
    }
    return 0;
}