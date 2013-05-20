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
    vector<vector<int> > small_length(point_size, vector<int>(point_size, -1));
    vector<vector<int> > sp(point_size, vector<int>(point_size, 0));
    for (int i=0; i<point_size; ++i) {
        small_length[i][i] = 0;
        sp[i][i] = i;
    }
    vector<int>    pre_node;
    pre_node.push_back(0);
    value_index[0]=0;
    for (int i=0; i<edge_size; ++i) {
        value_index[toJunction[i]] = i+1;	
        //small_length[fromJunction[i]][toJunction[i]]=ductLength[i];
        //small_length[toJunction[i]][fromJunction[i]]=ductLength[i]; 
        for (int j=0; j<pre_node.size(); ++j) {
            if (small_length[pre_node[j]][value_index[fromJunction[i]]] == -1) {
                continue;
            }
            small_length[pre_node[j]][value_index[toJunction[i]]] = small_length[pre_node[j]][value_index[fromJunction[i]]] + ductLength[i];
            small_length[value_index[toJunction[i]]][pre_node[j]] = small_length[pre_node[j]][value_index[toJunction[i]]];
            sp[pre_node[j]][value_index[toJunction[i]]] = sp[pre_node[j]][value_index[fromJunction[i]]];
        }
        pre_node.push_back(value_index[toJunction[i]]);
    }
    //get min_length
    int last_node=value_index[toJunction[0]];
    int min_length = ductLength[0];
    vector<int> min_array;
    int common_father = 0;
    int increase_length = 0;
    for (int i=1; i<edge_size; ++i) {
        min_length += ductLength[i];
        common_father = sp[last_node][value_index[fromJunction[i]]];
        increase_length =  small_length[common_father][last_node] - small_length[value_index[fromJunction[i]]][common_father]; 
        if (ductLength[i] < increase_length) {
            min_length += ductLength[i];
        } else {
            min_length += increase_length;
            last_node = value_index[toJunction[i]];
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
