#include<stdio.h>

void print(int a[], int len)
{
    for(int i=0; i<len; ++i) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}

int partition(int a[], int start, int end)
{
    if(start>=end) {
        return start;
    }
    int key = a[start];
    while(start < end) {
        while(start < end && key <= a[end]) --end;
        if(start < end) {
            a[start] = a[end];
            ++start;
        }
        while(start < end && a[start]<key) ++start;
        if (start < end) {
            a[end] = a[start];
            --end;
        }
    }
    a[start] = key;
    return start;
}

void quick_sort2(int a[], int head, int tail)
{
    if(head>=tail) {
        return;
    }
    int pos = partition(a, head, tail);
    quick_sort2(a, head, pos-1);
    quick_sort2(a, pos+1, tail);

}

void quick_sort(int a[], int head, int tail)
{
    if(head>=tail) {
        return;
    }
    int cur = a[head];
    int start = head;
    int end = tail;
    while(start<end) {
        while(start<end && cur <=a[end]) --end;
        if(start < end) {
            a[start++]=a[end];
        }
        while(start<end && cur > a[start]) ++start;
        if (start < end) {
            a[end--] = a[start];
        }
    }
    a[start]=cur;
//    print(a, 5);
    quick_sort(a, head, start-1);
    quick_sort(a, start+1, tail);
}

int main()
{
    int a[]={1,2,3,4,5};
    int b[]={5,4,3,2,1};
    int c[]={1,4,3,2,1};
    int d[]={1,3,3,2,1};
    print(a, 5);
    quick_sort(a, 0, 4);
    print(a, 5);
    print(b, 5);
    quick_sort(b, 0, 4);
    print(b, 5);
    print(c, 5);
    quick_sort(c, 0, 4);
    print(c, 5);
    print(d, 5);
    quick_sort(d, 0, 4);
    print(d, 5);
    return 0;
}
