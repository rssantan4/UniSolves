#include <iostream>

using namespace std;

struct node{
    int info;
    node* left;
    node* right;
};

bool isbinary(node* raiz){
    if(raiz == nullptr)
    return true;
if((raiz -> left == nullptr && raiz -> right == nullptr) || (raiz -> left != nullptr && raiz -> right != nullptr))
return (isbinary(raiz -> left)) && isbinary(raiz -> right);
}