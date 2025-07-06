#ifndef TAXI_H
#define TAXI_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/select.h>
#include<signal.h>
#include<time.h>
#include<fcntl.h>
#include<pthread.h>

struct driver{
	pid_t pid_driver;
	int pipe_cli[2];
	int pipe_driver[2];
	int status; // 0 - свободен, 1 - занят
};

struct TimerArgs {
    long int start_time;
    long int task_time;
    long int pipe_fd;
};

void start_cli();

void run_command(char *command);

void run_driver(int pipe_cli[2], int pipe_driver[2]);

void get_status(pid_t pid_driver);

void get_drivers();

void send_task(pid_t pid_driver, int task_time);

void *update_status(void *args);

void *timer_driver(void *args);

#endif // CLI_H

