// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class BST {
 private:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;

        Node(T val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* insert(Node* node, const T& value) {
        if (!node) {
            return new Node(value);
        }
        if (value == node->value) {
            node->count++;
        } else if (value < node->value) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    int getDepth(Node* node) const {
        if (!node) return -1;
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    Node* searchNode(Node* node, const T& value) const {
        if (!node || node->value == value) return node;
        if (value < node->value) return searchNode(node->left, value);
        return searchNode(node->right, value);
    }

    void collectData(Node* node, std::vector<std::pair<T, int>>& list) const {
        if (!node) return;
        collectData(node->left, list);
        list.push_back({node->value, node->count});
        collectData(node->right, list);
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void add(const T& value) {
        root = insert(root, value);
    }

    int depth() const {
        return getDepth(root);
    }

    int search(T value) const {
        Node* result = searchNode(root, value);
        return result ? result->count : 0;
    }

    std::vector<std::pair<T, int>> getSortedByFreq() const {
        std::vector<std::pair<T, int>> list;
        collectData(root, list);

        std::sort(list.begin(), list.end(), [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });

        return list;
    }
};

#endif  // INCLUDE_BST_H_
