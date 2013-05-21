#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class PowerOutage {
public:
    int estimateTimeOut(vector<int> fromJunction, vector<int> toJunction, vector<int> ductLength);
};

int PowerOutage::estimateTimeOut(vector<int> fromJunction, vector<int> toJunction, vector<int> ductLength) {
//small_length[ni][nj] is the smallest length from node i to node j. 
//min_length[i] is the minimum minutes with graph    represented by set of edges( from edge[0] to edge[i])
    //contruct graph represented by matrix
    int value_index[50];
    int edge_size = fromJunction.size();
    int point_size = fromJunction.size()+1;
    value_index[0]=0;
    //get min_length
    int last_node=0;
    int min_length = 0;
    int increase_length = 0;
    vector<int> depth(point_size, 0);
    for (int i=0; i<edge_size; ++i) {
        value_index[toJunction[i]] = i + 1;
        depth[i+1] = depth[value_index[fromJunction[i]]] + ductLength[i];
        min_length += ductLength[i];
        increase_length = depth[last_node] - depth[value_index[fromJunction[i]]];
        if (ductLength[i] < increase_length) {
            min_length += ductLength[i];
        } else {
            min_length += increase_length;
            last_node = i+1;
        }
    }
    return min_length;
}

int main()
{
    PowerOutage so ;
    vector<int> fromJunction;
    fromJunction.push_back(0);
    fromJunction.push_back(0);
    fromJunction.push_back(0);
    fromJunction.push_back(1);
    fromJunction.push_back(4);
    fromJunction.push_back(4);
    fromJunction.push_back(6);
    fromJunction.push_back(7);
    fromJunction.push_back(7);
    fromJunction.push_back(7);
    fromJunction.push_back(20);
    vector<int> toJunction;
    toJunction.push_back(1);
    toJunction.push_back(3);
    toJunction.push_back(4);
    toJunction.push_back(2);
    toJunction.push_back(5);
    toJunction.push_back(6);
    toJunction.push_back(7);
    toJunction.push_back(20);
    toJunction.push_back(9);
    toJunction.push_back(10);
    toJunction.push_back(31);
    vector<int> ductLength;
    ductLength.push_back(10);
    ductLength.push_back(10);
    ductLength.push_back(100);
    ductLength.push_back(10);
    ductLength.push_back(5);
    ductLength.push_back(1);
    ductLength.push_back(1);
    ductLength.push_back(100);
    ductLength.push_back(1);
    ductLength.push_back(1);
    ductLength.push_back(5);
    int result = so.estimateTimeOut(fromJunction, toJunction, ductLength);
    cout<<result<<endl;
}
