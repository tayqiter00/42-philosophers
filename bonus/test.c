#include "philo_bonus.h"

int	main()
{
	// pid_t	pid;
	sem_t	*sem;
	// int	i = 1;

	// printf("Before forking\n");
	// printf("pid: %d\n", getpid());
	// while (i <= 2)
	// {
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{	
			// if (sem_unlink("/sem") == -1)
			// 	printf("no.1: sem unlink failed\n");
			sem = sem_open("/sem", O_CREAT, 0644, 1);
			if (sem == SEM_FAILED)
				printf("SEM_FAILED\n");
			printf("%p\n", sem);
			sem = sem_open("/sem", O_CREAT, 0644, 1);
			if (sem == SEM_FAILED)
				printf("SEM_FAILED\n");
			printf("%p\n", sem);
	// 		if (sem_unlink("/sem") == -1)
	// 			printf("no.2: sem unlink failed\n");
	// 		if (sem_wait(sem) == -1)
	// 			printf("Sem wait failed\n");
	// 		else
	// 		{
	// 			printf("Sem wait success\n");
	// 			sem_post(sem);
	// 		}
	// 		printf("fork no.%d with pid %d and ppid %d\n\n", i, getpid(), getppid());
	// 	}
	// 	i++;
	// }
	// pid = waitpid(0, NULL, 0);
	// while (pid != -1)
	// 	pid = waitpid(0, NULL, 0);
}
