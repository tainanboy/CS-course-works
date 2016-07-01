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
    int Maximim(int heapArray[]){
        return heapArray[0];
    };
    void BuildMaxHeap(int heapArray[], int heapSize);
    void MaxHeapify(int heapArray[], int i, int heapSize);
    void heapsort();
    void print();
    void modify(int index, int data);
    void insert(int data);
    
private:
    int size;
    int* maxHeap;
};

Heapp::Heapp(){
    maxHeap = NULL;
    size = 0;
}

void Heapp::BuildMaxHeap(int heapArray[], int heapSize){
    size = heapSize;
    for(int i = floor(size/2);i>=0;i--){
        MaxHeapify(heapArray, i, size);
    }
    maxHeap = heapArray;
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

void Heapp::heapsort(){
    int heapsize = size;
    BuildMaxHeap(maxHeap, heapsize);
    for (int i=heapsize -1;i>=1;i--){
        swap(maxHeap[0], maxHeap[i]);
        heapsize = heapsize-1;
        MaxHeapify(maxHeap,0, heapsize);
    }
}

void Heapp::modify(int i, int data){
    if(data<maxHeap[i]){
        cout<<"Error, new key is smaller than current";
        cout<<",current:"<<maxHeap[i];
        cout<<",new:"<<data<<endl;
    }
    maxHeap[i] = data;
    while(i>1 && maxHeap[parent(i)]<maxHeap[i]){
        swap(maxHeap[i], maxHeap[parent(i)]);
        i =  parent(i);
    }
}


void Heapp::insert(int data){
    size = size+1;
    int *tmp = new int[size];
    for(int i =0;i<size-1;i++){
        tmp[i] = maxHeap[i];
    }
    tmp[size-1] = data;
    maxHeap = tmp;
    /*for(int i =0;i<size;i++){
        cout<<maxHeap[i]<<",";
    }*/
    delete [] tmp;
}


void Heapp::print(){
    for (int i=0;i<size;i++){
        cout<<maxHeap[i]<<", ";
    }
    cout<<endl;
}


int main(){
    int array[7] = {0, 5, 2, 47, 54, 7, 99};
    Heapp t;
    t.BuildMaxHeap(array, sizeof(array)/sizeof(array[0]));
    cout<< "Max value is "<<t.Maximim(array)<<endl;
    t.print();
    t.modify(2,10);
    t.print();
    t.insert(33);
    t.print();
    t.heapsort();
    t.print();
    return 0;
}