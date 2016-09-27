//
//  AVL.cpp
//  Lab 09
//
//  Created by Zac Clark on 3/27/16.
//  Copyright © 2016 Zac Clark. All rights reserved.
//

#include "AVL.h"

using namespace std;

NodeInterface * AVL::getRootNode()
{
    return Root;
}
bool AVL::add(int data)
{
    return addNode(Root, data);
}
bool AVL::remove(int data)
{
    return removeNode(Root, data);
}
bool AVL::addNode(Node*& n, int data)
{
    //cout << "Ran addNode() with new value: " << data << endl;
    if (prevNode == 0 && data == 0)
    {
        //cout << "prevNode == 0" << endl;
        prevNode = -1;
        return false;
    }
    if (n == NULL)
    {
        n = new Node(data, 0);
        if (data == 0)
            prevNode = 0;
        added = true;
    }
    else if (data < n->getData())
    {
        addNode(n->Left, data);
    }
    else if (data > n->getData())
    {
        addNode(n->Right, data);
    }
    if (added)
    {
        Balance(n);
        return true;
    }
    return true;
}
bool AVL::removeNode(Node*& n, int data)
{
    if (prevNodeR == 0 && data == 0)
    {
        prevNodeR = -1;
        return false;
    }
    
    if (n == NULL)
        return false;
    else if (data < n->value)
        removeNode(n->Left, data);
    else if (data > n->value)
        removeNode(n->Right, data);
    else
    {
        Node* temp = n;
        if (temp->value == 0)
            prevNodeR = 0;
        if (n->Left == NULL)
            n = n->Right;
        else if (n->Right == NULL)
            n = n->Left;
        else
        {
            n = replaceParent(temp, temp->Left);
        }
        delete temp;
        return true;
    }
    Balance(n);
    return true;
}
Node* AVL::replaceParent(Node*& oldRoot, Node*& currentRoot)
{
    if (currentRoot->Right != NULL)
        replaceParent(oldRoot, currentRoot->Right);
    else
    {
        oldRoot->value = currentRoot->value;
        oldRoot = currentRoot;
        currentRoot = currentRoot->Left;
    }
    return oldRoot;
}
void AVL::Balance (Node*& n)
{
    cout << "Ran Balance()" << endl;
    //update height of nodes coming back up from recursion
    updateHeight(n);
    if (height(n->Left) - height(n->Right) > 1)
    {
        //if true, rotate right
        BalanceToRight(n);
    }
    else if (height(n->Right) - height(n->Left) > 1)
    {
        //if true, rotate left
        BalanceToLeft(n);
    }
}
void AVL::BalanceToRight(Node*& n)
{
    balanceR  = true;
    cout << "Ran BalanceToRight()" << endl;
    //check to see if double or single rotate
    if (height(n->Left->Right) >  height(n->Left->Left))
    {
        //crooked path is greater
        rotateLeft(n->Left);
    }
    rotateRight(n);
    
}
void AVL::BalanceToLeft(Node*& n)
{
    balanceL = true;
    cout << "Ran BalanceToLeft()" << endl;
    //check to see if double or single rotate
    if (height(n->Right->Left) >  height(n->Right->Right))
    {
        //crooked path is greater
        rotateRight(n->Right);
    }
    rotateLeft(n);
    
}
void AVL::rotateRight(Node*& n)
{
    //cout << "Ran rotateRight() on Node " << n->value << endl;
    Node* t = n->Left;
    Node* tOriginal = t;
    Node* nOriginal = n;
    n->Left = t->Right;
    t->Right = n;
    n = t;
    
    //cout << "value of nOriginal: " << nOriginal->value << endl;
    //cout << "value of tOriginal: " << tOriginal->value << endl;
    
    //update height
    updateHeight(nOriginal);
    updateHeight(tOriginal);
    
}
void AVL::rotateLeft(Node*& n)
{
    //cout << "Ran rotateLeft() on Node " << n->value << endl;
    Node* t = n->Right;
    Node* tOriginal = t;
    Node* nOriginal = n;
    n->Right = t->Left;
    t->Left = n;
    n = t;
    
    //cout << "value of nOriginal: " << nOriginal->value << endl;
    //cout << "value of tOriginal: " << tOriginal->value << endl;
    
    //update height
    updateHeight(nOriginal);
    updateHeight(tOriginal);
    
}
int AVL::height(Node*& n)
{
    //cout << "Ran height()" << endl;
    if (n == NULL)
        return 0;
    else
        return n->height;
}
void AVL::updateHeight(Node*& n)
{
    //cout << "Ran updateHeight()" << endl;
    n->height = max(height(n->Left), height(n->Right)) + 1;
    //cout << "value: " << n->value << " with new height: " << n->height << endl;
}