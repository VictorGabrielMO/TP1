#ifndef NODE
#define NODE

//#include "nodecontent.hpp"

template <typename V> class node
{
    public:
        node(){
            //data = NULL;
            next = nullptr;
        }

    private:
        V data;
        node<V>* next;

        template <typename U> friend class linkedstack;
};

#endif