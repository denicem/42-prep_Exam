/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:52:03 by dmontema          #+#    #+#             */
/*   Updated: 2021/12/16 16:19:16 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

////////////////////////////////////////
////////////** PRINTERS **/////////////

int ft_putchar(unsigned char c)
{
	return (write(1, &c, 1));
}

int ft_putstr(char *str)
{
	int res = 0;

	if (str == 0)
		res += write(1, "(null)", 6);
	else
	{
		while (*str)
		{
			res += ft_putchar(*str);
			str++;
		}

	}
	return (res);
}

int ft_putnbr(int nbr)
{
	int res = 0;

	if (nbr == INT_MIN)
	{
		res += write(1, "-2", 2);
		nbr = 147483648;
	}
	if (nbr < 0)
	{
		res += write (1, "-", 1);
		nbr *= -1;
	}
	if (nbr > 9)
		res += ft_putnbr(nbr / 10);
	res += ft_putchar(48 + (nbr % 10));
	return (res);
}

int ft_putnbr_base(unsigned long long nbr, int base, char *set)
{
	int res;

	res = 0;
	if (nbr >= (unsigned long long) base)
		res += ft_putnbr_base(nbr / base, base, set);
	res += ft_putchar(set[nbr % base]);
	return (res);
}

////////////////////////////////////////
////////////////////////////////////////

int	ft_printf(char *format, ...)
{
	int res;
	va_list args;

	res = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 0)
				break ;
			if (*format == 's')
				res += ft_putstr(va_arg(args, char *));
			else if (*format == 'd')
				res += ft_putnbr(va_arg(args, int));
			else if (*format == 'x')
				res += ft_putnbr_base(va_arg(args, unsigned long long), 16, "0123456789abcdef");
			else if (*format == '%')
				res += ft_putchar(*format);
		}
		else 
			res += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (res);
}

int main()
{
	ft_printf("Hello, %s!\n", "42Heilbronn");
	ft_printf("nbr: %d, neg nbr: %d, hex: %x\n", 42, -42, 42);
	ft_printf("%s\n", NULL);
	ft_printf("---------------\n");
	/* <<<<<<< INT_MIN && INT_MAX >>>>>>> */
	// ft_printf("MY:\tINT_MIN: %d | INT_MAX: %d\n", INT_MIN, INT_MAX);
	// printf("OG:\tINT_MIN: %d | INT_MAX: %d\n", INT_MIN, INT_MAX);
	// ft_printf("\n");
	// ft_printf("MY:\tINT_MIN-1: %d | INT_MAX+1: %d\n", INT_MIN - 1, INT_MAX) + 1;
	// printf("OG:\tINT_MIN-1: %d | INT_MAX+1: %d\n", INT_MIN - 1, INT_MAX) + 1;

	return (0);
}