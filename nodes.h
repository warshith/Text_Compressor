#ifndef NODES_H
#define NODES_H

struct Node {
    char data;
    unsigned freq;
    Node *left, *right;

    Node(char data, unsigned freq);
};

#endif