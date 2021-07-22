#include <iostream>
#include <map>
#include <vector>

#define pi acos(-1)
#define endl '\n'
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define MaxN 100000

typedef long long ll;
using namespace std;

int pfactor[MaxN + 1];
vector<int> prime = {2};
map<int, int> factor;

void Eratosthenes(int n) {
    int i;
    for (i = 3; i * i <= n; i += 2) {
        if (!pfactor[i]) {  // i為質數
            prime.emplace_back(i);
            for (int j = i * i; j <= n; j += (2 * i))
                //避開偶數，小於i*i的會被其他小於i的數篩掉
                pfactor[j] = i;  //紀錄j被質數i篩掉
        }
    }
    for (; i <= n; i += 2)
        if (!pfactor[i]) prime.emplace_back(i);
}

void Linear(int n) {
    for (int i = 2; i <= n; i++) {
        if (!pfactor[i]) prime.emplace_back(i);
        for (int j = 0; j < prime.size() && (i * prime[j] <= n); j++) {
            pfactor[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }
}

void Factorization(int n) {
    factor.clear();
    while (n > 1) {
        int p = ((n % 2) ? pfactor[n] : 2);
        if (p == 0) {
            p = n;
        }
        while (n % p == 0) {
            n /= p;
            factor[p]++;
        }
    }
}

int main() {
    Linear(MaxN);
    Factorization(121);
    for (auto i : factor) {
        cout << i.first << ' ' << i.second << '\n';
    }
    return 0;
}