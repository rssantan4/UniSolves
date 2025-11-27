#include <iostream>
#include <string>
using namespace std;

struct Node {
    string palavra;
    Node* ant;
    Node* prox;
};

class ListaCircular {
private:
    Node* inicio; // primeiro da frase
    Node* atual;  // ponteiro para edição

public:
    ListaCircular() {
        inicio = nullptr;
        atual = nullptr;
        inicializarFrase();
    }

    void inicializarFrase() {
        inserirFinal("Estrutura");
        inserirFinal("Dados");
        inserirFinal("I");
        atual = inicio; // ponteiro atual começa em "Estrutura"
    }

    void inserirFinal(const string& palavra) {
        Node* novo = new Node{palavra, nullptr, nullptr};
        if (inicio == nullptr) {
            novo->prox = novo;
            novo->ant = novo;
            inicio = novo;
        } else {
            Node* ultimo = inicio->ant;
            novo->prox = inicio;
            novo->ant = ultimo;
            ultimo->prox = novo;
            inicio->ant = novo;
        }
    }

    void mostrarFrase() {
        if (!inicio) return;
        Node* temp = inicio;
        do {
            cout << temp->palavra << " ";
            temp = temp->prox;
        } while (temp != inicio);
        cout << endl;
    }

    void mostrarAtual() {
        if (atual)
            cout << "Palavra atual: " << atual->palavra << endl;
        else
            cout << "Nenhuma palavra selecionada." << endl;
    }

    void moverProximo() {
        if (atual) atual = atual->prox;
    }

    void moverAnterior() {
        if (atual) atual = atual->ant;
    }

    void editarPalavra(const string& nova) {
        if (atual)
            atual->palavra = nova;
    }

    void inserirDepois(const string& nova) {
        if (!atual) return;
        Node* novo = new Node{nova, atual, atual->prox};
        atual->prox->ant = novo;
        atual->prox = novo;
    }

    void removerAtual() {
        if (!atual) return;

        if (atual->prox == atual) {
            delete atual;
            atual = nullptr;
            inicio = nullptr;
            return;
        }

        if (atual == inicio)
            inicio = inicio->prox;

        Node* anterior = atual->ant;
        Node* proximo = atual->prox;
        anterior->prox = proximo;
        proximo->ant = anterior;

        Node* temp = atual;
        atual = proximo;
        delete temp;
    }
};

int main() {
    ListaCircular lista;
    char opcao;
    string palavra;

    do {
        cout << "\n--- Editor de Texto ---" << endl;
        lista.mostrarFrase();
        lista.mostrarAtual();
        cout << "E - Editar palavra atual" << endl;
        cout << "D - Inserir (depois da palavra atual)" << endl;
        cout << "S - Eliminar palavra atual" << endl;
        cout << "< - Mover para palavra anterior" << endl;
        cout << "> - Mover para palavra posterior" << endl;
        cout << "X - Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 'E':
            case 'e':
                cout << "Digite a nova palavra: ";
                cin >> palavra;
                lista.editarPalavra(palavra);
                break;
            case 'D':
            case 'd':
                cout << "Digite a palavra a inserir: ";
                cin >> palavra;
                lista.inserirDepois(palavra);
                break;
            case 'S':
            case 's':
                lista.removerAtual();
                break;
            case '<':
                lista.moverAnterior();
                break;
            case '>':
                lista.moverProximo();
                break;
            case 'X':
            case 'x':
                cout << "Encerrando o programa..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }

    } while (opcao != 'X' && opcao != 'x');

    return 0;
}
