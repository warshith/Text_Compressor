#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>
using namespace std;

class Compressor {
public:
    static void compress(const string& inputFile, 
                         const string& outputFile,
                         double& compressionRatio,
                         double& timeTaken);
};

#endif