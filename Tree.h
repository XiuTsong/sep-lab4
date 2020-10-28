//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
//#include <queue> //for debugging
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

class TreeNode{
    friend ostream &operator<<(ostream &out, const TreeNode &b);
    friend class BinaryTree;
    friend class BinaryDimonTree;

private:
    /* data */
    int data[2];
    int depth = 0 ;
    TreeNode* left ;
    TreeNode* right ;
public:
    /* methods */
    TreeNode(int a0 = 0 , int a1 = 0):depth(0) , left(NULL) , right(NULL){
        data[0] = a0 ;
        data[1] = a1 ;
    }
    int getX();  /* DO NOT CHANGE */
    int getY();  /* DO NOT CHANGE */
    ~TreeNode(); /* DO NOT CHANGE */
    int getX() const ;
    int getY() const ;
    void setdepth(int d){ depth = d ;}
};


class BinaryDimonTree {
    friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */
private:
    /* data */
    TreeNode *root;
    int _size ;
    void remove(TreeNode *cur){
        if(cur->left) remove(cur->left) ;
        if(cur->right) remove(cur->right) ;
        //delete *cur ;
        delete cur ;
        --_size ;
    }
    bool insert(int a0 , int a1 , TreeNode* &cur , int d){
        if(!cur){
            cur = new TreeNode(a0 , a1) ;
            cur->setdepth(d) ;
            ++_size ;
            return true ;
        }
        if(cur->data[0] == a0 && cur->data[1] == a1) return false ;
        if(cur->depth % 2){
            if(cur->data[1] > a1) return insert(a0 , a1 , cur->left , d + 1) ;
            else return insert(a0 , a1 , cur->right , d + 1) ;
        }
        else{
            if(cur->data[0] > a0) return insert(a0 , a1 , cur->left , d + 1) ;
            else return insert(a0 , a1 , cur->right , d + 1) ;
        }
    }
    long long distance(TreeNode* a , TreeNode* b){
        return (a->data[0] - b->data[0]) * (a->data[0] - b->data[0]) + (a->data[1] - b->data[1]) * (a->data[1] - b->data[1]) ;
    }
public:
    /* methods */
    BinaryDimonTree();          /* DO NOT CHANGE */
    TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */
    void recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode *&guess);
    ~BinaryDimonTree();
    bool insert(int a0 , int a1){
        return insert(a0 , a1 , root , 0) ;
    }
    /*void print(TreeNode *cur){       //for testing
        std::queue<TreeNode*> s ;
        while(!s.empty()) s.pop() ;
        s.push(root) ;
        while(!s.empty()){
            TreeNode *tmp = s.front() ;
            s.pop() ;
            std::cout << *tmp << '(' << tmp->depth << ')' << '\n' ;
            if(tmp->left) s.push(tmp->left) ;
            if(tmp->right) s.push(tmp->right) ;
        }
    }*/
    TreeNode* & getroot(){ return root ; }
    int size() { return _size ;}
};

#endif //C_BINARYDIMEN_TREE_H
