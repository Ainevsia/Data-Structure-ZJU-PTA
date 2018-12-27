#include <iostream>
#include <cstring>

using namespace std;

void cal_pi(const char * pattern, int length, int * pi) {
    pi[0] = 0;
    int pre_pi = 0;
    for (int i = 1; i < length; ++i) {
        while (pre_pi > 0 && pattern[i]!=pattern[pre_pi]) pre_pi = pi[pre_pi-1];
        if (pattern[i] == pattern[pre_pi]) pre_pi++;
        pi[i] = pre_pi;
    }
}

int main() {
    char pattern[] = "ababbabbabbababbabb";
    int length = (int)(strlen(pattern));
    int * pi = new int [length];
    cal_pi(pattern, length, pi);
    for (int i = 0; i < length; ++i) cout << pattern[i] << '\t';
    cout << endl;
    for (int i = 0; i < length; ++i) cout << pi[i] << '\t';
    delete [] pi;
    return 0;
}