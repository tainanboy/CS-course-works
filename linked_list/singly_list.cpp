//singly linked list
#include <iostream>
using namespace std;


class Node{
    friend class LinkedList;
public:
    Node(void): next(NULL) { }
    
    Node(int val): value(val), next(NULL){ }
    
    Node(int val, Node* next): value(val), next(next){}
    
    int getValue(void)
    { return value; }
    
    Node* getNext(void)
    { return next; }

private:
    int value;
    Node *next;

};


class LinkedList{
public:
    // constructor
    LinkedList(){
        head = NULL;
    }
    
    // Insert a value at the beginning of the list
    void Insert(int val){
        Node *n = new Node();
        if (head == NULL) {
            tail = head = new Node(val);
        }
        else {
        n->value = val;
        n->next = head;
        head = n;
        }
    }
    
    
    void Delete(int val){
        Node *Pre = NULL, *Del = NULL;
        Pre = head;
        Del = head->next;
        if (head->value ==val){
            Del = head;
            head = Del->next;
            delete Del;
            return;
        }
        while(Del != NULL){
            if (Del->value == val){
                Pre->next = Del->next;
                if (Del == tail){
                    tail = Pre;
                }
                delete Del;
                break;
            }
            Pre = Del;
            Del = Del->next;
        }
    }
    
    Node* Search(int k){
        Node *n = head;
        while(n!= NULL && n->value!=k){
            n = n->next;
        }
        return n;
    }
    
    void print()
    {
        Node *p = head;
        
        if (head == NULL) {
            cout << "The list is empty." << endl;
            return;
        }
        cout << "LinkedList: ";
        while (p != NULL) {
            cout << p->value << ",";
            p = p->next;
        }
        cout << endl;
    }
    
private:
    Node *head;
    Node *tail;
};

int main() {
    LinkedList list;
    
    list.Insert(5);
    list.Insert(10);
    list.Insert(20);
    list.Delete(5);
    
    Node* node;
    cout << "Searching the list:" << endl;
    node = list.Search(10);
    if (node != NULL)
        cout << "Find a node with value " << node->getValue() << endl;
    else
        cout << "Cannot find a node with the value" << endl;
    cout << endl;
    
    list.print();
    return 0;
}
