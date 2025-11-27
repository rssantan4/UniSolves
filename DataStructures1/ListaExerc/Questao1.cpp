/*Escreva funções, em C, que recebam uma lista simplesmente encadeada 
ordenada, e realizem as seguintes operações: 
a. retirar todos os elementos ímpares que são primos, e, gerar uma 
outra lista contendo apenas os elementos retirados da lista inicial, 
em ordem decrescente;
b. retirar todos os elementos pares da lista inicial.
OBS.: utilize o tipo Nodo criado em aula.*/

#include <iostream>

using namespace std;

struct Node {
    int valor;
    Node* prox;
};

bool ehPrimo(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

class Lista {
private:
    Node* inicio;

public:
    Lista() {
        inicio = nullptr;
    }

    void inserir(int n) {
        Node* novo = new Node();
        novo->valor = n;
        novo->prox = nullptr;

        if (!inicio || n < inicio->valor) {
            novo->prox = inicio;
            inicio = novo; // CORRIGIDO: atualizar início
            return;
        }

        Node* atual = inicio;
        while (atual->prox && atual->prox->valor < n) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }

    void inserirNoInicio(int n) {
        Node* novo = new Node();
        novo->valor = n;
        novo->prox = inicio;
        inicio = novo;
    }

    void listar() {
        Node* atual = inicio;
        cout << "[ ";
        while (atual != nullptr) {
            cout << atual->valor << " ";
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
        Node* anterior = nullptr;
        while (atual != nullptr && atual->valor != n) {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual == nullptr) {
            cout << "Elemento não encontrado." << endl;
            return false;
        }

        if (atual == inicio) {
            inicio = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }

        delete atual;
        return true;
    }

    void listarParesImpares() {
        Node* atual = inicio;
        cout << "Pares: [ ";
        while (atual != nullptr) {
            if (atual->valor % 2 == 0) {
                cout << atual->valor << " ";
            }
            atual = atual->prox;
        }
        cout << "]" << endl;

        atual = inicio;
        cout << "Ímpares: [ ";
        while (atual != nullptr) {
            if (atual->valor % 2 != 0) {
                cout << atual->valor << " ";
            }
            atual = atual->prox;
        }
        cout << "]" << endl;
    }

    void removerPares() {
        Node* atual = inicio;
        Node* anterior = nullptr;

        while (atual != nullptr) {
            if (atual->valor % 2 == 0) {
                Node* temp = atual;
                if (anterior == nullptr) {
                    inicio = atual->prox;
                    atual = inicio;
                } else {
                    anterior->prox = atual->prox;
                    atual = atual->prox;
                }
                delete temp;
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }
    }

    Lista* retirarPrimosImpares() {
        Lista* novaLista = new Lista();
        Node* atual = inicio;
        Node* anterior = nullptr;

        while (atual) {
            bool isPrimoImpar = (atual->valor % 2 != 0) && ehPrimo(atual->valor);

            if (isPrimoImpar) {
                Node* paraMover = atual;
                if (!anterior) {
                    inicio = atual->prox;
                    atual = inicio;
                } else {
                    anterior->prox = atual->prox;
                    atual = atual->prox;
                }
                novaLista->inserirNoInicio(paraMover->valor); // inserir em ordem decrescente
                delete paraMover;
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }
        return novaLista;
    }
};

int main() {
    Lista lista1;
    int option, item;

    do {
        cout << "\n--- Lista Encadeada ---" << endl;
        cout << "1 - Inserir número (em ordem crescente)" << endl;
        cout << "2 - Remover número específico" << endl;
        cout << "3 - Listar tudo" << endl;
        cout << "4 - Listar pares e ímpares" << endl;
        cout << "5 - Remover números pares" << endl;
        cout << "6 - Retirar primos ímpares (para nova lista decrescente)" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> option;

        switch (option) {
        case 1:
            cout << "Digite o número: ";
            cin >> item;
            lista1.inserir(item);
            break;
        case 2:
            cout << "Digite o número a remover: ";
            cin >> item;
            if (lista1.retirar(item))
                cout << "Removido com sucesso!" << endl;
            else
                cout << "Não encontrado!" << endl;
            break;
        case 3:
            lista1.listar();
            break;
        case 4:
            lista1.listarParesImpares(); // Nome corrigido
            break;
        case 5:
            lista1.removerPares();
            cout << "Pares removidos." << endl;
            break;
        case 6: {
            Lista* nova = lista1.retirarPrimosImpares();
            cout << "Lista com primos ímpares em ordem decrescente: ";
            nova->listar();
            delete nova;
            break;
        }
        case 0:
            cout << "Encerrando programa..." << endl;
            break;
        default:
            cout << "Opção inválida!" << endl;
        }
    } while (option != 0);

    return 0;
}
