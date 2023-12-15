#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define MAX 100
#define TAMANHO 100000000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    /*
    INICIO
    */

    setlocale(LC_ALL, "Portuguese");
    time_t t;
    srand(time(NULL));

    int *vetor = NULL;
    int i, busca, num_threads, quantidade = 0;
    double inicioSequencial, fimSequencial, inicioParalelo, fimParalelo, tempoSequencial, tempoParalelo;

    vetor = gerar_vetor_inteiro(TAMANHO);

    printf("Digite o número para buscar: ");
    scanf("%d", &busca);


    //Execução sequencial

    inicioSequencial = omp_get_wtime();

    for(i = 0; i < TAMANHO; i++){

        if(vetor[i] == busca)
            quantidade++;

    }

    fimSequencial = omp_get_wtime();

    tempoSequencial = fimSequencial - inicioSequencial;


    //Execução paralela

    quantidade = 0;

    inicioParalelo = omp_get_wtime();

    #pragma omp parallel num_threads(4)
    {

        num_threads = omp_get_num_threads();

        #pragma omp for reduction(+: quantidade)

            for(i = 0; i < TAMANHO; i++){

                if(vetor[i] == busca)
                    quantidade++;

            }

    }

    fimParalelo = omp_get_wtime();

    tempoParalelo = fimParalelo - inicioParalelo;

    //Saída

    printf("O número %d foi encontrado %d vezes no vetor.\n", busca, quantidade);
    printf("Tempo de execução sequencial: %.2f segundos.\n", tempoSequencial);
    printf("Tempo de execução paralelo com %d threads: %.2f segundos.\n", num_threads, tempoParalelo);
    printf("Speed Up: %.2f.\n", tempoSequencial / tempoParalelo);
    printf("Eficiência: %.2f.\n\n", (tempoSequencial / tempoParalelo) / num_threads);
    
    /*
    FIM
    */
    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
}