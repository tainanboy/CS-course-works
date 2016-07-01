//
//  fiboheap.cpp
//  Fibonacci_Heap
//
//  Created by frank on 5/23/16.
//  Copyright © 2016 frank. All rights reserved.
//

#include "fiboheap.hpp"

int fiboheap::getsize(){
    return size;
}

Node* fiboheap::Insert(int k){
    Node* x = new Node(k);
    if(min==nullptr){
        //create a root list for H just x
        leftmost = rightmost = min = x;
    }
    else{ //insert x into H's root list
        if(min == leftmost){
            leftmost = x;
        }
        min->left->right = x;
        x->left = min->left;
        min->left = x;
        x->right = min;
        if(x->key < min->key){
            min = x;
        }
    }
    size++;
    return x;
}

int fiboheap::minimum(){
    return min->key;
}

Node* fiboheap::extract_min(){
    Node *z = min;
    Node *x, *next;
    Node ** childlist;
    if(!z){
        x = z->child;
        if(!x){
            childlist = new Node*[min->degree];
            next = x;
            for(int i=0; i<min->degree; i++){ //create childlist
                childlist[i] = next;
                next = next->right;
            }
            for(int i=0; i<min->degree; i++){ //add x into root list of H
                x = childlist[i];
                x->left = min->left;
                min->left->right = x;
                min->left = x;
                x->right = min;
                x->parent = nullptr;
            }
            //We update leftmost and rightmost if needed
            if (min == leftmost) {
                leftmost = childlist[0];
            }
            if (min == rightmost) {
                rightmost = childlist[min->degree];
            }
            delete[] childlist;
        }
        //remove z from root list
        z->left->right = z->right;
        z->right->left = z->left;
        if(z==z->right){
            min = nullptr;
        }
        else{
            min = z->right;
            consolidate();
        }
        size--;
    }
    return z;
}

void fiboheap::Union(fiboheap *h2){
    //concatenate root list of h1 and h2 into circular doubly list
    rightmost->right = h2->leftmost->left;
    h2->leftmost->left = rightmost;
    leftmost->left = h2->rightmost;
    h2->rightmost->right = leftmost;
    rightmost = h2->rightmost;
    if((!min)|| (h2->min!=nullptr && h2->min->key < min->key)){
        min = h2->min;
    }
    size = size + h2->size;
}

void fiboheap::consolidate(){
    Node* w, *next, *x, *y, *temp;
    Node** Array, ** rootList;
    int d, rootSize;
    int max_degree = static_cast<int>(floor(log(static_cast<double>(size)) / log(static_cast<double>(1 + sqrt(static_cast<double>(5))) / 2)));
    
    //We create an array of pointers to Nodes and we fill it with NULL values
    Array = new Node*[max_degree + 2];
    for (int k = 0; k < max_degree + 2; k++) {
        Array[k] = nullptr;
    }
    //We calculate the size of the root list
    w = min;
    rootSize = 0;
    next = w;
    do
    {
        rootSize++;
        next = next->right;
    } while (next != w);
    //We create a list with only the Nodes in the root
    next = leftmost;
    rootList = new Node*[rootSize];
    for (int i = 0; i < rootSize; i++)
    {
        rootList[i] = next;
        next = next->right;
    }
    //For each node in the list we get it and link it to the Node in the vector Array[] that has it same degree but respecting always that the key of the father is lower than the key of the son
    for (int i = 0; i < rootSize; i++)
    {
        w = rootList[i];
        x = w;
        d = x->degree;
        while (Array[d] != nullptr)
        {
            y = Array[d];
            if (x->key > y->key)
            {
                temp = x;
                x = y;
                y = temp;
            }
            heap_link(y, x);
            Array[d] = nullptr;
            d++;
        }
        Array[d] = x;
    }
    delete[] rootList;
    min = nullptr;
    //We traverse the vector Array[] adding all the nodes in it to the root list of the FibHeap and updating the _minimum _leftmost and _rightmost when necessary
    for (int i = 0; i < max_degree + 2; i++)
    {
        if (Array[i] != nullptr)
        {
            if (min == nullptr)
            {
                min =leftmost = rightmost = Array[i]->left = Array[i]->right = Array[i];
            }
            else
            {
                min->left->right = Array[i];
                Array[i]->left = min->left;
                min->left = Array[i];
                Array[i]->right = min;
                if (min == rightmost) {
                    rightmost = Array[i];
                }
                if (Array[i]->key < min->key)
                {
                    min = Array[i];
                }
            }
        }
    }
    delete[] Array;
}

void fiboheap::heap_link(Node *y, Node *x){
    //remove y from H rootlist
    y->left->right = y->right;
    y->right->left = y->left;
    //make y a child of x, increase x degree
    if(!x->child){
        x->child = y;
        y->parent = x;
        y->left = y;
        y->right = y;
    }
    else{
        y->left = x->child->left;
        x->child->left->right = y;
        x->child->left = y;
        y->right = x->child;
        x->child = y;
        y->parent = x;
    }
    x->degree = x->degree+1;
    y->mark = false;
}

void fiboheap::cut(Node *x, Node *y){
    //remove x from y child list, y degree --
    if(!x->right){
        y->child = nullptr;
    }
    else{
        x->left->right = x->right;
        x->right->left = x->left;
        if(y->child == x){
            y->child = x->right;
        }
    }
    y->degree--;
    //add x to root list of h
    min->right->left = x;
    x->right = min->right;
    min->right = x;
    x->left = min;
    x->parent = nullptr;
    x->mark = false;
}


void fiboheap::cascading_cut(Node *y){
    Node* z = y->parent;
    if(!z){
        if(y->mark==false){
            y->mark = true;
        }
        else{
            cut(y, z);
            cascading_cut(z);
        }
    }
}

void fiboheap::decrease_key(Node *x, int k){
    if(k > x->key){
        cout<<"error, new key is greater than current key"<<endl;
        return;
    }
    x->key = k;
    Node *y = x->parent;
    if(y!=nullptr && x->key<y->key){
        cut(x, y);
        cascading_cut(y);
    }
    if(x->key < min->key){
        min = x;
    }
}


void fiboheap::Delete(Node *x){
    decrease_key(x, min->key);
    Node *m = extract_min();
    delete m;
}



