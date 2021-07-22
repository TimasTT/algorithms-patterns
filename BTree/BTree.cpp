//
// Created by timas on 22.07.2021.
//

#include <iostream>
#include <stack>
#include <vector>

template <class T>
struct Node {
    T data;

    Node* left;
    Node* right;

    Node(): left(nullptr), right(nullptr) {}

    explicit Node(const T &data): data(data), left(nullptr), right(nullptr) {}
};

template <class T>
struct Writer {
    void operator()(Node<T>* node) {
        std::cout << node->data << " ";
    }
};

template <class T>
class Tree {
    Node<T>* head;

public:
    explicit Tree();

    ~Tree();

    template <class F>
    void traverse(F func);

    void Add(const T &data);
};

template <class T>
Tree<T>::Tree(): head(nullptr) {}

template <class T>
Tree<T>::~Tree() {
    std::vector<Node<T>*> vec;
    traverse([&](Node<T>* node) {
        vec.push_back(node);
    });
    for (Node<T>* node : vec) {
        delete node;
    }
}

template <class T>
template <class F>
void Tree<T>::traverse(F func) {
    std::stack<Node<T>*> stack1;
    std::stack<Node<T>*> stack2;

    if (head == nullptr) {
        return;
    }

    stack1.push(head);
    while (!stack1.empty()) {
        stack2.push(stack1.top());
        Node<T>* currentNode = stack1.top();
        stack1.pop();

        if (currentNode->left != nullptr) {
            stack1.push(currentNode->left);
        }
        if (currentNode->right != nullptr) {
            stack1.push(currentNode->right);
        }
    }

    while (!stack2.empty()) {
        func(stack2.top());
        stack2.pop();
    }
}

template <class T>
void Tree<T>::Add(const T &data) {
    if (head == nullptr) {
        auto* newNode = new Node<T>(data);
        head = newNode;
        return;
    }

    Node<T>* currentNode = head;
    while (true) {
        if (data <= currentNode->data) {
            if (currentNode->left == nullptr) {
                auto* newNode = new Node<T>(data);
                currentNode->left = newNode;
                return;
            } else {
                currentNode = currentNode->left;
                continue;
            }
        } else {
            if (currentNode->right == nullptr) {
                auto* newNode = new Node<T>(data);
                currentNode->right = newNode;
                return;
            } else {
                currentNode = currentNode->right;
                continue;
            }

        }
    }
}

int main() {
    Tree<int> myTree;
    int number;
    std::cin >> number;
    for (int i = 0; i < number; ++i) {
        int data;
        std::cin >> data;
        myTree.Add(data);
    }

    Writer<int> writer;
    myTree.traverse(writer);

    return 0;
}
