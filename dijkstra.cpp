#include <cstdio>
#include <climits>
#include <iostream>
#include <list>
#include <vector>
#include <priority_queue>
using std::list;
using std::vector;
using std::cout;
using std::endl;
using std::priority_queue;

class Node {
public:
    int id;
    int distance;
};

class NodeComp {
public:
    bool operator()(const Node &left, const Node &right) {
        return left.distance > right.distance;
    }
};

vector<int> heap_dijkstra(int **matrix, int size, int source) {
    vector<int> preview(size, -1);
    vector<int> distance(size, LONG_MAX);
    distance[source] = 0;
    vector<vector<int> > adjecent_matrix(size, vector<int>());
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            if(matrix[i][j] !=-1 && i!=j) {
                adjecent_matrix[i].push_back(j);
        }
    }
    NodeComp cmp;
    priority_queue<Node> q(cmp);
    int current_node = source;
    int min_length;
    Node min_node, current_node;
    int setcount = 0;
    vector<bool> inset(size, false);
    min_node.id = 0;
    min_node.distance = 0;
    q.push(min_node);

    while (setcount<size) {
        min_node = q.top();
        q.pop();
        min_length = min_node.distance;
        cout <<min_node.id << '\t' << min_length << endl;
        if (inset[min_node.id]) continue;  //important becasuse a node will be add many times
        setcount++;
        inset[min_node.id] = true;
        //update distance
        for (vector<int>::iterator it = adjecent_matrix[min_node.id].begin();
            it != adjecent_matrix[min_node.id].end(); ++it) {
            if (distance[*it] > (min_length+matrix[min_node.id][*it])) {
                distance[*it] = min_length+matrix[min_node.id][*it]; 
                current_node.id = *it;
                current_node.length = distance[*it];
                q.push(current_node);
                preview[*it] = min_node.id;
            }
        }
    }
    return distance;
}
vector<int> dijkstra(int **matrix, int size, int source) {
    list<int> q;
    vector<int> preview(size, -1);
    vector<int> distance(size, -1);
    distance[source] = 0;
    for(int i=0; i<size; ++i) {
        q.push_back(i);
    }
    int current_node = source;
    int min_length;
    list<int>::iterator min_node;
    while(!q.empty()) {
        min_length = -1;
        min_node = q.end();
        for (list<int>::iterator it=q.begin(); it!=q.end(); ++it) {
            if (distance[*it] >=0 && (min_length < 0 || min_length > distance[*it])) {
                min_length = distance[*it];
                min_node = it;
            }
        }
        cout << *min_node << '\t' << q.size() << endl;
        if (min_node == q.end()) {
            //node in q can't connect to source
            break;
        }
        q.erase(min_node);
        //update distance
        for (list<int>::iterator it=q.begin(); it!=q.end(); ++it) {
            if (matrix[*min_node][*it]>=0 && 
                        (distance[*it]<0 || distance[*it] > (distance[*min_node]+matrix[*min_node][*it]))) {
                    distance[*it] = distance[*min_node]+matrix[*min_node][*it]; 
                    preview[*it] = *min_node;
            }
        }
    }
    return distance;
}

int main()
{
    int **matrix = new int *[5];
    for (int i=0; i< 5; ++i) {
        matrix[i] = new int[5];
    }
    for (int i=0; i< 5; ++i) {
        for (int j=0; j< 5; ++j) {
            matrix[i][j] = -1;
        }
        matrix[i][i] = 0;
    }
    matrix[0][1] = 1;
    matrix[0][2] = 2;
    matrix[2][3] = 4;
    matrix[2][4] = 1;
    matrix[3][4] = 2;
    for (int i=0; i< 5; ++i) {
        for (int j=0; j< i; ++j) {
            matrix[i][j] = matrix[j][i];
        }
    }
    vector<int> result = dijkstra(matrix, 5, 0);
    for (int i=0; i<5; ++i) {
        cout << result[i] << '\t';
    }
    cout << endl;
    for (int i=0; i< 5; ++i) {
        delete []matrix[i];
    }
    delete []matrix;
}
