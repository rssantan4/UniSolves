/*Intercalar listas encadeadas x e y em z*/
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prox;
    Node* ant;
};

// Criar novo nó
Node* criarNo(int valor) {
    Node* novo = new Node;
    novo->data = valor;
    novo->prox = nullptr;
    novo->ant = nullptr;
    return novo;
}

// Inserir no final
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

// Exibir do início ao fim
void exibirDireita(Node* inicio) {
    Node* temp = inicio;
    cout << "Lista (inicio -> fim): ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->prox;
    }
    cout << endl;
}

// Intercalar duas listas e retornar nova lista
Node* intercalarListas(Node* lista1, Node* lista2) {
    Node* temp1 = lista1;
    Node* temp2 = lista2;
    Node* listaZ = nullptr;

    while (temp1 != nullptr || temp2 != nullptr) {
        if (temp1 != nullptr) {
            inserirFinal(listaZ, temp1->data);
            temp1 = temp1->prox;
        }
        if (temp2 != nullptr) {
            inserirFinal(listaZ, temp2->data);
            temp2 = temp2->prox;
        }
    }

    return listaZ;
}

int main() {
    Node* lista1 = nullptr;
    Node* lista2 = nullptr;

    // Inserindo elementos
    inserirFinal(lista1, 3);
    inserirFinal(lista1, 5);
    inserirFinal(lista1, 6);

    inserirFinal(lista2, 4);
    inserirFinal(lista2, 5);

    cout << "Lista X: ";
    exibirDireita(lista1);
    cout << "Lista Y: ";
    exibirDireita(lista2);

    // Intercalar
    Node* listaZ = intercalarListas(lista1, lista2);

    cout << "Lista Z (intercalada): ";
    exibirDireita(listaZ);

    return 0;
}