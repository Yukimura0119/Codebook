
#include <math.h>

#include <iostream>
typedef long long ll;
using namespace std;

//常數很大 小心食用XD
// Todo:Smartpoint

struct Node {
    int data;
    int rev;
    int _max;
    int size;
    Node *l, *r;
    Node(int x) : data(x), rev(0), _max(x), size(1), l(0), r(0) {}
    void update() {
        size = 1;
        _max = data;
        if (l) {
            size += l->size;
            _max = max(l->_max, _max);
        }
        if (r) {
            size += r->size;
            _max = max(_max, r->_max);
        }
    }
    void lazy() {
        if (rev) {
            swap(l, r);
            if (l) l->rev = l->rev ^ 1;
            if (r) r->rev = r->rev ^ 1;
            rev = 0;
        }
    }
} * root;

int size(Node* a) { return a ? a->size : 0; }

// Smartpoint
// void Used(Node *a) {
//     if (a) a->used_cnt++;
// }
// void Unused(Node *a) {
//     if (a) {
//         a->used_cnt--;
//         if (!a->used_cnt) {
//             Unused(a->l);
//             Unused(a->r);
//             delete a;
//         }
//     }
// }

// a中最大的data值必須小於b中最小的data值
Node* Merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
    if (rand() % (a->size + b->size) < a->size) {
        a->lazy();
        a = new Node(*a);
        a->r = Merge(a->r, b);
        a->update();
        return a;
    } else {
        b->lazy();
        b = new Node(*b);
        b->l = Merge(a, b->l);
        b->update();
        return b;
    }
}

//前K個分至a剩餘給b
void Split(Node* tar, Node*& a, Node*& b, int k) {
    if (!tar)
        a = b = 0;
    else {
        tar->lazy();
        tar = new Node(*tar);
        if (k <= size(tar->l)) {
            b = tar;
            Split(tar->l, a, b->l, k);
        } else {
            a = tar;
            Split(tar->r, a->r, b, k - size(tar->l) - 1);
        }
        tar->update();
    }
}

void Insert(Node*& tar, int k) { tar = Merge(tar, new Node(k)); }

//得到第k個節點
Node* GetKth(Node*& tar, int k) {
    Node *lower, *ans, *upper;
    Split(tar, lower, upper, k);
    Split(lower, lower, ans, k - 1);
    tar = Merge(Merge(lower, ans), upper);
    return ans;
}

//遍歷
void Traversal(Node* a) {
    if (!a) return;
    a->lazy();  //可能懶標還沒推完
    Traversal(a->l);
    // Do something with a
    cout << a->data << ' ';
    Traversal(a->r);
}

//區間反轉
void Reverse(Node*& tar, int l, int r) {
    Node *low, *aim, *up;
    Split(tar, low, aim, l - 1);
    Split(aim, aim, up, r - l + 1);
    aim->rev = aim->rev ^ 1;
    tar = Merge(Merge(low, aim), up);
}

//區間最大值
int Query(Node*& tar, int l, int r) {
    Node *low, *aim, *up;
    Split(tar, low, aim, l - 1);
    Split(aim, aim, up, r - l + 1);
    aim->lazy();
    int ans = aim->_max;
    tar = Merge(Merge(low, aim), up);
    return ans;
}

int main() {
    srand(time(NULL));
    int n, data;
    cin >> n;
    while (n--) {
        cin >> data;
        Insert(root, data);
    }
    root = Merge(root, root);
    Traversal(root);
    cout << '\n';
    return 0;
}