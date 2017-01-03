//
//  List.h
//  OpenCV
//
//  Created by Daniil Vinogradov on 03.01.17.
//  Copyright © 2017 noname. All rights reserved.
//

#ifndef List_h
#define List_h

template <typename T>
class List {
    
    struct Node{
        T item;
        Node *next;
    };
    
private:
    int mLength;
    Node *head;
    
public:
    List(){
        mLength = 0;
        head = NULL;
    }
    
    void add(T item){
        Node *it = new Node;
        it->item = item;
        it->next = NULL;
        
        if (mLength == 0){
            head = it;
            mLength++;
        }
        else {
            Node *n = head;
            for (int i = 1; i < mLength; i++){
                n = n->next;
            }
            n->next = it;
            mLength++;
        }
        
    }
    
    T get(int item){
        if (item >= mLength){
            return *new T;
        }
        if (item == 0){
            return head->item;
        }
        else {
            Node *n = head;
            for (int i = 0; i < item; i++){
                n = n->next;
            }
            return n->item;
        }
    }
    
    int length(){
        return mLength;
    }
};

#endif /* List_h */
