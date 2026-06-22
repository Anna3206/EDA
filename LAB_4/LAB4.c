#include <stdio.h>
#include <stdlib.h>
 
#define MAX 4
#define MIN 2
 
typedef struct no t_no;
struct no {
    int ndesc;
    int chave[MAX];   /* não inclui overflow da chave */
    t_no *ramo[MAX+1];
};

/* Questão 2 */

void intervalo(t_no *arv, int lim_inf, int lim_sup) {
    int i;
    if (arv == NULL)
        return;
    for (i = 0; i < arv->ndesc; i++) {
        intervalo(arv->ramo[i], lim_inf, lim_sup);
        if (arv->chave[i] > lim_inf && arv->chave[i] < lim_sup)
            printf("%d ", arv->chave[i]);
    }
    intervalo(arv->ramo[arv->ndesc], lim_inf, lim_sup);
}

int main() {

    /* Questão 1 */

    /* Raiz */
    t_no *raiz = (t_no *)malloc(sizeof(t_no));
    raiz->ndesc = 1;
    raiz->chave[0] = 100;
    raiz->ramo[2] = NULL; raiz->ramo[3] = NULL; raiz->ramo[4] = NULL;
 
    /* Nós internos */
    t_no *ramo_1 = (t_no *)malloc(sizeof(t_no));
    ramo_1->ndesc = 2;
    ramo_1->chave[0] = 50;
    ramo_1->chave[1] = 75;
    ramo_1->ramo[3] = NULL; ramo_1->ramo[4] = NULL;
    raiz->ramo[0] = ramo_1;
 
    t_no *ramo_2 = (t_no *)malloc(sizeof(t_no));
    ramo_2->ndesc = 2;
    ramo_2->chave[0] = 120;
    ramo_2->chave[1] = 200;
    ramo_2->ramo[3] = NULL; ramo_2->ramo[4] = NULL;
    raiz->ramo[1] = ramo_2;
 
    /* Folhas (ramo_1) */
    t_no *ramo_3 = (t_no *)malloc(sizeof(t_no));
    ramo_3->ndesc = 2;
    ramo_3->chave[0] = 10;
    ramo_3->chave[1] = 40;
    ramo_3->ramo[0] = NULL; ramo_3->ramo[1] = NULL;
    ramo_3->ramo[2] = NULL; ramo_3->ramo[3] = NULL; ramo_3->ramo[4] = NULL;
    ramo_1->ramo[0] = ramo_3;
 
    t_no *ramo_4 = (t_no *)malloc(sizeof(t_no));
    ramo_4->ndesc = 2;
    ramo_4->chave[0] = 60;
    ramo_4->chave[1] = 70;
    ramo_4->ramo[0] = NULL; ramo_4->ramo[1] = NULL;
    ramo_4->ramo[2] = NULL; ramo_4->ramo[3] = NULL; ramo_4->ramo[4] = NULL;
    ramo_1->ramo[1] = ramo_4;
 
    t_no *ramo_5 = (t_no *)malloc(sizeof(t_no));
    ramo_5->ndesc = 2;
    ramo_5->chave[0] = 80;
    ramo_5->chave[1] = 90;
    ramo_5->ramo[0] = NULL; ramo_5->ramo[1] = NULL;
    ramo_5->ramo[2] = NULL; ramo_5->ramo[3] = NULL; ramo_5->ramo[4] = NULL;
    ramo_1->ramo[2] = ramo_5;
 
    /* Folhas (ramo_2) */
    t_no *ramo_6 = (t_no *)malloc(sizeof(t_no));
    ramo_6->ndesc = 2;
    ramo_6->chave[0] = 110;
    ramo_6->chave[1] = 115;
    ramo_6->ramo[0] = NULL; ramo_6->ramo[1] = NULL;
    ramo_6->ramo[2] = NULL; ramo_6->ramo[3] = NULL; ramo_6->ramo[4] = NULL;
    ramo_2->ramo[0] = ramo_6;
 
    t_no *ramo_7 = (t_no *)malloc(sizeof(t_no));
    ramo_7->ndesc = 4;
    ramo_7->chave[0] = 130;
    ramo_7->chave[1] = 135;
    ramo_7->chave[2] = 140;
    ramo_7->chave[3] = 170;
    ramo_7->ramo[0] = NULL; ramo_7->ramo[1] = NULL;
    ramo_7->ramo[2] = NULL; ramo_7->ramo[3] = NULL; ramo_7->ramo[4] = NULL;
    ramo_2->ramo[1] = ramo_7;
 
    t_no *ramo_8 = (t_no *)malloc(sizeof(t_no));
    ramo_8->ndesc = 4;
    ramo_8->chave[0] = 220;
    ramo_8->chave[1] = 230;
    ramo_8->chave[2] = 240;
    ramo_8->chave[3] = 250;
    ramo_8->ramo[0] = NULL; ramo_8->ramo[1] = NULL;
    ramo_8->ramo[2] = NULL; ramo_8->ramo[3] = NULL; ramo_8->ramo[4] = NULL;
    ramo_2->ramo[2] = ramo_8;

    /* Questão 3 */
 
    /* Testes */
    printf("Intervalo (5, 300):  ");
    intervalo(raiz, 5, 300);
    printf("\n");
 
    printf("Intervalo (50, 100): ");
    intervalo(raiz, 50, 100);
    printf("\n");
 
    printf("Intervalo (70, 135): ");
    intervalo(raiz, 70, 135);
    printf("\n");
 
    return 0;
}