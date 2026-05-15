#include <stdio.h>

#define m 4919

long long tabela[m];

void gerar_grafico(int inseridos, int colisoes){

    FILE *grafico = fopen("grafico.txt", "a");

    if(grafico == NULL){
        printf("Erro ao criar grafico.\n");
        return;
    }

    fprintf(grafico, "%d %d\n", inseridos, colisoes);

    fclose(grafico);
}

int func_hash(long long chave){

    int verificadores = chave % 100;
    chave /= 100;
    int tres_finais = chave % 1000;
    chave /= 1000;
    int tres_meio = chave % 1000;
    chave /= 1000;
    int tres_primeiros = chave % 1000;

    int soma = tres_primeiros + tres_meio;

    long long resultado = soma * tres_finais;

    if(verificadores == 0){
        verificadores = 1;
    }

    resultado /= verificadores;

    return resultado % m;
}

// Métodos para Tratamento de Colisão:

int colisao_linear(int indice, int tentativa){
    return (indice + tentativa) % m;
}

int colisao_quadratica(int indice_original, int tentativa){
    int c1 = 1;
    int c2 = 3;

    return (indice_original + c1 * tentativa + c2 * tentativa * tentativa) % m;
}

int colisao_dupla(long long chave, int tentativa){
    int h1 = func_hash(chave);
    int h2 = 1 + (chave % (m - 1));
    return (h1 + tentativa * h2) % m;
}

int main(void){
    FILE *limpa = fopen("grafico.txt", "w");
    fclose(limpa);

    FILE* arq = fopen("CPFsValidos.txt", "r");

    if(!arq){
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    for(int i = 0; i < m; i++){
        tabela[i] = -1;
    }

    long long chave;

    int colisoes = 0;
    int inseridos = 0;

    while(fscanf(arq, "%lld", &chave) != EOF){

        int indice = func_hash(chave);

        int tentativa = 0;

        while(tabela[indice] != -1){

            colisoes++;

            tentativa++;

            indice = colisao_dupla(chave, tentativa);

            if(tentativa == m){
                printf("Tabela cheia!\n");
                break;
            }
        }

        if(tentativa < m){
            tabela[indice] = chave;
            inseridos++;
        }
    }

    gerar_grafico(inseridos, colisoes);
    fclose(arq);

    printf("\n");
    printf("Quantidade de chaves inseridas: %d\n", inseridos);
    printf("Quantidade de colisoes: %d\n", colisoes);

    printf("\nPrimeiras 100 posicoes da tabela:\n\n");

    for(int i = 0; i < 100; i++){

        if(tabela[i] != -1)
            printf("[%4d] -> %lld\n", i, tabela[i]);

        else
            printf("[%4d] -> vazio\n", i);
    }

    return 0;
}