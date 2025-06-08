# Huffman File Compressor and Decompressor!!!

This repository contains all the resources needed to compress and decompress files using Huffman trees.


Place all the .cpp files and .h files in a single directory.

## Run the following command to compile:

g++ compressor.cpp decompressor.cpp frequencycounter.cpp huffman.cpp main.cpp nodes.cpp -o a



./a.exe `<mode>` `<input_file>` `<output_file>`

`<mode>`: Use c for compression, d for decompression.

`<input_file>`: Path to the input text file.

`<output_file>`: Path where the output will be written.

## Examples

Compress input.txt into output.txt:

./a.exe c input.txt output.txt

Decompress output.txt into output2.txt:

./a.exe d output.txt output2.txt

## Metrics

Compression Time: The program prints the time taken to compress the input.

Decompression Time: The program prints the time taken to decompress the input.

Compression Ratio: The ratio of compressed size to original size.

## Sample

Original: input.txt

Compressed: output.txt

Decompressed: output2.txt

You can verify that output2.txt matches input.txt to ensure lossless compression.


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

