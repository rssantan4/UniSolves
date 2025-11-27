 #include <iostream>
 #include <cstddef>
 #include "arvorebinaria.h"

 using namespace std;
 
    binarySearchTree::binarySearchTree(){  //constructor function
        raiz = nullptr;
    }

    binarySearchTree::~binarySearchTree(){ //destructor function

    }

    void binarySearchTree::treeDelete(node* actualnode){
        node* aux;
        if(raiz == nullptr)
        return raiz;
        if(n > raiz -> info)
        raiz -> right = treeDelete(raiz -> right);
        else
        if(n < raiz -> info)
        raiz -> left = treeDelete(raiz -> left);
    else
    if(raiz -> left == nullptr){
        aux = raiz;
        raiz = raiz -> right;
        delete aux;
        return raiz;
    }
    else if(raiz -> right == nullptr){
        aux = raiz;
        raiz = raiz -> left;
        delete aux;
        return raiz;
    }

    node* binarySearchTree::obterRaiz(){
        return raiz;
    }

    bool binarySearchTree::isempty(){
        return (raiz == NULL);
    }

    bool binarySearchTree::isfull(){
        try{
            node* aux = new node;
            delete aux;
            return false;
        } catch(bad_alloc exception){
            return true;
        }
    }

    void binarySearchTree::insert(Aluno aluno){
        if (isfull()){
            cout << "The tree is Full!\n";
            cout << "Cannot insert\n";
        } else{
            node* newNode = new node;
            newNode -> aluno = aluno;
            newNode -> rightson = NULL;
            newNode -> leftson = NULL;
            if(isempty()){
                raiz = newNode;
            } else{
                node* aux = raiz;
                while(aux != NULL){
                    if(aluno.obterRa() < aux -> aluno.obterRa()){
                        if(aux -> leftson == NULL){
                            aux -> leftson = newNode;
                            break;
                        } else {
                            aux = aux -> leftson;
                        }
                    } else{
                        if (aux -> rightson == NULL){
                            aux -> rightson = newNode;
                            break;
                        } else{
                            aux = aux -> rightson; 
                        }
                    }
                }
            }
        }
    }

    void binarySearchTree::pop(Aluno aluno){

    }

    void binarySearchTree::search(Aluno& aluno, bool& busca){
        
    }

    void binarySearchTree::printpreordem(node* actualnode){

    }

    void binarySearchTree::printemordem(node* actualnode){

    }

    void binarySearchTree::printposordem(node* actualnode){

    }
