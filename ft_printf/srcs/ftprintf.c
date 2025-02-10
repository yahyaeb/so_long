/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:43:03 by yel-bouk          #+#    #+#             */
/*   Updated: 2024/12/17 21:30:53 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_format_specifier(va_list *args, char format)
{
	int	count;

	count = 0;
	if (format == 'u')
		return (count += ft_putnbr_unsigned(va_arg(*args, unsigned int)));
	else if (format == 'd' || format == 'i')
		return (count += ft_putnbr(va_arg(*args, int)));
	else if (format == 's')
		return (count += handle_strings(va_arg(*args, char *)));
	else if (format == 'c')
		return (count += handle_char((char)(va_arg(*args, int))));
	else if (format == 'p')
		return (count += handle_pointers(va_arg(*args, void *)));
	else if (format == 'x')
		return (count += ft_putnbr_hex_lower(va_arg(*args, unsigned int)));
	else if (format == 'X')
		return (count += ft_putnbr_hex_upper(va_arg(*args, unsigned int)));
	else if (format == '%')
		return (count += write(1, "%", 1));
	else
		count = write(1, &format, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	const char	*ptr;
	int			count;

	count = 0;
	va_start(args, format);
	ptr = format;
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			if (*ptr)
			{
				count += ft_format_specifier(&args, *ptr);
				ptr++;
			}
		}
		else
			count += write(1, ptr++, 1);
	}
	va_end(args);
	return (count);
}
