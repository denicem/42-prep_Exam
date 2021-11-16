/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 02:50:19 by dmontema          #+#    #+#             */
/*   Updated: 2021/11/16 03:05:05 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	if (argc == 3)
	{
		unsigned char chars[128];
		int i;

		i = 0;
		while (i < 128)
			chars[i++] = 0;
		i = 0;
		while (argv[1][i])
			chars[(unsigned char)argv[1][i++]] = 1;
		i = 0;
		while (argv[2][i])
		{
			if (chars[(unsigned char)argv[2][i]] == 1)
				write(1, &chars[(unsigned char)argv[2][i++]], 1);
			else
				i++;
		}
	}
	write(1,"\n", 1);
	return 0;
}
