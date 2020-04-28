#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>
#include "tqueue.h"
#include "bthread.h"


//

typedef struct {
    char str[10];
    int len;
} data_t;

int test_data(data_t data[], long int data_sz);

void test_tqueue_null() {
    fprintf(stdout, "test_tqueue_null ");
    tqueue_get_data(NULL);
    tqueue_pop(NULL);
    tqueue_size(NULL);
    tqueue_enqueue(NULL, NULL);
    tqueue_at_offset(NULL, 0);
    fprintf(stdout, ": PASSED\n");
}

void test_tqueue_many_elements() {
    fprintf(stdout, "test_tqueue_many_elements ");
    data_t data[] = {
            {"ciao", 1},
            {"pippo", 2},
            {"urchi", 3}
    };
    long int data_sz = sizeof(data) / sizeof(data[0]);
    test_data(data, data_sz);
}

void test_tqueue_one_element() {
    fprintf(stdout, "test_tqueue_one_element ");
    data_t data[] = {"ciao", 10};
    long int data_sz = sizeof(data) / sizeof(data[0]);
    test_data(data, data_sz);
}

int test_data(data_t data[], long int data_sz) {
    TQueue q = NULL;
    for (int i = 0; i < data_sz; ++i) {
        tqueue_enqueue(&q, &data[i]);
    }

    unsigned long int queue_sz = tqueue_size(q);
    if (queue_sz != data_sz) {
        fprintf(stderr, "FAILED: wrong queue size. expected %ld actual %ld\n", data_sz, queue_sz);
        return (1);
    }

    for (int j = 0; j <=  data_sz-1; ++j) {
        void *val = tqueue_pop(&q);
        if (((data_t *) val) != &data[j]) {
            fprintf(stderr, "FAILED: wrong return data from pop\n");
            return (1);
        }
    }

    queue_sz = tqueue_size(q);
    if (queue_sz != 0) {
        fprintf(stderr, "FAILED: wrong queue size. expected 0 actual %ld\n", queue_sz);
        return (1);
    }

    fprintf(stdout, ": PASSED\n");
    return 0;
}

void* my_routine(void* param) {
    int p = (int)param;
    fprintf(stdout, "thread %d  START \n", p);

    for (int i = 0; i < 5; ++i) {
        fprintf(stdout, "thread %d  -> %d\n", p, i);
        bthread_yield();
    }

    return (void*)p;
}
void test_bthread_create() {
    fprintf(stdout, "** test_bthread_create **\n");

    bthread_t tid[2];
    for (int i = 0; i < 2; ++i) {
        bthread_create(&tid[i], NULL, my_routine, (void*)i);
        fprintf(stdout, "%i) thread %d created\n", i, tid[i]);
    }

    for (int i = 0; i < 2; ++i) {
        int retval = -1;
        fprintf(stdout, "bthread_join: %d\n", tid[i]);
        bthread_join(tid[i], (void**)&retval);
    }

    fprintf(stdout, ": PASSED\n");
}
int main() {
//    TQueue q = NULL;
//    for (int i = 0; i < size_of_dati; ++i) {
//        printf("ASCII value = %d\n", tqueue_enqueue(&q, &dati[i]));
//    }
//    printf("size = %d\n", tqueue_size(q));
//    dati_nodo *d = tqueue_pop(&q);
//    printf("dati = %s,%s,%s\n", d->str1, d->str2, d->str3);
//    printf("size = %d\n", tqueue_size(q));
//    d = tqueue_pop(&q);
//    printf("dati = %s,%s,%s\n", d->str1, d->str2, d->str3);
//    printf("size = %d\n", tqueue_size(q));
//
//    return 0;

   test_tqueue_null();
   test_tqueue_many_elements();
   test_tqueue_one_element();
   test_bthread_create();
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