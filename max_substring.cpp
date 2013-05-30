#include <string>
#include <iostream>

using namespace std;

string max_substring(string str) {
    char x1, x2;
    if (str.length() <3) {
        return str;
    }
    int size = str.length();
    int pos = 0;
    int max = 0;
    int pre_length = 0;
    int pre_postfix = 0;
    pre_length = 2;
    x1 = str[0];
    x2 = str[1];
    pre_postfix = x1==x2? 2 : 1;
    for (int i=2; i<size; ++i) {
        if (x1==x2 || str[i] == x1 || str[i] == x2) {
            pre_length++;
            if (str[i] == str[i-1]) {
                pre_postfix++;
            } else {
                pre_postfix = 1;
            }
            if (x1==x2) {
                x2 = str[i];
            }
        } else {
            pre_length = pre_postfix + 1;
            pre_postfix = 1;
            x1=str[i-1];
            x2=str[i];

        }
        if (max < pre_length) {
            max = pre_length;
            pos = i-max+1;
        }
    }
    return str.substr(pos, max);
}

int main(int argc, char **argv) {
    cout << max_substring("aaaaa") << endl;
    cout << max_substring("abaaa") << endl;
    cout << max_substring("abaca") << endl;
    cout << max_substring("abacca") << endl;
    cout << max_substring("aaaccababbab") << endl;
}
