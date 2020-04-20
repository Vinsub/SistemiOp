#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>
#include "tqueue.h"


typedef struct {
    char str1[10];
    char str2[10];
    char str3[10];
} dati_nodo;
dati_nodo dati[] = {
        {"asdfasd", "asfsadfa", "asfsadfa"},
        {"qewqweq", "qwerqwer", "qwerqwer"},
        {"dgfdgfg", "dgfdgfg", "dgfdgfg"}
};
int size_of_dati = sizeof(dati) / sizeof(dati[0]);

int test_tqueue_pop() {
    TQueue q = NULL;

    printf(tqueue_pop(&q));
    return 0;
}
int main() {
    TQueue q = NULL;
    for (int i = 0; i < size_of_dati; ++i) {
        printf("ASCII value = %d\n", tqueue_enqueue(&q, &dati[i]));
    }
    printf("size = %d\n", tqueue_size(q));
    dati_nodo *d = tqueue_pop(&q);
    printf("dati = %s,%s,%s\n", d->str1, d->str2, d->str3);
    printf("size = %d\n", tqueue_size(q));
    d = tqueue_pop(&q);
    printf("dati = %s,%s,%s\n", d->str1, d->str2, d->str3);
    printf("size = %d\n", tqueue_size(q));

    return 0;
}
/*
int main() {
    TQueue* tQueue = (TQueue*) malloc(sizeof(TQueue*));
    char test1 = 'a';
    char test2 = 'b';
    char test3 = 'b';
    tqueue_enqueue(tQueue ,&test1);
    tqueue_enqueue(tQueue ,&test2);
    int i = tqueue_enqueue(tQueue ,&test3);
    return i;
}

*/