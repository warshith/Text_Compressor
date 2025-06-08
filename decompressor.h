#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <string>
using namespace std;

class Decompressor {
public:
    static void decompress(const string& inputFile,
                           const string& outputFile,
                           double& timeTaken);
};

#endif