// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

int main() {
    BST<std::string> tree;
    const char* filename = "src/war_peace.txt";

    makeTree(tree, filename);

    std::cout << "Unique words: " << tree.size() << "\n";
    std::cout << "Tree depth: " << tree.depth() << std::endl;

    if (tree.search("war"))
        std::cout << "Found: war" << std::endl;
    else
        std::cout << "Not found: war" << std::endl;

    printFreq(tree);
    return 0;
}
