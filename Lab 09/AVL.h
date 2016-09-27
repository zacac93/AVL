//
//  AVL.hpp
//  Lab 09
//
//  Created by Zac Clark on 3/27/16.
//  Copyright © 2016 Zac Clark. All rights reserved.
//

#pragma once
#include "AVLInterface.h"
#include "Node.h"
#include <stdio.h>
#include <stack>
#include <iostream>

using namespace std;

class AVL : public AVLInterface
{
public:
    AVL() : Root(NULL) {}
    //~AVL();
    NodeInterface * getRootNode();
    bool add(int data);
    bool remove(int data);
    bool addNode(Node*& n, int data);
    bool removeNode(Node*& n, int data);
    Node* replaceParent(Node*& oldRoot, Node*& currentRoot);
    void Balance (Node*& n);
    void BalanceToRight(Node*& n); //check to see if double or single rotate
    void BalanceToLeft(Node*& n);  //check to see if double or single rotate
    void rotateRight(Node*& n);
    void rotateLeft(Node*& n);
    int height(Node*& n);
    void updateHeight(Node*& n);
    int prevNode = -1;
    int prevNodeR = -1;
    bool replace = false;
    Node* temp = NULL;
    bool parent = false;
    bool balanceR  = false;
    bool balanceL = false;
    
private:
    Node* Root;
    bool added = false;
    bool removed = false;
    
};