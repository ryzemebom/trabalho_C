#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DOMINIO 100
#define MAX_REGISTRO 100

// Definindo a estrutura do nó
typedef struct dominio {
    char nome[MAX_DOMINIO];   // Nome do domínio
    char registro[MAX_REGISTRO]; // Nome do registro (associado ao domínio)
    struct dominio* proximo;
} Dominio;

// Função para verificar se um caractere é válido em um domínio
int isValidCharForDomain(char c) {
    return (isalnum(c) || c == '.' || c == '-');
}

// Função para validar se o nome do domínio tem um formato correto
int validarDominio(const char* nome) {
    int len = strlen(nome);
    
    if (len < 5) // Domínios muito curtos não são válidos (ex: 'a.b' não é válido)
        return 0;

    int hasDot = 0;
    int hasAlphanumeric = 0;

    // Verifica cada caractere
    for (int i = 0; i < len; i++) {
        char c = nome[i];
        
        if (!isValidCharForDomain(c)) {
            return 0; // Caracter inválido encontrado
        }

        if (c == '.') {
            hasDot = 1; // Encontrou um ponto
        } else if (isalnum(c)) {
            hasAlphanumeric = 1; // Encontrou um caractere alfanumérico
        }
    }

    // Verifica se o domínio possui ao menos um ponto e ao menos um caractere alfanumérico
    if (!hasDot || !hasAlphanumeric) {
        return 0;
    }

    // Certifica-se de que o domínio não começa nem termina com um ponto
    if (nome[0] == '.' || nome[len - 1] == '.') {
        return 0;
    }

    return 1; // Dominio válido
}

// Função para criar um novo domínio com um nome de registro
Dominio* criarDominio(const char* nome, const char* registro) {
    Dominio* novo = (Dominio*)malloc(sizeof(Dominio));
    if (novo) {
        strncpy(novo->nome, nome, MAX_DOMINIO);
        novo->nome[MAX_DOMINIO - 1] = '\0';  // Garantir que a string seja terminada corretamente
        strncpy(novo->registro, registro, MAX_REGISTRO);
        novo->registro[MAX_REGISTRO - 1] = '\0'; // Garantir que o nome de registro seja terminado corretamente
        novo->proximo = NULL;
    }
    return novo;
}

// Função para adicionar um domínio à lista
void adicionarDominio(Dominio** lista, const char* nome, const char* registro) {
    if (!validarDominio(nome)) {
        printf("Erro: O domínio '%s' não é válido.\n", nome);
        return;
    }

    Dominio* novo = criarDominio(nome, registro);
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    if (*lista == NULL) {
        *lista = novo;
    } else {
        Dominio* temp = *lista;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }
    printf("Domínio '%s' com registro '%s' adicionado com sucesso!\n", nome, registro);
}

// Função para listar todos os domínios e seus registros
void listarDominios(Dominio* lista) {
    if (lista == NULL) {
        printf("Não há domínios registrados.\n");
        return;
    }
    
    printf("Lista de domínios registrados:\n");
    Dominio* temp = lista;
    while (temp != NULL) {
        printf("Domínio: %s | Registro: %s\n", temp->nome, temp->registro);
        temp = temp->proximo;
    }
}

// Função para buscar um domínio na lista
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

// Função para remover um domínio da lista
void removerDominio(Dominio** lista, const char* nome) {
    if (*lista == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    
    Dominio* temp = *lista;
    Dominio* anterior = NULL;

    // Caso especial: remover o primeiro domínio
    if (strcmp(temp->nome, nome) == 0) {
        *lista = temp->proximo;
        free(temp);
        printf("Domínio '%s' removido com sucesso.\n", nome);
        return;
    }
    
    // Procurar o domínio na lista
    while (temp != NULL && strcmp(temp->nome, nome) != 0) {
        anterior = temp;
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("Domínio '%s' não encontrado.\n", nome);
        return;
    }

    // Remover o domínio encontrado
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

    do {
        printf("\n1. Adicionar Domínio\n");
        printf("2. Listar Domínios\n");
        printf("3. Buscar Domínio\n");
        printf("4. Remover Domínio\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Para consumir o caractere de nova linha que fica no buffer

        switch (opcao) {
            case 1:
                printf("Digite o nome do domínio: ");
                fgets(nome, MAX_DOMINIO, stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remover a nova linha no final

                printf("Digite o nome do registro (pessoa/empresa): ");
                fgets(registro, MAX_REGISTRO, stdin);
                registro[strcspn(registro, "\n")] = '\0'; // Remover a nova linha no final

                adicionarDominio(&lista, nome, registro);
                break;
            case 2:
                listarDominios(lista);
                break;
            case 3:
                printf("Digite o nome do domínio a buscar: ");
                fgets(nome, MAX_DOMINIO, stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remover a nova linha no final
                {
                    Dominio* encontrado = buscarDominio(lista, nome);
                    if (encontrado) {
                        printf("Domínio '%s' encontrado. Registro: %s\n", encontrado->nome, encontrado->registro);
                    } else {
                        printf("Domínio '%s' não encontrado.\n", nome);
                    }
                }
                break;
            case 4:
                printf("Digite o nome do domínio a remover: ");
                fgets(nome, MAX_DOMINIO, stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remover a nova linha no final
                removerDominio(&lista, nome);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    // Liberar memória alocada
    while (lista != NULL) {
        Dominio* temp = lista;
        lista = lista->proximo;
        free(temp);
    }

    return 0;
}
