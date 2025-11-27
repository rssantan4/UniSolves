/*implementar árvore binária*/
#include <iostream>
#include <algorithm> // para std::max
#include <queue> // necessário para std::queue
using namespace std;

struct node {
    int info;
    node* esq;
    node* dir;
};

// Função para criar um novo nó
node* criar_no(int valor) {
    node* novo = new node;
    novo->info = valor;
    novo->esq = nullptr;
    novo->dir = nullptr;
    return novo;
}

// Inserção
node* inserir(node* raiz, int x) {
    if (raiz == nullptr) {
        return criar_no(x);
    }
    if (x < raiz->info) {
        raiz->esq = inserir(raiz->esq, x);
    } else if (x > raiz->info) {
        raiz->dir = inserir(raiz->dir, x);
    }
    return raiz; // mantém a raiz atual
}

// Impressão em ordem
void em_ordem(node* raiz) {
    if (raiz != nullptr) {
        em_ordem(raiz->esq);
        cout << raiz->info << " ";
        em_ordem(raiz->dir);
    }
}

// Busca
bool buscar(node* raiz, int x) {
    if (raiz == nullptr) return false;
    if (raiz->info == x) return true;
    if (x < raiz->info) return buscar(raiz->esq, x);
    return buscar(raiz->dir, x);
}

// Contar nós
int contar(node* raiz) {
    if (raiz == nullptr) 
    return 0;
    return 1 + contar(raiz->esq) + contar(raiz->dir);
}
            
// Altura da árvore
int altura(node* raiz) {
    if (raiz == nullptr)
    return -1;
int e = altura(raiz -> esq);
int d = altura(raiz -> dir);
if(e > d)
return e + 1;
else
return d+1;
}

// Encontrar o menor valor da subárvore
node* encontrar_minimo(node* raiz) {
    while (raiz->esq != nullptr) {
        raiz = raiz->esq;
    }
    return raiz;
}

// Remover nó
node* retirar(node* raiz, int x) {
    if (raiz == nullptr) return nullptr;
    if (x < raiz->info) {
        raiz->esq = retirar(raiz->esq, x);
    } else if (x > raiz->info) {
        raiz->dir = retirar(raiz->dir, x);
    } else {
        // Encontrou o nó
        if (raiz->esq == nullptr && raiz->dir == nullptr) {
            delete raiz;
            return nullptr;
        } else if (raiz->esq == nullptr) {
            node* temp = raiz->dir;
            delete raiz;
            return temp;
        } else if (raiz->dir == nullptr) {
            node* temp = raiz->esq;
            delete raiz;
            return temp;
        } else {
            node* temp = encontrar_minimo(raiz->dir);
            raiz->info = temp->info;
            raiz->dir = retirar(raiz->dir, temp->info);
        }
    }
    return raiz;
}
void imprimir_por_niveis(node* raiz) {
    if (raiz == nullptr) 
    return;

    queue<node*> fila;
    fila.push(raiz);

    while (!fila.empty()) {
        int tamanhoNivel = fila.size(); // número de nós neste nível

        // Imprime todos os nós do nível atual
        for (int i = 0; i < tamanhoNivel; ++i) {
            node* atual = fila.front();
            fila.pop();

            cout << atual->info << " ";

            if (atual->esq != nullptr) fila.push(atual->esq);
            if (atual->dir != nullptr) fila.push(atual->dir);
        }

        cout << endl; // nova linha entre os níveis
    }
}

int main() {
    node* raiz = nullptr;
    int x;
    
    cout << "Digite valores (0 para parar):\n";
    while (cin >> x && x != 0) {
        raiz = inserir(raiz, x);
    }

    cout << "Em ordem: ";
    em_ordem(raiz);
    cout << endl;

    cout << "Total de nós: " << contar(raiz) << endl;
    cout << "Altura da árvore: " << altura(raiz) << endl;

    cout << "Digite um valor para remover: ";
    cin >> x;
    raiz = retirar(raiz, x);

    cout << "Em ordem após remoção: ";
    em_ordem(raiz);
    cout << endl;

    return 0;
}
