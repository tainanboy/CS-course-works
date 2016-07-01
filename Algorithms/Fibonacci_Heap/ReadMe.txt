#fibonacci heap
I use class to implement fibonacci heap in C++, since the whole program is relatively complicated.
The program consists of two classes, including class Node and class fiboheap, Node is the construct element of fiboheap.
Node has the following pinters and value:     
	int key;
    Node* left;
    Node* right;
    Node* parent;
    Node* child;
    bool mark;
    int degree;
fiboheap has the following operations:     
	Node* Insert(int val); //insert a node with key=val
    int minimum(); //return min value
    int getsize();
    Node* extract_min(); //extract min node and return its value
    void Union(fiboheap *h2);
    void decrease_key(Node* x, int k); //decreas value of node x with k
    void Delete(Node *x); //delete node x
    ~fiboheap(){} //destructor
    void consolidate();
    void cut(Node *x, Node *y);
    void cascading_cut(Node *y);
    void heap_link(Node *y, Node *x);
which you can see it clearly in the fiboheap.hpp header file
all of the above operations are sililar to those in the CLRS textbook