/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:52:03 by dmontema          #+#    #+#             */
/*   Updated: 2021/11/17 23:01:36 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

////////////////////////////////////////
////////////** PRINTERS **/////////////

int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int ft_putstr(char *s)
{
	int res;

	if (s == NULL)
		return (write(1, "(null)", 6));
	res = 0;
	while (*s)
	{
		res += ft_putchar(*s);
		s++;
	}
	return (res);
}

int ft_putnbr(int n)
{
	int res;

	res = 0;
	if (n == INT_MIN)
	{
		res += write(1, "-2", 2);
		n = 147483648;
	}
	if (n < 0)
	{
		res += write (1, "-", 1);
		n *= -1;
	}
	if (n > 9)
		res += ft_putnbr(n / 10);
	res += ft_putchar((n % 10) + 48);
	return (res);
}

int ft_putnbr_base(unsigned long n, int base, char *set)
{
	int res;

	res = 0;
	if (n > (unsigned long) base)
		res += ft_putnbr_base(n / base, base, set);
	res += write(1, &set[n%base], 1);
	return (res);
}

////////////////////////////////////////
////////////////////////////////////////

int select_conv_spec(char format, va_list args)
{
	if (format == 0)
		return (0);
	if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned long), 16, "0123456789abcdef"));
	return (ft_putchar(format));
}

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
			res += select_conv_spec(*format, args);
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
	int out = printf("%d\n", INT_MIN);
	int out1 = ft_printf("%d\n", INT_MIN);

	printf("\n%d | %d\n", out, out1);

	return (0);
}