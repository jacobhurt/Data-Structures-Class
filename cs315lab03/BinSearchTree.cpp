//
//  BinSearchTree.cpp
//  cs315lab03
//
//  Created by Jacob Hurt on 10/4/17.
//  Copyright © 2017 Jacob Hurt. All rights reserved.
//

#include "BinSearchTree.hpp"
#include "TreeNode.hpp"
#include <iostream>
#include <string.h>
#include <queue>

TreeNode *BinSearchTree::local_insert( TreeNode *root, int v ) {
    if( root == nullptr )
        return new TreeNode( v );
    if( root->value() < v )
        root->rightSubtree( local_insert( root->rightSubtree(), v ) );
    else
        root->leftSubtree( local_insert( root->leftSubtree(), v ) );
    return root;
}

void BinSearchTree::insert(int v) {
    if( ! find(v) )
        root = local_insert( root, v );
}


bool BinSearchTree::find( int v ){
    if ( root == nullptr)
        return false;
    if ( root -> value() == v)
        return true;
    if ( root -> value() < v)
        return local_find ( root -> rightSubtree(), v );
    return local_find( root -> leftSubtree(), v );
    
}

bool BinSearchTree::local_find(TreeNode * node, int v) {
    
    
    if (node == NULL)
        return false;
    else if (node->value() == v)
        return true;
    else if (root->value() < v)
        return local_find(root->rightSubtree(), v);
    return local_find(root->leftSubtree(), v);
}



int BinSearchTree::size(){
    
    if ( root == NULL) return 0;
    return local_size(root);
    
}

int BinSearchTree::local_size(TreeNode* node) {
    
    if (node == NULL)
        return 0;
    else return local_size(node->leftSubtree()) + local_size(node->rightSubtree());
    
}


void BinSearchTree::inorderDump(){
    local_inorder(root);
}

void BinSearchTree::local_inorder(TreeNode * node) {
    if (node != NULL)
    {
        local_inorder(node->leftSubtree());
        std::cout << node->value() << " ";
        local_inorder(node->rightSubtree());
    }
}

int BinSearchTree::maxDepth(){
    
    return local_maxDepth(root);
}

int BinSearchTree::local_maxDepth(TreeNode* node) {
    if (root == nullptr)
        return 0;
    int lDepth = local_maxDepth(node->leftSubtree());
    int rDepth = local_maxDepth(node->rightSubtree());
    if (lDepth > rDepth)
        return (lDepth + 1);
    return (rDepth + 1);
}



void BinSearchTree::levelOrderDump() {
    // no levels to print for empty BST
    if (root == NULL)
        return;
    
    // queue of nodes (FCFS data structure)
    std::queue<TreeNode*> treeQueue;
    
    // start with root
    treeQueue.push(root);
    
    // repeat till queue not empty
    while (treeQueue.size() > 0)
    {
        // current level nodes
        for (int i = 0; i < treeQueue.size(); i++)
        {
            // get the node, and print
            TreeNode* node = treeQueue.front();
            std::cout << node->value() << " ";
            
            // pop the node after it's processed
            treeQueue.pop();
            
            // check and add left & right subtree nodes
            if (node->leftSubtree() != NULL)
                treeQueue.push(node->leftSubtree());
            if (node->rightSubtree() != NULL)
                treeQueue.push(node->rightSubtree());
        }
        // a new line to mark end of a level
        std::cout << std::endl;
    }

}


TreeNode* TreeNode::remove(int value, TreeNode *parent) {
    
    if (value < this->value()) {
        if (left != NULL)
            return left->remove(value, this);
        else
            return NULL;
    }
    else if (value > this->value()) {
        if (right != NULL)
            return right->remove(value, this);
        else
            return NULL;
    }
    else {
        if (left != NULL && right != NULL) {
            this->value() = right->minValue();
            
            return right->remove(this->value(), this);
        }
        else if (parent->left == this) {
            if (left != NULL)
                parent->left = left;
            else
                parent->left = right;
            return this;
        }
        else if (parent->right == this) {
            if (left != NULL)
                parent->right = left;
            else
                parent->right = right;
            return this;
        }
    }
    return this;
}


int TreeNode::minValue() {
    
    if (left == NULL)
        return data;
    else
        return left->minValue();
}


bool BinSearchTree::remove(int v) {
    // nothing to remove from empty BST
    if (root == NULL)
        return false;
    // remove at root of the tree
    else if (root->value() == v) {
        // assume a temporary node
        TreeNode tempRoot;
        tempRoot.value() = 0;
        tempRoot.leftSubtree(root);
        
        // process remove on it
        TreeNode* removedNode = root->remove(v, &tempRoot);
        // the left subtree points to the new root we need
        root = tempRoot.leftSubtree();
        
        // only if node removed is NOT null, do we remove
        if (removedNode != NULL) {
            delete removedNode;
            return true;
        }
        else {
            return false;
        }
    }
    else {
        // get the removed node
        TreeNode* removedNode = root->remove(v, NULL);
        // only if node removed is NOT null, do we remove
        if (removedNode != NULL) {
            delete removedNode;
            return true;
        }
        else {
            return false;
        }
    }
}

int BinSearchTree::kthSmallest(int k) {
    
    // precondition check
    if (size() < k)
        return 0;
    else // recursive local call
        return local_kthSmallest(root, 0, k);
}

int BinSearchTree::local_kthSmallest(TreeNode * node, int c, int k){
    // process in inorder sequence
    if (node->leftSubtree() != NULL)
        return local_kthSmallest(node->leftSubtree(), c, k);
    
    ++c;
    
    if (c == k)
        return node->value();
    
    if (node->rightSubtree() != NULL)
        return local_kthSmallest(node->rightSubtree(), c, k);
    return 0;
}

void BinSearchTree::valuesAtLevel(int k) {
    
    // start recursion from root
    local_valuesAtLevel(root, 0, k);
    std::cout << std::endl;
}

void BinSearchTree::local_valuesAtLevel(TreeNode* node, int c, int k) {
    // if node is NULL, just return
    if (node == NULL) {
        return;
    }
    // when we reach the k level, we print the value
    else if (c == k) {
        std::cout << node->value() << " ";
        return;
    }
    // for when we haven't reached, we recursively process on left & right subtrees
    else {
        local_valuesAtLevel(node->leftSubtree(), c + 1, k);
        local_valuesAtLevel(node->rightSubtree(), c + 1, k);

    }
}
void BinSearchTree::iterValuesAtLevel(int k) {
    std::queue<TreeNode*> treeQueue;
    
    // at level 1, start with root
    int level = 1;
    treeQueue.push(root);
    
    // push extra null
    treeQueue.push(NULL);

    // repeat till queue not empty
    while (!treeQueue.empty()) {
        
        // get the queue front
        TreeNode* node = treeQueue.front();
        
        // reached level k
        if (level == k && node != NULL) {
            std::cout << node->value() << " ";
        }
        
        // pop the processed node
        treeQueue.pop();
        
        // when node is null
        if (node == NULL) {
            
            // check if queue front is not null, need to push null again
            if (treeQueue.front() != NULL)
                treeQueue.push(NULL);
            
            // level increment
            level++;
            // level exceeded case
            if (level > k)
                break;
        }
        else {
            // check and push left/righ subtree
            if (node->leftSubtree() != NULL)
                treeQueue.push(node->leftSubtree());
            
            if (node->rightSubtree() != NULL)
                treeQueue.push(node->rightSubtree());
        }
    }
    std::cout << std::endl;

}
    

int BinSearchTree::iterMaxDepth(){
    // empty tree is 0 height
    if (root == NULL)
        return 0;
    
    // queue of tree nodes
    std::queue<TreeNode*> treeQueue;
    
    // start with root
    treeQueue.push(root);
    int depth = 0;
    
    // repeat till tree queue is not empty
    while (treeQueue.size() > 0) {
        
        // as we go down, depth is increased
        depth++;
        
        // current queue size
        int count = treeQueue.size();
        for (int i = 0; i < count; i++) {
            
            // get current node
            TreeNode* node = treeQueue.front();
            
            // push to queue if left/right is not null
            if (node->leftSubtree() != NULL)
                treeQueue.push(node->leftSubtree());
            if (node->rightSubtree() != NULL)
                treeQueue.push(node->rightSubtree());
            
            // pop the processed node
            treeQueue.pop();
        }
    }
    // return the computed value
    return depth;
}

bool BinSearchTree::hasRootToLeafSum(int sum){
    // call the recursive method
    return local_hasRootToLeafSum(root, sum);
}

bool BinSearchTree::local_hasRootToLeafSum(TreeNode* node, int sum){
    // if we are out of tree (leaf reached)
    if (node == NULL)
        // return true if left over sum is now 0
        return (sum == 0);
    else {
        
        bool result = false;
        
        // find left over sum, after removing this node's value
        int leftOverSum = sum - node->value();
        
        // no left over sum, and it is a leaf (no left/right child)
        if (leftOverSum == 0 && node->leftSubtree() == NULL && node->rightSubtree() == NULL)
            return true; // path found
        
        // check on the left/right side with recursion
        if (node->leftSubtree() != NULL)
            result = result || local_hasRootToLeafSum(node->leftSubtree(), leftOverSum);
        if (node->rightSubtree() != NULL)
            result = result || local_hasRootToLeafSum(node->rightSubtree(), leftOverSum);
        
        // return final result
        return result;
    }

}

bool BinSearchTree::areIdentical(BinSearchTree *bst){
    // call recursive method
    return local_areIdentical(root, bst->root);
}

    
bool BinSearchTree::local_areIdentical(TreeNode* node1, TreeNode* node2){
    // both null (identical)
    if (node1 == NULL && node2 == NULL)
        return true;
    // both are not null right now, need to check ahead
    else if (node1 != NULL && node2 != NULL) {
            
        // return true, only if both values are same, & left/right comparison yields true
        bool result = true;
        result = result && (node1->value() == node2->value());
        result = result && (local_areIdentical(node1->leftSubtree(), node2->leftSubtree()));
        result = result && (local_areIdentical(node1->rightSubtree(), node2->rightSubtree()));
            
        return result;
        }
        // 1 is null, and other is not null (not identical)
    else
        return false;
}
    
    
BinSearchTree* BinSearchTree::intersectWith(BinSearchTree *bst){
        
    // create the result BST
    BinSearchTree* result = new BinSearchTree;
    // invoke the local recursive on it with the root of both trees
    result->local_intersectWith(root, bst->root);
    return result;
}

void BinSearchTree::local_intersectWith(TreeNode* node1, TreeNode* node2) {
        
    // when nodes are both null, nothing to intersect
    if (node1 == NULL || node2 == NULL)
        return;
        
    // interesect found on matching values
    if (node1->value() == node2->value()) {
        // insert this value
        insert(node1->value());
            
        // recursively go both sides
        local_intersectWith(node1->leftSubtree(), node2->leftSubtree());
        local_intersectWith(node1->rightSubtree(), node2->rightSubtree());
    }
    // for mismatches value, do alternate recursion
    else if (node1->value() < node2->value()) {
        local_intersectWith(node1, node2->leftSubtree());
        local_intersectWith(node1->rightSubtree(), node2);
    }
    else {
        local_intersectWith(node1->leftSubtree(), node2);
        local_intersectWith(node1, node2->rightSubtree());
    }

}




BinSearchTree* BinSearchTree::unionWith(BinSearchTree *bst) {
        
    // create the result BST
    BinSearchTree* result = new BinSearchTree;
    // invoke the local recursive on it with the root of both trees
    result->local_unionWith(root, bst->root);
    return result;
}

void BinSearchTree::local_unionWith(TreeNode* node1, TreeNode* node2) {
        
    // no union on empty nodes
    if (node1 == NULL || node2 == NULL)
        return;
    
    // value match, and not already exists. insert only 1 time
    if (node1->value() == node2->value() && !find(node1->value()))
        insert(node1->value());
    else {
            
        // if the value of node1 or node2, not already there. THen insert it
        if (!find(node1->value()))
            insert(node1->value());
        if (!find(node2->value()))
            insert(node2->value());
    }
        
    // recursively process on left/right subtrees
    local_unionWith(node1->leftSubtree(), node2->leftSubtree());
    local_unionWith(node1->rightSubtree(), node2->rightSubtree());
}

BinSearchTree* BinSearchTree::differenceOf(BinSearchTree *bst) {
    // create the result BST
    BinSearchTree* result = new BinSearchTree;
    // invoke the local recursive on it with the root of both trees
    result->local_differenceOf(root, bst->root);
    return result;
}

    
void BinSearchTree::local_differenceOf(TreeNode* node1, TreeNode* node2) {
    // no union on empty nodes
    if (node1 == NULL || node2 == NULL)
        return;
        
    // only for the non matching values
    if (node1->value() != node2->value()) {
        // insert the value of node 1
        insert(node1->value());
        // make sure node2 was never inserted on the tree,
        // by processing find/remove
        if (find(node2->value()))
            remove(node2->value());
    }
        
    // recursively process on left/right subtrees
    local_differenceOf(node1->leftSubtree(), node2->leftSubtree());
    local_differenceOf(node1->rightSubtree(), node2->rightSubtree());
}


















