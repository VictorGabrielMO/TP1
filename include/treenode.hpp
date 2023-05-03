#ifndef TREENODE
#define TREENODE

#include <string>

class treenode{
    public:
        treenode(){
            item = "empty node";
            esq = nullptr;
            dir = nullptr;
        }
    private:
        std::string item;
        treenode *esq;
        treenode *dir;
    friend class algebricExpressionTree;
};


#endif