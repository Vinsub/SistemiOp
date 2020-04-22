//
// Created by Vincenzo on 29/03/2020.
//

#include <setjmp.h>
#include "bthread.h"
#include "tqueue.h"

#ifndef SISTEMIOP_BTHREAD_PRIVATE_H
#define SISTEMIOP_BTHREAD_PRIVATE_H


typedef enum { __BTHREAD_READY = 0, __BTHREAD_BLOCKED, __BTHREAD_SLEEPING, __BTHREAD_ZOMBIE
} bthread_state;

typedef struct {
    bthread_t tid;
    bthread_routine body;
    void* arg;
    bthread_state state;
    bthread_attr_t attr;
    char* stack;
    jmp_buf context;
    void* retval;
    double wake_up_time;
} __bthread_private;

typedef struct {
    TQueue queue;
    TQueue current_item;
    jmp_buf context;
    bthread_t current_tid;
} __bthread_scheduler_private;

//Private
__bthread_scheduler_private* bthread_get_scheduler();
static int bthread_check_if_zombie(bthread_t bthread, void **retval);
static TQueue bthread_get_queue_at(bthread_t bthread);
void bthread_cleanup(); // Private

#endif //SISTEMIOP_BTHREAD_PRIVATE_H