#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "nodes.h"
#include <map>
#include <queue>
#include <functional>
#include <vector>
#include <string>
using namespace std;

class Huffman {
public:
    static Node* buildTree(const map<char, unsigned>& freqMap);
    static void generateCodes(Node* root, const string& str, 
                              map<char, string>& huffmanCodes);
    static void deleteTree(Node* root);
};

#endif