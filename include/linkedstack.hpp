#ifndef LKDSTACK
#define LKDSTACK

#include "node.hpp"

template <typename U> class linkedstack
{   
    
    public:
        
        linkedstack();
        ~linkedstack();
        int getSize();
        U getTop();
        bool empty();

        void push(U item);
        U pop();
        void clean();
        

    private:
        int size;
        node<U>* top;
};

template <typename U> linkedstack<U>::linkedstack(){
    size = 0;
    top = nullptr;
}

template <typename U> linkedstack<U>::~linkedstack(){
    clean();
}

template <typename U> bool linkedstack<U>::empty(){
    return size == 0;
}

template <typename U> int linkedstack<U>::getSize(){
    return size;
}

template <typename U> void linkedstack<U>::push(U item){
    node<U>* insertNode;
    insertNode = new node<U>();
    insertNode->data = item;
    insertNode->next = top;
    top = insertNode;
    size ++;
}

template <typename U> U linkedstack<U>::pop(){
    U aux;
    node<U>* p;

    if(size == 0)
        throw "A pilha está vazia";

    aux = top->data;
    p = top;
    top = top->next;
    delete p;
    size --;

    return aux;
}

template <typename U> void linkedstack<U>::clean(){
    while(!empty()){
        pop();
    }
}

template <typename U> U linkedstack<U>::getTop(){
    return top->data;
}

#endif