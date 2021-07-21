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

int not_prime[MaxN + 1];
vector<int> prime = {2};
map<int, int> factor;

void Sieve(int n) {
    int i;
    for (i = 3; i * i <= n; i += 2) {
        if (!not_prime[i]) {  // i借计
            prime.emplace_back(i);
            for (int j = i * i; j <= n; j += (2 * i))
                //磷秨案计i*i计穦砆ㄤ借计縵
                not_prime[j] = i;  //魁砆街縵
        }
    }
    for (; i <= n; i += 2)
        if (!not_prime[i]) prime.emplace_back(i);
}

void Factorization(int n) {
    factor.clear();
    while (n > 1) {
        int p = ((n % 2) ? not_prime[n] : 2);
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
    Sieve(MaxN);
    Factorization(40);
    for (auto i : factor) {
        cout << i.first << ' ' << i.second << '\n';
    }
    return 0;
}