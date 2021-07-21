#include <iostream>
#include <vector>

#define pi acos(-1)
#define endl '\n'
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define MaxN 1005

typedef long long ll;
using namespace std;

vector<vector<int>> matrix_MUL(vector<vector<int>> m1, vector<vector<int>> m2,
                               int size) {
    vector<vector<int>> ans(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                ans[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return ans;
}
vector<vector<int>> matrix_Qpow(vector<vector<int>> m, ll k, int size) {
    vector<vector<int>> ans(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++) ans[i][i] = 1;
    while (k) {
        if (k & 1) ans = matrix_MUL(ans, m, size);
        m = matrix_MUL(m, m, size);
        k >>= 1;
    }
    return ans;
}

ll QuickMUL(ll a, ll b) {
    ll ans = 0;
    while (b) {
        if (b & 1) ans += a;
        a <<= 1;
        b >>= 1;
    }
    return ans;
}

ll QuickMUL_mod(ll a, ll b, ll mod) {
    ll ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % mod;
        a <<= 1;
        b >>= 1;
    }
    return ans;
}

ll QuickPow(ll n, ll k) {
    if (n == 0) return 0;
    ll ans = 1;
    while (k) {
        if (k & 1) ans *= n;
        n *= n;
        k >>= 1;
    }
    return ans;
}

ll QuickPow_mod(ll n, ll k, ll mod) {
    if (n == 0) return 0;
    ll ans = 1;
    while (k) {
        if (k & 1) ans = (ans * n) % mod;
        n = (n * n) % mod;
        k >>= 1;
    }
    return ans;
}

int main() {
    vector<vector<int>> m1 = {{1, 1}, {1, 1}};
    vector<vector<int>> res = matrix_Qpow(m1, 5, 2);
    // for (int i = 0; i < res.size(); i++) {
    //     for (int j : res[i]) cout << j << ' ';
    //     cout << '\n';
    // }
    return 0;
}