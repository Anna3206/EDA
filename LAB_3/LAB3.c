#include <stdio.h>
#include <stdlib.h>

#define N 100

typedef struct nodo{
    int chave;
    int altura;
    struct nodo* esq;
    struct nodo* dir;
} Nodo;

typedef struct fila {
    int n; 
    int ini; 
    Nodo* vet[N]; 
} Fila;

Nodo* cria_arvore(int chave, int altura, Nodo* esq, Nodo* dir);
Fila* cria_fila(void);
void insere_arvore(Nodo* novo, Nodo* topo);
void insere_fila(Fila* f, Nodo* no);
Nodo* remove_fila(Fila* f);
int insere_altura(Nodo* topo);
void exibe_pre_ordem(Nodo* topo);
void exibe_em_ordem(Nodo* topo);
void exibe_por_nivel(Nodo* topo);
void libera_fila(Fila* f);
void libera_arvore(Nodo* topo);

Nodo* cria_arvore(int chave, int altura, Nodo* esq, Nodo* dir){
    Nodo * folha = (Nodo*)malloc(sizeof(Nodo));

    folha->chave = chave;
    folha->altura = altura;
    folha->esq = esq;
    folha->dir = dir;

    return folha;
}

Fila* cria_fila(void){
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->n = 0;
    f->ini = 0;
    return f;
}

void insere_arvore(Nodo* novo, Nodo* topo){
    if(novo->chave < topo->chave){
        if(topo->esq == NULL){
            topo->esq = novo;
        }
        else{
            insere_arvore(novo, topo->esq);
        }
    }
    else{
        if(topo->dir == NULL){
            topo->dir = novo;
        }
        else{
            insere_arvore(novo, topo->dir);
        }
    }
    return;
}

void insere_fila(Fila* f, Nodo* no){
    if(f->n == N){
        printf("Fila cheia\n");
        exit(1);
    }

    int fim = (f->ini + f->n) % N;
    f->vet[fim] = no;
    f->n++;
}

Nodo* remove_fila(Fila* f){
    if(f->n == 0){
        return NULL;
    }

    Nodo* no = f->vet[f->ini];
    f->ini = (f->ini + 1) % N;
    f->n--;

    return no;
}

int insere_altura(Nodo* topo){
    int altura_esquerda = -1;
    int altura_direita = -1;

    if(topo->dir){
        altura_direita = insere_altura(topo->dir);
    }
    if(topo->esq){
        altura_esquerda = insere_altura(topo->esq);
    }
    if(topo->dir == NULL && topo->esq == NULL){
        topo->altura = 0;
    }
    else{
        topo->altura = ((altura_direita > altura_esquerda) ? altura_direita : altura_esquerda) + 1;
    }
    return topo->altura;
}

void exibe_pre_ordem(Nodo* topo){
    if(topo == NULL){
        return;
    }

    printf("%d(%d) ", topo->chave, topo->altura);

    exibe_pre_ordem(topo->esq);
    exibe_pre_ordem(topo->dir);
}

void exibe_em_ordem(Nodo* topo){
    if(topo == NULL){
        return;
    }

    exibe_em_ordem(topo->esq);

    printf("%d(%d) ", topo->chave, topo->altura);

    exibe_em_ordem(topo->dir);
}

void exibe_por_nivel(Nodo* topo){
    if(topo == NULL){
        return;
    }

    Fila* f = cria_fila();
    insere_fila(f, topo);

    while(f->n > 0){
        Nodo* atual = remove_fila(f);

        printf("%d(%d) ", atual->chave, atual->altura);

        if(atual->esq){
            insere_fila(f, atual->esq);
        }

        if(atual->dir){
            insere_fila(f, atual->dir);
        }
    }

    libera_fila(f);
}

void libera_arvore(Nodo* topo){
    if(topo == NULL){
        return;
    }

    libera_arvore(topo->esq);
    libera_arvore(topo->dir);

    free(topo);
}

void libera_fila(Fila* f){
    free(f);
}

int main(){
    FILE* arq = fopen("entrada.txt", "r");

    if (!arq){
        printf("Erro ao tentar abrir o arquivo.\n");
        return 1;
    }

    int chave;
    Nodo* topo = NULL;

    while (fscanf(arq, " %d", &chave) != EOF) {
        if (topo == NULL){
            topo = cria_arvore(chave, 0, NULL, NULL);
        }
        else{
            Nodo* no = cria_arvore(chave, 0, NULL, NULL);
            insere_arvore(no, topo);
        }
    }
    fclose(arq);

    insere_altura(topo);

    printf("Pré-ordem: ");
    exibe_pre_ordem(topo);

    printf("\nOrdem simétrica: ");
    exibe_em_ordem(topo);

    printf("\nPor nível: ");
    exibe_por_nivel(topo);

    printf("\n");

    libera_arvore(topo);

    return 0;
}