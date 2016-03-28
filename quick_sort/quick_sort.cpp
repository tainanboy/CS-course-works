#include <iostream>
#include <cstring>
#include <array>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
vector<int> data;

void quick_sort(vector<int> &data,int left,int right);
int partition(vector<int> &a,int left,int right);
void SWAP(vector<int> &data,int i,int j);


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
    quick_sort(data, 1, data.size()-1);
    for (int i=1;i<data.size();i++){
        cout<<data[i]<<endl;
    }
    return 0;
}
