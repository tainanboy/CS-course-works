#include <iostream>
#include <cmath>
#include <array>
using namespace std;

class Heapp{
public:
Heapp(); //constructer
int left(int i){
    return 2*i;
};
int right(int i){
    return 2*i+1;
};
int parent(int i){
    return floor(i/2); 
};
void insert(int data);
void BuildMaxHeap(int heapArray[], int heapSize); 
void MaxHeapify(int heapArray[], int i, int heapSize);
void heapsort(int heapArray[], int heapSize);
void print(int heapArray[], int heapSize);

private:
int size;
int index;
int* maxHeap;
};

Heapp::Heapp(){
    maxHeap = NULL;
    size = 0;
    index = 0;
}

void Heapp::BuildMaxHeap(int heapArray[], int heapSize){
    for(int i = floor(heapSize/2);i>=0;i--){
        MaxHeapify(heapArray, i, heapSize);
    }
}

void Heapp::MaxHeapify(int heapArray[], int i, int heapSize){
    int largest = 0;
    int l = left(i);
    int r = right(i);
    if ((l < heapSize) && (heapArray[l] > heapArray[i])) {
        largest = l;
    } else {
        largest = i;
    }
    if ((r < heapSize) && (heapArray[r] > heapArray[largest])) {
        largest = r;
    }
    if(largest != i){
        swap(heapArray[i], heapArray[largest]);
        MaxHeapify(heapArray, largest, heapSize);
    }
}

void Heapp::heapsort(int heapArray[], int heapSize){
    BuildMaxHeap(heapArray, heapSize);
    for (int i=heapSize -1;i>=1;i--){
        swap(heapArray[0], heapArray[i]);
        heapSize = heapSize-1;
        MaxHeapify(heapArray,0, heapSize);
    }
}

void Heapp::print(int heapArray[], int heapSize){
    for (int i=0;i<heapSize;i++){
        cout<<heapArray[i]<<", ";
    }
    cout<<endl;
}

int main(){
    int array[7] = {0, 2, 5, 7, 45, 67, 99};
    Heapp t;
    t.heapsort(array, sizeof(array)/sizeof(array[0]));
    t.print(array, sizeof(array)/sizeof(array[0]));
    return 0;
}