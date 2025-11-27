#include <iostream>
#include "aluno.h"

struct node{
    Aluno aluno;
    node* leftson;
    node* rightson;
};

class binarySearchTree{ //BST
    private:
    node* raiz;
    
    public:
    binarySearchTree();
    ~binarySearchTree();
    void treeDelete(node* actualnode);
    node* obterRaiz();
    bool isempty();
    bool isfull();
    void insert(Aluno aluno);
    void pop(Aluno aluno);
    void search(Aluno& aluno, bool& busca);
    void printpreordem(node* actualnode);
    void printemordem(node* actualnode);
    void printposordem(node* actualnode);
};