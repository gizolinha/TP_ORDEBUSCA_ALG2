#ifndef ORDEBUSCA
#define ORDEBUSCA


// Função para gerar o vetor com valores aleatórios
void geravetor(int vetor[]); //feito

// Função que copia os elementos de 'vetor' para 'vetor_copia'
void copiaVetor(int vetor[], int vetor_copia[], int tamanho); //feito

// Função para copiar o valor da posição 0 para todo o vetor (exceto a posição 0)
void copia_sentinnela(int vetor[]); //feito

// Função para exibir o conteúdo do vetor
void exibir_vetor(int vetor[]); //feito

// Função de busca sequencial, retorna a posição do elemento ou -1 se não for encontrado
int pesquisa_sequencial(int vetor[], int chave, long *comparacoes); //feito

// Função de busca binária, retorna a posição do elemento ou -1 se não for encontrado
int pesquisa_binaria(int elemento, int vetor[], long *comparacoes); //feito

// Função de ordenação Shell Sort com espaçamento 1, 4, 13, ....
void shellsort1(int vetor[], long *comparacoes, long *trocas); //feito

// Shell Sort com espaçamento baseado em potências de 2 (1, 2, 4, 8, 16, ...)
void shellsort2(int vetor[], long *comparacoes, long *trocas); //feito

// Função de ordenação Bubble Sort
void bubble_sort(int vetor[], long *comparacoes, long *trocas); //feito

// Função de ordenação Quick Sort com pivo na primeira posição
void quick_sort1(int vetor[], int esq, int dir, long *comparacoes, long *trocas); //feito

// QuickSort recursivo com pivo aleatorio
void quick_sort2(int vetor[], int esq, int dir, long *comparacoes, long *trocas) ; //feio

//calcula a media e desvio de comparações
void mediaedesvio(long comp[], double *media, double *desvio);

//zera o vetor que conta as comparações
void zeravetor(long vetor[]);

#endif // Fim do bloco ORDEBUSCA
