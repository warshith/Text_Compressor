#include <iostream>
#include <string>
#include "compressor.h"
#include "decompressor.h"
#include <iomanip>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "How to run the code  "<<endl
        << argv[0] << " <c|d> <input_file> <output_file>"<<endl
        << "  c: Compress" <<endl
        << "  d: Decompress"<<endl;
        return 1;
    }

    char mode = argv[1][0];
    string inputFile = argv[2];
    string outputFile = argv[3];
    
    try {
        if (mode == 'c') {
            double ratio, time;
            Compressor::compress(inputFile, outputFile, ratio, time);
            cout << "Compression successful\n"
                      << "Time: " << fixed << setprecision(4) 
                      << time << " seconds\n"
                      << "Compression ratio: " << ratio << "\n";
        } 
        else if (mode == 'd') {
            double time;
            Decompressor::decompress(inputFile, outputFile, time);
            cout << "Decompression successful\n"
                      << "Time: " << fixed << setprecision(4) 
                      << time << " seconds\n";
        }
        else {
            cerr << "Invalid mode. Use 'c' for compress or 'd' for decompress\n";
            return 1;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}