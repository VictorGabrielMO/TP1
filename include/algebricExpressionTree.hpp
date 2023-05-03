#ifndef BINTREE
#define BINTREE

#include <string>
#include "linkedStack.hpp" 
#include "treenode.hpp"

class algebricExpressionTree
{
    public:
        algebricExpressionTree();
        ~algebricExpressionTree();

        void BuildTree(std::string exp);
        //void Caminha(int tipo);
        void Clean();
    private:
        void BuildTreeRecursive(treenode* &father, treenode* &child, std::string item, bool left = true);
        void CleanRecursive(treenode* p);
        bool hasOperatorProvisorio(std::string exp);
        bool isOperatorProvisorio(char c);
        //void PorNivel();
        //void PreOrdem(treenode* p);
        //void InOrdem(treenode* p);
        //void PosOrdem(treenode* p);
        treenode *root;
};

#endif