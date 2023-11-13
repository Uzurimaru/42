/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:09:30 by rwintgen          #+#    #+#             */
/*   Updated: 2023/11/13 11:22:48 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char str[] = "test";

	printf("==========CHAR==========\n\n");

	printf("%d\n\n", printf("   printf: %c\n", 'x'));
	printf("%d\n\n", ft_printf("ft_printf: %c\n", 'x'));

	printf("=========STRING=========\n\n");

	printf("%d\n\n", printf("   printf: %s\n", "giga teub"));
	printf("%d\n\n\n", ft_printf("ft_printf: %s\n", "giga teub"));

	printf("%d\n\n", printf("   printf: %s\n", ""));
	printf("%d\n\n\n", ft_printf("ft_printf: %s\n", ""));

	printf("%d\n\n", printf("   printf: %s\n", "\t\0"));
	printf("%d\n\n", ft_printf("ft_printf: %s\n", "\t\0"));

	printf("%d\n\n", printf("   printf: NULL %s NULL\n", (char *)NULL));
	printf("%d\n\n", ft_printf("ft_printf: NULL %s NULL\n", (char *)NULL));


	printf("==========INT===========\n\n");

	printf("%d\n\n", printf("   printf: %d\n", -2147483647));
	printf("%d\n\n\n", ft_printf("ft_printf: %d\n", -2147483647));

	printf("%d\n\n", printf("   printf: %i\n", -1234));
	printf("%d\n\n\n", ft_printf("ft_printf: %i\n", -1234));

	printf("%d\n\n", printf("   printf: %d\n", 654321));
	printf("%d\n\n\n", ft_printf("ft_printf: %d\n", 654321));

	printf("%d\n\n", printf("   printf: %i\n", 2147483647));
	printf("%d\n\n\n", ft_printf("ft_printf: %i\n", 2147483647));

	printf("%d\n\n", printf("   printf: %d\n", 0));
	printf("%d\n\n\n", ft_printf("ft_printf: %d\n", 0));

	printf("%d\n\n", printf("   printf: %i\n", 1234));
	printf("%d\n\n\n", ft_printf("ft_printf: %i\n", 1234));

	printf("======UNSIGNED INT======\n\n");

	printf("%d\n\n", printf("   printf: %u\n", -147483647));
	printf("%d\n\n\n", ft_printf("ft_printf: %u\n", -147483647));

	printf("%d\n\n", printf("   printf: %u\n", 1234567890));
	printf("%d\n\n", ft_printf("ft_printf: %u\n", 1234567890));
	
	printf("==========HEXA==========\n\n");

	printf("%d\n\n", printf("   printf: %x\n", -7654321));
	printf("%d\n\n\n", ft_printf("ft_printf: %x\n", -7654321));

	printf("%d\n\n", printf("   printf: %x\n", 1234567890));
	printf("%d\n\n\n", ft_printf("ft_printf: %x\n", 1234567890));
	
	printf("%d\n\n", printf("   printf: %x\n", 0));
	printf("%d\n\n", ft_printf("ft_printf: %x\n", 0));

	printf("========HEXA MAJ========\n\n");

	printf("%d\n\n", printf("   printf: %X\n", -7654321));
	printf("%d\n\n\n", ft_printf("ft_printf: %X\n", -7654321));

	printf("%d\n\n", printf("   printf: %X\n", 1234567890));
	printf("%d\n\n\n", ft_printf("ft_printf: %X\n", 1234567890));

	printf("%d\n\n", printf("   printf: %X\n", 0));
	printf("%d\n\n", ft_printf("ft_printf: %X\n", 0));

	printf("=========PERCENT========\n\n");

	printf("%d\n\n", printf("   printf: %%\n"));
	printf("%d\n\n", ft_printf("ft_printf: %%\n"));

	printf("=========POINTER========\n\n");

	printf("%d\n\n", printf("   printf: %p\n", &str));
	printf("%d\n\n\n", ft_printf("ft_printf: %p\n", &str));

	printf("%d\n\n", printf("   printf: %p\n", (void *)0));
	printf("%d\n\n\n", ft_printf("ft_printf: %p\n", (void *)0));

	printf("========================\n\n");

	return (0);
}

