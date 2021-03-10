#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

struct Node {
    int data;
    int size;
    int used_cnt;
    Node *l, *r;
    Node(int x) : data(x), size(1), used_cnt(0), l(0), r(0) {}
    void Resize() {
        size = 1;
        if (l) size += l->size;
        if (r) size += r->size;
    }
} * root;

int size(Node* a) { return a ? a->size : 0; }

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
        // a = new Node(*a);
        a->r = Merge(a->r, b);
        a->Resize();
        return a;
    } else {
        // b = new Node(*b);
        b->l = Merge(a, b->l);
        b->Resize();
        return b;
    }
}

//前K個分至a剩餘給b
void Split(Node* tar, Node*& a, Node*& b, int k) {
    if (!tar)
        a = b = 0;
    else {
        // tar = new Node(*tar);
        if (k <= size(tar->l)) {
            b = tar;
            Split(tar->l, a, b->l, k);
        } else {
            a = tar;
            Split(tar->r, a->r, b, k - size(tar->l) - 1);
        }
        tar->Resize();
    }
}

//小於k的分至a
void Split2(Node* tar, Node*& a, Node*& b, int k) {
    if (!tar)
        a = b = 0;
    else {
        // tar = new Node(*tar);
        if (tar->data < k) {
            a = tar;
            Split2(tar->r, a->r, b, k);
        } else {
            b = tar;
            Split2(tar->l, a, b->l, k);
        }
        tar->Resize();
    }
}

void Insert(Node*& tar, int k) {
    Node *a, *b;
    Split2(tar, a, b, k);
    tar = Merge(Merge(a, new Node(k)), b);
}

//回傳成功或失敗
bool Erase(Node*& tar, int k) {
    if (!tar) return 0;
    Node* tmp;
    if (tar->data == k) {
        tmp = tar;
        tar = Merge(tar->l, tar->r);
        delete tmp;
        return 1;
    } else if (tar->data < k)
        tmp = tar->r;
    else {
        tmp = tar->l;
    }
    if (Erase(tmp, k)) {
        tar->Resize();
        return 1;
    } else {
        return 0;
    }
}

void Traversal(Node* a, int dep) {
    if (!a) return;
    Traversal(a->l, dep + 1);
    cout << a->data << ' ' << dep << '\n';
    Traversal(a->r, dep + 1);
}

int main() {
    srand(time(NULL));
    int n, data;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> data;
        Insert(root, data);
    }
    return 0;
}