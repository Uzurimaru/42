/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:12:17 by rwintgen          #+#    #+#             */
/*   Updated: 2023/11/12 12:24:43 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(char c, va_list ap)
{
	int	cw;

	cw = 0;
	if (c == 'c')
		cw = ft_printfchar(va_arg(ap, int));
	else if (c == 's')
		cw = ft_printfstr(va_arg(ap, char *));
	else if (c == 'p')
	{
		cw = 2;
		cw += ft_printfptr(va_arg(ap, long unsigned int), "0123456789abcdef", 0);
	}
	else if (c == 'd' || c == 'i')
		cw = ft_printfnbr(va_arg(ap, int), "0123456789");
	else if (c == 'u')
		cw = ft_printfnbru(va_arg(ap, unsigned int), "0123456789");
	else if (c == 'x')
		cw = ft_printfnbrhex(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		cw = ft_printfnbrhex(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		cw = ft_printfpercent(va_arg(ap, int));
	else
		cw = -1;
	return (cw);
}
