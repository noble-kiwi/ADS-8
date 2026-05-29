// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    std::string word;
    char c;
    while (file.get(c)) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (c >= 'A' && c <= 'Z')
                c = c + ('a' - 'A');
            word.push_back(c);
        } else {
            if (!word.empty()) {
                tree.add(word);
                word.clear();
            }
        }
    }
    if (!word.empty())
        tree.add(word);
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto pairs = tree.getPairs();
    std::sort(pairs.begin(), pairs.end(),
              [](const std::pair<std::string, int>& a,
                 const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });

    std::system("mkdir result 2>nul");

    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Warning: cannot create result/freq.txt" << std::endl;
    }

    for (const auto& p : pairs) {
        std::cout << p.first << " : " << p.second << std::endl;
        if (out)
            out << p.first << " : " << p.second << std::endl;
    }

}
