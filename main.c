
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ordebusca.h"

#define TAM 1024
#define EXECUCOES 1000

// Função principal
int main() {

    srand(0);
    int vetor[TAM + 1], vetor_copia[TAM + 1];
    long comp[EXECUCOES];
    geravetor(vetor); 
    exibir_vetor(vetor);
    copia_sentinnela(vetor);

    int elemento;
    int escolha;

    // Pergunta ao usuário se ele quer fornecer o elemento ou gerar aleatoriamente
    printf("Inserir um valor para busca (0) ou gerar aleatoriamente (1)? ");
    scanf(" %d", &escolha);
    printf("\n");

    if (escolha == 0) {
        printf("Digite o valor para buscar: ");
        scanf("%d", &elemento);
        printf("\n");
    } else if (escolha == 1) {
        elemento = rand() % 2049; // Número aleatório entre 0 e 2048
        printf("Valor gerado aleatoriamente: %d\n", elemento);
        printf("\n");
    }


    // Declaração das variáveis de comparação
    long comparacoes_sequencial = 0; 
    long comparacoes_binaria = 0;
    
    // Pesquisa Sequencial
    int resultado_sequencial = pesquisa_sequencial(vetor, elemento, &comparacoes_sequencial);
    if (resultado_sequencial != -1) {
        printf("Elemento %d encontrado na posição %d (Busca Sequencial).\n", elemento, resultado_sequencial);
    } else {
        printf("Elemento %d não encontrado na Busca Sequencial.\n", elemento);
    }
    printf("Comparações na busca sequencial: %ld\n", comparacoes_sequencial);
    printf("\n");

    // Cria uma copia vetor para usar no shell e ordenar para pesquisa binária
    copiaVetor(vetor,vetor_copia, TAM);


    // Executa o shellsort1 com espaçamento 1, 4, 13, 40, 121, ..., para pesquisa binaria
    long comparacoes_shell_1 = 0, trocas_shell_1 = 0;
    shellsort1(vetor_copia, &comparacoes_shell_1, &trocas_shell_1);
    

    // Pesquisa Binária
    int resultado_binaria = pesquisa_binaria(elemento, vetor_copia, &comparacoes_binaria);
    if (resultado_binaria != -1) {
        printf("Elemento %d encontrado na posição %d (Busca Binária).\n", elemento, resultado_binaria);
    } else {
        printf("Elemento %d não encontrado na Busca Binária.\n", elemento);
    }
    printf("Comparações na busca binária: %ld\n", comparacoes_binaria);
    printf("\n");


    // Contagens para uma única execução algoritmos de ordenação
    long comparacoes_quick1 = 0, trocas_quick1 = 0;
    long comparacoes_quick2 = 0, trocas_quick2 = 0;
    long comparacoes_bubble = 0, trocas_bubble = 0;
    long comparacoes_shell_2 = 0, trocas_shell_2 = 0;
    

    // Cria uma copia vetor para usar no quick1
    copiaVetor(vetor,vetor_copia, TAM + 1);

    // realiza uma única execução para QuickSort com pivo na primeira posicao
    quick_sort1(vetor_copia, 1, TAM - 1, &comparacoes_quick1, &trocas_quick1);
    printf("QuickSort pivo na primeira posicao - Comparações: %ld, Trocas: %ld\n", comparacoes_quick1, trocas_quick1);


     // Cria uma copia vetor para usar no quick2
    copiaVetor(vetor,vetor_copia, TAM + 1);
    
    //realiza uma unica execução para quicksort com pivo aleatorio
    quick_sort2(vetor_copia, 1, TAM - 1, &comparacoes_quick2, &trocas_quick2);
    printf("QuickSort pivo aleatorio - Comparações: %ld, Trocas: %ld\n", comparacoes_quick2, trocas_quick2);
    printf("\n");


    // realiza uma execução do shellsort com espaçamento 1, 4, 13
    //so imprime, calculado na ln 79 para busca binaria
    printf("ShellSort com espaçamento 1, 4, 13, 40, 121, ... - Comparações: %ld, Trocas: %ld", comparacoes_shell_1, trocas_shell_1);
    printf("\n");

    // Cria uma copia vetor para usar no shellsort2
    copiaVetor(vetor,vetor_copia, TAM + 1);
    
    // realiza uma execução do shellsort com espaçamento em potencia de 2
    shellsort2(vetor_copia, &comparacoes_shell_2, &trocas_shell_2);
    printf("ShellSort com espaçamento em potencia de 2 - Comparações: %ld, Trocas: %ld", comparacoes_shell_2, trocas_shell_2);
    printf("\n");
    printf("\n");


    // Cria uma copia vetor para usar no bubble
    copiaVetor(vetor,vetor_copia, TAM + 1);

    //realiza uma única execução para bubblesort
    bubble_sort(vetor_copia, &comparacoes_bubble, &trocas_bubble);
    printf("Bubble Sort - Comparações: %ld, Trocas: %ld\n", comparacoes_bubble, trocas_bubble);
    printf("\n");


    printf("Para as 1000 execucoes");
    printf("\n");

    //calculo das mil execuções da busca sequencial
    double mediabuscseq, desviobuscseq;
    for (int i = 0; i < EXECUCOES; i++) {
        comparacoes_sequencial = 0;
        geravetor(vetor);

        pesquisa_sequencial(vetor, elemento, &comparacoes_sequencial);
        comp[i] = comparacoes_sequencial;

    }

    //calcula a media e o desvio
    mediaedesvio(comp, &mediabuscseq, &desviobuscseq);
    printf("Busca sequencial:");
    printf("\n");
    printf("Média de comparações: %.2f\n", mediabuscseq);
    printf("Desvio padrão das comparações: %.2f\n", desviobuscseq);
    printf("\n");

    //zera o vetor para o proximo calculo
    zeravetor(comp);

    //calculo das mil execuções da busca binaria
    double mediabuscbin, desviobuscbin;
    for (int i = 0; i < EXECUCOES; i++) {
        comparacoes_binaria = 0;
        geravetor(vetor);

        //ordena o vetor
        long comparacoes_shell_1 = 0, trocas_shell_1 = 0;
        shellsort1(vetor, &comparacoes_shell_1, &trocas_shell_1);

        pesquisa_binaria(elemento, vetor, &comparacoes_binaria);
        comp[i] = comparacoes_binaria;

    }

    
    mediaedesvio(comp, &mediabuscbin, &desviobuscbin);
    printf("Busca Binária:");
    printf("\n");
    printf("Média de comparações: %.2f\n", mediabuscbin);
    printf("Desvio padrão das comparações: %.2f\n", desviobuscbin);
    printf("\n");

  
    zeravetor(comp);

    //calculo das mil execuções do quicksort1
    double mediaquick1, desvioquick1;
    for (int i = 0; i < EXECUCOES; i++) {
        comparacoes_quick1 = 0;
        geravetor(vetor);

        quick_sort1(vetor, 1, TAM - 1, &comparacoes_quick1, &trocas_quick1);
        comp[i] = comparacoes_quick1;

    }

    
    mediaedesvio(comp, &mediaquick1, &desvioquick1);
    printf("QuickSort pivo na primeira posicao:");
    printf("\n");
    printf("Média de comparações: %.2f\n", mediaquick1);
    printf("Desvio padrão das comparações: %.2f\n", desvioquick1);
    printf("\n");

 
    zeravetor(comp);

    //calculo das mil execuções do quicksort2
    double mediaquick2, desvioquick2;
    for (int i = 0; i < EXECUCOES; i++) {
        comparacoes_quick2 = 0;
        geravetor(vetor);

        quick_sort2(vetor, 1, TAM - 1, &comparacoes_quick2, &trocas_quick2);
        comp[i] = comparacoes_quick2;

    }
 
    mediaedesvio(comp, &mediaquick2, &desvioquick2);
    printf("QuickSort pivo aleatorio:");
    printf("\n");
    printf("Média de comparações: %.2f\n", mediaquick2);
    printf("Desvio padrão das comparações: %.2f\n", desvioquick2);
    printf("\n");

    //zera o vetor para o proximo calculo
    zeravetor(comp);

    //calculo das mil execuções do shellsort1
    double mediashell1, desvioshell1;
    for (int i = 0; i < EXECUCOES; i++) {
        comparacoes_shell_1 = 0;
        geravetor(vetor);

        shellsort1(vetor, &comparacoes_shell_1, &trocas_shell_1);
        comp[i] = comparacoes_shell_1;

    }
 
    mediaedesvio(comp, &mediashell1, &desvioshell1);
    printf("ShellSort com espaçamento 1, 4, 13, 40, 121, ...:");
    printf("\n");
    printf("Média de comparações: %.2f\n", mediashell1);
    printf("Desvio padrão das comparações: %.2f\n", desvioshell1);
    printf("\n");


    
    zeravetor(comp);

    //calculo das mil execuções do shellsort2
    double mediashell2, desvioshell2;
    for (int i = 0; i < EXECUCOES; i++) {
        comparacoes_shell_2 = 0;
        geravetor(vetor);

        shellsort1(vetor, &comparacoes_shell_2, &trocas_shell_2);
        comp[i] = comparacoes_shell_2;

    }
 
    mediaedesvio(comp, &mediashell2, &desvioshell2);
    printf("ShellSort com espaçamento em potencia de 2 :");
    printf("\n");
    printf("Média de comparações: %.2f\n", mediashell2);
    printf("Desvio padrão das comparações: %.2f\n", desvioshell2);
    printf("\n");

    zeravetor(comp);

    //calculo das mil execuções do bubblesort
    double mediabubble, desviobubble;
    for (int i = 0; i < EXECUCOES; i++) {
        comparacoes_bubble = 0;
        geravetor(vetor);

        bubble_sort(vetor_copia, &comparacoes_bubble, &trocas_bubble);
        comp[i] = comparacoes_bubble;

    }
 
    mediaedesvio(comp, &mediabubble, &desviobubble);
    printf("BubbleSort:");
    printf("\n");
    printf("Média de comparações: %.2f\n", mediabubble);
    printf("Desvio padrão das comparações: %.2f\n", desviobubble);
    printf("\n");

    return 0;
}






























