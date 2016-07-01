//
//  main.cpp
//  binary_tree
//
//  Created by frank on 4/9/16.
//  Copyright © 2016 frank. All rights reserved.
//
//binary tree
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class tree_node{
    friend class BST;
private:
    int data;
    tree_node *left;
    tree_node *right;
};


class BST{
public:
    BST(){
        root = NULL;
    }
    
    bool isEmpty() const {
        return root==NULL;
    }
    
    tree_node* getroot(){
        return root;
    }
    
    void postorder(tree_node* p, int indent=0)
    {
        if(p != NULL) {
            if(p->left) postorder(p->left, indent+4);
            if(p->right) postorder(p->right, indent+4);
            if (indent) {
                cout << setw(indent) << ' ';
            }
            cout<< p->data << "\n ";
        }
    }
    
    
    void insert(int d)
    {
        tree_node* t = new tree_node;
        tree_node* parent;
        t->data = d;
        t->left = NULL;
        t->right = NULL;
        parent = NULL;
        
        if(isEmpty()){
            root = t;
        }
        
        else{
            tree_node* curr;
            curr = root;
            while(curr){
                parent = curr;
                if(t->data > curr->data) curr = curr->right;
                else curr = curr->left;
            }
            
            if(t->data < parent->data){
                parent->left = t;
            }
            else{
                parent->right = t;
            }
        }
    }
    
    
    
private:
    tree_node *root;
};


int main(int argc, const char * argv[]) {
    BST tree;
    tree.insert(10);
    tree.insert(1);
    tree.insert(14);
    tree.insert(12);
    tree.insert(6);
    tree.insert(17);
    tree.insert(8);
    
    tree.postorder(tree.getroot());
    
    return 0;
}
