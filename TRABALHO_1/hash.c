#include <stdio.h>

#define m 4903

long long tabela[m];

int func_hash(long long chave){

    long long primeiros9 = chave / 100;
    int ultimos2 = chave % 100;

    int soma = 0;
    int pos = 1;

    while(primeiros9 > 0){

        int digito = primeiros9 % 10;

        soma += digito * pos;

        primeiros9 /= 10;

        pos++;
    }

    int indice = soma * ultimos2;

    return indice % m;
}

int colisao_linear(int indice, int tentativa){
    return (indice + tentativa) % m;
}

int colisao_quadratica(int indice_original, int tentativa){
    int c1 = 1;
    int c2 = 3;

    return (indice_original + c1 * tentativa + c2 * tentativa * tentativa) % m;
}

int colisao_dupla(int chave, int tentativa){
    int h1 = func_hash(chave);
    int h2 = 7 - (chave % 7);

    return (h1 + tentativa * h2) % m;
}

int main(void){

    FILE* arq = fopen("cpf.txt", "r");

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