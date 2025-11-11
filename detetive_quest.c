/*
===========================================================
🕵️ DETECTIVE QUEST: A MANSÃO ENIGMA
===========================================================
Desenvolvido por: Enigma Studios
Implementação técnica: (Seu Nome)
Ano: 2025

Descrição:
Jogo educacional de lógica e programação em C.
O jogador explora uma mansão representada por uma Árvore Binária,
coleta pistas armazenadas em uma Árvore BST e associa-as a suspeitos
em uma Tabela Hash. Ao final, realiza uma acusação.

===========================================================
Estruturas utilizadas:
- Árvore binária → mapa da mansão
- Árvore BST → pistas coletadas
- Tabela hash → relação pista/suspeito
===========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_HASH 10

// =====================
// STRUCTS PRINCIPAIS
// =====================

// Representa um cômodo da mansão
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Nó da árvore BST de pistas coletadas
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// Par chave-valor da tabela hash
typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode *prox;
} HashNode;

// =====================
// FUNÇÕES DE SALAS
// =====================

// Cria dinamicamente uma sala com nome e pista opcional
Sala* criarSala(char *nome, char *pista) {
    Sala *nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

// =====================
// FUNÇÕES DA BST DE PISTAS
// =====================

// Cria um nó de pista
PistaNode* criarPistaNode(char *pista) {
    PistaNode *novo = (PistaNode*)malloc(sizeof(PistaNode));
    strcpy(novo->pista, pista);
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Insere pista na árvore BST
PistaNode* inserirPista(PistaNode *raiz, char *pista) {
    if (raiz == NULL) return criarPistaNode(pista);

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

// Exibe pistas em ordem alfabética
void exibirPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// =====================
// FUNÇÕES DE TABELA HASH
// =====================

int hash(char *pista) {
    int soma = 0;
    for (int i = 0; pista[i] != '\0'; i++)
        soma += pista[i];
    return soma % TAM_HASH;
}

// Inicializa a tabela hash
void inicializarHash(HashNode *tabela[]) {
    for (int i = 0; i < TAM_HASH; i++)
        tabela[i] = NULL;
}

// Insere associação pista → suspeito
void inserirNaHash(HashNode *tabela[], char *pista, char *suspeito) {
    int indice = hash(pista);
    HashNode *novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabela[indice];
    tabela[indice] = novo;
}

// Retorna suspeito correspondente à pista
char* encontrarSuspeito(HashNode *tabela[], char *pista) {
    int indice = hash(pista);
    HashNode *aux = tabela[indice];
    while (aux != NULL) {
        if (strcmp(aux->pista, pista) == 0)
            return aux->suspeito;
        aux = aux->prox;
    }
    return "Desconhecido";
}

// Conta quantas pistas associam-se a um suspeito
int contarPistasSuspeito(HashNode *tabela[], char *suspeito) {
    int cont = 0;
    for (int i = 0; i < TAM_HASH; i++) {
        HashNode *aux = tabela[i];
        while (aux != NULL) {
            if (strcmp(aux->suspeito, suspeito) == 0)
                cont++;
            aux = aux->prox;
        }
    }
    return cont;
}

// =====================
// EXPLORAÇÃO DA MANSÃO
// =====================

void explorarSalas(Sala *atual, PistaNode **arvorePistas, HashNode *tabela[]) {
    char escolha;

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);
        if (strlen(atual->pista) > 0) {
            printf("🔎 Pista encontrada: %s\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        } else {
            printf("Nenhuma pista neste cômodo.\n");
        }

        printf("\nOpções:\n");
        if (atual->esquerda) printf(" - (e) Ir para %s\n", atual->esquerda->nome);
        if (atual->direita) printf(" - (d) Ir para %s\n", atual->direita->nome);
        printf(" - (s) Sair da exploração\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);

        escolha = tolower(escolha);

        if (escolha == 'e' && atual->esquerda)
            atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita)
            atual = atual->direita;
        else if (escolha == 's')
            break;
        else
            printf("Opção inválida!\n");
    }
}

// =====================
// JULGAMENTO FINAL
// =====================

void verificarSuspeitoFinal(HashNode *tabela[]) {
    char acusado[50];
    printf("\n=== Fase de Julgamento ===\n");
    printf("Digite o nome do suspeito que deseja acusar: ");
    scanf(" %[^\n]", acusado);

    int cont = contarPistasSuspeito(tabela, acusado);

    if (cont >= 2)
        printf("\n✅ Acusação confirmada! %s foi considerado CULPADO com %d pistas!\n", acusado, cont);
    else
        printf("\n❌ Acusação insuficiente. %s é inocente (apenas %d pista associada).\n", acusado, cont);
}

// =====================
// MAIN — Montagem da Mansão
// =====================

int main() {
    // --- Criação da mansão ---
    Sala *hall = criarSala("Hall de Entrada", "Chave caída próxima à porta");
    Sala *salaEstar = criarSala("Sala de Estar", "Relógio parado às 23:00");
    Sala *biblioteca = criarSala("Biblioteca", "Livro rasgado com iniciais L.M.");
    Sala *cozinha = criarSala("Cozinha", "Faca suja de tinta vermelha");
    Sala *jardim = criarSala("Jardim", "");
    Sala *escritorio = criarSala("Escritório", "Envelope aberto com carta ameaçadora");
    Sala *adega = criarSala("Adega", "Taça quebrada e manchas no chão");

    // --- Estrutura da mansão ---
    hall->esquerda = salaEstar;
    hall->direita = biblioteca;
    salaEstar->esquerda = cozinha;
    salaEstar->direita = jardim;
    biblioteca->esquerda = escritorio;
    biblioteca->direita = adega;

    // --- Inicialização das estruturas ---
    PistaNode *arvorePistas = NULL;
    HashNode *tabela[TAM_HASH];
    inicializarHash(tabela);

    // --- Associações pista → suspeito ---
    inserirNaHash(tabela, "Chave caída próxima à porta", "Sr. Victor");
    inserirNaHash(tabela, "Relógio parado às 23:00", "Sra. Lúcia");
    inserirNaHash(tabela, "Livro rasgado com iniciais L.M.", "Sra. Lúcia");
    inserirNaHash(tabela, "Faca suja de tinta vermelha", "Jardineiro");
    inserirNaHash(tabela, "Envelope aberto com carta ameaçadora", "Sr. Victor");
    inserirNaHash(tabela, "Taça quebrada e manchas no chão", "Empregada");

    // --- Início da exploração ---
    printf("====================================\n");
    printf("🔍 DETECTIVE QUEST: A MANSÃO ENIGMA\n");
    printf("====================================\n");
    explorarSalas(hall, &arvorePistas, tabela);

    // --- Exibição das pistas ---
    printf("\n=== PISTAS COLETADAS ===\n");
    if (arvorePistas == NULL)
        printf("Nenhuma pista coletada!\n");
    else
        exibirPistas(arvorePistas);

    // --- Fase de julgamento ---
    verificarSuspeitoFinal(tabela);

    printf("\n👋 Fim da investigação!\n");
    return 0;
}