/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:08:09 by rwintgen          #+#    #+#             */
/*   Updated: 2023/11/12 12:24:29 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printfptr(unsigned long int n, char *base, int index)
{
	int				cw;
	unsigned int	bn;

	bn = ft_strlen(base);
	if (index == 0)
		write(1, "0x", 2);
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_printfptr(-n, base, index + 1) + 1);
	}
	else if (n < bn)
		return (write(1, &base[n], 1));
	else
	{
		cw = ft_printfptr(n / bn, base, index + 1);
		return (cw + ft_printfptr(n % bn, base, index + 1));
	}
}
