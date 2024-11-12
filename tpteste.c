#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

// Função para copiar o valor da posição 0 para uma ultima posicao do vetor 
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

//função para a pesquisa binaria
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

        for (i = k + 1; i <= TAM; i++) { // começa em k+1 para considerar o sentinela
            aux = vetor[i];
            j = i;

            (*comparacoes)++; // comparacao inicial do while
            while (j > k && vetor[j - k] > aux) { 
                vetor[j] = vetor[j - k];
                j = j - k;
                (*trocas)++;
                (*comparacoes)++; // conta para cada nova iteracao
            }

            if (j != i) { 
                vetor[j] = aux;
                (*trocas)++; // Conta apenas se houve movimento
            }
        }
    } while (k != 1);
}

// Shell Sort com espaçamento  em potencias de 2 (1, 2, 4, 8, 16, ...)
void shellsort2(int vetor[], long *comparacoes, long *trocas) {
    int i, j, aux;
    int k = 1;

    //calcula espaçamentos ate passar o tamamnho do vetor
    do {
        k = k * 2;
    } while (k <= TAM);

    k = k / 2; // garante que nao use um espaçamento maior que o tamanho de vetor

    do {
        for (i = k + 1; i <= TAM; i++) { // começa em k+1 para considerar o sentinela
            aux = vetor[i];
            j = i;

            (*comparacoes)++; // comparacao inicial do while
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



//particao com o pivo como primeiro elemento para o quicksort recursivo
void particao1(int *vetor, int esq, int dir, int *pos_pivo, long *comparacoes, long *trocas) {
    int i, j, pivo, aux;

    pivo = vetor[esq];
    i = esq;
    j = dir;

    while (i < j) {
        // acha a posição onde o elemento à esquerda é maior ou igual ao pivô
        (*comparacoes)++;
        while (vetor[i] <= pivo && i < dir)
            i++;

        // acha a posição onde o elemento à direita é menor ou igual ao pivô
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

//quicksort reursico com pivo na primeira posição
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

// Função principal
int main() {

    srand(time(NULL));
    int vetor[TAM + 1], vetor_copia[TAM + 1];
    long comp[EXECUCOES];
    geravetor(vetor); 
    exibir_vetor(vetor);
    copia_sentinnela(vetor);

    int elemento;
    char escolha;

    // Pergunta ao usuário se ele quer fornecer a elemento ou gerar aleatoriamente
    printf("inserir um valor para busca (s/n)? ");
    scanf(" %c", &escolha);
    printf("\n");
    
    if (escolha == 's' || escolha == 'S') {
        printf("Digite o valor para buscar: ");
        scanf("%d", &elemento);
        
    } else {
        elemento = rand() % 2049; // Número aleatorio entre 0 e 2048
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