#include <math.h>

#include <iostream>

#define pi acos(-1)
#define endl '\n'
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define MaxN 1005

typedef long long ll;
using namespace std;

int arr[MaxN];

struct node {
    int sum = 0;
    int lazy = 0;
};

struct SegmentTree {
    node seg[MaxN << 2];
    void update(int idx);
    void pushdown(int idx, int leng);
    void build(int l, int r, int idx);
    void insert(int l, int r, int pos, int val, int idx);
    void insert2(int l, int r, int posL, int posR, int val, int idx);
    int query(int l, int r, int ql, int qr, int idx);
};

void SegmentTree::update(int idx) {
    seg[idx].sum = (seg[idx * 2].sum + seg[idx * 2 + 1].sum);
    // seg[idx] = max(seg[idx * 2], seg[idx * 2 + 1]);
}

void SegmentTree::pushdown(int idx, int leng) {
    if (seg[idx].lazy) {
        seg[idx * 2].sum += seg[idx].lazy * (leng - (leng / 2));
        seg[idx * 2 + 1].sum += seg[idx].lazy * (leng / 2);
        seg[idx * 2].lazy += seg[idx].lazy;
        seg[idx * 2 + 1].lazy += seg[idx].lazy;
        seg[idx].lazy = 0;
    }
}

void SegmentTree::build(int l, int r, int idx = 1) {
    if (l == r) {
        // seg[idx] = 0;
        seg[idx].sum = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, idx * 2);
    build(mid + 1, r, idx * 2 + 1);
    update(idx);
}

void SegmentTree::insert(int l, int r, int pos, int val, int idx = 1) {
    if (pos < l || pos > r) return;
    if (l == r && l == pos) {
        seg[idx].sum += val;
        return;
    }
    int mid = (l + r) / 2;
    insert(l, mid, pos, val, idx * 2);
    insert(mid + 1, r, pos, val, idx * 2 + 1);
    update(idx);
}
void SegmentTree::insert2(int l, int r, int posL, int posR, int val,
                          int idx = 1) {
    if (posR < l || posL > r) return;
    if (posL <= l && r <= posR) {
        seg[idx].sum += val * (r - l + 1);
        seg[idx].lazy += val;
        return;
    }
    int mid = (l + r) / 2;
    insert2(l, mid, posL, posR, val, idx * 2);
    insert2(mid + 1, r, posL, posR, val, idx * 2 + 1);
    update(idx);
}

int SegmentTree::query(int l, int r, int ql, int qr, int idx = 1) {
    if (qr < l || ql > r) return 0;  //詢問的區間完全在現在尋訪的區間外
    if (ql <= l && r <= qr) {
        return seg[idx].sum;
    }  //詢問的區間完全在現在尋訪的區間內
    int mid = (l + r) / 2;
    pushdown(idx, r - l + 1);
    return query(l, mid, ql, qr, idx * 2) +
           query(mid + 1, r, ql, qr, idx * 2 + 1);
    // return max(query(l, mid, ql, qr, idx) , query(mid + 1, r, ql, qr, idx))
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    SegmentTree ST;
    ST.build(1, n);
    return 0;
}