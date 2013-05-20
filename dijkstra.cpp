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
    while(!q.empty()) {
        
    }

}
int main()
{
}
