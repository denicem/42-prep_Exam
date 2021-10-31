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

// TODO:	implement own ver
// Olawale's ver 
int main(int argc, char const *argv[])
{
	unsigned char x[256];
	int i = 0;
	if (argc == 3)
	{
		while (i++ < 256)
			x[i-1] = 0;
		i = 0;
		while (argv[1][i++])
		{
			if (x[(unsigned char)(argv[1][i - 1])] == 0)
			{
				x[(unsigned char)(argv[1][i-1])] = 1;
				write(1, &(argv[1][i-1]), 1);
			}
		}
		i = 0;
		while (argv[2][i++])
		{
			if (x[(unsigned char)(argv[2][i - 1])] == 0)
			{
				x[(unsigned char)(argv[2][i-1])] = 1;
				write(1, &(argv[2][i-1]), 1);
			}
		}

	}
	write (1, "\n", 1);
	return 0;
}

// TODO:	also implement String intersection.
// TODO:	divide into different sections and implement a selection mode to select one of the funcs (with the help of argv)
// TODO:	rename this .c-file