#ifndef FREQUENCYCOUNTER_H
#define FREQUENCYCOUNTER_H

#include <map>
#include <string>
using namespace std;

class FrequencyCounter {
public:
    static map<char, unsigned> count(const string& content);
};

#endif