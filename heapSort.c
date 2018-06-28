// recursice approach for the heapOr method(max-heapify)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define N 9 // for textbook examples where the lenght is 9 elements
#define SIZE 20000 // when using a file

void print(int* ptr, int start, int n)
{
	ptr += start; // for the offset when printing the substring
	for (int i = start; i <= n; i++)
	{
		printf("%d ", *ptr);
		ptr += 1;
	} printf("\n");
}
void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
// do the checking of valid child index within the methods
// works on indicies
int left(int i, int n)
{ 
	int i_temp = (2  * i) + 1;
	return (i_temp <= n) ? i_temp : -1; 
}
int right(int i, int n)
{ 
	int i_temp = (i * 2) + 2;
	return (i_temp <= n) ? i_temp : -1;
}
int parent(int i)
{
	if (i == 1 || i == 2) { return 0; }
	else if ( i % 2 == 0) { return floor(i / 2) - 1; } 
	else { return floor(i / 2); }
}
// counts the numer of parent nodes
void isParent(int* ptr, int* height, int n)
{
	// loop over the array
	for (int i = 0; i <= n; i++)
	//for (int i = start; i <= n; i++) // optional, if looping form a specific starting position
	{
		int l = left(i, n); int r = right(i, n); // indicies
		int lChild, rChild ; // local values, just for comparison

		// if both of left/right is -1, then it's not a parent node
		if (l != -1) { lChild = ptr[l]; } else { lChild = l; }
		if (r != -1) { rChild = ptr[r]; } else { rChild = r; }
		if (lChild != -1 && rChild != -1) { *height += 1; }		
		// increment the ptr
		ptr += 1;
	}
}
// boolen function for chekcing if the node is in heap order
int isOrder(int arr[], int index, int n)
{
	int l = left(index, n); int r = right(index, n);
	if (arr[index] > arr[l] && arr[index] > arr[r]) { return 1; }
	return 0;
}
// returns an info about index changes
void heapOr(int arr[], int* i, int n)
{
	int l = left(*i, n); int r = right(*i, n);
	static int largest;
	assert(l <= n && r <= n); // 0 <= A.heap_size <= A.size, n is the heap size
	
	if (arr[l] > arr[*i] && arr[l] > arr[r]) { largest = l; } //&& was added after by me
	else if (arr[r] > arr[*i] && arr[r] > arr[l]) { largest = r; }
	else { largest = *i; }	
	// do the swap with the root
	swap(&arr[*i], &arr[largest]);
	// update the root index, the postion in the main
	*i = largest;
}
// check if each index is in order(triplet) if not in order, heap
void drive(int arr[], int root, int n)
{
	// int* local_root = &root;
	// while not in order, do the ordering
	while(!isOrder(arr, root, n))
	{	
		int* local_root = &root;
		heapOr(arr, local_root, n); // this acts like a recursive call thet should havebeen done in heapOr
		root = *local_root; // updating the root value acts like a recursion
		// no need for the explicit recursion, results are just fine
	}
}
void heapsort(int arr[], int n)
{
	for (int i = n; i >= 1; i--)
	{
		swap(&arr[0], &arr[i]);
		// n -= 1; // decrement the heap size A.length
		int heap_size = (n -= 1); // = (n -= 1) works only with -O1 compiler optimization
		drive(arr, 0, heap_size); // always build max heap taking the beginning as root
	}
}

int main(void)
{
	int arr[SIZE];
	// read form the input file and fill the local array
	FILE* myfile = fopen("IntegerArray.txt", "r");
	FILE* short_input = fopen("inputArray.txt", "w");
	for (size_t i = 0; i < SIZE; ++i)
	{
		fscanf(myfile, "%d", &arr[i]);
		fprintf(short_input, "%d\n", arr[i]);
	}
	
	int mid = (int)floor(SIZE / 2) + 1;	printf("mid_index = %d\n", mid);
	// build a maxheap
    for (int j = mid; j >= 0; --j) 
    {
   		drive(arr, j, SIZE);
    }
   	//heapsort
    heapsort(arr, SIZE); //print(arr, 0, SIZE);

	// save the sorted elements into a separate file
	FILE* sorted = fopen("hs.txt", "w");
	for (int i = 0; i < SIZE; ++i)
	{
		fprintf(sorted,"%d\n", arr[i]);
	}
	fclose(sorted);

	return 0;
}
	