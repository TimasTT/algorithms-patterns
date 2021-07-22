//
// Created by timas on 22.07.2021.
//

#include <iostream>

template <class T>
struct DefaultComparator {
    int operator()(const T &l, const T &r) const {
        if (l < r) {
            return -1;
        } else if (l > r) {
            return 1;
        }
        return 0;
    }
};

template <class Key, class Value, class Comparator = DefaultComparator<Key>>
class AvlTree {
    struct Node {
        Key key;
        Value value;

        Node* left;
        Node* right;

        uint8_t height;
        size_t childrenCnt;

        Node(const Key &k, const Value &v): key(k), value(v), height(1), childrenCnt(0) {}

        ~Node() {
            delete left;
            delete right;
        }
    };

    Node* root;
    size_t items_cnt;

    Comparator comp;

public:
    AvlTree(): root(nullptr), items_cnt(0) {};

    ~AvlTree() {}

    Value find(const Key &k) {
        if (find_auxiliary(k, root) == nullptr) {
            return 0;
        }
        return *find_auxiliary(k, root);
    };

    void insert(const Key &k, const Value &v) {
        root = insert_auxiliary(k, v, root);
    };

    void erase(const Key &k) {
        erase_auxiliary(k, root);
    };

    size_t size() const { return items_cnt; }

    bool isEmpty() const { return items_cnt == 0; }

private:
    Value* find_auxiliary(const Key &k, Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        int comp_res = comp(k, node->key);
        if (comp_res == -1) {
            return find_auxiliary(k, node->left);
        } else if (comp_res == 1) {
            return find_auxiliary(k, node->right);
        }
        return &node->value;
    }

    Node* insert_auxiliary(const Key &k, const Value &v, Node* node) {
        if (node == nullptr) {
            items_cnt++;
            return new Node(k, v);
        }

        int comp_res = comp(k, node->key);
        if (comp_res == -1) {
            node->childrenCnt++;
            node->left = insert_auxiliary(k, v, node->left);
        } else if (comp_res == 1) {
            node->childrenCnt++;
            node->right = insert_auxiliary(k, v, node->right);
        }

        return balance(node);
    }

    Node* erase_auxiliary(const Key &k, Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        int comp_res = comp(k, node->key);
        if (comp_res == -1) {
            node->childrenCnt--;
            node->left = erase_auxiliary(k, node->left);
        } else if (comp_res == 1) {
            node->childrenCnt--;
            node->right = erase_auxiliary(k, node->right);
        } else {
            items_cnt--;
            Node* left = node->left;
            Node* right = node->right;

            delete node;
            if (right == nullptr) {
                return left;
            }

            Node* min_node = find_min(right);
            min_node->right = remove_min(right);
            min_node->left = left;

            return balance(min_node);
        }

        return balance(node);
    }

    Node* find_min(Node* p) {
        while (p->left) {
            p = p->left;
        }
        return p;
    }

    Node* remove_min(Node* p) {
        if (!p->left) {
            return p->right;
        }
        p->left = remove_min(p->left);
        return balance(p);
    }

    unsigned char height(Node* p) {
        return p ? p->height : 0;
    }

    int b_factor(Node* p) {
        return height(p->right) - height(p->left);
    }

    void fix_height(Node* p) {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    Node* rotate_right(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fix_height(p);
        fix_height(q);
        return q;
    }

    Node* rotate_left(Node* q) {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fix_height(q);
        fix_height(p);
        return p;
    }

    Node* balance(Node* p) {
        fix_height(p);

        if (b_factor(p) == 2) {
            if (b_factor(p->right) < 0)
                p->right = rotate_right(p->right);
            return rotate_left(p);
        }
        if (b_factor(p) == -2) {
            if (b_factor(p->left) > 0)
                p->left = rotate_left(p->left);
            return rotate_right(p);
        }
        return p;
    }

};


int main() {
    AvlTree<int, int> myAvl;
    myAvl.insert(3,2);
    myAvl.insert(4,5);
    myAvl.erase(3);
    myAvl.find(3);
    return 0;
}
