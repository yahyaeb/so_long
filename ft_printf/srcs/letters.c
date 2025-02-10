/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:44:20 by yel-bouk          #+#    #+#             */
/*   Updated: 2024/11/25 16:28:50 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_print_pointer(uintptr_t num)
{
	char	*hex_base;
	int		count;

	hex_base = "0123456789abcdef";
	count = 0;
	if (num >= 16)
		count += ft_print_pointer(num / 16);
	write(1, &hex_base[num % 16], 1);
	count++;
	return (count);
}
