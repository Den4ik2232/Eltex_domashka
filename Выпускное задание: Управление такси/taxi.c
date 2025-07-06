#include"taxi.h"

struct driver drivers[32];
int count_drivers = 0;
pthread_t thread_update_status;
int status_thread_created = 0;

void start_cli(){
	while(1){
		char command[64] = {0};
		printf(">>>>>");
		if(fgets(command, 64, stdin) == NULL) break;
		command[strcspn(command, "\n")]	= 0;
		run_command(command);
	}
}

void run_command(char *command){
	int end_command;
	if (strncmp(command, "create_driver", 13) == 0){
		if(count_drivers > 31){
			printf("Превышено число водителей!");
			return;
		}
		int pipe_cli[2], pipe_driver[2];
		if(pipe(pipe_cli) == -1){ // для записи CLI и чтения водителем
			perror("pipe_cli");
			exit(1);
		}
		if(pipe(pipe_driver) == -1){ // для записи водителя и чтением CLI
			perror("pipe_driver");
			exit(1);
		}
		drivers[count_drivers].pipe_cli[0] = pipe_cli[0];
		drivers[count_drivers].pipe_cli[1] = pipe_cli[1];
		drivers[count_drivers].pipe_driver[0] = pipe_driver[0];
		drivers[count_drivers].pipe_driver[1] = pipe_driver[1];
		int pid_driver = fork();
		if(pid_driver == 0){
			close(pipe_cli[1]); // пишет CLI
			close(pipe_driver[0]); // читает CLI
			run_driver(pipe_cli, pipe_driver);
			exit(0);
		}
		if(pid_driver < 0){
			perror("fork");
			exit(1);
		}
		else{
			printf("Создан водитель с pid = %d\n", pid_driver);
			close(pipe_cli[0]); // читает только водитель
			close(pipe_driver[1]); // пишет только водитель
			drivers[count_drivers].pid_driver = pid_driver;
			count_drivers++;
			if (!status_thread_created) {
				if (pthread_create(&thread_update_status, NULL, (void *)update_status, NULL) != 0) {
					perror("pthread_create");
					exit(1);
				}
				status_thread_created = 1;
			}
		}
	}
	else if (strncmp(command, "send_task", 9) == 0){
		int pid_driver = 0, task_time = 0;
		if(sscanf(command, "send_task %d %d", &pid_driver, &task_time) == 2){
			send_task(pid_driver, task_time);
		}
		else printf("Неверно введена команда, попробуй еще раз!\n");
	}
	else if(strncmp(command, "get_status", 10) == 0){
		int pid_driver;
		if(sscanf(command, "get_status %d", &pid_driver) == 1){
			get_status(pid_driver);
		}
		else printf("Неверно введена команда, попробуй еще раз!\n");
	}
	else if(strncmp(command, "get_drivers", 11) == 0){
		printf("Список водителей:");
		get_drivers();
	}
	else if(strncmp(command, "help", 4) == 0){
		printf("COMMANDS:\n---send_task <pid_driver>---\n---create_driver---\n---get_status <pid_driver>---\n---get_drivers---\n");
	}
	else printf("Неизвестная команда напиши help\n");
}

void run_driver(int pipe_cli[2], int pipe_driver[2]) {
	char buffer[64];
	fcntl(pipe_cli[0], F_SETFL, fcntl(pipe_cli[0], F_GETFL, 0) | O_NONBLOCK);//Чтобы вызов read был неблокирующим
	long int task_time = 0;
	long int start_time = 0;
	while (1) {
		int bytes = read(pipe_cli[0], buffer, sizeof(buffer));
		if (bytes > 0) {
			if (strncmp(buffer, "TASK", 4) == 0) {
				sscanf(buffer, "TASK %ld", &task_time);
				start_time = clock();
				pthread_t tid;
				struct TimerArgs *targs = malloc(sizeof(struct TimerArgs));
				targs->start_time = clock();
				targs->task_time = task_time;
				targs->pipe_fd = pipe_driver[1];

				pthread_create(&tid, NULL, timer_driver, targs);
				pthread_detach(tid); 
			}
			else if (strncmp(buffer, "STATUS", 6) == 0) {
				long int time_left = task_time -(clock() - start_time)/CLOCKS_PER_SEC;
				char msg[5];
				sprintf(msg, "%ld", time_left);
				write(pipe_driver[1], msg, strlen(msg) + 1);
			}
		}
	}
}

void *timer_driver(void *args) {
    struct TimerArgs *targs = (struct TimerArgs *)args;

    while (1) {
        if (clock() - targs->start_time >= targs->task_time * CLOCKS_PER_SEC) {
		write(targs->pipe_fd, "Available", 9);
            	break;
        }
        usleep(100000); 
    }

    free(targs);  
    return NULL;
}

void get_drivers(){
	printf("\npid_driver\tstatus\n");
	for(int i = 0; i < count_drivers; i++){
		printf("%d\t", drivers[i].pid_driver);
		if(drivers[i].status == 0) printf("Свободен!\n");
		else printf("Занят!\n");
	}
}

void get_status(pid_t pid_driver){
	for(int i = 0; i < count_drivers; i++){
		if(pid_driver == drivers[i].pid_driver){
			if(drivers[i].status == 0) printf("Водитель свободен!\n>>>>>");
			else {
				write(drivers[i].pipe_cli[1], "STATUS", 6);
				char left[5];
				read(drivers[i].pipe_driver[0], left, 5);
				printf("Водитель занят еще %s секунд\n>>>>>", left);
			}
			return;
		}
	}
	printf("\nВодитель с таким pid не найден!\n>>>>>");
}

void send_task(pid_t pid_driver, int task_time){
	char msg[64];
	snprintf(msg, 64, "TASK %d", task_time);
	for(int i = 0; i < count_drivers; i++){
		if(pid_driver == drivers[i].pid_driver){
			if(drivers[i].status){
				printf("Водитель занят!\n");
				return;
			}
			write(drivers[i].pipe_cli[1], msg, 64);
			drivers[i].status = 1;
			return;
		}
	}
	printf("\nВодитель с таким pid не найден!\n>>>>>");
}

void *update_status(void *args){
	fd_set readfds;
	int max_fd = 0;
	while (1){
		FD_ZERO(&readfds);
		max_fd = 0;
		// добавляем все pipe_driver[i][0] в readfds
		for (int i = 0; i < count_drivers; i++){
			int fd = drivers[i].pipe_driver[0];
			FD_SET(fd, &readfds);
			if (fd > max_fd) max_fd = fd;
		}
		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 100;
		int activity = select(max_fd + 1, &readfds, NULL, NULL, &timeout);
		if (activity < 0){
			perror("select");
			continue;
		}

		for (int i = 0; i < count_drivers; i++){
			int fd = drivers[i].pipe_driver[0];
			if (FD_ISSET(fd, &readfds)){
				char buffer[64] = {0};
				int bytes = read(fd, buffer, sizeof(buffer));
				if (bytes > 0){
					if (strncmp(buffer, "Available", 9) == 0){
						drivers[i].status = 0;
				//		printf("\nВодитель %d стал свободен\n>>>>>", drivers[i].pid_driver);
					}
				}
			}
		}
	}
	return NULL;
}

