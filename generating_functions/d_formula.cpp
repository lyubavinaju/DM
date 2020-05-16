#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

uint64_t gcd(uint64_t a, uint64_t b) {
    if (a == 0) {
        return b;
    }
    uint64_t d = gcd(b % a, a);
    return d;
}

void reduce(uint64_t &chisl, uint64_t &znam) {
    if (chisl == 0) {
        znam = 1;
        return;
    }
    while (true) {
        uint64_t g = gcd(chisl, znam);
        if (g == 1)break;
        chisl /= g;
        znam /= g;
    }

}

void hard_sum(uint64_t &chisl, uint64_t &znam, bool &negative,
              uint64_t chisl1, uint64_t znam1, bool negative1) {

    if (chisl == 0) {
        chisl = chisl1;
        znam = znam1;
        negative = negative1;
        return;
    }
    if (chisl1 == 0) {
        return;
    }

    uint64_t g = gcd(znam, znam1);
    uint64_t g_all = 1;
    while (g != 1) {
        g_all *= g;
        znam /= g;
        znam1 /= g;
        g = gcd(znam, znam1);
    }
    uint64_t res_chisl;
    uint64_t res_znam;
    if ((!negative && !negative1) || (negative && negative1)) {
        res_chisl = chisl * znam1 + chisl1 * znam;

    } else {
        uint64_t left = chisl * znam1;
        uint64_t right = chisl1 * znam;
        if (negative) {
            if (left < right) {
                res_chisl = right - left;
                negative = false;
            } else {
                res_chisl = left - right;
            }
        } else {
            if (left >= right) {
                res_chisl = left - right;
            } else {
                res_chisl = right - left;
                negative = true;
            }
        }
    }
    res_znam = g_all;
    reduce(res_chisl, res_znam);
    res_znam *= znam;
    reduce(res_chisl, res_znam);
    res_znam *= znam1;
    reduce(res_chisl, res_znam);
    chisl = res_chisl;
    znam = res_znam;
}

//void summa(long long &x, long long &y, long long a, long long b) {
//    if (x == 0) {
//        x = a;
//        y = b;
//        return;
//    }
//    reduce(a, b);
//    reduce(x, y);
//    long long g = gcd(y, b);
//    long long another2 = b / g;
//    long long another1 = y / g;
//    long long chisl = x * another2 + a * another1;
//    long long znam = g * another1 * another2;
//    g = gcd(chisl, znam);
//    chisl /= g;
//    znam /= g;
//    x = chisl;
//    y = znam;
//}

void SUM(vector<uint64_t> &x, vector<uint64_t> &y, vector<bool> &negative,
         vector<uint64_t> a, vector<uint64_t> b, vector<bool> negative1) {
    for (int k = 0; k <= x.size() - 1; ++k) {
        uint64_t xk = (k < x.size() ? x[k] : 0);
        uint64_t yk = (k < y.size() ? y[k] : 1);
        bool neg = (k < negative.size() ? negative[k] : false);
        uint64_t ak = (k < a.size() ? a[k] : 0);
        uint64_t bk = (k < b.size() ? b[k] : 1);
        bool neg1 = (k < negative1.size() ? negative1[k] : false);
        reduce(xk, yk);
        reduce(ak, bk);
        hard_sum(xk, yk, neg, ak, bk, neg1);
        if (k < x.size()) {
            x[k] = xk;
        }
        if (k < y.size()) {
            y[k] = yk;
        }
        if (k < a.size()) {
            a[k] = ak;
        }
        if (k < b.size()) {
            b[k] = bk;
        }
        if (k < negative.size()) {
            negative[k] = neg;
        }
    }
}

void prod(vector<uint64_t> &product, vector<uint64_t> &a, vector<uint64_t> &q) {
    for (int l = 0; l <= product.size() - 1; ++l) {
        product[l] = 0;
        for (int i = 0; i <= l; ++i) {
            product[l] += (i < a.size() ? a[i] : 0) *
                          (l - i >= 0 && l - i < q.size() ? q[l - i] : 0);
        }
    }
}

uint64_t factorial(uint64_t n) {
    uint64_t res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

uint64_t getZnam(uint64_t alpha) {
    return factorial(alpha - 1);
}


uint64_t C(uint64_t k, uint64_t n) {
    uint64_t res = factorial(n);
    res /= factorial(k);
    res /= factorial(n - k);
    return res;
}

uint64_t r_pow(uint64_t pow, uint64_t r) {
    uint64_t res = 1;
    for (int i = 1; i <= pow; ++i) {
        res *= (-r);
    }
    return res;
}


int main() {
    int r, k;
    cin >> r >> k;
    vector<uint64_t> p_chisl(k + 1);
    vector<uint64_t> p_znam(k + 1);
    vector<bool> p_negative(k + 1);
    for (int i = 0; i <= k; ++i) {
        int pi;
        cin >> pi;
        long long ri = r_pow(i, r);
        bool negative = true;
        if ((pi >= 0 && ri >= 0) || (pi <= 0 && ri <= 0)) {
            negative = false;
        }
        uint64_t pi_positive = abs(pi);
        uint64_t ri_positive = abs(ri);
        p_chisl[i] = pi_positive;
        p_znam[i] = ri_positive;
        p_negative[i] = negative;
    }
    vector<uint64_t> b_chisl(k + 1);
    vector<uint64_t> b_znam(k + 1);
    vector<bool> b_negative(k + 1, false);
    for (int i = k; i >= 0; i--) {
        uint64_t sum_chisl = 0;
        uint64_t sum_znam = 0;
        bool sum_negative = false;
        for (int n = 0; n <= k - i - 1; ++n) {
            uint64_t temp = b_chisl[n] * C(i, k - n);
            uint64_t znamenatel = b_znam[n];
            bool negative = b_negative[n];
            reduce(temp, znamenatel);
            hard_sum(sum_chisl, sum_znam, sum_negative, temp, znamenatel, negative);
        }
        if (sum_chisl > 0)sum_negative ^= true;
        reduce(sum_chisl, sum_znam);
        hard_sum(sum_chisl, sum_znam, sum_negative,
                 p_chisl[i], p_znam[i], p_negative[i]);
        reduce(sum_chisl, sum_znam);
        b_chisl[k - i] = sum_chisl;
        b_znam[k - i] = sum_znam;
        b_negative[k - i] = sum_negative;
    }

    vector<vector<uint64_t >> x_chisl;
    vector<vector<bool >> x_negative;
    vector<vector<uint64_t >> x_znam;
    for (int i = 0; i <= k; ++i) {
        uint64_t alpha = i + 1;
        x_chisl.push_back(vector<uint64_t>(k + 1, 0));
        x_znam.push_back(vector<uint64_t>(k + 1, 1));
        x_negative.push_back(vector<bool>(k + 1, false));
        b_znam[i] *= getZnam(alpha);
        reduce(b_chisl[i], b_znam[i]);
        x_chisl[i][0] = 1;
        for (int j = 1; j <= alpha - 1; ++j) {
            vector<uint64_t> currentBrace(2);
            currentBrace[1] = 1;
            currentBrace[0] = j;
            if (j > 1) {
                vector<uint64_t> result(x_chisl[i].size());
                prod(result, x_chisl[i], currentBrace);
                for (int l = 0; l < x_chisl[i].size(); ++l) {
                    x_chisl[i][l] = result[l];
                }

            } else {
                x_chisl[i][1] = 1;
                x_chisl[i][0] = j;
            }
        }
        for (int l = 0; l < x_chisl[i].size(); ++l) {
            x_chisl[i][l] *= b_chisl[i];
            x_negative[i][l] = b_negative[i];
            x_znam[i][l] = b_znam[i];
            reduce(x_chisl[i][l], x_znam[i][l]);
        }
    }

    for (int i = 1; i <= k; ++i) {
        SUM(x_chisl[i], x_znam[i], x_negative[i],
            x_chisl[i - 1], x_znam[i - 1],
            x_negative[i - 1]);
    }
    for (int i = 0; i < x_chisl[k].size(); ++i) {
        reduce(x_chisl[k][i], x_znam[k][i]);
        if (x_chisl[k][i] == 0) {
            cout << x_chisl[k][i] << "/" << x_znam[k][i] << " ";
        } else
            cout << (x_negative[k][i] ? "-" : "") << x_chisl[k][i] << "/" << x_znam[k][i] << " ";
    }

    return 0;
}

