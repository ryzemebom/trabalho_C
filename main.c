#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

// Criar novo nó
No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Inserir valor na árvore
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

// Imprimir em ordem
void em_ordem(No* raiz) {
    if (raiz) {
        em_ordem(raiz->esq);
        printf("%d ", raiz->valor);
        em_ordem(raiz->dir);
    }
}

// Buscar valor na árvore
No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor)
        return raiz;
    if (valor < raiz->valor)
        return buscar(raiz->esq, valor);
    return buscar(raiz->dir, valor);
}

// Encontrar o menor valor (usado na remoção)
No* minimo(No* raiz) {
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

// Remover valor da árvore
No* remover(No* raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        // Caso 1: Nó sem filhos
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: Um filho
        else if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // Caso 3: Dois filhos
        else {
            No* temp = minimo(raiz->dir);
            raiz->valor = temp->valor;
            raiz->dir = remover(raiz->dir, temp->valor);
        }
    }
    return raiz;
}

// Liberar toda a árvore
void liberar(No* raiz) {
    if (raiz) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}

// Menu interativo
void menu() {
    printf("\n=== MENU ÁRVORE BINÁRIA ===\n");
    printf("1. Inserir número\n");
    printf("2. Listar em ordem\n");
    printf("3. Buscar número\n");
    printf("4. Remover número\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    No* raiz = NULL;
    int opcao, valor;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite um número para inserir: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                printf("Inserido com sucesso.\n");
                break;

        case 2:
    if (raiz == NULL) {
        printf("Árvore vazia. Nenhum elemento para listar.\n");
    } else {
        printf("Elementos em ordem: ");
        em_ordem(raiz);
        printf("\n");
    }
    break;


            case 3:
                printf("Digite o número para buscar: ");
                scanf("%d", &valor);
                if (buscar(raiz, valor))
                    printf("Valor %d encontrado na árvore.\n", valor);
                else
                    printf("Valor %d NÃO encontrado.\n", valor);
                break;

            case 4:
                printf("Digite o número para remover: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                printf("Remoção concluída (se valor existia).\n");
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberar(raiz);
    return 0;
}
