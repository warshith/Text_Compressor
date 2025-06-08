#include "decompressor.h"
#include "huffman.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <bitset>
using namespace std;

void Decompressor::decompress(const string& inputFile,
                              const string& outputFile,
                              double& timeTaken) {
    auto start = chrono::high_resolution_clock::now();
    
    ifstream in(inputFile, ios::binary);
    if (!in) throw runtime_error("Cannot open input file");
    
    // Read frequency map
    size_t mapSize;
    in.read(reinterpret_cast<char*>(&mapSize), sizeof(size_t));
    
    map<char, unsigned> freqMap;
    for (size_t i = 0; i < mapSize; ++i) {
        char c;
        unsigned freq;
        in.read(&c, sizeof(char));
        in.read(reinterpret_cast<char*>(&freq), sizeof(unsigned));
        freqMap[c] = freq;
    }
    
    // Read padding info
    size_t padding;
    in.read(reinterpret_cast<char*>(&padding), sizeof(size_t));
    
    // Read compressed data
    stringstream buffer;
    buffer << in.rdbuf();
    string compressedData = buffer.str();
    in.close();
    
    // Convert to bit string
    string bitString;
    for (char c : compressedData) {
        bitString += bitset<8>(c).to_string();
    }
    
    // Remove padding
    if (padding != 8) {
        bitString.erase(bitString.end() - padding, bitString.end());
    }
    
    // Rebuild Huffman tree
    Node* root = Huffman::buildTree(freqMap);
    
    // Decode content
    string decoded;
    Node* current = root;
    for (char bit : bitString) {
        current = (bit == '0') ? current->left : current->right;
        
        if (current->data != '\0') {
            decoded += current->data;
            current = root;
        }
    }
    
    // Write decompressed data
    ofstream out(outputFile, ios::binary);
    if (!out) throw runtime_error("Cannot create output file");
    out << decoded;
    out.close();
    
    // Clean up
    Huffman::deleteTree(root);
    
    auto end = chrono::high_resolution_clock::now();
    timeTaken = chrono::duration<double>(end - start).count();
}