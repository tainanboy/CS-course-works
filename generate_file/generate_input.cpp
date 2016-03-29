
#include <iostream>
#include <cstring>
#include <array>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
vector<int> data;
void Fileoutput(string filename);


int main(int argc, char const *argv[])
{
    /* code */
    int size = 10000;
    data.push_back(size);
    for (int i=0;i<=size;i++){
        data.push_back(i);
    }
    for (int i=0;i<data.size();i++){
        cout<<data[i]<<endl;
    }
    Fileoutput("file.txt");
    return 0;
}


void Fileoutput(string filename)
{
    ofstream ff;
    filename="file.txt";
    ff.open(filename.c_str());
    for(int i=0;i<data.size();i++)
        ff<<data[i]<<endl;
    ff.close();
}
