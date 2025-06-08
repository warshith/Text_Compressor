#include "frequencycounter.h"
using namespace std;

map<char, unsigned> FrequencyCounter::count(const string& content) {
    map<char, unsigned> freqMap;
    for (char c : content) {
        freqMap[c]++;
    }
    return freqMap;
}