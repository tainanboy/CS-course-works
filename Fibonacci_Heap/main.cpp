#include <iostream>
#include "fiboheap.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    fiboheap h1;
    fiboheap h2;
    Node *q;
    Node *p;
    for(int i=0; i<=10;i++){
        h1.Insert(i);
    }
    /*for(int j=11;j<=20;j++){
        h2.Insert(j);
    }*/
    //h1.Union(&h2);
    //cerr<<"size of h1 is: "<<h1.getsize()<<endl;
    cerr<<"minimum value in h1 is: "<<h1.minimum()<<endl;
    q = h1.extract_min();
    //cout<<"minimum value in h1 is: "<<q->key<<endl;
    p = h1.extract_min();
    //cout<<"minimum value in h1 is: "<<p->key<<endl;
    return 0;
}
