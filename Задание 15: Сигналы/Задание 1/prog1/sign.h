#ifndef SIGN_H
#define SIGN_H

#include<stdio.h>
#include<signal.h>
#include <stdlib.h>
#include <unistd.h>

void run();

void hdl(int signum, siginfo_t *info, void *context);

#endif // SIGN_H
