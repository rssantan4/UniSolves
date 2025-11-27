/*Escreva uma função, em C, que receba uma lista simplesmente encadeada, e 
retorne uma lista ordenada (crescente) sem alocar espaços para novos 
elementos da lista.*/

#include <iostream>

void ordenarLista(Node* &inicio) {
    if (!inicio || !inicio->prox) return;

    Node* i = inicio;
    while (i != nullptr) {
        Node* min = i;
        Node* j = i->prox;
        while (j != nullptr) {
            if (j->valor < min->valor) {
                min = j;
            }
            j = j->prox;
        }
        if (min != i) {
            // Troca apenas os valores, não os nós
            int temp = i->valor;
            i->valor = min->valor;
            min->valor = temp;
        }
        i = i->prox;
    }
}

