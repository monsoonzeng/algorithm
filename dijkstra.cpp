#include<stdio.h>
#include <list>
using std::list;
void dijkstra(int[][] matrix, int size, int source) {
    list<int> q;
    vector<int> preview(size, -1);
    vector<int> distance(size, -1);
    distance[source] = 0;
    for(int i=0; i<size; ++i) {
        q.push_back(i);
    }
    int current_node = source;
    int min_length;
    while(!q.empty()) {
        min_length = -1;
        for (list<int>::iterator it=q.begin(); it!=q.end(); ++it) {
            if (distance[*it] < 0 || matrix[*it][current_node]>=0 
                        && distance[*it] > (distance[current_node]+matrix[*it][current_node])) {
                distance[*it] = distance[current_node]+matrix[*it][current_node]; 
            }

        }
    }

}
int main()
{
}
