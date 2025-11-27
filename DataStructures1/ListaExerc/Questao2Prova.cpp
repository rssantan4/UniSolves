/* Escreva uma função, em C++ receba um ponteiro como parâmetro chamado Início, para uma 
lista duplamente encadeada e um valor inteiro N, a função devera eliminar da lista o nodo 
antecessor e nodo sucessor, de cada ocorrência de N na lista. */

#include <iostream>
using namespace std;

struct Node {
    int valor;
    Node* ant;
    Node* prox;
};

void removerNo(Node*& inicio, Node* aux) {
    if (aux == nullptr) 
    return;

    if (aux->ant != nullptr)
        aux->ant->prox = aux->prox;
    else
        inicio = aux->prox; 

    if (aux->prox != nullptr)
        aux->prox->ant= aux->ant;

    delete aux;
}

void removerVizinhos(Node*& inicio, int n) {
    Node* atual = inicio;

    while (atual != nullptr) {
        if (atual->valor == n) {
            Node* ant = atual->ant;
            Node* prox = atual->prox;

            Node* depoisdoProximo = nullptr; //n verifiquei na prova
            if (prox != nullptr) 
            depoisdoProximo = prox->prox;

            if (ant != nullptr) removerNo(inicio, ant);
            if (prox != nullptr) removerNo(inicio, prox);

            atual = depoisdoProximo;
        } else {
            atual = atual->prox;
        }
    }
}

void inserirFim(Node*& inicio, int valor) {
    Node* novo = new Node{valor, nullptr, nullptr};
    if (inicio == nullptr) {
        inicio = novo;
        return;
    }

    Node* temp = inicio;
    while (temp->prox != nullptr)
        temp = temp->prox;

    temp->prox = novo;
    novo->ant = temp;
}

void exibirLista(Node* inicio) {
    if (inicio == nullptr) {
        cout << "Lista vazia" << endl;
        return;
    }
    while (inicio != nullptr) {
        cout << inicio->valor << " - ";
        inicio = inicio->prox;
    }
    cout << endl;
}
 
void menu() {
    Node* lista = nullptr;
    int opcao = 0;
    int valor, n;

    while (true) {
        cout << "\n|* Menu de Opções *| \n";
        cout << "1. Inserir um número na lista\n";
        cout << "2. Exibir lista\n";
        cout << "3. Remover vizinhos de um número\n";
        cout << "4. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        if (opcao == 1) {
            cout << "Digite um número para inserir na lista: ";
            cin >> valor;
            inserirFim(lista, valor);
        } 
        else if (opcao == 2) {
            cout << "Lista atual: ";
            exibirLista(lista);
        } 
        else if (opcao == 3) {
            cout << "Digite o número cujo vizinhos deseja remover: ";
            cin >> n;
            removerVizinhos(lista, n);
            cout << "Após remoção dos vizinhos de " << n << ": ";
            exibirLista(lista);
        } 
        else if (opcao == 4) {
            cout << "Saindo . . .\n";
            break;
        } 
        else {
            cout << "Opção inválida! Tente novamente.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}