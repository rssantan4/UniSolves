/*Escreva uma função, em C, para eliminar todos os elementos inteiros 
repetidos em uma lista simplesmente encadeada. Considere que os elementos 
nesta estrutura não estão ordenados.*/

#include <iostream>
using namespace std;

struct Node {
    int valor;
    Node* prox;
};

void removerDuplicatas(Node* inicio) {
    Node* atual = inicio;

    while (atual != nullptr) {
        Node* anterior = atual;
        Node* comparador = atual->prox;

        while (comparador != nullptr) {
            if (comparador->valor == atual->valor) {
                // Remove o nó duplicado
                anterior->prox = comparador->prox;
                delete comparador;
                comparador = anterior->prox;
            } else {
                anterior = comparador;
                comparador = comparador->prox;
            }
        }

        atual = atual->prox;
    }
}

int main() {
    Node* lista = nullptr; 

    inserirInicio(lista, 5);
    inserirInicio(lista, 1);
    inserirInicio(lista, 3);
    inserirInicio(lista, 2);
    inserirInicio(lista, 3);
    inserirInicio(lista, 5);

    cout << "Lista original: ";
    imprimirLista(lista);

    removerDuplicatas(lista);

    cout << "Lista sem duplicatas: ";
    imprimirLista(lista);

    return 0;
}
