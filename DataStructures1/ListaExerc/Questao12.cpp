/*Considere uma lista simplesmente encadeada na qual cada nó contém as 
seguintes informações: matrícula (tipo inteiro) de um professor, ponteiro para o 
próximo nó dessa lista e um ponteiro para o primeiro nó de uma lista que 
contém os códigos (tipo inteiro) das disciplinas lecionadas por este professor. 
Implemente uma função em C para imprimir a matrícula do professor que 
leciona mais disciplinas8*/

#include <stdio.h>

void add_professor(lista professor *lista_professor, int matricula){
    if(!lista_professor){
        printf("Lista de professores vazia\n");
        exit(1);
    }

    Node_prof *newNode = malloc(sizeof(Node_prof));
    if(!newNode){
        printf("Erro ao alocar node para disciplina\n");
        exit(1);
    }

    newNode->next= NULL;
    newNode->disciplina = NULL;
    newNode->matricula = matricula;

    if(lista_prof->ini){
        lista_prof-> ini = newNode;
    }else{
        Node_prof *aux = lista_prof->ini;
        while(aux->next){
            aux = aux->next;
        }
        aux->next = newNode;
    }
}
