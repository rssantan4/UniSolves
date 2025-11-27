#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prox;
    Node* ant;
};
// Função para criar um novo nó
Node* criarNo(int valor) {
    Node* novo = new Node;
    novo->data = valor;
    novo->prox = nullptr;
    novo->ant = nullptr;
    return novo;
}

// Inserir no final da lista
void inserirFinal(Node*& inicio, int valor) {
    Node* novo = criarNo(valor);

    if (inicio == nullptr) {
        inicio = novo;
        return;
    }

    Node* temp = inicio;
    while (temp->prox != nullptr) {
        temp = temp->prox;
    }

    temp->prox = novo;
    novo->ant = temp;
}

// Exibir lista do início ao fim
void exibirDireita(Node* inicio) {
    Node* temp = inicio;
    cout << "Lista (inicio -> fim): ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        if (temp->prox == nullptr) break;  // Guardar último para exibir reverso depois
        temp = temp->prox;
    }
    cout << endl;
}

// Exibir lista do fim ao início
void exibirEsquerda(Node* fim) {
    cout << "Lista (fim -> inicio): ";
    while (fim != nullptr) {
        cout << fim->data << " ";
        fim = fim->ant;
    }
    cout << endl;
}

int main() {
    Node* lista = nullptr;

    inserirFinal(lista, 10);
    inserirFinal(lista, 20);
    inserirFinal(lista, 30);

    exibirDireita(lista);

    // Encontrar o último nó para exibir reverso
    Node* temp = lista;
    while (temp->prox != nullptr) temp = temp->prox;
    exibirEsquerda(temp);

    return 0;
}

