/* Pseudo code:
 insertion_sort(A)
 for j = 2 to A.length
	key = A[j]
	i = j-1
	while i>0 & A[i]>key
 A[i+1] = A[i]
 i = i-1
	A[i+1] = key
 */
#include <iostream>
#include <cstring>
#include <array>
#include <string>
#include <fstream>
#include <vector>
#include<time.h>
using namespace std;
vector<double> data;


void Fileoutput(string filename)
{
    ofstream ff;
    filename="E24016506_HW1_InsertionSort_"+filename;
    ff.open(filename.c_str());
    for(int i=0;i<data.size();i++)
        ff<<data[i]<<endl;
    ff.close();
}

void insertion_sort(vector<double>& a, int length){
    for (int j=1;j<length;j++){
        int key = a[j];
        int i = j-1;
        while(i>0 && a[i]>key){
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    ifstream infile("file.txt");
    if(infile){
        double value;
        while (infile >> value) {
            data.push_back(value);
        }
    }
    double START,END;
    START = clock();
    insertion_sort(data, data.size());
    END = clock();
    for (int i=1;i<data.size();i++){
        cout<<data[i]<<endl;
    }
    Fileoutput("file.txt");
    cout<<"CPU Time"<<END-START<<endl;
    return 0;
}

