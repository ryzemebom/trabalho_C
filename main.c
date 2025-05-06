#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DOMINIO 100
#define MAX_REGISTRO 100
#define MAX_DNS 100
#define QTD_DNS 2

// Estrutura para armazenar domínio e dados associados
typedef struct dominio {
    char nome[MAX_DOMINIO];         // Nome do domínio
    char registro[MAX_REGISTRO];    // Nome do registro
    char dns[QTD_DNS][MAX_DNS];     // Lista de até 3 DNS
    struct dominio* proximo;        // Próximo domínio
} Dominio;

// Cria novo domínio
Dominio* criarDominio(const char* nome, const char* registro, char dns[][MAX_DNS]) {
    Dominio* novo = (Dominio*)malloc(sizeof(Dominio));
    if (novo != NULL) {
        strncpy(novo->nome, nome, MAX_DOMINIO);
        strncpy(novo->registro, registro, MAX_REGISTRO);

        for (int i = 0; i < QTD_DNS; i++) {
            strncpy(novo->dns[i], dns[i], MAX_DNS);
        }

        novo->proximo = NULL;
    }
    return novo;
}

// Adiciona domínio à lista
void adicionarDominio(Dominio** lista, const char* nome, const char* registro, char dns[][MAX_DNS]) {
    if (strchr(nome, '.') == NULL) {
        printf("Erro: O domínio '%s' não é válido (precisa ter um ponto).\n", nome);
        return;
    }

    Dominio* novo = criarDominio(nome, registro, dns);

    if (*lista == NULL) {
        *lista = novo;
    } else {
        Dominio* temp = *lista;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }

    printf("Domínio '%s' registrado com sucesso!\n", nome);
}

// Lista todos os domínios
void listarDominios(Dominio* lista) {
    if (lista == NULL) {
        printf("Nenhum domínio registrado.\n");
        return;
    }

    Dominio* temp = lista;
    while (temp != NULL) {
        printf("\nDomínio: %s\n", temp->nome);
        printf("Registro: %s\n", temp->registro);
        for (int i = 0; i < QTD_DNS; i++) {
            printf("DNS %d: %s\n", i + 1, temp->dns[i]);
        }
        temp = temp->proximo;
    }
}

// Busca um domínio
Dominio* buscarDominio(Dominio* lista, const char* nome) {
    Dominio* temp = lista;
    while (temp != NULL) {
        if (strcmp(temp->nome, nome) == 0) {
            return temp;
        }
        temp = temp->proximo;
    }
    return NULL;
}

// Remove domínio
void removerDominio(Dominio** lista, const char* nome) {
    if (*lista == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    Dominio* temp = *lista;
    Dominio* anterior = NULL;

    if (strcmp(temp->nome, nome) == 0) {
        *lista = temp->proximo;
        free(temp);
        printf("Domínio '%s' removido com sucesso.\n", nome);
        return;
    }

    while (temp != NULL && strcmp(temp->nome, nome) != 0) {
        anterior = temp;
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("Domínio '%s' não encontrado.\n", nome);
        return;
    }

    anterior->proximo = temp->proximo;
    free(temp);
    printf("Domínio '%s' removido com sucesso.\n", nome);
}

// Função principal
int main() {
    Dominio* lista = NULL;
    int opcao;
    char nome[MAX_DOMINIO];
    char registro[MAX_REGISTRO];
    char dns[QTD_DNS][MAX_DNS];

    do {
        printf("\n1. Adicionar Domínio\n");
        printf("2. Listar Domínios\n");
        printf("3. Buscar Domínio\n");
        printf("4. Remover Domínio\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // limpa \n

        switch (opcao) {
            case 1:
                printf("Nome do domínio: ");
                fgets(nome, MAX_DOMINIO, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Nome do registro: ");
                fgets(registro, MAX_REGISTRO, stdin);
                registro[strcspn(registro, "\n")] = '\0';

                for (int i = 0; i < QTD_DNS; i++) {
                    printf("Digite o DNS %d: ", i + 1);
                    fgets(dns[i], MAX_DNS, stdin);
                    dns[i][strcspn(dns[i], "\n")] = '\0';
                }

                adicionarDominio(&lista, nome, registro, dns);
                break;

            case 2:
                listarDominios(lista);
                break;

            case 3:
                printf("Digite o domínio a buscar: ");
                fgets(nome, MAX_DOMINIO, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                {
                    Dominio* encontrado = buscarDominio(lista, nome);
                    if (encontrado) {
                        printf("\nDomínio encontrado: %s\n", encontrado->nome);
                        printf("Registro: %s\n", encontrado->registro);
                        for (int i = 0; i < QTD_DNS; i++) {
                            printf("DNS %d: %s\n", i + 1, encontrado->dns[i]);
                        }
                    } else {
                        printf("Domínio não encontrado.\n");
                    }
                }
                break;

            case 4:
                printf("Digite o domínio a remover: ");
                fgets(nome, MAX_DOMINIO, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerDominio(&lista, nome);
                break;

            case 5:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 5);

    // Libera memória
    while (lista != NULL) {
        Dominio* temp = lista;
        lista = lista->proximo;
        free(temp);
    }

    return 0;
}
