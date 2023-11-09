/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:12:17 by rwintgen          #+#    #+#             */
/*   Updated: 2023/11/09 18:25:08 by rwintgen         ###   ########.fr       */
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
		cw = ft_printfnbrptr(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (c == 'd')
		cw = ft_printfnbr(va_arg(ap, int), "0123456789");
	/*else if (c == 'i')
		cw = ft_();*/
	else if (c == 'u')
		cw = ft_printfnbru(va_arg(ap, unsigned int), "0123456789");
	else if (c == 'x')
		cw = ft_printfnbrhex(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		cw = ft_printfnbrhex(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		cw = ft_printfpercent(va_arg(ap, int));
	/*else
		cw = write(1, &c, 1);*/
	return (cw);
}
