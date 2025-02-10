/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:44:24 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/10 12:57:24 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putnbr(int n)
{
	int		count;
	char	c;

	count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		n = -n;
		count += write(1, "-", 1);
	}
	if (n < 10)
	{
		c = n + '0';
		count += write(1, &c, 1);
	}
	else
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	return (count);
}

int	ft_putnbr_hex_lower(unsigned int num)
{
	char	*hex_base;
	int		count;

	hex_base = "0123456789abcdef";
	count = 0;
	if (num >= 16)
		count += ft_putnbr_hex_lower(num / 16);
	write(1, &hex_base[num % 16], 1);
	count++;
	return (count);
}

int	ft_putnbr_hex_upper(unsigned int num)
{
	char	*hex_base;
	int		count;

	hex_base = "0123456789ABCDEF";
	count = 0;
	if (num >= 16)
		count += ft_putnbr_hex_upper(num / 16);
	write(1, &hex_base[num % 16], 1);
	count++;
	return (count);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	char	i;
	int		count;

	count = 0;
	if (n <= 9)
	{
		i = n + '0';
		write(1, &i, 1);
		count++;
	}
	else
	{
		count += ft_putnbr_unsigned(n / 10);
		count += ft_putnbr_unsigned(n % 10);
	}
	return (count);
}
