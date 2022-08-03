//
//  BPTree.cpp
//  Database 1.0
//
//  Created by Saman Givian on 7/7/22.
//

int MAX = 3;
#include "BPTree.hpp"


Node::Node() {
    key = new int[MAX];
    ptr = new Node *[MAX + 1];
    recordptr = new record_node *[MAX];
}

BPTree::BPTree() {
    root = NULL;
}


// Search operation
bool BPTree::search(int x) {
    if (root == NULL) {
        //cout << "Tree is empty\n";
        return false;
    } else {
        Node *cursor = root;
        while (cursor->IS_LEAF == false) {
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        for (int i = 0; i < cursor->size; i++) {
            if (cursor->key[i] == x) {
                //cout << "Found\n";
                
                return true;
            }
        }
        // cout << "Not found\n";
        return false;
    }
}

// Insert Operation
void BPTree::insert(int x,record_node *recordptr) {
    
    if (root == NULL) {
        root = new Node;
        root->recordptr[0] = recordptr;
        root->key[0] = x;
        //std::cout<<recordptr<<"    "<<root->recordptr[0]<<"    "<<recordptr->record[0]<<std::endl;
        root->IS_LEAF = true;
        root->size = 1;
    } else {
        Node *cursor = root;
        Node *parent = NULL;
        while (cursor->IS_LEAF == false) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        if (cursor->size < MAX) {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->recordptr[j] = cursor->recordptr[j - 1];
                cursor->key[j] = cursor->key[j - 1];
            }
            
            cursor->recordptr[i] = recordptr;
            cursor->key[i] = x;
            cursor->size++;
            //std::cout<<"Address -if- : "<<cursor->recordptr<<std::endl;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        } else {
            
            Node *newLeaf = new Node;
            record_node *virtualRecord[MAX + 1];
            int virtualNode[MAX + 1];
            for (int i = 0; i < MAX; i++) {
                virtualRecord[i] = cursor->recordptr[i];
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;
            while (x > virtualNode[i] && i < MAX)
                i++;
            for (int j = MAX ; j > i; j--) {
                virtualRecord[j] = virtualRecord[j - 1];
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualRecord[i] = recordptr;
            virtualNode[i] = x;
            
            newLeaf->IS_LEAF = true;
            cursor->size = (MAX + 1) / 2;
            newLeaf->size = MAX + 1 - (MAX + 1) / 2;
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
            cursor->ptr[MAX] = NULL;
            
            //std::cout<<"Address-else- : "<<newLeaf->recordptr<<std::endl;
            for (i = 0; i < cursor->size; i++) {
                cursor->recordptr[i] = virtualRecord[i];
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->recordptr[i] = virtualRecord[j];
                newLeaf->key[i] = virtualNode[j];
            }
            if (cursor == root) {
                Node *newRoot = new Node;
                newRoot->recordptr[0] = newLeaf->recordptr[0];
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            } else {
                insertInternal(newLeaf->key[0],newLeaf->recordptr[0], parent, newLeaf);
            }
        }
    }
}

// Insert Operation
void BPTree::insertInternal(int x,record_node * recordPtr, Node *cursor, Node *child) {
    //std::cout<<"Addr: "<<recordPtr<<std::endl;
    if (cursor->size < MAX) {
        int i = 0;
        while (x > cursor->key[i] && i < cursor->size)
            i++;
        for (int j = cursor->size; j > i; j--) {
            cursor->recordptr[j] = cursor->recordptr[j - 1];
            cursor->key[j] = cursor->key[j - 1];
        }
        
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->recordptr[i] = recordPtr;
        cursor->key[i] = x;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    } else {
        Node *newInternal = new Node;
        int virtualKey[MAX + 1];
        record_node * virtualRecord[MAX + 1];
        Node *virtualPtr[MAX + 2];
        for (int i = 0; i < MAX; i++) {
            virtualRecord[i] = cursor->recordptr[i];
            virtualKey[i] = cursor->key[i];
        }
        
        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i = 0, j;
        while (x > virtualKey[i] && i < MAX)
            i++;
        for (int j = MAX ; j > i; j--) {
            virtualRecord[j] = virtualRecord[j - 1];
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualRecord[i] = recordPtr;
        virtualKey[i] = x;
        
        for (int j = MAX + 1; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (MAX + 1) / 2;
        newInternal->size = MAX - (MAX + 1) / 2;
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
            newInternal->recordptr[i] = virtualRecord[j];
            newInternal->key[i] = virtualKey[j];
        }
        
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        if (cursor == root) {
            Node *newRoot = new Node;
            newRoot->recordptr[0] = cursor->recordptr[cursor->size];
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        } else {
            insertInternal(cursor->key[cursor->size],cursor->recordptr[cursor->size], findParent(root, cursor), newInternal);
        }
    }
}

// Find the parent
Node *BPTree::findParent(Node *cursor, Node *child) {
    Node *parent = NULL;
    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
        return NULL;
    }
    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        } else {
            parent = findParent(cursor->ptr[i], child);
            if (parent != NULL)
                return parent;
        }
    }
    return parent;
}

// Print the tree
void BPTree::display(Node *cursor) {
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; i++) {
            std::cout <<"Expected Key: "<<cursor->key[i]<<" "<< cursor->recordptr[i]->record[0] << ": "<<cursor->recordptr[i]<<" ";
            //std::cout <<"Expected Key: "<<cursor->key[i]<<std::endl;
        }
        std::cout << "\n";
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                display(cursor->ptr[i]);
            }
        }
    }
}
record_node * BPTree::RecordArrayFinder(BPTree ReleationTree){
    record_node * recordNodeTemp = new record_node[100];
    int recordArrayCounter = 0;
    RecordFinder(ReleationTree,ReleationTree.getRoot(),recordNodeTemp,&recordArrayCounter);
    return recordNodeTemp;
}
record_node * BPTree::RecordFinder(BPTree ReleationTree, Node *cursor, record_node RecordNodesTempPtr[100],int *recordArrayCounterPtr) {
    //std::cout<<recordNodeTemp<<std::endl;
    //std::cout<<&recordNodeTemp[0]<<std::endl;
    //std::cout<<&recordNodeTemp[1]<<std::endl;
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; i++) {
           // std::cout<< cursor->recordptr[i]->record[0]<<std::endl;
           // std::cout<<cursor->recordptr[i]->record[1]<<std::endl;
           // std::cout<<cursor->recordptr[i]->record[2]<<std::endl;
            for(int Col = 0;Col < ReleationTree.Attributes.size();Col++){
            std::strcpy(RecordNodesTempPtr[*recordArrayCounterPtr ].record[Col]  , cursor->recordptr[i]->record[Col]);
            }
            *recordArrayCounterPtr += 1;
            //std::cout <<"Expected Key: "<<cursor->key[i]<<" "<< cursor->recordptr[i]->record[0] << ": "<<cursor->recordptr[i]<<" ";
            //std::cout <<"Expected Key: "<<cursor->key[i]<<std::endl;
        }
    
        std::cout << "\n";
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                RecordFinder(ReleationTree, cursor->ptr[i],RecordNodesTempPtr,recordArrayCounterPtr);
            }
        }
    }
    return RecordNodesTempPtr;
}

void BPTree::ReleationDisplay(BPTree ReleationTree, Node *cursor,std::vector<std::string>Attributes) {
    for (int Attr = 0; Attr<Attributes.size(); Attr++){
        std::cout<<"+--------------------";
    }
    std::cout<<"+"<<std::endl;
    std::vector<int>Cols;
    for(int SelectedAttr = 0;SelectedAttr< Attributes.size();SelectedAttr++ ){
        for (int Attr = 0;Attr <  ReleationTree.Attributes.size(); Attr++){
            if(Attributes[SelectedAttr] ==  ReleationTree.Attributes[Attr]){
                Cols.push_back(Attr);
                std::cout<<"|"<< ReleationTree.Attributes[Attr]<<std::string(20 - ReleationTree.Attributes[Attr].length(),' ');
                break;
            }
        }
    }
    std::cout<<"|"<<std::endl;
    for(int i = 0;i<Attributes.size();i++){
        std::cout<<"+--------------------";
    }
    std::cout<<"+"<<std::endl;
    
    ReleationTree.ReleationDisplayHelper(ReleationTree,cursor,Cols);
    std::cout<<std::endl;
}
void BPTree::ReleationDisplayHelper(BPTree ReleationTree, Node *cursor,std::vector<int>Cols){
    if (cursor != NULL) {
        if (cursor->IS_LEAF == true) {
            for (int i = 0; i < cursor->size; i++ ) {
                std::cout<<"|";
                for (int Col = 0; Col< ReleationTree.Attributes.size(); Col++){
                    // std::cout <<"|"<< cursor->recordptr[i]->record[Col];
                    if (std::find(Cols.begin(),Cols.end(),Col) != Cols.end()){
                        //std::cout<<"FOUND"<<Col<<std::endl;
                        std::cout<<cursor->recordptr[i]->record[Col]<<std::string(20 - strlen(cursor->recordptr[i]->record[Col]),' ') ;
                        std::cout<<"|";
                  
                    }
                }
            std::cout<<std::endl;
                for (int Attr = 0; Attr< Cols.size(); Attr++){
                    std::cout<<"+--------------------";
                }
                std::cout<<"+"<<std::endl;
                
                
                //std::cout <<"Expected Key: "<<cursor->key[i]<<std::endl;
            }
        }
        
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                ReleationDisplayHelper(ReleationTree,cursor->ptr[i],Cols);
            }
        }
    }
}


// Get the root
Node *BPTree::getRoot() {
    return root;
}

