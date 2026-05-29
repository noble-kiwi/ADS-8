// Copyright 2021 NNTU-CS
#include "bst.h"

int main() {
    BST<std::string> tree;
    const char* filename = "src/war_peace.txt";

    makeTree(tree, filename);

    std::cout << "Tree built.\n"
              << "Unique words: " << tree.size() << "\n"
              << "Tree depth: " << tree.depth() << std::endl;

    if (tree.search("war"))
        std::cout << "Word 'war' found." << std::endl;
    else
        std::cout << "Word 'war' not found." << std::endl;

    printFreq(tree);
    return 0;
}
