#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

int TreeNode::getX() {
    return data[0] ;
}

int TreeNode::getY() {
    return data[1] ;
}

int TreeNode::getX() const{
    return data[0] ;
}

int TreeNode::getY() const{
    return data[1] ;
}

ostream &operator<<(ostream &out, const TreeNode &b){
    out << b.getX() << " " << b.getY() << endl ;
    return out ;
}

TreeNode::~TreeNode() = default;

BinaryDimonTree::BinaryDimonTree() {
    _size = 0 ;
}

BinaryDimonTree::~BinaryDimonTree() {
    if(root) remove(root) ;
}

istream &operator>>(istream &in, BinaryDimonTree &tree){
    int m ;
    in >> m ;
    int x , y ;
    while(m--){
        in >> x >> y ;
        tree.insert(x , y) ;
    }
}

void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode *&guess) {
    if(!cur) return ;
    long long d = (cur->data[0] - x) * (cur->data[0] - x) + (cur->data[1] - y) * (cur->data[1] - y) ;
    if(d < min_distance){
        min_distance = d ;
        guess = cur ;
    }
    if(cur->depth % 2){
        if(y < cur->data[1]) recur_search(cur->left , x , y , min_distance , guess) ;
        else recur_search(cur->right , x , y , min_distance , guess) ;
    }
    else{
        if(x < cur->data[0]) recur_search(cur->left , x , y , min_distance , guess) ;
        else recur_search(cur->right , x , y , min_distance , guess) ;
    }
    if(cur->depth % 2){
        if((cur->data[1] - y) * (cur->data[1] - y) < min_distance){
            if (y < cur->data[1]) recur_search(cur->right, x, y, min_distance, guess);
            else recur_search(cur->left , x, y, min_distance, guess);
        }
    }
    else{
        if((cur->data[0] - x) * (cur->data[0] - x) < min_distance){
            if(x < cur->data[0]) recur_search(cur->right , x , y , min_distance , guess) ;
            else recur_search(cur->left , x , y , min_distance , guess) ;
        }
    }
}

TreeNode * BinaryDimonTree::find_nearest_node(int x, int y){
    TreeNode *guess = NULL ;
    unsigned long long a = -1 ;
    long long _Max = a / 2 ;
    recur_search(root , x , y , _Max , guess) ;
    return guess ;
}

