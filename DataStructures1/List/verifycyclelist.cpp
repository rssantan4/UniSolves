#include <iostream>

struct Node {
    int data;
    Node* next;
};
void imprimirCiclo(Node* inicio, Node* fim) {
    Node* atual = inicio;
    std::cout << "Ciclo: ";
    do {
        std::cout << atual->data << " ";
        atual = atual->next;
    } while(atual != fim);
    std::cout << std::endl;
}
void ciclo(Node* inicio) {
    Node* aux, *atual, *cicloptr;
    cicloptr = nullptr;

    atual = inicio;
    if(inicio == nullptr) {
        std::cout << "Lista vazia" << std::endl;
        return;
    }
    while(atual != nullptr) {
        aux = inicio;
        while(aux != atual) {
            if(aux == atual->next) {
                cicloptr = aux;
                std::cout << "Ciclo detectado entre os nós " << atual->data << " e " << cicloptr->data << std::endl;
                break;
            }
            aux = aux->next;
        }
        if(cicloptr != nullptr) {
            imprimirCiclo(cicloptr, atual);
            break;
        }
        atual = atual->next;
        if(atual == nullptr) {
            std::cout << "Lista não é circular" << std::endl;
            return;
        }
    }
}

void contaciclos(Node* inicio) {
    Node* atual = inicio;
    int cont = 0;

    while (atual != nullptr) {
        cont++;
        atual = atual->next;
        if (atual == inicio) {
            std::cout << "Número de ciclos: " << cont << std::endl;
            return;
        }
    }
}

int main() {
    Node* inicio = new Node{1, nullptr};
    Node* segundo = new Node{2, nullptr};
    Node* terceiro = new Node{3, nullptr};

    inicio->next = segundo;
    segundo->next = terceiro;
    terceiro->next = inicio; // Criando um ciclo

    ciclo(inicio);
    contaciclos(inicio);

    return 0;
}