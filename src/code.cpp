// ============================================================
// CSCI 232 Assignment 05 – Evolution of Data Structures
// Student Implementation
// ============================================================
// Author: Caden Johns
// ============================================================

#include "code.hpp"
#include <iostream>
#include <format>

// ============================================================
// STAGE 0: Legacy C Union
// ============================================================

/// Converts a LegacyData union to a formatted string.
/// Format specs:
/// 'i' -> integer value as string (e.g., "42")
/// 'd' -> double value formatted to 2 decimal places (e.g., "3.14")
/// 'c' -> string pointer content (or "nullptr" if cPtr is null)
/// default -> "unknown"

std::string printLegacyData(LegacyData data, char type) {
    switch(type){
        case 'i':
            return std::format("{}",data.i);
        case 'd':
            return std::format("{}",data.d);
        case 'c':
            if (data.cPtr==nullptr){
                return "nullptr";
            }
            return std::format("{}",data.cPtr);
        default:
            return "unknown";
    }
    
}

// ============================================================
// STAGE 1: C-Style Struct
// ============================================================

/// Initializes a structNode with value, type indicator, and nullptr nextPtr.
void initStructNode(structNode* nPtr, LegacyData val, char type) {
    nPtr->value=val;
    nPtr->typeData=type;
    nPtr->nextPtr=NULL;
}

/// Dynamically allocates two structNodes.
/// Node 1: int 5 ('i')
/// Node 2: double 3.14 ('d')
/// Links Node 1 -> Node 2 -> nullptr
/// Returns pointer to Node 1.
structNode* createTwoStructNodes() {
    structNode *node1Ptr = new structNode;
    LegacyData n1;
    n1.i=5;
    initStructNode(node1Ptr,n1,'i');
    structNode *node2Ptr = new structNode;
    LegacyData n2;
    n2.d=3.14;
    initStructNode(node2Ptr,n2,'d');

    node1Ptr->nextPtr=node2Ptr;
    return node1Ptr;
}

// ============================================================
// STAGE 2: Early C++ Class (Classic Constructor)
// ============================================================

/// Constructor: Assign fields inside curly braces.
/// DO NOT use member initializer lists here!

// uncomment the following code to implement the classNode constructor

classNode::classNode(LegacyData val, char type) {
    this->value=val;
    this->typeData=type;
    this->nextPtr=nullptr;
 }

/// Dynamically allocates two classNodes (int 5, double 3.14) and links them.
classNode* createTwoClassNodes() {
    LegacyData n1;
    n1.i=5;
    classNode* head = new classNode(n1, 'i');
    LegacyData n2;
    n2.d=3.14;
    classNode* node2 = new classNode(n2, 'd');

    head->nextPtr=node2;

    return head;
}

// ============================================================
// STAGE 3: C++98 Templates
// ============================================================

/// Dynamically allocates two classNodeT<int> objects (int 5, int 3) and links them.
classNodeT<int>* createTwoTemplateNodes() {
    classNodeT<int>* head= new classNodeT<int>(5);
    classNodeT<int>* node2= new classNodeT<int>(3);
    head->nextPtr=node2;
    return head;
}

// ============================================================
// STAGE 4: C++17 Variant and LinkedList Manager
// ============================================================

// uncomment the following code to implement the LinkedList methods

LinkedList::LinkedList() {
    //TODO: Initialize headPtr to nullptr and counter to 0
    this->headPtr=nullptr;
    this->counter=0;
}

LinkedList::~LinkedList() {
//     // TODO: Clean up memory by calling destroyList()
    destroyList();
}
//uncoment the following code to implement the LinkedList methods

void LinkedList::destroyList() {
//     // TODO: Iterate through list, delete all nodes, and reset counter to 0
    classNodeVariant* current=headPtr;
    while (current!=nullptr)
    {
        classNodeVariant* next=current->nextPtr;
        free(current);
        current=next;
    }

    this->counter=0;
    
}

int LinkedList::addFirst(classNodeVariant* newNodePtr) {
//     // TODO: Prepend node to the front of list, increment counter
//     // Return -1 if newNodePtr is nullptr, 0 on success
    if (newNodePtr==nullptr){
        return -1;
    }
    newNodePtr->nextPtr=this->headPtr;
    this->headPtr=newNodePtr;
    this->counter+=1;

    return 0;
}

int LinkedList::addLast(classNodeVariant* newNodePtr) {
//     // TODO: Append node to the end of list, increment counter
//     // Return -1 if newNodePtr is nullptr, 0 on success
    if (newNodePtr==nullptr){
        return -1;
    }
    classNodeVariant* current=headPtr;
    if (current==nullptr){
        this->headPtr=newNodePtr;
        this->counter+=1;
        return 0;
    }
    while (current->nextPtr!=nullptr)
    {
        current=current->nextPtr;
    }
    current->nextPtr=newNodePtr;
    this->counter+=1;
    return 0;
}

int LinkedList::deleteFirst() {
//     // TODO: Delete first node, update headPtr, decrement counter
//     // Return -1 if list is empty, 0 on success
    if (this->headPtr==nullptr){
        return -1;
    }

    classNodeVariant* storedFirst=this->headPtr;

    this->headPtr=storedFirst->nextPtr;

    free(storedFirst);

    this->counter-=1;
    
    return 0;
}

int LinkedList::deleteLast() {
//     // TODO: Find second-to-last node, delete last node, decrement counter
//     // Return -1 if list is empty, 0 on success
    if (this->headPtr==nullptr){
        return -1;
    }
    classNodeVariant* secondToLast=this->headPtr;
    if (secondToLast->nextPtr!=NULL){
        free(secondToLast);
        this->counter-=1;
        return 0;
    }
    while (secondToLast->nextPtr->nextPtr!=nullptr){
        secondToLast=secondToLast->nextPtr;
    }

    free(secondToLast->nextPtr);

    secondToLast->nextPtr=nullptr;

    this->counter-=1;

    return 0;
}

int LinkedList::deleteValue(ModernData targetValue) {
//     // TODO: Traverse list, find node matching targetValue, unlink and delete it
//     // Decrement counter
//     // Return 0 if found and removed, -1 if not found or list is empty

    classNodeVariant* currentNode=this->headPtr;
    classNodeVariant* previousNode;

    if (currentNode==nullptr){
        return -1;
    }

    while(currentNode->value!=targetValue){
        if (currentNode->nextPtr==nullptr){
            return -1;
        }
        previousNode=currentNode;
        currentNode=currentNode->nextPtr;
    }

    previousNode->nextPtr=currentNode->nextPtr;

    this->counter-=1;

    free(currentNode);

    return 0;
}
#include <cassert>
int LinkedList::printList() {
//     // TODO: Iterate through list and print each variant value to std::cout
//     // Use std::holds_alternative or std::get
//     // Return -1 if list is empty, 0 on success
    if (this->headPtr==nullptr){
        return -1;
    } 
    
    classNodeVariant* currentNode=this->headPtr;

    while (currentNode!=nullptr)
    {
        if (std::holds_alternative<int>(currentNode->value)){
            std::cout<<std::get<int>(currentNode->value)<<std::endl;
        }
        else if (std::holds_alternative<double>(currentNode->value))
        {
            std::cout<<std::get<double>(currentNode->value)<<std::endl;
        }
        else if (std::holds_alternative<std::string>(currentNode->value))
        {
            std::cout<<std::get<std::string>(currentNode->value)<<std::endl;
        }
        
        currentNode=currentNode->nextPtr;
    }

    return 0;
}

int LinkedList::listLength() {
//     // TODO: Return node count
    return this->counter;
}