#include "compressor.h"
#include "frequencycounter.h"
#include "huffman.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <bitset>
using namespace std;

void Compressor::compress(const string& inputFile, 
                          const string& outputFile,
                          double& compressionRatio,
                          double& timeTaken) {
    auto start = chrono::high_resolution_clock::now();
    
    // Read input file
    ifstream in(inputFile, ios::binary);
    if (!in) throw runtime_error("Cannot open input file");
    stringstream buffer;
    buffer << in.rdbuf();
    string content = buffer.str();
    in.close();
    
    // Handling empty file
    if (content.empty()) {
        ofstream out(outputFile);
        compressionRatio = 0.0;
        timeTaken = 0.0;
        return;
    }
    
    // Calculate frequencies
    auto freqMap = FrequencyCounter::count(content);
    
    // Build Huffman tree
    Node* root = Huffman::buildTree(freqMap);
    
    // Generate codes
    map<char, string> huffmanCodes;
    Huffman::generateCodes(root, "", huffmanCodes);
    
    // Encode content
    string encodedStr;
    for (char c : content) {
        encodedStr += huffmanCodes[c];
    }
    
    // Calculate padding
    size_t padding = 8 - (encodedStr.length() % 8);
    if (padding != 8) {
        encodedStr.append(padding, '0');
    }
    
    // Write to output
    ofstream out(outputFile, ios::binary);
    if (!out) throw runtime_error("Cannot create output file");
    
    // Write header (freqMap size + freqMap data + padding info)
    size_t mapSize = freqMap.size();
    out.write(reinterpret_cast<char*>(&mapSize), sizeof(size_t));
    for (const auto& pair : freqMap) {
        out.write(&pair.first, sizeof(char));
        out.write(reinterpret_cast<const char*>(&pair.second), sizeof(unsigned));
    }
    out.write(reinterpret_cast<char*>(&padding), sizeof(size_t));
    
    // Write compressed data
    for (size_t i = 0; i < encodedStr.length(); i += 8) {
        bitset<8> bits(encodedStr.substr(i, 8));
        out.put(static_cast<char>(bits.to_ulong()));
    }
    
    // Clean up
    out.close();
    Huffman::deleteTree(root);
    
    // Calculate metrics
    auto end = chrono::high_resolution_clock::now();
    timeTaken = chrono::duration<double>(end - start).count();
    
    ifstream inOriginal(inputFile, ios::ate | ios::binary);
    ifstream inCompressed(outputFile, ios::ate | ios::binary);
    size_t originalSize = inOriginal.tellg();
    size_t compressedSize = inCompressed.tellg();
    compressionRatio = (originalSize > 0) ? 
        static_cast<double>(compressedSize) / originalSize : 0;
}