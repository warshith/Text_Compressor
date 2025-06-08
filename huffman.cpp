#include "huffman.h"
#include <queue>
using namespace std;

Node* Huffman::buildTree(const map<char, unsigned>& freqMap) {
    if (freqMap.empty()) return nullptr;
    
    auto comp = [](Node* l, Node* r) { return l->freq > r->freq; };
    priority_queue<Node*, vector<Node*>, decltype(comp)> minHeap(comp);
    
    for (const auto& pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        
        Node* top = new Node('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    
    return minHeap.top();
}

void Huffman::generateCodes(Node* root, const string& str, 
                            map<char, string>& huffmanCodes) {
    if (!root) return;
    
    if (root->data != '\0') {
        huffmanCodes[root->data] = str;
    }
    
    generateCodes(root->left, str + "0", huffmanCodes);
    generateCodes(root->right, str + "1", huffmanCodes);
}

void Huffman::deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}