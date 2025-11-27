#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int count;

public:
    DoublyLinkedList() {
        head = tail = nullptr;
        count = 0;
    }

    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void inserir(int value) {
        Node* newNode = new Node{value, nullptr, nullptr};

        if (!head) {
            head = tail = newNode;
        } else if (value > head->data) {
            // Inserir no início
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else {
            // Inserir no meio ou fim
            Node* current = head;
            while (current->next && current->next->data > value) {
                current = current->next;
            }

            newNode->next = current->next;
            newNode->prev = current;

            if (current->next)
                current->next->prev = newNode;
            else
                tail = newNode;

            current->next = newNode;
        }

        count++;
        cout << "Valor inserido com sucesso.\n";
        mostrarContagem();
    }

    void remover(int value) {
        if (!head) {
            cout << "Lista vazia.\n";
            return;
        }

        Node* current = head;
        while (current && current->data != value)
            current = current->next;

        if (!current) {
            cout << "Valor não encontrado.\n";
            return;
        }

        if (current == head)
            head = current->next;
        if (current == tail)
            tail = current->prev;

        if (current->prev)
            current->prev->next = current->next;
        if (current->next)
            current->next->prev = current->prev;

        delete current;
        count--;

        cout << "Valor removido com sucesso.\n";
        mostrarContagem();
    }

    void consultar() {
        if (!head) {
            cout << "Lista vazia.\n";
            return;
        }

        cout << "Esquerda para direita: ";
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }

        cout << "\nDireita para esquerda: ";
        current = tail;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;

        mostrarContagem();
    }

    void mostrarContagem() {
        cout << "Quantidade de nós (E->D): " << count << endl;
        cout << "Quantidade de nós (D->E): " << count << endl;
    }
};

int main() {
    DoublyLinkedList lista;
    int opcao, valor;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Inserir valor\n";
        cout << "2. Remover valor\n";
        cout << "3. Consultar lista\n";
        cout << "4. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "Digite o valor a inserir: ";
            cin >> valor;
            lista.inserir(valor);
            break;
        case 2:
            cout << "Digite o valor a remover: ";
            cin >> valor;
            lista.remover(valor);
            break;
        case 3:
            lista.consultar();
            break;
        case 4:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opção inválida!\n";
        }

    } while (opcao != 4);

    return 0;
}