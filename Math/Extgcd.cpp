#include <iostream>
#include <tuple>

#define pi acos(-1)
#define endl '\n'
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define MaxN 1005

typedef long long ll;
using namespace std;

tuple<int, int, int> extgcd(int a, int b) {  // tuple(x,y,r) ax+by=r
    if (!b) return make_tuple(1, 0, a);
    int x, y, r;
    tie(x, y, r) = extgcd(b, a % b);
    return make_tuple(y, x - (a / b) * y, r);  // x1=y2 y1=x2-(a/b)*y2
}

int main() {
    //¨D13ªº¼Ò°f¤¸(mod 17) 13x+17y=gcd(13,17)=1
    int x, y, r;
    tie(x, y, r) = extgcd(13, 17);
    cout << x << '\n';
    return 0;
}