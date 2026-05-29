// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string current_word = "";

    while (!file.eof()) {
        int ch = file.get();
        if (ch == EOF) break;

        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch + ('a' - 'A');
            }
            current_word += static_cast<char>(ch);
        } else {
            if (!current_word.empty()) {
                tree.add(current_word);
                current_word = "";
            }
        }
    }

    if (!current_word.empty()) {
        tree.add(current_word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> sorted_words = tree.getSortedByFreq();

    std::ofstream out_file("result/freq.txt");
    if (!out_file) {
        std::cout << "Error creating result/freq.txt!" << std::endl;
        return;
    }

    for (const auto& pair : sorted_words) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        out_file << pair.first << ": " << pair.second << "\n";
    }

    out_file.close();
}
