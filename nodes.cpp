#include "nodes.h"

Node::Node(char data, unsigned freq) : 
    data(data), freq(freq), left(nullptr), right(nullptr) {}