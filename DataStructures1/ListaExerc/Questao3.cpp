/*Escreva uma função, em C, que receba duas listas simplesmente encadeadas 
A e B, contendo informações (Código e Nome) dos pacientes do médico X e do 
médico Y (respectivamente), de uma determinada clínica. A clínica deseja 
possuir uma lista única com as informações dos pacientes desses dois médicos 
a partir da junção dessas duas listas. Considere que as listas A e B estão 
ordenadas por código de pacientes e que não existem dois (ou mais) pacientes 
com o mesmo código. A lista resultante deve conter todos os pacientes dos 
médicos X e Y ordenados por código e sem elementos repetidos.*/

#include <stdio.h>
#include <string>

struct Paciente {
    int codigo;
    string nome ;
};

struct node {
    Paciente info;
    node* prox;
};

node* unirListas(node* A, node* B){
    node* novaLista = nullptr;
    node* fim = nullptr;

        while (A && B) {
            node* menor = nullptr;
    
            if (A->info.codigo < B->info.codigo) {
                menor = A;
                A = A->prox;
            } else {
                menor = B;
                B = B->prox;
            }
    
            menor->prox = nullptr; // Desvincula o nó original
    
            if (!novaLista) {
                novaLista = menor;
                fim = menor;
            } else {
                fim->prox = menor;
                fim = menor;
            }
        }
    
        // Anexa o restante da lista A (se houver)
        while (A) {
            node* temp = A;
            A = A->prox;
            temp->prox = nullptr;
    
            if (!novaLista) {
                novaLista = temp;
                fim = temp;
            } else {
                fim->prox = temp;
                fim = temp;
            }
        }
    
        // Anexa o restante da lista B (se houver)
        while (B) {
            node* temp = B;
            B = B->prox;
            temp->prox = nullptr;
    
            if (!novaLista) {
                novaLista = temp;
                fim = temp;
            } else {
                fim->prox = temp;
                fim = temp;
            }
        }
    
        return novaLista;
    }    
}

void imprimirLista(Node* inicio) {
    Node* atual = inicio;
    while (atual) {
        cout << "Código: " << atual->info.codigo << ", Nome: " << atual->info.nome << endl;
        atual = atual->prox;
    }
}

void inserirOrdenado(Node*& inicio, int codigo, string nome) {
    Node* novo = new Node{{codigo, nome}, nullptr};

    if (!inicio || codigo < inicio->info.codigo) {
        novo->prox = inicio;
        inicio = novo;
        return;
    }

    Node* atual = inicio;
    while (atual->prox && atual->prox->info.codigo < codigo) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

int main() {
    Node* listaA = nullptr;
    Node* listaB = nullptr;

    // Médico X
    inserirOrdenado(listaA, 1, "Alice");
    inserirOrdenado(listaA, 3, "Carlos");
    inserirOrdenado(listaA, 5, "Eduardo");

    // Médico Y
    inserirOrdenado(listaB, 2, "Bruna");
    inserirOrdenado(listaB, 4, "Daniela");
    inserirOrdenado(listaB, 6, "Fernanda");

    Node* listaUnica = unirListas(listaA, listaB);

    cout << "Lista unificada de pacientes:\n";
    imprimirLista(listaUnica);

    return 0;
}
