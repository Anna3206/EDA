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

int h1(long long chave) {
    int verif = chave % 100; chave /= 100;
    int b3 = chave % 1000; chave /= 1000; 
    int b2 = chave % 1000; chave /= 1000; 
    int b1 = chave % 1000;               

    if (verif == 0) verif = 1;

    unsigned long long h = (unsigned long long)((b1 ^ b2) * b3) ^ verif;
    return (int)(h % m);
}

int h2(long long chave) {
    unsigned long long h = 0;
    int shift = 0;
    while (chave > 0) {
        int digito = chave % 10;
        h ^= (digito << shift);
        shift = (shift + 3) % 16;
        chave /= 10;
    }
    return (int)(h % (m - 1)) + 1;
}

int colisao_dupla(long long chave, int tentativa){
    return (h1(chave) + tentativa * h2(chave)) % m;
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

        int indice = h1(chave);

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

        if (tentativa < m) {
            tabela[indice] = chave;
            inseridos++;

            if (inseridos % 100 == 0 || inseridos == 4096)
                gerar_grafico(inseridos, colisoes);
        }
    }
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