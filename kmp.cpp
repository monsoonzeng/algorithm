#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using std::vector;
using std::string;

class Kmp {
public:
    Kmp(const char *pattern);
    int kmp_match(const char *t);
private:
    vector<int> pi;
    string p;
};

Kmp::Kmp(const char *pattern) {
    p = pattern;
    pi.resize(p.size(), 0);
    // pi[i] = max({k+1: p[0-k] is postfix of p[0-i], k<i);
    pi[0] = 0;
    int k=0;
    for (int i=1; i<p.size(); ++i) {
        while (k>0 && p[k] != p[i]) {
            k = pi[k-1];
        }
        if (p[k] == p[i]) {
            ++k;
        }
        pi[i] = k;
        //std::cout<< i << '\t' << pi[i] << '\n';
    }
    //std::cout << std::endl;
}
int Kmp::kmp_match(const char *t) {
    int n = strlen(t);
    int m = p.size();
    int k=0;
    for (int i=0; i<n; ++i) {
        while (k>0 && p[k] != t[i]) {
            k = pi[k-1];
        }
        if (p[k] == t[i]) {
            ++k;
        }
        if (k==p.size()) {
            std::cout<< i-k+1 << std::endl;
            k = pi[k-1];
            //return i-k+1;
        }
    }
    return -1;
}

int main(int argc, char **argv) {
    Kmp so("ababababab");
    int ret = so.kmp_match("ababababababacacbaababacacabaac");
    std::cout << ret << std::endl;
    return 0;
}
