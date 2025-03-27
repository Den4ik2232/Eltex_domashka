#ifndef THREADS_H
#define THREADS_H

#include<stdio.h>
#include<pthread.h>

#define N 1

void run();

void *summator(void *args);

#endif //THREADS_H
