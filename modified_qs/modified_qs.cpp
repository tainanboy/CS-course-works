#define k 400

#include <iostream>
#include <cstring>
#include <array>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
using namespace std;
vector<int> data;

void Fileoutput(string filename);
void quick_sort(vector<int> &data,int left,int right);
int partition(vector<int> &a,int left,int right);
void SWAP(vector<int> &data,int i,int j);
void insertion_sort(vector<int>& a, int p, int r);
void limited_quicksort(vector<int> &a, int p, int r, int treshold);
void modified_quicksort(vector<int> &a, int p, int r);


int main(int argc, char const *argv[])
{
    /* code */
    ifstream infile("file.txt");
    if(infile){
        int value;
        while (infile >> value) {
            data.push_back(value);
        }
    }
    double START, END;
    START = clock();
    modified_quicksort(data, 1, data.size());
    END = clock();
    for (int i=1;i<data.size();i++){
        cout<<data[i]<<endl;
    }
    Fileoutput("file.txt");
    cout<<"CPU Time"<<END-START<<endl;
    return 0;
}


void Fileoutput(string filename)
{
    ofstream ff;
    filename="E24016506_HW1_modified_qs_"+filename;
    ff.open(filename.c_str());
    for(int i=0;i<data.size();i++)
        ff<<data[i]<<endl;
    ff.close();
}

void modified_quicksort(vector<int> &a, int p, int r) {
    limited_quicksort(a, p, r, k);
    insertion_sort(a, p, r);
}

void limited_quicksort(vector<int> &a, int p, int r, int treshold) {
    if (r - p > treshold) {
        int q = partition(a, p, r);
        limited_quicksort(a, p, q, treshold);
        limited_quicksort(a, q + 1, r, treshold);
    }
}

void quick_sort(vector<int> &data,int left,int right)
{
    if (right <= left) return ;
    int pivot=partition(data,left,right);
    quick_sort(data,left,pivot-1);
    quick_sort(data,pivot+1,right);
}

int partition(vector<int> &a,int low,int high)
{
    int left=low;
    int right=high;
    int v=a[left];
    while(left<right)
    {
        while( a[left]<=v) left++;
        while(a[right]>v) right--;
        if (left<right)
            SWAP(a,left,right);
    }
    
    SWAP(a,low,right);
    return right;
}

void SWAP(vector<int> &data,int i,int j)
{
    int s=data[i];
    data[i]=data[j];
    data[j]=s;
    
}

void insertion_sort(vector<int>& a, int p, int r) {
    int i, j, key;
    
    for (j = p + 1; j < r; j++) {
        key = a[j];
        for (i = j - 1; i >= p && a[i] > key; i--) {
            a[i + 1] = a[i];
        }
        a[i + 1] = key;
    }
}
