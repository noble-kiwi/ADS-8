// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int sz;

    Node* insert(Node* node, const T& key, bool& isNew) {
        if (!node) {
            isNew = true;
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key, isNew);
        } else if (key > node->key) {
            node->right = insert(node->right, key, isNew);
        } else {
            node->count++;
            isNew = false;
        }
        return node;
    }

    Node* find(Node* node, const T& key) const {
        if (!node || node->key == key) return node;
        if (key < node->key) return find(node->left, key);
        return find(node->right, key);
    }

    int height(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(height(node->left), height(node->right));
    }

    void collect(Node* node, std::vector<std::pair<T, int>>& out) const {
        if (!node) return;
        collect(node->left, out);
        out.emplace_back(node->key, node->count);
        collect(node->right, out);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr), sz(0) {}
    ~BST() { clear(root); }

    void add(const T& key) {
        bool isNew = false;
        root = insert(root, key, isNew);
        if (isNew) ++sz;
    }

    bool search(const T& key) const {
        return find(root, key) != nullptr;
    }

    int depth() const {
        return height(root);
    }

    int size() const { return sz; }

    std::vector<std::pair<T, int>> getSortedByFreq() const {
        std::vector<std::pair<T, int>> result;
        collect(root, result);
        std::sort(result.begin(), result.end(),
                  [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
                      return a.second > b.second;
                  });
        return result;
    }
};

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

#endif  // INCLUDE_BST_H_
