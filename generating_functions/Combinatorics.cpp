#include <utility>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void multiply(long long coefficient, vector<long long> &vec, vector<long long> &source) {
    for (int i = 0; i < vec.size(); ++i) {
        vec[i] = source[i];
        vec[i] *= coefficient;
    }
}

long long factorial(long long n) {
    long long res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

long long chislitel(long long n, long long alpha) {
    long long res = 1;
    for (int i = 0; i < n; ++i) {
        res *= (alpha - i);
    }
    return res;
}

pair<long long, long long> getCoefficient(long long n, long long alpha) {
    if (n == 0)return make_pair(1, 1);
    long long a = chislitel(n, alpha);
    long long b = factorial(n);
    return make_pair(a, b);
}


void summa(vector<long long> &s, vector<long long> &p, vector<long long> &q) {
    for (int k = 0; k <= s.size() - 1; ++k) {
        s[k] = p[k] + q[k];
    }
}

void prod(vector<long long> &product, vector<long long> &a, vector<long long> &q, long long limit) {
    for (int l = 0; l <= limit; ++l) {
        product[l] = 0;
        for (int i = 0; i <= l; ++i) {
            product[l] += a[i] * q[l - i];
        }
    }
    for (int j = limit + 1; j < product.size(); ++j) {
        product[j] = 0;
    }
}

void binom(vector<long long> &res, long long alpha, vector<long long> &source) {
    if (alpha == 0) {
        res[0] = 1;
        return;
    }
    vector<vector<long long>> x;
    for (int j = 0; j < 7; ++j) {
        x.push_back(vector<long long>(7));
    }
    for (int l = 0; l < 7; ++l) {
        x[1][l] = source[l];
        x[0][l] = 0;
    }
    x[0][0] = 1;
    for (int j = 2; j < 7; ++j) {
        prod(x[j], x[j - 1], source, x[j].size()-1);
    }
    vector<pair<long long, long long>> coeffs(7);
    for (int j = 0; j < 7; ++j) {
        coeffs[j] = getCoefficient(j, alpha);
    }
    for (int j = 0; j < 7; ++j) {
        multiply(coeffs[j].first / coeffs[j].second, x[j], x[j]);
    }
    for (int j = 1; j < 7; ++j) {
        summa(x[j], x[j], x[j - 1]);
    }
    for (int i = 0; i < 7; ++i) {
        res[i] = x[6][i];
    }
}


class ExpressionParser {
    string expression;
    int index;
public:
    ExpressionParser(string expression) : expression(std::move(expression)) {
        index = -1;
    }

public:
    void parse(vector<long long> &result) {
        index++;
        if (expression[index] == 'P') {
            index++;
            vector<long long> a(7);
            vector<long long> b(7);
            parse(a);
            index++;
            parse(b);
            for (int i = 0; i < result.size(); ++i) {
                result[i] = 0;
                for (int k = 0; k <= i; ++k) {
                    result[i] += a[k] * b[i - k];
                }
            }
            index++;
        } else if (expression[index] == 'L') {
            index++;
            vector<long long> tempRes(7);
            parse(tempRes);
            vector<vector<long long>> x;
            for (int j = 0; j < 7; ++j) {
                x.push_back(vector<long long>(7, 0));
            }
            tempRes[0] = 0;
            for (int l = 0; l < 7; ++l) {
                x[1][l] = tempRes[l];
            }
            for (int j = 2; j < 7; ++j) {
                for (int i = 0; i < 7; ++i) {
                    x[j][i] = 0;
                    for (int k = 0; k <= i; ++k) {
                        x[j][i] += x[j - 1][k] * tempRes[i - k];
                    }

                }
            }
            x[0][0] = 1;

            for (int j = 1; j < 7; ++j) {
                summa(x[j], x[j], x[j - 1]);
            }
            for (int i = 0; i < 7; ++i) {
                result[i] = x[6][i];
            }
            index++;
        } else if (expression[index] == 'S') {
            index++;
            vector<long long> tempRes(7);
            parse(tempRes);
            vector<vector<long long>> x;
            for (int j = 0; j < 7; ++j) {
                x.push_back(vector<long long>(7, 0));
            }
            for (int l = 0; l < 6; ++l) {
                x[l][l + 1] = -1;
            }
            vector<vector<long long>> mults;
            for (int k = 0; k < 6; ++k) {
                mults.push_back(vector<long long>(7));
            }
            for (int k = 0; k < 6; ++k) {
                binom(mults[k], -tempRes[k + 1], x[k]);
            }
            vector<long long> resMults(7, 0);
            for (int j = 1; j < 6; ++j) {
                prod(resMults, mults[j - 1], mults[j], resMults.size()-1);
                for (int i = 0; i < mults[j].size(); ++i) {
                    mults[j][i] = resMults[i];
                }
            }

            for (int m = 0; m < result.size(); ++m) {
                result[m] = mults[5][m];
            }
            index++;
        } else if (expression[index] == 'B') {
            result[1] = 1;
        }

    }
};

int main() {
    string expression;
    getline(cin, expression);
    ExpressionParser *expressionParser = new ExpressionParser(expression);
    vector<long long> result(7, 0);
    expressionParser->parse(result);
    for (long long i : result) {
        cout << i << " ";
    }
    return 0;
}