/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:53:31 by rwintgen          #+#    #+#             */
/*   Updated: 2023/11/12 12:27:05 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		cw;
	va_list	ap;

	va_start(ap, str);
	cw = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			cw += ft_format(str[i], ap);
		}
		else
			cw += write(1, &str[i], 1);
		i++;
	}
	va_end(ap);
	return (cw);
}

//===============================================================================

#include <stdio.h>

int	main(void)
{
	char str[] = "test";

	printf("==========CHAR==========\n\n");

	printf("%d\n\n", printf("   printf: %c\n", 'x'));
	printf("%d\n\n", ft_printf("ft_printf: %c\n", 'x'));
	printf("=========STRING=========\n\n");

	printf("%d\n\n", printf("   printf: %s\n", "giga teub"));
	printf("%d\n\n", ft_printf("ft_printf: %s\n", "giga teub"));
	printf("==========INT===========\n\n");

	printf("%d\n\n", printf("   printf: %d\n", -2147483647));
	printf("%d\n\n", ft_printf("ft_printf: %d\n", -2147483647));

	printf("%d\n\n", printf("   printf: %i\n", -2147483647));
	printf("%d\n\n", ft_printf("ft_printf: %i\n", -2147483647));
	printf("======UNSIGNED INT======\n\n");

	printf("%d\n\n", printf("   printf: %u\n", -147483647));
	printf("%d\n\n", ft_printf("ft_printf: %u\n", -147483647));
	printf("==========HEXA==========\n\n");

	printf("%d\n\n", printf("   printf: %x\n", -147483647));
	printf("%d\n\n", ft_printf("ft_printf: %x\n", -147483647));
	printf("========HEXA MAJ========\n\n");
	
	printf("%d\n\n", printf("   printf: %X\n", -1474987647));
	printf("%d\n\n", ft_printf("ft_printf: %X\n", -1474987647));
	printf("=========PERCENT========\n\n");

	printf("%d\n\n", printf("   printf: %%\n"));
	printf("%d\n\n", ft_printf("ft_printf: %%\n"));
	printf("=========POINTER========\n\n");

	printf("%d\n\n", printf("   printf: %p\n", &str));
	printf("%d\n\n", ft_printf("ft_printf: %p\n", &str));
	printf("========================\n\n");

	return (0);
}

/*
int	main(int argc, char **argv)
{
	int	i;

	(void)argc;
	i = 0;
	while (i++ <= argc)
	{
		ft_printf("%s\n", argv[i]);
		printf("%s\n", argv[i]);
	}
	return (0);
}
*/
