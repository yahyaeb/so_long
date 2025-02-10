/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:46:19 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/02/10 12:06:01 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	handle_strings(char *str)
{
	if (!str)
		str = "(null)";
	ft_putstr(str);
	return (ft_strlen_printf(str));
}

int	handle_char(char c)
{
	ft_putchar(c);
	return (1);
}

int	handle_pointers(void *ptr)
{
	if (!ptr)
	{
		write(1, "0x0", 3);
		return (3);
	}
	write(1, "0x", 2);
	return (2 + ft_print_pointer((uintptr_t)ptr));
}
