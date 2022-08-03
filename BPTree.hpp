//
//  BPTree.hpp
//  Database 1.0
//
//  Created by Saman Givian on 7/7/22.
//

#ifndef BPTree_hpp
#define BPTree_hpp

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <cstring>


struct record_node
{
    char  record[20][50] = { " " };
};

// BP node
class Node {
public:
    bool IS_LEAF;
    int *key, size;
    record_node ** recordptr;
    Node **ptr;
    friend class BPTree;
    Node();
};

// BP tree
class BPTree {
    Node *root;
    void insertInternal(int,record_node *, Node *, Node *);
    Node *findParent(Node *, Node *);
   
    
public:
    BPTree();
    std:: string BPTreeReleationName;
    int RecordNum = 0;
    std:: vector<std::string> Attributes;
    std:: vector<std::string> AttributesTypes;
    std:: string Primarykey;
    bool search(int);
    void insert(int,record_node *);
    void display(Node *);
    Node *getRoot();
    void ReleationDisplay(BPTree ReleationTree, Node *cursor,std::vector<std::string>Attributes);
    void ReleationDisplayHelper(BPTree ReleationTree, Node *cursor,std::vector<int>Cols);
    record_node * RecordArrayFinder(BPTree ReleationTree);
    record_node * RecordFinder(BPTree ReleationTree, Node *cursor, record_node RecordNodesTempPtr[100],int *recordArrayCounter);
};



#endif /* BPTree_hpp */
