#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ordebusca.h"

#define TAM 1024
#define EXECUCOES 1000

// Função para gerar números aleatórios
void geravetor(int vetor[]) {
    for (int i = 0; i < TAM; i++) {
        vetor[i] = rand() % 2049; // Números entre 0 e 2048
    }
}

// Função que copia os elementos de 'vetor' para 'vetor_copia'
void copiaVetor(int vetor[], int vetor_copia[], int tamanho) {
    for (int j = 0; j < tamanho + 1; j++) {
        vetor_copia[j] = vetor[j];  // Cópia dos elementos
    }
}

// Função para copiar o valor da posição 0 para todo o vetor (exceto a posição 0)
void copia_sentinnela(int vetor[]) {
    int sentinela = vetor[0];  // O valor da posição 0 é copiado para a variável sentinela
    vetor[TAM + 1] = sentinela;
}

//zera o vetor que conta as comparações
void zeravetor(long vetor[]) {
    for (int i = 0; i < EXECUCOES; i++) {
        vetor[i] = 0;
    }
}

// Função para exibir parte do vetor
void exibir_vetor(int vetor[]) {
    printf("Primeiros 10 elementos:\n");
    for (int i = 0; i < 10 && i < TAM; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    printf("Últimos 10 elementos:\n");
    for (int i = TAM - 10; i < TAM; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    printf("\n");
}

//função para pesquisa sequencial
int pesquisa_sequencial(int vetor[], int chave, long *comparacoes) {
    int i;

    for (i = 1; i <= TAM; i++) {
        (*comparacoes)++;
        if (vetor[i] == chave) 
            return i; // Encontrado
    }
    return -1; // Não encontrado
}

int pesquisa_binaria (int elemento,int vetor[], long *comparacoes) {
    int esq = 1;
    int dir = TAM;

    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;

        (*comparacoes)++;
        if (vetor[meio] == elemento) {
            return meio; // Encontrado
        }
        if (vetor[meio] < elemento) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return -1; // Não encontrado
}


//shell com espaçamento 1, 4, 13, 40, 121, ...
void shellsort1 (int vetor[], long *comparacoes, long *trocas) {
    int i, j, aux;
    int k = 1;
    
    do {
        k = k * 3 + 1;
    } while (k <= TAM);

    do {
        k = k / 3;

        for (i = k + 1; i <= TAM; i++) {
            aux = vetor[i];
            j = i;

            (*comparacoes)++; // Comparação inicial do while
            while (j > k && vetor[j - k] > aux) { 
                vetor[j] = vetor[j - k];
                j = j - k;
                (*trocas)++;
                (*comparacoes)++; // Contagem para cada nova iteração
            }

            if (j != i) { 
                vetor[j] = aux;
                (*trocas)++; // Conta apenas se houve movimento
            }
        }
    } while (k != 1);
}

// Shell Sort com espaçamento baseado em potências de 2 (1, 2, 4, 8, 16, ...)
void shellsort2(int vetor[], long *comparacoes, long *trocas) {
    int i, j, aux;
    int k = 1;

    do {
        k = k * 2;
    } while (k <= TAM);

    k = k / 2; // garante que nao use um espaçamento maior que o tamanho de vetor

    do {
        for (i = k + 1; i <= TAM; i++) { // começa em k+1 para considerar o sentinela
            aux = vetor[i];
            j = i;

            (*comparacoes)++; // Comparação inicial do while
            while (j > k && vetor[j - k] > aux) { 
                vetor[j] = vetor[j - k];
                j = j - k;
                (*trocas)++;
                (*comparacoes)++; 
            }

            if (j != i) { 
                vetor[j] = aux;
                (*trocas)++;
            }
        }
        k = k / 2;
    } while (k != 1);
}


void particao1(int *vetor, int esq, int dir, int *pos_pivo, long *comparacoes, long *trocas) {
    int i, j, pivo, aux;

    pivo = vetor[esq];
    i = esq;
    j = dir;

    while (i < j) {
        // Encontra a posição onde o elemento à esquerda é maior ou igual ao pivô
        (*comparacoes)++;
        while (vetor[i] <= pivo && i < dir)
            i++;

        // Encontra a posição onde o elemento à direita é menor ou igual ao pivô
        (*comparacoes)++;
        while (vetor[j] > pivo && j > esq)
            j--;

        // Realiza a troca se i e j ainda são válidos
        if (i < j) {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            (*trocas)++;
        }
    }

    // Coloca o pivô na posição correta
    vetor[esq] = vetor[j];
    vetor[j] = pivo;
    *pos_pivo = j;
}

void quick_sort1(int vetor[], int esq, int dir, long *comparacoes, long *trocas ){
    int pos_pivo;

    if (esq < dir){
        particao1(vetor, esq, dir, &pos_pivo, comparacoes, trocas);
        quick_sort1(vetor, esq, pos_pivo - 1, comparacoes, trocas);
        quick_sort1(vetor, pos_pivo + 1, dir, comparacoes, trocas);
    }
}

// Função de particao com pivo aleatorio
void particao2(int *vetor, int esq, int dir, int *pos_pivo, long *comparacoes, long *trocas) {
    int i, j, pivo, aux;
    
    // escolhe o pivo aleatoriamente entre esq e dir
    int aleat = esq + rand() % (dir - esq + 1);
    pivo = vetor[aleat];
    
    // Troca o pivo aleatorio com o primeiro elemento
    aux = vetor[esq];
    vetor[esq] = vetor[aleat];
    vetor[aleat] = aux;
    (*trocas)++;

    i = esq;
    j = dir;

    while (i < j) {
        // acha a posicao onde o elemento da esquerda é maior ou igual ao pivo
        (*comparacoes)++;
        while (vetor[i] <= pivo && i < dir)
            i++;

        // acha a posicao onde o elemento à direita é menor ou igual ao pivo
        (*comparacoes)++;
        while (vetor[j] > pivo && j > esq)
            j--;

        if (i < j) {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            (*trocas)++;
        }
    }

    // coloca o pivo na posicao correta
    vetor[esq] = vetor[j];
    vetor[j] = pivo;
    *pos_pivo = j;
}

// QuickSort recursivo com pivo aleatorio
void quick_sort2(int vetor[], int esq, int dir, long *comparacoes, long *trocas) {
    int pos_pivo;

    if (esq < dir) {
        particao2(vetor, esq, dir, &pos_pivo, comparacoes, trocas);
        quick_sort2(vetor, esq, pos_pivo - 1, comparacoes, trocas);
        quick_sort2(vetor, pos_pivo + 1, dir, comparacoes, trocas);
    }
}


// Função Bubble Sort
void bubble_sort(int vetor[], long *comparacoes, long *trocas) {
    int i, j, aux;

    for (i = 1; i < TAM; i++) {

        for (j = TAM + 1; j >= i; j--) {
            (*comparacoes)++;

            if (vetor[j] < vetor[j - 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j - 1];
                vetor[j - 1] = aux;
                (*trocas)++;
            }
        }
    }
}
//calcula a media e desvio de comparações
void mediaedesvio(long comp[], double *media, double *desvio) {
    double soma = 0.0, somaQuadrados = 0.0;
    
    for (int i = 0; i < EXECUCOES; i++) {
        soma += comp[i];
        somaQuadrados += comp[i] * comp[i];
    }

    *media = soma / EXECUCOES;
    *desvio = sqrt((somaQuadrados / EXECUCOES) - (*media * *media));
}