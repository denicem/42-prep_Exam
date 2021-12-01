/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:57:50 by dmontema          #+#    #+#             */
/*   Updated: 2021/12/01 23:15:24 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 26
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

char *ft_str_calloc(int size)
{
	char *res;
	int i;

	res = malloc(size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
		res[i++] = 0;
	return (res);
}

char *ft_strjoin_gnl(char **str1, char *str2, int size)
{
	char *res;
	int i, j;

	res = ft_str_calloc(ft_strlen(*str1) + size + 1);
	if (!res)
		return (NULL);
	i = 0;
	while ((*str1)[i])
	{
		res[i] = (*str1)[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		res[i + j] = str2[j];
		j++;
	}
	res[i + j] = 0;
	free(*str1);
	return (res);
}

char *ft_strdup (char *str)
{
	char *res;
	int i = 0;

	res = ft_str_calloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

//////////////////////////////////////////////////

char *getRes(char **storage, char **res)
{
	char *newl;
	newl = ft_strchr_nl(*res);
	if (newl && *(newl + 1))
	{
		*storage = ft_strdup(newl + 1);
		*(newl + 1) = 0;
	}
	else
	{
		free(*storage);
		*storage = 0;
	}
	if (!(*res))
	{
		free(*res);
		return (NULL);
	}
	return (*res);
}

char *readLine(int fd, char **storage, char **res)
{
	int bytesRead;

	if (!ft_strchr_nl(*res))
	{
		bytesRead = 1;
		while (bytesRead && !ft_strchr_nl(*storage))
		{
			bytesRead = read(fd, *storage, BUFFER_SIZE);
			if (bytesRead < 0)
			{
				free(*res);
				free(*storage);
				return (NULL);
			}
			(*storage)[bytesRead] = 0;
			*res = ft_strjoin_gnl(res, *storage, bytesRead);
		}
	}
	return getRes(storage, res);
}

int prepareVars(char **storage, char **res)
{
	if (*storage)
	{
		*res = ft_strdup(*storage);
		free(*storage);
		*storage = NULL;
	}
	else
		*res = ft_str_calloc(1);
	*storage = ft_str_calloc(BUFFER_SIZE);
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
	res = readLine(fd, &storage, &res);
	return (res);
}

int main (void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
		printf("%s", line);
	return (0);
}