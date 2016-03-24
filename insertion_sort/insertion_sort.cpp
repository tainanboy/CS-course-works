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
using namespace std;
vector<double> data;

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
    insertion_sort(data, data.size());
    for (int i=1;i<data.size();i++){
        cout<<data[i]<<endl;
    }
    return 0;
}
