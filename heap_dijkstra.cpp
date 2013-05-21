#include <iostream>
#include <vector>
using namespace std;
const unsigned int NoEdge=0xfffffff;
struct vertex{
    int n;
    int weight;
};

vertex heap[100];
int ph[100];//ph[i]存放顶点i在堆中的下标,当i的位置改变时它也随之改变 
int size;//堆的大小
inline int parent(int i)
{
    return (i+1)/2-1;
}
inline int left(int i)
{
    return (i+1)*2-1;
}
inline int right(int i)
{
    return (i+1)*2;
}
void heapify(int i)
{
    int smallest=i;
    if(left(i)<size&&heap[left(i)].weight<heap[smallest].weight)
    {
        smallest=left(i);
    }
    if(right(i)<size&&heap[right(i)].weight<heap[smallest].weight)
    {
        smallest=right(i);
    }
    if(smallest!=i)
    {//交换heap[smallest]和heap[i]中的值,并实ph[]中的值与交换后的情况一致
        ph[heap[smallest].n]=i;
        ph[heap[i].n]=smallest;
        vertex temp;
        temp=heap[smallest];
        heap[smallest]=heap[i];
        heap[i]=temp;
        heapify(smallest);
    }
}
vertex extract()
{
    //得到从原点出发的可到达的最近的点
    vertex min=heap[0];
    heap[0]=heap[--size];
    ph[heap[0].n]=0;
    heapify(0);
    return min;
}
void build()
{
    //initialize a heap from an array , but not used in Dijkstra.
    for(int i = parent(size-1) ; i >=0 ; --i)
    {
        heapify(i);
    }
}
void decrease(int i,int key)
{
    //更新heap[i]的值为key,且key必须为非负
    heap[i].weight=key;
    while(i>0&&heap[i].weight<heap[parent(i)].weight)
    {
        ph[heap[i].n]=parent(i);
        ph[heap[parent(i)].n]=i;
        vertex temp;
        temp=heap[i];
        heap[i]=heap[parent(i)];
        heap[parent(i)]=temp;
        i=parent(i);
    }
}
bool empty()
{//测试堆是否为空
    return size==0;
}
int n;//顶点的个数
int d[100];//存放从原点到此顶点的最短距离
vector<vertex> v[100];
void Dijkstra(int source)
{
    for(int i = 0 ; i < n ; ++i )
    {
        heap[i].n=i;
        heap[i].weight=NoEdge;
        ph[i]=i;
    }
    decrease(source,0);
    vertex min;
    while(!empty())
    {
        min=extract();
        d[min.n]=min.weight;
        cout << endl;
        for(vector<vertex>::iterator itr=v[min.n].begin();itr!=v[min.n].end();++itr)
        {
            if(heap[ph[itr->n]].weight>min.weight+itr->weight)
            {
                decrease(ph[itr->n],min.weight+itr->weight);
            }
        }
    }
} 
int main()
{
    int a,b,w;
    int edges;
    vertex temp;
    cin >> n;
    cin >> edges;
    size=n;
    for(int i = 0 ; i < n ; ++i )
    {
        d[i]=NoEdge;
    }
    for(int i = 0 ; i < edges; ++i )
    {
        cin >> a >> b >> w;
        temp.n=b;
        temp.weight=w;
        v[a].push_back(temp);
    }

    int s,t;
    while(cin>>s>>t)
    {
        Dijkstra(s);
        cout<<d[t]<<endl;
    }
    return 0;
}

