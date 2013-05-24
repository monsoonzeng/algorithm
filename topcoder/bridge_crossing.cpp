#include <string>
#include <vector>

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
    return 0;
}
