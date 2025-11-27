/*fazer uma lista e uma sub lista para armazenar numeros impares e pares*/

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* ant;
    Node* prox;
};

class ListaDupla {
private:
    Node* inicio;

public:
    ListaDupla() {
        inicio = nullptr;
    }

    void inserir(int n) {
        Node* novo = new Node();
        novo->data = n;
        novo->ant = nullptr;
        novo->prox = nullptr;

        if (inicio == nullptr) {
            inicio = novo;
            return;
        }

        Node* atual = inicio;
        while (atual->prox != nullptr) {
            atual = atual->prox;
        }
        atual->prox = novo;
        novo->ant = atual;
    }
    void listarParesEImpares() {
        Node* atual = inicio;
        cout << "Pares: [ ";
        while (atual != nullptr) {
            if (atual->data % 2 == 0)
                cout << atual->data << " ";
            atual = atual->prox;
        }
        cout << "]" << endl;

        atual = inicio;
        cout << "Ímpares: [ ";
        while (atual != nullptr) {
            if (atual->data % 2 != 0)
                cout << atual->data << " ";
            atual = atual->prox;
        }
        cout << "]" << endl;
    }

    bool retirar(int n) {
        if (inicio == nullptr) {
            cout << "Lista vazia!" << endl;
            return false;
        }

        Node* atual = inicio;
        while (atual != nullptr && atual->data != n) {
            atual = atual->prox;
        }

        if (atual == nullptr) {
            cout << "Elemento não encontrado." << endl;
            return false;
        }

        if (atual == inicio) {
            inicio = atual->prox;
            if (inicio != nullptr)
                inicio->ant = nullptr;
        } else {
            atual->ant->prox = atual->prox;
            if (atual->prox != nullptr)
                atual->prox->ant = atual->ant;
        }

        delete atual;
        return true;
    }

    void listar() {
        Node* atual = inicio;
        cout << "[ ";
        while (atual != nullptr) {
            cout << atual->data << " ";
            atual = atual->prox;
        }
        cout << "]" << endl;
    }

};

int main() {
    ListaDupla lista;
    int option, item;

    do {
        cout << "\n--- Lista Dupla ---" << endl;
        cout << "1 - Inserir" << endl;
        cout << "2 - Remover" << endl;
        cout << "3 - Listar tudo" << endl;
        cout << "4 - Listar pares e ímpares" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> option;

        switch (option) {
        case 1:
            cout << "Digite o número: ";
            cin >> item;
            lista.inserir(item);
            break;
        case 2:
            cout << "Digite o número a remover: ";
            cin >> item;
            if (lista.retirar(item))
                cout << "Removido com sucesso!" << endl;
            break;
        case 3:
            lista.listar();
            break;
        case 4:
            lista.listarParesEImpares();
            break;
        case 0:
            cout << "Encerrando programa..." << endl;
            break;
        default:
            cout << "Opção inválida!" << endl;
        }
    } while (option != 0);

    return 0;
}

