#define MAX 100

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    char info;
    struct no* prox;
} No;

/* PUSH */
No* PUSH(No* topo, char c) {
    No* novo = (No*) malloc(sizeof(No));
    novo->info = c;
    novo->prox = topo;
    return novo;
}

/* POP */
No* POP(No* topo) {
    if (topo == NULL) {
        return NULL;
    }
    No* t = topo;
    topo = topo->prox;
    free(t);
    return topo;
}

void imprime(No* topo) {
    No* p;
    char temp[MAX];
    int i = 0;

    // Copia elementos para vetor auxiliar para inverter a ordem
    for (p = topo; p != NULL; p = p->prox) {
        temp[i++] = p->info;
    }

    printf("[");

    // Impressão da base para o topo
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", temp[j]);
        if (j > 0) printf(", ");
    }

    printf("]\n");
}

int main() {
    FILE* f = fopen("lista.txt", "r");
    if (!f) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    No* topo = NULL;
    char op;

    while (fscanf(f, " %c", &op) != EOF) {

        if (op == 'e') {
            char valor;
            fscanf(f, "%c", &valor);
            topo = PUSH(topo, valor);
        }
        else if (op == 'r') {
            topo = POP(topo);
        }

        imprime(topo);
    }

    fclose(f);
    return 0;
}