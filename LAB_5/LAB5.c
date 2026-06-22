#include <stdio.h>
#include <stdlib.h>

typedef struct _bitvector BitVector;

struct _bitvector {
    int max;
    int *vector;
};

int tam = sizeof(int) * 8;

BitVector* bvInit(int max) {
    int i;
    int num = ((max - 1) / tam) + 1;

    BitVector* bv = (BitVector*) malloc(sizeof(BitVector));
    bv->max = max;
    bv->vector = (int*) malloc(num * sizeof(int));

    for (i = 0; i < num; i++)
        bv->vector[i] = 0;

    return bv;
}

BitVector* bvCopy(BitVector* s) {
    int i;
    int num = ((s->max - 1) / tam) + 1;

    BitVector* t = bvInit(s->max);

    for (i = 0; i < num; i++)
        t->vector[i] = s->vector[i];

    return t;
}

void bvSet(BitVector* bv, int i) {
    bv->vector[i / tam] |= 1 << (i % tam);
}

void bvShowHex(BitVector* bv, char* title) {
    int i;
    int num = ((bv->max - 1) / tam) + 1;

    printf("%s = ", title);

    for (i = num - 1; i >= 0; i--)
        printf("%08X ", bv->vector[i]);

    printf("\n");
}

/* Remove o i-ésimo elemento do conjunto s */
BitVector* set_remove(BitVector* s, int i) {
    BitVector* t = bvCopy(s);

    t->vector[i / tam] &= ~(1 << (i % tam));

    return t;
}

/* Inclui o i-ésimo elemento no conjunto s */
BitVector* set_inclui(BitVector* s, int i) {
    BitVector* t = bvCopy(s);

    t->vector[i / tam] |= 1 << (i % tam);

    return t;
}

/* t = r - s */
BitVector* set_diferenca(BitVector* r, BitVector* s) {
    int i;
    int num = ((r->max - 1) / tam) + 1;

    BitVector* t = bvInit(r->max);

    for (i = 0; i < num; i++)
        t->vector[i] = r->vector[i] & ~(s->vector[i]);

    return t;
}

/* t = r U s */
BitVector* set_uniao(BitVector* r, BitVector* s) {
    int i;
    int num = ((r->max - 1) / tam) + 1;

    BitVector* t = bvInit(r->max);

    for (i = 0; i < num; i++)
        t->vector[i] = r->vector[i] | s->vector[i];

    return t;
}

int main(void) {
    BitVector *s, *r;
    BitVector *s1, *s2, *s3;
    BitVector *s_inc1, *s_inc2, *s_inc3;
    BitVector *dif, *uni;

    s = bvInit(80);
    r = bvInit(80);

    s->vector[0] = 0xCCDDEEFF;
    s->vector[1] = 0x11FFAABB;
    s->vector[2] = 0x000000FA;

    r->vector[0] = 0x00003377;
    r->vector[1] = 0x00114455;
    r->vector[2] = 0x05EE00F1;

    bvShowHex(s, "s original");
    bvShowHex(r, "r original");

    s1 = set_remove(s, 30);
    s2 = set_remove(s1, 39);
    s3 = set_remove(s2, 73);

    bvShowHex(s3, "s removendo 30, 39 e 73");

    s_inc1 = set_inclui(s3, 30);
    s_inc2 = set_inclui(s_inc1, 39);
    s_inc3 = set_inclui(s_inc2, 73);

    bvShowHex(s_inc3, "s incluindo 30, 39 e 73");

    dif = set_diferenca(s, r);
    bvShowHex(dif, "s - r");

    uni = set_uniao(r, s);
    bvShowHex(uni, "r uniao s");

    return 0;
}