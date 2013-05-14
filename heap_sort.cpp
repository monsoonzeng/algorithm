#include<cstdio>
#include<iostream>

#define N 7
#define PARENT(i) (((i)-1)/2)
#define LEFT(i) ((i)*2+1)
#define RIGHT(i) ((i)*2+2)

void print(int a[], int len) 
{
	for(int i=0; i < len; ++i) {
		std::cout<<a[i]<<'\t';
	}
	std::cout<<std::endl;
}
void build_heap(int a[], int i, int length) {
	int l=0;
	if(LEFT(i)< length && a[i] < a[LEFT(i)]) {
		l = LEFT(i);
	} else {
		l = i;
	}
	if (RIGHT(i) < length && a[l] < a[RIGHT(i)]) {
		l = RIGHT(i);
	}
	if (l != i) {
		//swap l & i
		int tmp = a[l];
		a[l] = a[i];
		a[i] = tmp;
		build_heap(a, l, length);
	}
}
void heap_sort(int a[], int length)
{
	//build heap
	for(int i= PARENT(length-1); i>=0; --i){
		build_heap(a, i, length);
	}	
	for(int len = length; len>0; --len) {
		//swap a[0] a[len-1]
		int tmp = a[len-1];
		a[len-1] = a[0];
		a[0] = tmp;
		build_heap(a, 0, len-1);
	}
}
int main(int argc, char** argv)
{
	int a[] = {10,2,3,8,7,6,6};
	print(a, 7);
	heap_sort(a, N);
	print(a, 7);
	std::cout<<"hello world" << std::endl;
}
