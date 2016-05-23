//
//  fiboheap.hpp
//  Fibonacci_Heap
//
//  Created by frank on 5/23/16.
//  Copyright © 2016 frank. All rights reserved.
//

#ifndef fiboheap_hpp
#define fiboheap_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

class Node {
    friend class fiboheap;
public:
    Node() :
    key(0),
    left(this),
    right(this),
    parent(nullptr),
    child(nullptr),
    mark(false),
    degree(0) {}
    
    Node(int k) :
    key(k),
    left(this),
    right(this),
    parent(nullptr),
    child(nullptr),
    mark(false),
    degree(0) {}
    
    ~Node() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        child = nullptr;
    }
    
    int key;
    Node* left;
    Node* right;
    Node* parent;
    Node* child;
    bool mark;
    int degree;
};

class fiboheap{
public:
    fiboheap():size(0){} //constructor
    fiboheap(int k){
        min = new Node(k);
        size = 1;
    }
    Node* Insert(int val); //insert a node with key=val
    int minimum(); //return min value
    int getsize();
    Node* extract_min(); //extract min node and return its value
    void Union(fiboheap *h2);
    void decrease_key(Node* x, int k); //decreas value of node x with k
    void Delete(Node *x); //delete node x
    ~fiboheap(){} //destructor
    
private:
    Node* min;
    Node* leftmost;
    Node* rightmost;
    int size;
    void consolidate();
    void cut(Node *x, Node *y);
    void cascading_cut(Node *y);
    void heap_link(Node *y, Node *x);
};



#endif /* fiboheap_hpp */
