#ifndef LIFE_H
#define LIFE_H

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


void *thread_customer(void *args);

void *thread_shop_loader(void *args);

void run();

#endif // LIFE_H
