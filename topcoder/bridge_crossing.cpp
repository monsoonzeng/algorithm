#include <string>
#include <vector>
#include <iostream>

using std::vector;

class BridgeCrossing {
public:
    int minTime(vector<int> times);
};

int BridgeCrossing::minTime(vector<int> times) {
    int k[2];
    int new_k;
    int size = times.size();
    if (size <1) {
        return -1;
    } else if (size == 1) {
        return times[0];
    } else if (size == 2) {
        return times[1];
    } else if (size == 3) {
        return times[0]+times[1]+times[2];
    }
    k[0] = times[1];
    k[1] = times[0] + times[1] +times[2];
    for (int i=3; i<size; ++i) {
        //k[n+2] = a[1] + a[0] + a[n+2] + a[1] + k[n]
        new_k = k[0] + times[1] + times[0] + times[i] + times[1];
        k[0] = k[1];
        k[1] = new_k;
    }
    return k[1];
}

int main() {
    BridgeCrossing bc;
    vector<int> times;
    times.push_back(1);
    times.push_back(2);
    times.push_back(5);
    //times.push_back(4);
    //times.push_back(10);
    int result = bc.minTime(times);
    std::cout << result << std::endl;
    times.push_back(99);
    times.push_back(100);
    result = bc.minTime(times);
    std::cout << result << std::endl;
    times.push_back(200);
    result = bc.minTime(times);
    std::cout << result << std::endl;
    return 0;
}
