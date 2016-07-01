#include <iostream>
#include <cmath>
using namespace std;

int size = 2;
int* arr = new int[size-1];
int num = 0;
double alpha = (double)num/size;


void expand()
{
    cout<<"expand called"<<endl;
    int* resize_arr = new int[size*2];
    for(int i = 0; i <= size; i++){
        resize_arr[i] = 0;
        resize_arr[i] = arr[i];
        //cout<<"resize"<<resize_arr[i]<<endl;
    }
    size = size*2;
    arr = resize_arr;
    delete[] resize_arr;
}

void contract()
{
    if(size>2){
        cout<<"contract called"<<endl;
        int* resize_arr = new int[size/2];
        for(int i = 0; i <= size; i++){
            resize_arr[i] = 0;
            resize_arr[i] = arr[i];
            //cout<<"resize"<<resize_arr[i]<<endl;
        }
        size = size/2;
        arr = resize_arr;
        delete[] resize_arr;
    }
}


void insert(int array[], int value){
    double alpha = (double)num/size;
    //cout << "num is "<<num<<endl;
    //cout << "size is "<<size<<endl;
    cout << "alpha is "<<alpha<<endl;
    if(alpha >= 1.0){
        expand();
    }
    if(alpha <= 0.5){
        contract();
    }
    arr[num] = value;
    num++;
    /*cout<<"size = "<<size<<endl;
    for(int i = 0; i <= size; i++){
        cout<<arr[i]<<endl;
    }*/
}

void Delete(int array[]){
    double alpha = (double)num/size;
    //cout << "num is "<<num<<endl;
    //cout << "size is "<<size<<endl;
    cout << "alpha is "<<alpha<<endl;
    if(alpha >= 1.0){
        expand();
    }
    if(alpha <= 0.5){
        contract();
    }
    arr[num] = 0;
    num--;
    /*cout<<"size = "<<size<<endl;
     for(int i = 0; i <= size; i++){
     cout<<arr[i]<<endl;
     }*/
}


int main(int argc, const char * argv[]) {
    // insert code here...
    int times = 20;
    for(int i=0;i<times;i++){
        insert(arr, i);
    }
    for(int i=0;i<times/2;i++){
        Delete(arr);
    }
    //cout<<"array size= "<<size<<endl;
    //cout<<"vacant spot= "<<size-num<<endl;
    for(int j =0;j<size;j++){
        cout<<"array["<<j<<"] is "<<arr[j]<<endl;
    }
    return 0;
}