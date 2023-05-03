#include "../include/algebricExpressionTree.hpp"

bool algebricExpressionTree::hasOperatorProvisorio(std::string exp){
    return (exp.find('+') != std::string::npos || 
            exp.find('-') != std::string::npos ||
            exp.find('*') != std::string::npos ||
            exp.find('/') != std::string::npos);
}

bool algebricExpressionTree::isOperatorProvisorio(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}


algebricExpressionTree::algebricExpressionTree(){
    root = nullptr;
}

algebricExpressionTree::~algebricExpressionTree(){
    Clean();
}

void algebricExpressionTree::BuildTree(std::string exp){
    BuildTreeRecursive(root,root,exp);
}

void algebricExpressionTree::BuildTreeRecursive(treenode* &father,treenode* &child, std::string exp , bool left){
    int i = 0;
    if(!hasOperatorProvisorio(exp)){
        i = 1;
        if(left){
            father->esq = new treenode();
            father->esq->item = exp;
            //adiciona folha a esquerda
        }else{
            father->dir = new treenode();
            father->dir->item = exp;
             //adiciona folha a direita
        }
    }else{
        linkedstack<char> openParentesis;
        int ci = 0;
        std::string expl;
        std::string expr;
        for(char c : exp){
            if(c == '('){
                openParentesis.push('(');
            }else if(c == ')'){
                openParentesis.pop();
            }else if(isOperatorProvisorio(c) && openParentesis.getSize() == 1){
                child = new treenode();
                child->item = c;
                //criar nó do operador e adicionar a arvore
                expl = exp.substr(2,ci - 3); //retiro o único ( que não foi fechado
                BuildTreeRecursive(child,child->esq,expl, true);
                expr = exp.substr(ci+2,exp.size() - (ci + 4)); // retiro o único ) que não foi aberto
                BuildTreeRecursive(child,child->dir,expr, false );
            }
            ci++;
        }
    }
}

void algebricExpressionTree::Clean(){
    CleanRecursive(root);
    root = nullptr;
}

void algebricExpressionTree::CleanRecursive(treenode * p){
    if(p != nullptr){
        CleanRecursive(p->esq);
        CleanRecursive(p->dir);
        delete p;
    }
}