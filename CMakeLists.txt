cmake_minimum_required(VERSION 3.10)
project(SistemiOp C)

set(CMAKE_C_STANDARD 99)

add_executable(SistemiOp main.c tqueue.h bthread.h tqueue.c bthread_private.h bthread.c)