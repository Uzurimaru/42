/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_print_stacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:54:40 by rwintgen          #+#    #+#             */
/*   Updated: 2024/01/27 19:06:25 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_print_stacks(t_node *stack_a, t_node *stack_b)
{
	int	index;
	int	max;
	int	len_a;
	int	len_b;

	len_a = ft_stack_len(stack_a);
	len_b = ft_stack_len(stack_b);
	printf("============\n");
	max = len_a;
	if (len_a < len_b)
		max = len_b;
	index = 0;
	while (index < max)
	{
		if (stack_a)
		{
			printf("%d", stack_a->nb);
			stack_a = stack_a->next;
		}
		else
			printf("_");
		printf("\t");
		if (stack_b)
		{
			printf("%d", stack_b->nb);
			stack_b = stack_b->next;
		}
		else
			printf("_");
		printf("\n");
		index++;
	}
	printf("_\t_\na\tb\n============\n\n");
}
