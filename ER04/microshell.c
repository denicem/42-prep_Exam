/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:57:12 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/27 22:37:33 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#ifdef TEST_SH
#define TEST 1
#else
#define TEST 0
#endif

int	print_error(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while (*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
	return (1);
}

int exec(char *argv[], int i, int tmp_fd, char *env[])
{
	argv[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(argv[0], argv, env);
	return (print_error("error: cannot execute ", argv[0]));
}

int main(int argc, char *argv[], char *env[])
{
	int	i;
	int	pid;
	int fd[2];
	int tmp_fd;

	(void) argc;

	pid = 0;
	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	while(argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		// CD
		if (!strcmp(argv[i], "cd"))
		{
			if (i != 2)
				print_error("error: cd: bad arguments", NULL);
			else if (!chdir(argv[1]))
				print_error("erro: cd: cannot change directory to ", argv[1]);
		}
		// EXEC IN STDOUT
		else if (i != 0 && (argv[i] == NULL || !strcmp(argv[i], ";")))
		{
			pid = fork();
			if (pid == 0)
			{
				if (exec(argv, i, tmp_fd, env))
					return (1);
			}
			else
			{
				close(tmp_fd);
				while (waitpid(-1, NULL, WUNTRACED) != -1);
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		// PIPE
		else if (i != 0 && !strcmp(argv[i], "|"))
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				if (exec(argv, i, tmp_fd, env))
					return (1);
			}
			else
			{
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
	if (TEST)
	while (1);
	return (0);
}

