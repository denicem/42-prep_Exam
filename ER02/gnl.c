/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:57:47 by dmontema          #+#    #+#             */
/*   Updated: 2022/01/27 16:09:10 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 21
#endif

int ft_strlen(char *str)
{
	int res = 0;

	while (*str++)
		res++;
	return (res);
}

char *ft_strchr_nl(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}

char *str_calloc(int size)
{
	char *res;
	int i = 0;

	res = malloc(size * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < size)
		res[i++] = 0;
	return (res);
}

char *strjoin_gnl(char **str1, char *str2, int len)
{
	char *res;
	int i = 0, j = 0;
	
	res = str_calloc(ft_strlen(*str1) + len + 1);
	if (res == NULL)
		return (NULL);
	while ((*str1)[i])
	{
		res[i] = (*str1)[i];
		i++;
	}
	while (str2[j])
	{
		res[i + j] = str2[j];
		j++;
	}
	res[i + j] = 0;
	free(*str1);
	return (res);
}

char *ft_strdup(char *str)
{
	char *res;
	int i = 0;

	res = str_calloc(ft_strlen(str) + 1);
	if (res == NULL)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char *getRes(char **storage, char **res)
{
	char *newl;

	free(*storage);
	*storage = 0;
	newl = ft_strchr_nl(*res);
	if (newl && *(newl + 1))
	{
		char *tmp;

		*storage = ft_strdup(newl + 1);
		*(newl + 1) = 0;

		tmp = *res;
		*res = ft_strdup(*res);
		free(tmp);
	}
	if (**res == 0)
	{
		free(*res);
		return (NULL);
	}
	return (*res);
}

char *readLine(char **storage, char **res, int fd)
{
	if (!ft_strchr_nl(*res))
	{
		int bytes = 1;

		while (bytes && !ft_strchr_nl(*storage))
		{
			bytes = read(fd, *storage, BUFFER_SIZE);
			if (bytes < 0)
			{
				free(*storage);
				free(res);
				return (NULL);
			}
			(*storage)[bytes] = 0;
			*res = strjoin_gnl(res, *storage, bytes);
		}
	}
	return (getRes(storage, res));
}

int prepareVars(char **storage, char **res)
{
	if (*storage)
	{
		*res = ft_strdup(*storage);
		free(*storage);
		*storage = 0;
	}
	else
		*res = str_calloc(1);
	*storage = str_calloc(BUFFER_SIZE);
	if (*res == NULL || *storage == NULL)
		return (0);
	return (1);
}

char *get_next_line(int fd)
{
	static char *storage;
	char *res;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!prepareVars(&storage, &res))
		return (NULL);
	res = readLine(&storage, &res, fd);
	return (res);
}

int main (void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	system("leaks a.out");
	return (0);
}