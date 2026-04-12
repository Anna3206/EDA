/*LABORATÓRIO 1*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSortDecrescente(int arr[], int n) {
    int i, j, idx_max, temp;

    for (i = 0; i < n - 1; i++) {
        idx_max = i;

        /*Encontra o maior valor no subvetor restante*/
        for (j = i + 1; j < n; j++) {
            if (arr[j] > arr[idx_max]) {
                idx_max = j;
            }
        }

        /*Troca de posição*/
        temp = arr[idx_max];
        arr[idx_max] = arr[i];
        arr[i] = temp;

        printf("Iteracao %d: ", i+1);
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");
    }
}

int main() {
    int vetor[10];
    int i;

    srand(time(NULL));

    /*Randomiza os valores do vetor*/
    printf("Vetor original: ");
    for(i = 0; i < 10; i++) {
        vetor[i] = rand() % 101;
        printf("%d ", vetor[i]);
    }
    printf("\n");

    selectionSortDecrescente(vetor, 10);

    return 0;
}