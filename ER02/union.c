/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 22:23:10 by dmontema          #+#    #+#             */
/*   Updated: 2021/10/31 23:18:36 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		int chars[256];
		int i = 0;

		while (i < 256)
			chars[i++] = 0;
		i = 0;
		while (argv[1][i])
		{
			if (chars[(unsigned char)argv[1][i]] == 0)
			{
				chars[(unsigned char)argv[1][i]] = 1;
				write(1, &argv[1][i], 1);
				i++;
			}
			else
				i++;
		}
		i = 0;
		while (argv[2][i])
		{
			if (chars[(unsigned char)argv[2][i]] == 0)
			{
				chars[(unsigned char)argv[2][i]] = 1;
				write(1, &argv[2][i], 1);
				i++;
			}
			else
				i++;
		}

	}
	write(1, "\n", 1);
	return (0);
}