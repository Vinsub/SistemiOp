//
// Created by Vincenzo on 29/03/2020.
//

#include <stdlib.h>
#include "tqueue.h"

typedef struct TQueueNode {
    struct TQueueNode* next;
    void* data;
} TQueueNode;


//typedef struct TQueueNode* TQueue;
/* Adds a new element at the end of the list, returns its position */
unsigned long int tqueue_enqueue(TQueue* q, void* data){
    int index = 0;
    TQueueNode* temp = malloc(sizeof(TQueueNode));
    TQueueNode* last;
    if (*q == NULL){
        (*temp).data = data;
        (*temp).next = temp;
        *q = temp;
    }else{
        last = *q;
        while((*last).next != *q){
            last = (*last).next;
            index++;
        }
        (*temp).data = data;
        (*temp).next = *q;
        (*last).next = temp;
        index++;
    }
    return index;
}

/* Removes and returns the element at the beginning of the list, NULL if the
queue is empty */
void* tqueue_pop(TQueue* q){
    if (*q == NULL){
        return NULL;
    }else{
        TQueueNode* temp;
        temp = *q;
        while((*temp).next != *q) {
            temp = (*temp).next;
        }
        (*temp).next = (**q).next;
        temp = *q;
        *q = (**q).next;
        return (*temp).data;
    }
}

/* Returns the number of elements in the list */
unsigned long int tqueue_size(TQueue q){
    int index = 0;
    if ((q) == NULL) {
        return 0;
    }else{
        TQueueNode* temp;
        temp = q;
        while((*temp).next != q){
            temp = (*temp).next;
            index++;
        }
        index++;
    }
    return index;
}

/* Returns a 'view' on the list starting at (a positive) offset distance,
* NULL if the queue is empty */
TQueue tqueue_at_offset(TQueue q, unsigned long int offset){
    if ((q) == NULL) {
        return NULL;
    }
    for (int i = 0; i < offset; ++i) {
        q = (*q).next;
    }
    return q;
}

/* Returns the data on the first node of the given list */
void* tqueue_get_data(TQueue q){
    if ((q) == NULL) {
        return NULL;
    }
    return (*q).data;
}